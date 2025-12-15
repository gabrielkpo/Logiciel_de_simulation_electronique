#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <string>


// Classe de base pour les sources de tension

class Source {
public:
    virtual ~Source() = default;
    virtual double ve(double t) const = 0;
    virtual std::string getType() const = 0;

protected:
    // Attributs communs à TOUTES les sources
    double amplitude_;  
    double offset_;     
};


// Source Sinus : V(t) = A*sin(2πft)

class SinusSource : public Source {
public:
    SinusSource();
    SinusSource(double amplitude, double frequency, double offset);
    double ve(double t) const override;
    std::string getType() const override { return "Sinus"; }
    
private:
    // amplitude_ et offset_ sont HÉRITÉS de Source
    // On ajoute seulement ce qui est spécifique à Sinus
    double frequency_;
};

// Source Échelon : V(t) = 0 si t<t0, V si t≥t0

class EchelonSource : public Source {
public:
    EchelonSource();
    EchelonSource(double amplitude, double startTime = 0.0);
    double ve(double t) const override;
    std::string getType() const override { return "Echelon"; }
    
private:
    // amplitude_ et offset_ sont HÉRITÉS de Source
    double startTime_;
};

// Source Triangulaire

class TriangulaireSource : public Source {
public:
    TriangulaireSource();
    TriangulaireSource(double amplitude, double frequency, double offset);
    double ve(double t) const override;                       
    std::string getType() const override { return "Triangulaire"; }

private:
    // amplitude_ et offset_ sont HÉRITÉS de Source
    double frequency_;
};

// Source Créneau

class CreneauSource : public Source {
public:
    CreneauSource();
    CreneauSource(double amplitude, double frequency, double dutyCycle, double offset);
    double ve(double t) const override;                    
    std::string getType() const override { return "Creneau"; }          
private:
    // amplitude_ et offset_ sont HÉRITÉS de Source
    double frequency_;
    double dutyCycle_;
};

class RectangulaireSource : public Source {
public:
    RectangulaireSource();
    RectangulaireSource(double amplitude, double frequency, double dutyCycle, double offset);
    double ve(double t) const override;                    
    std::string getType() const override { return "Rectangulaire"; }          
private:
    // amplitude_ et offset_ sont HÉRITÉS de Source
    double frequency_;
    double dutyCycle_;
};  


#endif // SOURCE_HPP