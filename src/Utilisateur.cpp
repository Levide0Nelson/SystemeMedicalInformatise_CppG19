#include "Utilisateur.h"
#include <iostream>
#include "UtilConsole.h"

Utilisateur::Utilisateur(int idCompteUser, const std::string& nomUser, const std::string& prenomUser, const std::string& loginUser,
                     const std::string& motDePasseUser,const std::string& roleUser, bool premiereConnexion)
                    : m_idCompteUser(idCompteUser),m_nomUser(nomUser), m_prenomUser(prenomUser), m_loginUser(loginUser),
                      m_motDePasseUserHashe(hashMotDePasse(motDePasseUser)), m_roleUser(roleUser), m_premiereConnexion(premiereConnexion)

{

}



// Accesseurs
int Utilisateur::getIdUser() const
{
    return m_idCompteUser;
}


std::string Utilisateur::getLogin() const
{
    return m_loginUser;
}



std::string Utilisateur::getNomComplet() const
{
    return m_prenomUser + " " + m_nomUser;
}


std::string Utilisateur::getNom() const
{
    return m_nomUser;
}



std::string Utilisateur::getPrenom() const
{
    return m_prenomUser;
}


std::string Utilisateur::getMdpHashe() const
{
    return m_motDePasseUserHashe;
}



std::string Utilisateur::getRole() const
{
    return m_roleUser;
}


bool Utilisateur::getPremiereConnexion() const
{
    return m_premiereConnexion;
}


        // Mutateurs
void Utilisateur::setNom(const std::string& nom)
{
    m_nomUser = nom;
}



void Utilisateur::setPrenom(const std::string& prenom)
{
    m_prenomUser = prenom;
}




void Utilisateur::setPasswordHashe(const std::string& passwordHashe)
{
    m_motDePasseUserHashe = passwordHashe;
}



void Utilisateur::setRole(const std::string& role)
{
    m_roleUser = role;
}


void Utilisateur::setPremiereConnexion(bool premiereConnexion)
{
    m_premiereConnexion = premiereConnexion;
}


        // Méthodes pour l'authentification
bool Utilisateur::verifierMotDePasse(const std::string& mdpFourni) const
{
    return (m_motDePasseUserHashe == hashMotDePasse(mdpFourni));
}



Utilisateur::~Utilisateur()
{

}
