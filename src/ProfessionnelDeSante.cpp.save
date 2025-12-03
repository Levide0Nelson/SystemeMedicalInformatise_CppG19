#include "ProfessionnelDeSante.h"
#include "Utilisateur.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "UtilConsole.h"


ProfessionnelDeSante::ProfessionnelDeSante(int idPro, const std::string& nomPro, const std::string& prenomPro,const std::string& loginPro,
                             const std::string& mdpPro, const std::string& role, const std::string& specialite, const std::string& grade, bool premiereConnexion) :
                                 Utilisateur(idPro,nomPro,prenomPro,loginPro,mdpPro, role, premiereConnexion), m_specialite(specialite), m_grade(grade)
{

}


        // Accesseurs
std::string ProfessionnelDeSante::getSpecialite() const
{
    return m_specialite;
}



std::string ProfessionnelDeSante::getGrade() const
{
    return m_grade;
}




        // Mutateurs
void ProfessionnelDeSante::setSpecialite(const std::string& specialite)
{
    m_specialite = specialite;
}



void ProfessionnelDeSante::setGrade(const std::string& grade)
{
    m_grade = grade;
}



std::string ProfessionnelDeSante::toCSV() const
{
    return std::to_string(m_idCompteUser) + ";" + m_nomUser + ";" + m_prenomUser + ";" + m_loginUser + ";" + m_motDePasseUserHashe + ";" + m_roleUser + ";" + m_specialite + ";" + m_grade + ";"
           + std::to_string(m_premiereConnexion);
}



void ProfessionnelDeSante::afficherMenu() const
{
    nettoyerEcran();
    std::cout << "\n===== Menu Professionnel de Sante (" << m_specialite << ") =====\n";
    std::cout << "1. Inscrire un nouveau patient\n";
    std::cout << "2. Consulter la liste des patients\n";
    std::cout << "3. Rechercher un patient\n";
    std::cout << "4. Consulter un dossier medical\n";
    std::cout << "5. Creer une consultation\n";
    std::cout << "6. Ajouter un antecedent\n";
    std::cout << "7. Prescrire un medicament\n";
    std::cout << "8. Afficher les administrateurs ayant une habilitation speciale\n";
    std::cout << "9. Accorder une habilitation speciale a un administrateur systeme\n";
    std::cout << "10. Retirer une habilitation accordee a un administrateur systeme\n";
    std::cout << "11. Mon agenda (consultations a venir)\n";
    std::cout << "0. Deconnexion\n";
}

