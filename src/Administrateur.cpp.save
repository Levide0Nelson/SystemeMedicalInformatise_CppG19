#include "Administrateur.h"
#include <iostream>
#include "UtilConsole.h"


Administrateur::Administrateur(int idAdmin, const std::string& nomAdmin, const std::string& prenomAdmin, const std::string& loginAdmin,
                       const std::string& mdpAdmin, bool accessMedical, bool premiereConnexion)
                       : Utilisateur(idAdmin,nomAdmin,prenomAdmin,loginAdmin,mdpAdmin,"Administrateur",premiereConnexion),
                         m_peutAccederDonneesMedicales(accessMedical)
{

}



bool Administrateur::getAutorisation() const
{
    return m_peutAccederDonneesMedicales;
}



void Administrateur::setAutorisation(bool autorisation)
{
    m_peutAccederDonneesMedicales = autorisation;
}



std::string Administrateur::toCSV() const
{
    return std::to_string(m_idCompteUser) + ";" + m_nomUser + ";" + m_prenomUser + ";" + m_loginUser + ";" + m_motDePasseUserHashe + ";Administrateur" + ";" + std::to_string(m_peutAccederDonneesMedicales)
            + ";" + std::to_string(m_premiereConnexion);
}




void Administrateur::afficherMenu() const
{
    nettoyerEcran();
    std::cout << "\n===== Menu Administrateur =====\n";
    std::cout << "1. Gestion des comptes utilisateurs\n";
    std::cout << "2. Consultation d'un dossier patient\n";
    std::cout << "3. Archivage de dossier\n";
    std::cout << "4. Afficher dossiers archivees\n";
    std::cout << "5. Affichage des statistiques\n";
    std::cout << "6. Import/Export de donnees (.csv)\n";
    std::cout << "0. Deconnexion\n";
}
