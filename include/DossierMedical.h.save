#ifndef DOSSIERMEDICAL_H
#define DOSSIERMEDICAL_H

#include <vector>
#include <string>
#include "Consultation.h"
#include "Antecedent.h"
#include "Prescription.h"

class Consultation;
class Antecedent;

/** Classe DossierMedical : Contient toutes les données médicales relatives à un patient (Consultations, Antecedents, Prescriptions)
*/


class DossierMedical
{
    public:
        // Constructeur
        DossierMedical(int idPatient, bool archive = false);

        // Accesseurs
        int getIdPatient() const;
        const std::vector<Consultation>& getConsultations() const;
        const std::vector<Antecedent>& getAntecedents() const;
        const std::vector<Prescription>& getPrescriptions() const;
        bool estArchive() const;

        // Mutateur
        void setArchive(bool archiver);

        // Méthodes pour la modification des éléments du dossier
        void ajouterConsultation(const Consultation& consult);
        void ajouterAntecedent(const Antecedent& antecedent);
        void ajouterPrescription(const Prescription& prescript);

        // Méthode pour une recherche plus ciblée
        Consultation* rechercherConsultation(int idConsultation);
        Antecedent* rechercherAntecedent(int idAntecedent);

        // Presistance des données de la classe
        std::string toCSV() const;
        static DossierMedical fromCSV(const std::string& ligne);

        void afficherResumeDossier() const;

    protected:

    private:
        int m_idPatient;
        std::vector<Consultation> m_consultations;
        std::vector<Antecedent> m_antecedents;
        std::vector<Prescription> m_prescriptions;
        bool m_archive;
};

#endif // DOSSIERMEDICAL_H
