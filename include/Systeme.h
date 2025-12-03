#ifndef SYSTEME_H
#define SYSTEME_H

#include <vector>
#include <string>
#include "Patient.h"
#include "ProfessionnelDeSante.h"
#include "DossierMedical.h"
#include "Administrateur.h"
#include "Consultation.h"
#include "Antecedent.h"
#include "Date.h"
#include "ImportExport.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "RendezVous.h"

/** Classe Systeme : Gère l'ensemble des donnnées et opérations du système médical
    Fournit des méthodes pour ajouter, rechercher, modifier et permet de lancer une interfacce console de base
    + Sauvegarde et chargement des données
*/


class Systeme
{
    public:
        //Constructeur par défaut
        Systeme();

        // ----Gestion de l'authentification-----
        Utilisateur* authentifierPremiereConnexion(const std::string& username);
        Utilisateur* authentifier(const std::string& username, const std::string& password);

        // ----Persistance des données ---
        void chargerDonnees();
        void sauvegarderDonnees() const;


        // ----Gestion des utilisateurs ---
        void ajouterAdministrateur(const Administrateur& admin);
        void ajouterProfessionnel(const ProfessionnelDeSante& pro);
        Administrateur* rechercherAdmin(const std::string& username);
        ProfessionnelDeSante* rechercherPro(const std::string& username);

        // ---- Gestion des patients ----
        int creerPatient(const Patient& patient);
        Patient* rechercherPatient(int idPatient);
        void afficherTousPatients() const;

        // ---- Gestion des dossiers médicaux ----
        DossierMedical* rechercherDossier(int idPatient);
        void creerDossierMedical(int idPatient);

        // ---- Gestion des consultations ----
        int creerConsultation(int idPatient,const std::string& nomCompletPro, const std::string& date, const std::string& motif, const std::string& observations );

        // ----Gestion des antecedents----
        int ajouterAntecedent(int idPatient, const std::string& type, const std::string& description, const std::string& date );

        // ----Gestion des rendez-vous ----
        void ajouterRdvProfessionnel(int idPro);
        void supprimerRdvProfessionnel(int idPro);

        // ----Affichage des stats
        void afficherStatistiques() const;
        void accorderHabilitation();
        void retirerHabilitation();

        // ---Menu principal----
        void lancerMenu();

        // utilitaires internes
        int genererIdPatient();
        int genererIdConsultation();
        int genererIdAntecedent();

        void menuRechercher();
        void menuGestionUtilisateurs();
        void menuInscriptionPatient();
        void menuConsultationDossier(Utilisateur* userConnecte);
        void menuRechercherPatient();
        void menuCreerConsultation();
        void menuAjouterAntecedent();
        void menuArchivageDossiers();
        void menuAjouterPrescriptions();
        void menuAgendaProfessionnel();
        void menuImportExport();
        void afficherMenuExport();

        // Accesseurs pour les statistiques
        int getNombrePatients() const;
        int getNombreProfessionnels() const;
        int getNombreAdmins() const;
        int getNombreConsultations() const;
        int getNombreAntecedents() const;
        int getNombrePrescriptions() const;
        const std::vector<Patient>& getPatients() const;

        void ajouterPatient(const Patient& p);

        void afficherDossiersArchives() const ;
        void afficherRdvProfessionnel(int idPro) const;
        void afficherAdministrateursHabilites() const;

        void sauvegarderUtilisateursAdmins() const;
        void sauvegarderUtilisateursPro() const;

    protected:

    private:
        // Stockage centralisé
        std::vector<Administrateur> m_admins;
        std::vector<ProfessionnelDeSante> m_professionnels;
        std::vector<Patient> m_patients;
        std::vector<DossierMedical> m_dossiers;
        std::vector<RendezVous> m_rendezVous;
        /**std::vector<Examen> m_examens;*/
        // Identifiant généré auto
        int m_nextIdPatient, m_nextIdConsultation, m_nextIdAntecedent, m_nextIdPrescription, m_nextIdRDV;;
        // Utilisateur actuellement connecté
        Utilisateur* m_utilisateurConnecte;
        // Chemin des fichiers de sauvegarde
        const std::string FICHIER_ADMINS = "data/administrateurs.csv";
        const std::string FICHIER_PROFESSIONNELS = "data/professionnels.csv";
        const std::string FICHIER_PATIENTS = "data/patients.csv";
        const std::string FICHIER_CONSULTATIONS = "data/consultations.csv";
        const std::string FICHIER_ANTECEDENTS = "data/antecedents.csv";

        // Méthodes de sauvegarde privées (aide au chargement et à la sauvegarde des données)
        void chargerAdmins();
        void chargerProfessionnels();
        void chargerPatients();
        void chargerConsultations();
        void chargerAntecedents();
        void chargerDossiers();
        void chargerPrescriptions();
        void chargerRDV();


        void sauvegarderAdmins() const;
        void sauvegarderProfessionnels() const;
        void sauvegarderPatients() const;
        void sauvegarderConsultations() const;
        void sauvegarderAntecedents() const;
        void sauvegarderDossiers() const ;
        void sauvegarderPrescriptions() const;
        void sauvegarderRDV() const;

};

#endif // SYSTEME_H
