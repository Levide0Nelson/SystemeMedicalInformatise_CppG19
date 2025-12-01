#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include "Utilisateur.h"
#include <vector>
#include <string>

/**Classe Administrateur : Représente un administrateur système hospitalier
    Permissions dans le système : Créer/modifier/supprimer des comptes Utilisateurs
    + Gérer les droits d'accès + Accès limité aux données + Peut voir les statistiques globales du système
*/


class Administrateur : public Utilisateur
{
    public:
        // Constructeur
        Administrateur(int idAdmin, const std::string& nomAdmin, const std::string& prenomAdmin, const std::string& loginAdmin,
                       const std::string& mdpAdmin, bool accessMedical, bool premiereConnexion = true);
        // Destructeur
        ~Administrateur() = default;

        // Accesseur
        bool getAutorisation() const;
        void setAutorisation(bool autorisation);

        // Méthodes pour la gestion des droits d'accès
        void gererUtilisateurs();
        void inscrirePatient();
        void afficherStatistiques();
        // Implémentation des méthodes virtuelles
        std::string toCSV() const override;
        void afficherMenu() const override;

    protected:

    private:
        bool m_peutAccederDonneesMedicales;
};

#endif // ADMINISTRATEUR_H
