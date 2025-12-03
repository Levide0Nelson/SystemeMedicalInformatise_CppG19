#include "Patient.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>




Patient::Patient(int idPatient, const std::string& nomPatient, const std::string& prenomPatient, const std::string& dateNaissance,
                 const std::string& genre, const std::string& adresse, const std::string& telephone, const std::string& email) :
                     m_idPatient(idPatient), m_nomPatient(nomPatient), m_prenomPatient(prenomPatient), m_dateDeNaissance(dateNaissance),
                     m_genre(genre), m_adresse(adresse), m_telephone(telephone), m_email(email)
{

}

Patient::~Patient()
{

}


        // Accesseurs
int Patient::getIdPatient() const
{
    return m_idPatient;
}



std::string Patient::getNomPatient() const
{
    return m_nomPatient;
}



std::string Patient::getPrenomPatient() const
{
    return m_prenomPatient;
}




std::string Patient::getDateDeNaissance() const
{
    return m_dateDeNaissance;
}



std::string Patient::getGenre() const
{
     return m_genre;
}





std::string Patient::getAdresse() const
{
    return m_adresse;
}




std::string Patient::getTelephone() const
{
    return m_telephone;
}




std::string Patient::getEmail() const
{
    return m_email;
}





        // Mutateurs
void Patient::setNomPatient(const std::string& nom)
{
    m_nomPatient = nom;
}





void Patient::setPrenomPatient(const std::string& prenom)
{
    m_prenomPatient = prenom;
}




void Patient::setDateDeNaissance(const std::string& date)
{
    m_dateDeNaissance = date;
}




void Patient::setGenre(const std::string& genre)
{
    m_genre = genre;
}




void Patient::setAdresse(const std::string& adresse)
{
    m_adresse = adresse;
}




void Patient::setTelephone(const std::string& telephone)
{
    m_telephone = telephone;
}





void Patient::setEmail(const std::string& email)
{
    m_email = email;
}




std::string Patient::toCSV() const
{
    return std::to_string(m_idPatient) + ";" + m_nomPatient + ";" + m_prenomPatient + ";" + m_dateDeNaissance + ";" + m_genre + ";" + m_adresse + ";" + m_telephone + ";" + m_email;
}





Patient Patient::fromCSV(const std::string& line)
{
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> elmts;

    while (std::getline(ss, item,';'))
    {
        elmts.push_back(item);
    }

    if (elmts.size() != 8)
    {
        throw std::invalid_argument("Format CSV incorrect pour le patient");
    }
    return Patient(std::stoi(elmts[0]), elmts[1], elmts[2], elmts[3], elmts[4],elmts[5],elmts[6], elmts[7]);
}





void Patient::afficherInfos() const
{
    std::cout << "\n===== INFORMATIONS PATIENT =====\n\n";

    // En-têtes de colonnes
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Nom"
              << std::setw(40) << "Prenom(s)"
              << std::setw(18) << "Date Naissance"
              << std::setw(10)  << "Genre"
              << std::setw(12) << "Telephone"
              << std::setw(20) << "Email"
              << "\n";

    std::cout << std::string(130, '-') << "\n";

    // Lignes
        std::cout << std::left
                  << std::setw(5)  << m_idPatient
                  << std::setw(20) << m_nomPatient
                  << std::setw(40) << m_prenomPatient
                  << std::setw(18) << m_dateDeNaissance
                  << std::setw(10)  << m_genre
                  << std::setw(12) << m_telephone
                  << std::setw(20) << m_email
                  << "\n";
    std::cout << std::string(130, '-') << "\n";
}
