#ifndef PROFESSIONNELDESANTE_H
#define PROFESSIONNELDESANTE_H

#include "Utilisateur.h"
#include "Patient.h"
#include <vector>
#include <string>

/** Classe ProfessionnelDeSante : Représente un professionnel de santé (médecin, infirmier, pharmacien, etc...)
    Permissions dans le système : Peut consulteer et créer des consultations pour les patients
*/


class ProfessionnelDeSante : public Utilisateur
{
    public:
        // Constructeur
        ProfessionnelDeSante(int idPro, const std::string& nomPro, const std::string& prenomPro,const std::string& loginPro,const std::string& mdpPro,
                             const std::string& role,const std::string& specialite, const std::string& grade = "Aucun grade precise", bool premiereConnexion = true);
        // Destructeur (par défaut celui de la classe Utilisateur
        ~ProfessionnelDeSante() = default;

        // Accesseurs
        std::string getSpecialite() const;
        std::string getGrade() const;
        bool getPremiereConnexion() const;

        // Mutateurs
        void setSpecialite(const std::string& specialite);
        void setGrade(const std::string& grade);
        void setPremiereConnexion(bool premiereConnexion);

        std::string toCSV() const override;
        void afficherMenu() const override;


    protected:

    private:
        std::string m_specialite;
        std::string m_grade;
};

#endif // PROFESSIONNELDESANTE_H
