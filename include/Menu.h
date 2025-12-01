#ifndef MENU_H
#define MENU_H

#include "../Enumeration.h"
#include "Systeme.h"

struct Sys
{
    Systeme systeme;
};

class Menu
{
    public:
        Menu();
        // Administration
        void afficherBienvenue();
        void afficherPageAdmin();
        void connexionAdministrateur();
        void connexioProfessionnel();
        void creerCompteAdmin(int id, std::string& login, std::string& mdp, std::string& nom, std::string& prenom);
        void creerComptePro();
        void supprimerCompteAdmin();
        void gererDroitsAcces();
        void voirLesStats();
        void voirLogsSysteme();

        // Professionnels


        ~Menu();

    protected:

    private:
};

#endif // MENU_H
