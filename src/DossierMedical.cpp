#include "DossierMedical.h"
#include <iostream>
#include <sstream>

DossierMedical::DossierMedical(int idPatient, bool archive) : m_idPatient(idPatient), m_consultations(), m_antecedents(), m_archive(archive)
{

}

        // Accesseurs
int DossierMedical::getIdPatient() const
{
    return m_idPatient;
}



const std::vector<Consultation>& DossierMedical::getConsultations() const
{
    return m_consultations;
}



const std::vector<Antecedent>& DossierMedical::getAntecedents() const
{
    return m_antecedents;
}



const std::vector<Prescription>& DossierMedical::getPrescriptions() const
{
    return m_prescriptions;
}




bool DossierMedical::estArchive() const
{
    return m_archive;
}




         // Mutateur
void DossierMedical::setArchive(bool archiver)
{
    m_archive = archiver;
}




        // Méthodes pour la modification des éléments du dossier
void DossierMedical::ajouterConsultation(const Consultation& consult)
{
    m_consultations.push_back(consult);
}



void DossierMedical::ajouterAntecedent(const Antecedent& antecedent)
{
    m_antecedents.push_back(antecedent);
}



void DossierMedical::ajouterPrescription(const Prescription& prescript)
{
    m_prescriptions.push_back(prescript);
}




        // Méthode pour une recherche plus ciblée
Consultation* DossierMedical::rechercherConsultation(int idConsultation)
{
    for (auto& consult : m_consultations)
    {
        if (consult.getIdConsultation() == idConsultation)
            return &consult;
    }
    return nullptr;
}



Antecedent* DossierMedical::rechercherAntecedent(int idAntecedent)
{
    for (auto& antecedent : m_antecedents)
    {
        if (antecedent.getIdAntecedent() == idAntecedent)
            return &antecedent;
    }
    return nullptr;
}




        // Presistance des données de la classe
std::string DossierMedical::toCSV() const
{
    std::string chaine = std::to_string(m_idPatient) + ";" + (m_archive ? "1" : "0");
    return chaine;
}




DossierMedical DossierMedical::fromCSV(const std::string& ligne)
{
    // Analyse de la ligne CSV
    std::stringstream ss(ligne);
    std::string idStr, archiveStr;
    std::getline(ss, idStr, ';');
    std::getline(ss, archiveStr, ';');
    int id = std::stoi(idStr);
    bool arch = (archiveStr == "1");
    return DossierMedical(id, arch);
}





void DossierMedical::afficherResumeDossier() const
{

    std::cout << "=== DOSSIER MEDICAL DU PATIENT #" << m_idPatient << " :\n";
    std::cout << "\t Consultations :\n";
    for (const auto& c : m_consultations)
    {
        c.afficherDetailsConsultation();
        std::cout << "\n";
    }
    std::cout << "\t Antecedents :\n";
    for (const auto& a : m_antecedents)
    {
        a.afficherDetailsAntecedent();
        std::cout << "\n";
    }
    std::cout << "\t Prescriptions :" << std::endl;
    for (const auto& p : m_prescriptions)
    {
        p.afficherDetailsPrescription();
        std::cout << "\n";
    }
}
