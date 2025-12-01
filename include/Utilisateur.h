#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>

/** Classe Utilisateur (Abstraite) : Classe de base pour tous les utilisateurs du système
    Gère l'authentification, l'identité et les droits d'accès
*/

class Utilisateur
{
    public:
        // Constructeur
        Utilisateur(int idCompteUser, const std::string& nomUser, const std::string& prenomUser, const std::string& loginUser,
                     const std::string& motDePasseUser, const std::string&  roleUser, bool premiereConnexion);
        //Destructeur
        virtual ~Utilisateur();

        // Accesseurs
        int getIdUser() const;
        std::string getLogin() const ;
        std::string getNomComplet() const;
        std::string getNom() const;
        std::string getPrenom() const;
        std::string getMdpHashe() const;
        std::string getRole() const;
        bool getPremiereConnexion() const;

        // Mutateurs
        void setNom(const std::string& nom);
        void setPrenom(const std::string& prenom);
        void setPasswordHashe(const std::string& passwordHashe);
        void setRole(const std::string& role);
        void setPremiereConnexion(bool premiereConnexion);

        // Méthodes pour l'authentification
        bool verifierMotDePasse(const std::string& mdpFourni) const;

        // Méthodes virtuelles à implémenter par toutes les sous-classes
        virtual std::string toCSV() const = 0;
        virtual void afficherMenu() const = 0;


    protected:
        int m_idCompteUser;
        std::string m_nomUser;
        std::string m_prenomUser;
        std::string m_loginUser;
        std::string m_motDePasseUserHashe;
        std::string m_roleUser;
        bool m_premiereConnexion;

    private:
};

#endif // UTILISATEUR_H
