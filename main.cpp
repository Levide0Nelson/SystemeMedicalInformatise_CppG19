#include <iostream>
#include <string>
#include "Systeme.h"
#include "UtilConsole.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

/** Programme principal du Système SIM
*/

int correctChoiceNumber(int minim, int maxi, int choice, std::string repetedPhrase)
{
    std::string stringChoice = std::to_string(choice);
    while(true)
    {

        getline(std::cin, stringChoice);

        try
        {
            choice = std::stoi(stringChoice);  // Convertion en entier
        }
        catch (...)
        {
            std::cout << "Entrée invalide. Veuillez entrer un nombre entre " << minim << " et " << maxi << std::endl;
            std::cout << repetedPhrase;
            continue;
        }
        if (choice < minim || choice >maxi)
        {
            std::cout << "Veuillez entrer un nombre entre " << minim << " et " << maxi << std::endl;
            std::cout << repetedPhrase;
        }
        else
        {
            return choice;
        }
    }
}



char correctChoiceBoolean (char booleanChoice, std::string repeatedPhrase)
{
    std::string stringBooleanChoice(1,booleanChoice);
    while (true)
    {
        getline(std::cin, stringBooleanChoice);

        try
        {
            booleanChoice = stringBooleanChoice.at(0);
        }
        catch (...)
        {
            std::cout << "Veuillez entrez une des options pour continuer." << std::endl;
            std::cout << repeatedPhrase;
            continue;
        }

        if (booleanChoice != 'o' && booleanChoice != 'O' && booleanChoice != 'n' && booleanChoice != 'N')
        {
            std::cout << "Entrée invalide. Veuillez entrer les options \"o\" ou \"n\" pour continuer." << std::endl;
            std::cout << repeatedPhrase;
        }
        else
        {
            return booleanChoice;
        }
    }
}



void afficherBienvenue()
{
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif // _WIN32
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║     SYSTEME D'INFORMATION MEDICAL        ║" << std::endl;
    std::cout << "║               MEDIPASS                   ║" << std::endl;
    std::cout << "║ Gestion     Hospitalière    Centralisée  ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
}



void afficherMenuAuthentification()
{
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif // _WIN32
    nettoyerEcran();
    std::cout << "1. Se connecter\n";
    std::cout << "2. Quitter le programme\n";
    std::cout << "Votre choix : ";
}



/**
 * Boucle d'authentification
 * Demande username/password, valide, retourne l'utilisateur connecté
 */

 Utilisateur* boucleAuthentification(Systeme& systeme)
 {
     const int NB_TENTATIVES_CONNEXION = 3;
     int essais = 0;
     std::string login, password;
     Utilisateur* userConnecte = nullptr;

     while (!userConnecte && essais < NB_TENTATIVES_CONNEXION)
     {
         Utilisateur* user = nullptr;
         while (!user && essais < NB_TENTATIVES_CONNEXION)
         {
             std::cout << "\n\t==== Authentification ====\n";
            std::cout << "Login : ";
            std::getline(std::cin, login);

            user = systeme.authentifierPremiereConnexion(login);
            if (!user)
            {
                essais++;
                std::cout << "\n[ERREUR] Identifiants incorrects. Veuillez réessayer.\n";
                std::cout << NB_TENTATIVES_CONNEXION - essais << " tentatives restantes / " << NB_TENTATIVES_CONNEXION << std::endl;
            }
         }
         if (!user)
        {
            std::cout << "[ECHEC] Trop de tentatives sans resultat. Veuillez recommencer ou contacter un administrateur.\n";
            pauseConsole();
            return user;
        }

         if (user -> getPremiereConnexion())
         {
                std::string nouveauMdp, confirmation;
                bool ok = false;
                while (!ok)
                {
                    std::cout << "Premiere connexion, veuillez choisir un nouveau mot de passe.\n";
                    std::cout << "Nouveau mot de passe : ";
                    std::getline(std::cin, nouveauMdp);
                    std::cout << "Confirmez le mot de passe : ";
                    std::getline(std::cin, confirmation);

                    if (nouveauMdp == confirmation && !nouveauMdp.empty())
                    {
                        user -> setPasswordHashe(hashMotDePasse(nouveauMdp));
                        user -> setPremiereConnexion(false);

                        // Sauvegarder selon le type (admin ou pro)
                        if (dynamic_cast<ProfessionnelDeSante*>(user))
                            systeme.sauvegarderUtilisateursPro();
                        else if (dynamic_cast<Administrateur*>(user))
                            systeme.sauvegarderUtilisateursAdmins();

                        std::cout << "[SUCCES] Mot de passe mis a jour.\n";
                        ok = true;
                    }
                    else
                    {
                        std::cout << "[ERREUR] Les mots de passe ne correspondent pas ou sont vides. Reessayez.\n";
                    }
                }
         }

         std::cout << "Mot de passe : ";
         std::getline(std::cin , password);

         userConnecte = systeme.authentifier(login, password);

         if (!userConnecte)
         {
             essais++;
             std::cout << "\n[ERREUR] Identifiants incorrects. Veuillez réessayer.\n";
             std::cout << NB_TENTATIVES_CONNEXION - essais << " tentatives restantes / " << NB_TENTATIVES_CONNEXION << std::endl;
         }
         else
         {
             std::cout << "\n[SUCCES] Authentification réussie.\n";
             std::cout << "Bienvenue " << userConnecte -> getNom() << " " << userConnecte -> getPrenom() << " !\n";
         }
     }

     if (!userConnecte)
     {
         std::cout << "[ECHEC] Trop de tentatives sans resultat. Veuillez recommencer ou contacter un administrateur.\n";
         pauseConsole();
     }
     return userConnecte;
 }


int main() {

    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif // _WIN32

    afficherBienvenue();

    // Initialisation de système
    Systeme systeme;

    // Chargement des données depuis les fichiers
    std::cout << "[ Chargement des données ]...\n";
    systeme.chargerDonnees();

    bool systemeEnExecution = true;

    while (systemeEnExecution)
    {
        afficherMenuAuthentification();
        int choix;
        choix = correctChoiceNumber(1,2,choix,"Votre choix : ");

        switch (choix)
        {
            case 1 :
                {
                   // Authentification
                    Utilisateur* user = boucleAuthentification(systeme);
                    if (user)
                    {
                        // Lancement du menu de l'utilisateur
                        std::cout << "\n\tLancement du menu utilisateur...\n";
                        systeme.lancerMenu();
                    }
                    break;
                }
            case 2 :
                {
                    nettoyerEcran();
                    char confirmQuit;
                    std::cout << "Voulez-vous vraiment quitter ? (o/n) : ";
                    confirmQuit = correctChoiceBoolean(confirmQuit, "Voulez-vous vraiment quitter ? (o/n) : ");
                    if (confirmQuit == 'o' || confirmQuit == 'O')
                    {
                        //Quitter
                        std::cout << "\n [ Sauvegarde des données en cours... ]\n";
                        systeme.sauvegarderDonnees();
                        std::cout << "[ Données savegardées. ]\n";
                        std::cout << "\tFermeture du système.\n" << std::endl;
                        systemeEnExecution = false;
                    }
                    break;
                }
            default :
                std::cout << "[ERREUR] Choix invalide. Veuillez réessayer." << std::endl;
                pauseConsole();
        }
    }

    return 0;
}
