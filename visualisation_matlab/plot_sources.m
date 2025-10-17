% Script MATLAB pour visualiser les sources de tension
% Assurez-vous d'avoir exécuté ./be-sim avant !

% Chercher le fichier CSV
if exist('../sources.csv', 'file')
    csv_file = '../sources.csv';
elseif exist('sources.csv', 'file')
    csv_file = 'sources.csv';
else
    error('❌ Fichier sources.csv introuvable. Exécutez d''abord : ./be-sim');
end

% Charger les données
disp('📂 Chargement de sources.csv...');
data = readmatrix(csv_file);

% Extraire les colonnes (en sautant l'en-tête)
t = data(:,1);
sinus = data(:,2);
echelon = data(:,3);
creneau = data(:,4);
triangle = data(:,5);

disp(['✅ ' num2str(length(t)) ' points chargés']);

% Créer une figure avec 4 sous-graphiques
figure('Position', [100, 100, 1400, 1000], 'Name', 'Sources de Tension');

% Sinus
subplot(2,2,1);
plot(t, sinus, 'r-', 'LineWidth', 2);
grid on;
title('Source Sinusoïdale', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Temps (s)', 'FontSize', 10);
ylabel('Tension (V)', 'FontSize', 10);
legend('Sinus', 'Location', 'best');

% Échelon
subplot(2,2,2);
plot(t, echelon, 'b-', 'LineWidth', 2);
grid on;
title('Source Échelon', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Temps (s)', 'FontSize', 10);
ylabel('Tension (V)', 'FontSize', 10);
legend('Échelon', 'Location', 'best');

% Créneau
subplot(2,2,3);
plot(t, creneau, 'g-', 'LineWidth', 2);
grid on;
title('Source Créneau', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Temps (s)', 'FontSize', 10);
ylabel('Tension (V)', 'FontSize', 10);
legend('Créneau', 'Location', 'best');

% Triangulaire
subplot(2,2,4);
plot(t, triangle, 'm-', 'LineWidth', 2);
grid on;
title('Source Triangulaire', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Temps (s)', 'FontSize', 10);
ylabel('Tension (V)', 'FontSize', 10);
legend('Triangulaire', 'Location', 'best');

% Titre général
sgtitle('Visualisation des Sources de Tension', 'FontSize', 16, 'FontWeight', 'bold');

% Sauvegarder la figure
output_file = '../sources_plot.png';
saveas(gcf, output_file);
disp(['✅ Figure sauvegardée : ' output_file]);
