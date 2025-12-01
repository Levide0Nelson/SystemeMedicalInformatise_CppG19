#include "RendezVous.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iomanip>

RendezVous::RendezVous(int idRDV, int idPatient, int idProfessionnel, const std::string& date, const std::string& heure, const std::string& motif)
                        : m_idRDV(idRDV), m_idPatient(idPatient), m_idProfessionnel(idProfessionnel), m_date(date), m_heure(heure), m_motif(motif)
{

}

        // Acccesseurs
int RendezVous::getIdRDV() const
{
    return m_idRDV;
}



int RendezVous::getIdPatient() const
{
    return m_idPatient;
}



int RendezVous::getIdProfessionnel() const
{
    return m_idProfessionnel;
}



std::string RendezVous::getDate() const
{
    return m_date;
}



std::string RendezVous::getHeure() const
{
    return m_heure;
}



std::string RendezVous::getMotif() const
{
    return m_motif;
}



        // Mutateurs
void RendezVous::setDate(const std::string& date)
{
    m_date = date;
}




void RendezVous::setHeure(const std::string& heure)
{
    m_heure = heure;
}



void RendezVous::setMotif(const std::string& motif)
{
    m_motif = motif;
}




        // Méthodes pour l'écriture et la lecture dans le fichier CSV correspondant
std::string RendezVous::toCSV() const
{
    return std::to_string(m_idRDV) + ";" + std::to_string(m_idPatient) + ";" + std::to_string(m_idProfessionnel) + ";" + m_date + ";" + m_heure + ";" + m_motif;
}




RendezVous RendezVous::fromCSV(const std::string& ligne)
{
    std::stringstream ss(ligne);
    std::string item;
    std::vector<std::string> elmts;

    while (std::getline(ss, item, ';'))
    {
        elmts.push_back(item);
    }

    if (elmts.size() != 6)
        throw std::invalid_argument("Format CSV incorrect pour RendezVous");

    int idRDV = std::stoi(elmts[0]);
    int idPatient = std::stoi(elmts[1]);
    int idProfessionnel = std::stoi(elmts[2]);

    return RendezVous(idRDV, idPatient, idProfessionnel, elmts[3], elmts[4], elmts[5]);
}



        // Méthode pour l'affichage
void RendezVous::afficherRDV() const
{
    std::cout << "\n===== VOS RENDEZ-VOUS =====\n\n";

    // En-têtes de colonnes
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(5) << "ID Patient"
              << std::setw(5) << "ID professionnel"
              << std::setw(12) << "Date"
              << std::setw(8)  << "Heure"
              << std::setw(30) << "Motif"
              << "\n";

    std::cout << std::string(100, '-') << "\n";

    // Lignes
        std::cout << std::left
                  << std::setw(5)  << m_idRDV
                  << std::setw(5) << m_idPatient
                  << std::setw(5) << m_idProfessionnel    /** Mettre les noms et prénoms pour les pros et patients au lieu des id*/
                  << std::setw(12) << m_date
                  << std::setw(8)  << m_heure
                  << std::setw(30) << m_motif
                  << "\n";
    std::cout << std::string(100, '-') << "\n";
}
