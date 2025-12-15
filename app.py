"""Dash app for visualizing circuit simulation results.

Layout:
- Left column (2/3): Graph 1 (OutputVoltage vs Time) on top, Graph 2 (InputVoltage vs Time) below.
- Right column (1/3): Top: Parameters panel. Middle/Bottom: DataTable showing first 10 rows of CSV.

The app uses a simulated CSV `simulation_output.csv` placed in the same folder. The "Lancer Simulation" button regenerates the CSV preview locally using the parameters and updates the plots.

Run with: python app.py
"""

import os
import math
import io
from datetime import datetime

import pandas as pd
import numpy as np
from dash import Dash, html, dcc, Input, Output, State, dash_table
import plotly.graph_objs as go

# -------------------- Helpers --------------------

import subprocess

CSV_PATH = os.path.join(os.path.dirname(__file__), 'resultats/simulations/circuit_output.csv')

def generate_simulation_csv(path, R=1e3, C=1e-6, L=0.0, h=1e-4, t_max=0.05,
                            method='Euler', source_type='Sinusoidal', amplitude=5.0, frequency=50.0,
                            circuit_type='A', R2=1e3, duty=0.5, offset=0.0):
    """
    Call the C++ binary 'be-sim' to generate the CSV.
    Input sequence expected by C++ main.cpp:
    1. 'n' (useDefaults = false)
    2. Circuit Choice: A/B/C/D
    3. npas (int)
    4. tmax (double)
    5. Source Choice: 1(Sin)/2(Step)/3(Tri)/4(Creneau)/5(Rect)
    6. Source Params...
    7. Method: 1/2/3/4
    8. Circuit Params...
    """
    warnings = []

    # 1. Prepare inputs
    try:
        # Avoid division by zero
        if h <= 0: h = 1e-4
        npas = int(float(t_max) / float(h))
        
        # Binary location
        binary_path = os.path.join(os.path.dirname(__file__), 'be-sim')
        if not os.path.exists(binary_path):
             # Try to compile if missing? Or just warn.
             return pd.DataFrame({'temps':[],'Vin':[],'Vout':[]}), ["Binary 'be-sim' not found"], h

        # Build input string
        input_str = "n\n"  # No defaults
        input_str += f"{circuit_type}\n" # A, B, C, D
        
        # Simulation params: npas, tmax
        input_str += f"{npas}\n"
        input_str += f"{t_max}\n"
        
        # Source params
        # Map source_type string to ID
        st_map = {'Sinusoidal': 1, 'Step': 2, 'Triangle': 3, 'Square': 4, 'Rect': 5}
        s_id = st_map.get(source_type, 1)
        input_str += f"{s_id}\n"
        
        if s_id == 1: # Sinus
            input_str += f"{amplitude}\n{frequency}\n{offset}\n"
        elif s_id == 2: # Step
            # Existing UI only has 'amplitude'. We can use 'offset' if needed. 
            # startTime assumed 0 or add input? Python sim assumed t>=0. C++ Echelon wants amp, t0.
            input_str += f"{amplitude}\n0\n" # t0=0
        elif s_id == 3: # Triangle
             input_str += f"{amplitude}\n{frequency}\n{offset}\n"
        elif s_id == 4: # Creneau
             input_str += f"{amplitude}\n{frequency}\n{duty}\n{offset}\n"
        elif s_id == 5: # Rect
             input_str += f"{amplitude}\n{frequency}\n{duty}\n{offset}\n"
             
        # Method
        # Map method string to ID
        m_map = {'Euler': 1, 'Euler2': 2, 'RK4': 3, 'Heun': 4}
        m_id = m_map.get(method, 1) # Default Euler
        input_str += f"{m_id}\n"
        
        # Circuit Params
        # Logic from main.cpp:
        # if B: ask R1, R2, C
        # else: ask R, C. If C/D ask L.
        if circuit_type == 'B':
            input_str += f"{R}\n"   # R1 maps to UI 'R'
            input_str += f"{R2}\n"  # R2
            input_str += f"{C}\n"
        else:
            input_str += f"{R}\n"
            input_str += f"{C}\n"
            if circuit_type in ['C', 'D']:
                input_str += f"{L}\n"

        # Run subprocess
        process = subprocess.Popen(
            [binary_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate(input=input_str)
        
        if process.returncode != 0:
            warnings.append(f"Erreur binaire C++ (code {process.returncode})")
            print(stderr)

    except Exception as e:
        warnings.append(str(e))
        return pd.DataFrame(), warnings, h

    # Read the generated CSV
    # Verify path exists
    # Note: C++ output path is fixed to "resultats/simulations/circuit_output.csv"
    # The 'path' arg passed to this func is mostly for where we *expect* it.
    actual_csv_path = os.path.join(os.path.dirname(__file__), 'resultats/simulations/circuit_output.csv')
    
    if os.path.exists(actual_csv_path):
        try:
            df = pd.read_csv(actual_csv_path)
            # rename columns to match Dash expectation if needed
            # C++: temps,Vin,Vout
            # Dash: Time,InputVoltage,OutputVoltage
            df = df.rename(columns={'temps': 'Time', 'Vin': 'InputVoltage', 'Vout': 'OutputVoltage'})
            return df, warnings, h
        except Exception as e:
            warnings.append(f"Impossible de lire le CSV généré: {e}")
            return pd.DataFrame(), warnings, h
    else:
        warnings.append("Fichier CSV non trouvé après exécution.")
        return pd.DataFrame(), warnings, h


# -------------------- Ensure CSV exists --------------------
# (skipped, will be generated on fly)

# -------------------- Dash App --------------------
external_stylesheets = ['https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;800&display=swap']
app = Dash(__name__, external_stylesheets=external_stylesheets)
app.title = 'Dashboard Simulation Circuit'


def load_csv_preview(path, nrows=10):
    if os.path.exists(path):
        df = pd.read_csv(path)
        df = df.rename(columns={'temps': 'Time', 'Vin': 'InputVoltage', 'Vout': 'OutputVoltage'})
        return df, df.head(nrows)
    return pd.DataFrame(), pd.DataFrame()


# Read CSV for initial display
df_full, df_preview = load_csv_preview(CSV_PATH, nrows=10)


# ---------- Layout ----------
app.layout = html.Div([
    html.Div(className='container', children=[
        # Left Column (2/3)
        html.Div(className='left-column card', children=[
            html.Div(className='card-header', children=html.H3('Réponse du Circuit (v_s(t) vs Temps)')),
            dcc.Graph(id='graph-output', config={'displayModeBar': False}),
            html.Div(className='card-header', children=html.H3('Source d\'Excitation (v_e(t) vs Temps)')),
            dcc.Graph(id='graph-input', config={'displayModeBar': False}),
        ]),

        # Right Column (1/3)
        html.Div(className='right-column', children=[
            # Parameters panel
            html.Div(className='card params-card', children=[
                html.Div(className='card-header', children=html.H3('Paramètres de la Simulation')),
                html.Div(className='params-section', children=[
                    html.H4('⚙️ Paramètres du Circuit'),
                    html.Div(className='param-row', children=[html.Label('Type Circuit'), dcc.Dropdown(id='circuit_type', options=[{'label':'A - RC (Passe-bas)', 'value':'A'}, {'label':'B - RC + Diode', 'value':'B'}, {'label':'C - RLC Série', 'value':'C'}, {'label':'D - RLC Parallèle', 'value':'D'}], value='A', clearable=False, searchable=False, className='themed-dropdown')]),
                    html.Div(className='param-row', children=[html.Label('Résistance R/R1 (Ω)'), dcc.Input(id='R', type='number', value=1000, min=0, step=1)]),
                    html.Div(className='param-row', children=[html.Label('Résistance R2 (pour B)'), dcc.Input(id='R2', type='number', value=1000, min=0, step=1)]),
                    html.Div(className='param-row', children=[html.Label('Capacité C (F)'), dcc.Input(id='C', type='number', value=1e-6, min=1e-12, step=1e-7)]),
                    html.Div(className='param-row', children=[html.Label('Inductance L (H)'), dcc.Input(id='L', type='number', value=1e-3, min=0, step=1e-6)]),
                ]),

                html.Hr(),
                html.Div(className='params-section', children=[
                    html.H4('⏰ Paramètres de Simulation'),
                    html.Div(className='param-row', children=[html.Label('Pas de temps h (s)'), dcc.Input(id='h', type='number', value=1e-4, min=1e-7, step=1e-5)]),
                    html.Div(className='param-row', children=[html.Label('Temps max t_max (s)'), dcc.Input(id='tmax', type='number', value=0.05, min=0.001, step=0.001)]),
                    html.Div(className='param-row', children=[html.Label('Méthode'), dcc.Dropdown(id='method', options=[{'label':'Euler (Ordre 1)','value':'Euler'},{'label':'Euler (Syst. 2)','value':'Euler2'},{'label':'Runge-Kutta 4','value':'RK4'}, {'label':'Heun','value':'Heun'}], value='RK4', clearable=False, searchable=False, className='themed-dropdown')]),
                ]),

                html.Hr(),
                html.Div(className='params-section', children=[
                    html.H4('⚡ Paramètres de la Source'),
                    html.Div(className='param-row', children=[html.Label('Type de Source'), dcc.Dropdown(id='source_type', options=[{'label':'Sinusoidal','value':'Sinusoidal'},{'label':'Step','value':'Step'},{'label':'Triangle','value':'Triangle'}, {'label':'Square (Creneau)','value':'Square'}], value='Sinusoidal', clearable=False, searchable=False, className='themed-dropdown')]),
                    html.Div(className='param-row', children=[html.Label('Amplitude (V)'), dcc.Input(id='amplitude', type='number', value=5.0, step=0.1)]),
                    html.Div(className='param-row', children=[html.Label('Fréquence (Hz)'), dcc.Input(id='frequency', type='number', value=50.0, step=1.0)]),
                    html.Div(className='param-row', children=[html.Label('Duty Cycle (0-1)'), dcc.Input(id='duty', type='number', value=0.5, step=0.1, min=0, max=1)]),
                    html.Div(className='param-row', children=[html.Label('Offset (V)'), dcc.Input(id='offset', type='number', value=0.0, step=0.1)]),

                ]),

                html.Div(className='button-row', children=[
                    html.Button('Lancer Simulation', id='run-sim', n_clicks=0, className='run-button')
                ]),

                html.Div(id='sim-info', className='sim-info')
            ]),

            # Data table card
            html.Div(className='card table-card', children=[
                html.Div(className='card-header', children=html.H3('Données Brutes (Extrait CSV)')),
                dash_table.DataTable(
                    id='csv-preview',
                    columns=[{"name": c, "id": c} for c in df_preview.columns],
                    data=df_preview.to_dict('records'),
                    style_table={'overflowX': 'auto'},
                    style_cell={'textAlign': 'left', 'padding': '8px'},
                    page_size=10,
                    style_header={'fontWeight': 'bold'},
                )
            ]),

        ])
    ])
], className='app-root')


# ---------- Callbacks ----------

@app.callback(
    Output('graph-output', 'figure'),
    Output('graph-input', 'figure'),
    Output('csv-preview', 'data'),
    Output('csv-preview', 'columns'),
    Output('sim-info', 'children'),
    Output('h', 'value'),
    Input('run-sim', 'n_clicks'),
    State('R', 'value'),
    State('C', 'value'),
    State('L', 'value'),
    State('h', 'value'),
    State('tmax', 'value'),
    State('method', 'value'),
    State('amplitude', 'value'),
    State('frequency', 'value'),
    State('source_type', 'value'),
    State('circuit_type', 'value'),
    State('R2', 'value'),
    State('duty', 'value'),
    State('offset', 'value'),
)
def update_all(n_clicks, R, C, L, h, tmax, method, amplitude, frequency, source_type, c_type, R2, duty, offset):
    # Apply some basic validation and defaults
    R = float(R) if R is not None else 1000.0
    C = float(C) if C is not None else 1e-6
    L = float(L) if L is not None else 0.0
    h = float(h) if h is not None and h > 0 else 0.0001
    tmax = float(tmax) if tmax is not None and tmax > 0 else 0.05
    method = method if method in ('Euler', 'Euler2', 'Heun', 'RK4') else 'RK4'
    amplitude = float(amplitude) if amplitude is not None else 5.0
    frequency = float(frequency) if frequency is not None else 50.0
    source_type = source_type if source_type is not None else 'Sinusoidal'
    c_type = c_type if c_type is not None else 'A'
    R2 = float(R2) if R2 is not None else 1000.0
    duty = float(duty) if duty is not None else 0.5
    offset = float(offset) if offset is not None else 0.0

    # Generate a new CSV preview (simulate running the C++ sim)
    df, warnings_list, h_used = generate_simulation_csv(CSV_PATH, R=R, C=C, L=L, h=h, t_max=tmax, method=method,
                                                        source_type=source_type, amplitude=amplitude, frequency=frequency,
                                                        circuit_type=c_type, R2=R2, duty=duty, offset=offset)

    # Build figures with dark theme styling
    fig_out = go.Figure()
    fig_out.add_trace(go.Scatter(x=df['Time'], y=df['OutputVoltage'], mode='lines+markers', name='v_s(t)', line={'width':3}, marker={'size':4}))
    fig_out.update_layout(template='plotly_dark', paper_bgcolor='rgba(0,0,0,0)', plot_bgcolor='rgba(10,10,10,0.6)', margin={'t':30,'b':20,'l':40,'r':20})
    fig_out.update_xaxes(title='Temps (s)', showgrid=True, gridcolor='rgba(255,255,255,0.05)')
    fig_out.update_yaxes(title='v_s(t) (V)', showgrid=True, gridcolor='rgba(255,255,255,0.05)')

    fig_in = go.Figure()
    fig_in.add_trace(go.Scatter(x=df['Time'], y=df['InputVoltage'], mode='lines', name='v_e(t)', line={'width':2, 'dash':'dash'}, marker={'size':3}))
    fig_in.update_layout(template='plotly_dark', paper_bgcolor='rgba(0,0,0,0)', plot_bgcolor='rgba(10,10,10,0.6)', margin={'t':30,'b':20,'l':40,'r':20})
    fig_in.update_xaxes(title='Temps (s)', showgrid=True, gridcolor='rgba(255,255,255,0.05)')
    fig_in.update_yaxes(title='v_e(t) (V)', showgrid=True, gridcolor='rgba(255,255,255,0.05)')

    preview = df.head(10)
    columns=[{"name": c, "id": c} for c in preview.columns]

    sim_info = f"Dernière simulation: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')} — méthode={method}, h={h}, tmax={tmax}, source={source_type}"
    if warnings_list:
        sim_info += ' — Warnings: ' + '; '.join(warnings_list)

    # return figures, table data, sim_info and the h actually used (to update the input value)
    return fig_out, fig_in, preview.to_dict('records'), columns, sim_info, h_used


# ---------- Run ----------
if __name__ == '__main__':
    # Dash 3+ uses app.run instead of app.run_server
    # Keep debug=True for development; port can be adjusted if needed
    try:
        app.run(debug=True)
    except TypeError:
        # Fallback for older Dash versions that expect run_server
        app.run_server(debug=True)
```
