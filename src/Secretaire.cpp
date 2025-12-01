#include "Secretaire.h"

#include <iostream>

Secretaire::Secretaire(int idSecretaire, const std::string& nomSecretaire, const std::string& prenomSecretaire, const std::string& mdpSecretaire,
                    const std::string& emailSecretaire, const std::string& telephoneSecretaire, bool accessDossiersMedicaux)
                    : m_idSecretraire(idSecretaire), m_nomSecretaire(nomSecretaire), m_prenomSecretaire(prenomSecretaire),
{
    //ctor
}

Secretaire::~Secretaire()
{
    //dtor
}



        // Accesseurs
int Secretaire::getIdSecretaire() const
{
    return m_idSecretaire;
}

std::string Secretaire::getNomSecretaire() const
{
    return m_nomSecretaire;
}
std::string Secretaire::getPrenomSecretaire() const
{
    return m_prenomSecretaire;
}

std::string Secretaire::getMdpSecretaire() const
{
    return m_mdpSecretaire;
}

std::string Secretaire::getEmailSecretaire() const
{
    return m_emailSecretaire;
}

std::string Secretaire::getTelephoneSecretaire() const
{
    return m_telephoneSecretaire;
}

        // Mutateurs
void Secretaire::setMdp(const std::string& mdp);
void Secretaire::setEmail(const std::string& email) ;
void Secretaire::setTelephone(const std::string& tel);
void Secretaire::setProfil();


        // méthodes générales
Secretaire Secretaire::fromCSV(const std::string& line);
std::string Secretaire::toCSV() const;
void Secretaire::afficherProfil() const;
