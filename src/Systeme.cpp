#include "Systeme.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "UtilConsole.h"
#include <thread>
#include <chrono>
#include "../Enumerations.h"



Systeme::Systeme() : m_nextIdPatient(1), m_nextIdConsultation(1), m_nextIdAntecedent(1),m_nextIdPrescription(1), m_nextIdRDV(1), m_utilisateurConnecte(nullptr)
{

}



// ----Gestion de l'authentification-----
Utilisateur* Systeme::authentifierPremiereConnexion(const std::string& username)
{
    for (auto& pro : m_professionnels)
    {
        if (pro.getLogin() == username)
        {
           return m_utilisateurConnecte = &pro;
        }
    }
    for (auto& admin : m_admins)
    {
        if (admin.getLogin() == username)
        {
            return m_utilisateurConnecte = &admin;
        }
    }
    return nullptr;
}

Utilisateur* Systeme::authentifier(const std::string& username, const std::string& password)
{
    for (auto& admin : m_admins)
    {
        if (admin.getLogin() == username && admin.verifierMotDePasse(password))
        {
            m_utilisateurConnecte = &admin;
            return m_utilisateurConnecte;
        }
    }
    for (auto& pro : m_professionnels)
    {
        if (pro.getLogin() == username && pro.verifierMotDePasse(password))
        {
            m_utilisateurConnecte = &pro;
            return m_utilisateurConnecte;
        }
    }
    return nullptr;
}




        // ----Persistance des donnees ---
void Systeme::chargerDonnees()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerAdmins();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerProfessionnels();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerPatients();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerConsultations();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerAntecedents();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerDossiers();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerPrescriptions();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    chargerRDV();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[SUCCES DU CHARGEMENT] Toutes les donnees ont ete chargees.\n" << std::endl;
    pauseConsole();
    nettoyerEcran();
}




void Systeme::chargerAdmins()
{
    std::ifstream fichier(FICHIER_ADMINS);
    bool premiereConnexion = false;

    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;

        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;


            if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            bool estHabilite;
            std::stringstream ss(ligne);
            std::string idStr, nom, prenom, login, password, role, habilitationStr, firstConnextionStr;

            std::getline(ss, idStr, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, login, ';');
            std::getline(ss, password, ';');
            std::getline(ss, role, ';');
            std::getline(ss, habilitationStr, ';');
            std::getline(ss, firstConnextionStr, ';');


            int id = std::stoi(idStr);
            int habilitation = std::stoi(habilitationStr);
            int firstConnextion = std::stoi(firstConnextionStr);
            estHabilite = (habilitation == 0) ? false : true;

            Administrateur admin(id,nom,prenom,login, "", estHabilite,(firstConnextion == 1) ? true : false);
            admin.setPasswordHashe(password);
            m_admins.push_back(admin);


            // Mise a jour du prochain ID
            if (id >= m_nextIdPatient)
                m_nextIdPatient = id +1;
        }
        fichier.close();
        std::cout << "[OK] " << m_admins.size() << " administrateur(s) charge(s).\n" << std::endl;
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier admins.csv non trouve. Creation nouvelle base de sauvegarde.\n" << std::endl;
        premiereConnexion = true;
    }

    if (m_admins.empty() || premiereConnexion)
    {
        std::cout << "[INFO] Creation du premier administrateur systeme requis.\n";
        pauseConsole();
        std::string nom, prenom, login, password;
        std::cout << "Nom : ";
        std::getline(std::cin, nom);
        std::cout << "Prenom : ";
        std::getline(std::cin, prenom);
        std::cout << "Login/Username : ";
        std::getline(std::cin, login);
        std::cout << "Password : ";
        std::getline(std::cin, password);

        Administrateur admin(m_nextIdPatient++, nom, prenom, login, password,false,false);
        m_admins.push_back(admin);
        std::cout << "[SUCCES] Premier administrateur cree.\n";
        std::cout << "Bienvenu sur le systeme.\n";
        pauseConsole();

        // Sauvegarde automatique :
        sauvegarderAdmins();
    }
}



void Systeme::chargerProfessionnels()
{
    std::ifstream fichier(FICHIER_PROFESSIONNELS);
    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;

        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;

            if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            std::stringstream ss(ligne);
            std::string idStr, nom, prenom, login, password, role, specialite, grade, premiereConnexionStr;

            std::getline(ss, idStr, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, login, ';');
            std::getline(ss, password, ';');
            std::getline(ss, role, ';');
            std::getline(ss, specialite, ';');
            std::getline(ss, grade, ';');
            std::getline(ss, premiereConnexionStr, ';');

            int id = std::stoi(idStr);
            int premiereConnexion = std::stoi(premiereConnexionStr);
            ProfessionnelDeSante pro(id, nom, prenom, login, "", role, specialite, grade, (premiereConnexion == 1) ? true : false);
            pro.setPasswordHashe(password);
            m_professionnels.push_back(pro);

            if (id >= m_nextIdPatient)
                m_nextIdPatient = id +1;
        }
        fichier.close();
        std::cout << "[OK] " << m_professionnels.size() << " professionnel(s) de sante charge(s).\n" << std::endl;
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier professionnels.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}



void Systeme::chargerPatients()
{
    std::ifstream fichier(FICHIER_PATIENTS);
    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;

             if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            try
            {
                Patient patient = Patient::fromCSV(ligne);
                m_patients.push_back(patient);
                creerDossierMedical(patient.getIdPatient());

                if (patient.getIdPatient() >= m_nextIdPatient)
                    m_nextIdPatient = patient.getIdPatient() + 1;
            }
            catch (const std::exception& e)
            {
                std::cout << "[ERREUR] Erreur lors de l'analyse d'un patient : " << e.what() << "\n" << std::endl;
                pauseConsole();
            }
        }
        fichier.close();
        std::cout << "[OK] " << m_patients.size()  << " patient(s) charge(s).\n" << std::endl;
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier patients.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}



void Systeme::chargerConsultations()
{
    std::ifstream fichier(FICHIER_CONSULTATIONS);
    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;
        int nbConsult = 0;
        while (getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;


             if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            try
            {
                Consultation consult = Consultation::fromCSV(ligne);
                DossierMedical* dossier = rechercherDossier(consult.getIdPatient());
                if (dossier)
                {
                    dossier -> ajouterConsultation(consult);
                    nbConsult++;
                }

                if (consult.getIdConsultation() >= m_nextIdConsultation)
                    m_nextIdConsultation = consult.getIdConsultation() + 1;
            }
            catch(const std::exception& e)
            {
                std::cout << "[ERREUR] Erreur lors de l'analyse d'une consultation : " << e.what() << "\n" << std::endl;
                pauseConsole();
            }
        }
        fichier.close();
        std::cout << "[OK] " << nbConsult << " consultation(s) chargee(s).\n" << std::endl;
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier consultations.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}



void Systeme::chargerAntecedents()
{
    std::ifstream fichier(FICHIER_ANTECEDENTS);
    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;
        int nbAnt = 0;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;

             if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            try
            {
                Antecedent ant = Antecedent::fromCSV(ligne);
                DossierMedical* dossier = rechercherDossier(ant.getIdPatient());
                if (dossier)
                {
                dossier->ajouterAntecedent(ant);
                nbAnt++;
                }

                if (ant.getIdAntecedent() >= m_nextIdAntecedent)
                    m_nextIdAntecedent = ant.getIdAntecedent() + 1;
            }
            catch (const std::exception& e)
            {
                std::cout << "[ERREUR] Erreur lors de l'analyse d'un antecedent : " << e.what() << "\n" << std::endl;
                pauseConsole();
            }
        }
        fichier.close();
        std::cout << "[OK] " << nbAnt << " antecedent(s) charge(s).\n" << std::endl;
    }
    else
    {
        std::cout << "[ATTENTION !] Fichier antecedents.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}



void Systeme::chargerDossiers()
{
    std::ifstream fichier("data/dossiersMedicals.csv");
    std::string ligne;
    bool premiereLigne = true;
    while (std::getline(fichier, ligne))
    {
         if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }
        DossierMedical dossier = DossierMedical::fromCSV(ligne);
        m_dossiers.push_back(dossier);
    }
    fichier.close();
    std::cout << "[OK] " << m_dossiers.size() << " dossier(s) charge(s).\n" << std::endl;
}



void Systeme::chargerPrescriptions()
{
    int nbrePrescript = 0;
    std::ifstream fichier("data/prescriptions.csv");
    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;

             if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            Prescription prescript = Prescription::fromCSV(ligne);

            for (auto& dossier : m_dossiers)
            {
                for (const auto& consult : dossier.getConsultations())
                {
                    if (consult.getIdConsultation() == prescript.getIdConsultation())
                    {
                        dossier.ajouterPrescription(prescript);
                        nbrePrescript += 1;
                        break;
                    }
                }
            }
            if (prescript.getIdPrescription() >= m_nextIdPrescription)
                m_nextIdPrescription = prescript.getIdPrescription() + 1;
        }
        fichier.close();
        std::cout << "[OK] " << nbrePrescript << " prescription(s) charge(s).\n" << std::endl;
    }
    else
    {
        std::cerr << "[ATTENTION !] Fichier prescriptions.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}



void Systeme::chargerRDV()
{
    std::ifstream fichier("data/rendezvous.csv");

    if (fichier.is_open())
    {
        std::string ligne;
        bool premiereLigne = true;
        while (std::getline(fichier, ligne))
        {
            if (ligne.empty())
                continue;

             if (premiereLigne)
            {
                premiereLigne = false;
                continue;
            }

            RendezVous rdv = RendezVous::fromCSV(ligne);
            m_rendezVous.push_back(rdv);

            if (rdv.getIdRDV() >= m_nextIdRDV)
                m_nextIdRDV = rdv.getIdRDV() + 1;
        }
        fichier.close();
        std::cout << "[OK] " << m_rendezVous.size() << " rendez-vous disponibles charge(s).\n" << std::endl;
    }
    else
    {
        std::cerr << "[ATTENTION !] Fichier rendezvous.csv non trouve.\n" << std::endl;
        pauseConsole();
    }
}


void Systeme::sauvegarderDonnees() const
{
    std::cout << "[Sauvegarde des donnees...]\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderAdmins();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderProfessionnels();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderPatients();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderConsultations();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderAntecedents();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderDossiers();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderPrescriptions();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sauvegarderRDV();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[SUCCES] Toutes les donnees ont ete sauvegardees.\n";
    pauseConsole();
}



void Systeme::sauvegarderAdmins() const
{
    std::ofstream fichier(FICHIER_ADMINS);

    fichier << "N°ID;NOM;Prenom;Login/Username;Password;Statut;Habilitation;MdpParDefaut"<< "\n";
    if (!m_admins.empty())
    {
        for (const auto& admin : m_admins)
        {
            fichier << admin.toCSV() << "\n";
        }
        fichier.close();
        std::cout << "[OK] Admins sauvegardes.\n" << std::endl;
    }
    else
        std::cout << "Aucun administrateur a sauvegarder.\n" << std::endl;
}



void Systeme::sauvegarderProfessionnels() const
{
    std::ofstream fichier(FICHIER_PROFESSIONNELS);

    fichier << "N°;Nom;Prenom;Login/Usernane;Password;Role;Specialite;Grade;MdpParDefaut" << "\n";
    if (!m_professionnels.empty())
    {
        for (const auto& pro : m_professionnels)
        {
            fichier << pro.toCSV() << "\n";
        }
        fichier.close();
        std::cout << "[OK] Professionnels de sante sauvegardes.\n" << std::endl;
    }
    else
    {
        std::cout << "Aucun professionnel a sauvegarder.\n" << std::endl;
    }
}



void Systeme::sauvegarderPatients() const
{
    std::ofstream fichier(FICHIER_PATIENTS);

    fichier << "N°;Nom;Prenom;DateDeNaissance;NumAssurance;Genre;Adresse;Telephone;Email" << "\n";
    if (!m_patients.empty())
    {
        for (const auto& patient : m_patients)
        {
            fichier << patient.toCSV() << "\n";
        }
        fichier.close();
        std::cout << "[OK] Patients sauvegardees.\n" << std::endl;
    }
    else
        std::cout << "Aucun patient a sauvegarder.\n" << std::endl;
}



void Systeme::sauvegarderConsultations() const
{
    std::ofstream fichier(FICHIER_CONSULTATIONS);

    fichier << "N°;Date;Motif;Observation;IdPatient;NomProfessionnel" << "\n";
    if (!m_dossiers.empty())
    {
        for (const auto& dossier : m_dossiers)
        {
            for (const auto& consult : dossier.getConsultations())
            {
                fichier << consult.toCSV() << "\n";
            }
        }
        fichier.close();
        std::cout << "[OK] Consultations sauvegardees.\n" << std::endl;
    }
}



void Systeme::sauvegarderAntecedents() const
{
    std::ofstream fichier(FICHIER_ANTECEDENTS);

    fichier << "N°;Type;Description;Date;IdPatient" << "\n";

    if (!m_dossiers.empty())
    {
        for (const auto& dossier : m_dossiers)
        {
            for (const auto& antecedent : dossier.getAntecedents())
            {
                fichier << antecedent.toCSV() << "\n";
            }
        }
        fichier.close();
        std::cout << "[OK] Antecedents sauvegardes.\n" << std::endl;
    }
}



void Systeme::sauvegarderDossiers() const
{
    std::ofstream fichier("data/dossiersMedicals.csv");

    fichier << "IdPatient;EstArchive" << "\n";

    if (!m_dossiers.empty())
    {
        for (const auto& dossier : m_dossiers)
        {
            fichier << dossier.toCSV() << "\n";
        }
        fichier.close();
        std::cout << "[OK] Dossier medical sauvegarde avec ses modifications.\n" << std::endl;
    }
    else
        std::cout << "Aucun dossier a sauvegarder.\n" << std::endl;
}




void Systeme::sauvegarderPrescriptions() const
{
    std::ofstream fichier("data/prescriptions.csv");

        fichier << "N°;IdConsultation;Date;Contenu;Remarque" << "\n";

    if (!m_dossiers.empty())
    {
        for (const auto& dossier : m_dossiers)
        {
            for (const auto& prescrit : dossier.getPrescriptions())
            {
                fichier << prescrit.toCSV() << "\n";
            }
        }
        fichier.close();
        std::cout << "[OK] Prescriptions sauvegardees.\n" << std::endl;
    }
}




void Systeme::sauvegarderRDV() const
{
    std::ofstream fichier("data/rendezvous.csv");

    fichier << "N°;IdPatient;IdProfessionnel;Date;Heure;Motif" << "\n";
    if (!m_rendezVous.empty())
    {
        for (const auto& rdv : m_rendezVous)
        {
            fichier << rdv.toCSV() << "\n";
        }
        fichier.close();
        std::cout << "[OK] Rendez-vous sauvegardes.\n" << std::endl;
    }
    else
        std::cout << "Aucun rendez-vous a sauvegarder.\n" << std::endl;
}




void Systeme::sauvegarderUtilisateursAdmins() const
{
    sauvegarderAdmins();
}




void Systeme::sauvegarderUtilisateursPro() const
{
    sauvegarderProfessionnels();
}




        // ----Gestion des utilisateurs ---
void Systeme::ajouterAdministrateur(const Administrateur& admin)
{
    m_admins.push_back(admin);
}



void Systeme::ajouterProfessionnel(const ProfessionnelDeSante& pro)
{
    m_professionnels.push_back(pro);
}



Administrateur* Systeme::rechercherAdmin(const std::string& username)
{
    for (auto& admin : m_admins)
        if (admin.getLogin() == username)
            return &admin;
    return nullptr;
}



ProfessionnelDeSante* Systeme::rechercherPro(const std::string& username)
{
    for (auto& pro : m_professionnels)
        if (pro.getLogin() == username)
            return &pro;
    return nullptr;
}



        // ---- Gestion des patients ----
int Systeme::creerPatient(const Patient& patient)
{
    m_patients.push_back(patient);
    creerDossierMedical(patient.getIdPatient());
    m_nextIdPatient++;
    return patient.getIdPatient();
}



Patient* Systeme::rechercherPatient(int idPatient)
{
    for (auto& p : m_patients)
        if (p.getIdPatient() == idPatient)
            return &p;
    return nullptr;
}



void Systeme::afficherTousPatients() const
{
    nettoyerEcran();
    if (m_patients.empty())
    {
        std::cout << "Aucun patient pour le moment\n" << std::endl;
    }
    for (const auto& p : m_patients)
    {
        p.afficherInfos();
    }
}



        // ---- Gestion des dossiers medicaux ----
DossierMedical* Systeme::rechercherDossier(int idPatient)
{
    for (auto& dossier : m_dossiers)
        if (dossier.getIdPatient() == idPatient)
            return &dossier;
    return nullptr;
}



void Systeme::creerDossierMedical(int idPatient)
{
    m_dossiers.emplace_back(idPatient);
}



        // ---- Gestion des consultations ----
int Systeme::creerConsultation(int idPatient, const std::string& nomCompletPro, const std::string& date, const std::string& motif, const std::string& observations )
{
    Consultation consult(m_nextIdConsultation++, date, motif,observations,idPatient, nomCompletPro);
    DossierMedical* dossier = rechercherDossier(idPatient);
    if (dossier)
        dossier -> ajouterConsultation(consult);
    // ... enregistrement optionnel vector consultations global
    return consult.getIdConsultation();
}




        // ----Gestion des antecedents----
int Systeme::ajouterAntecedent(int idPatient, const std::string& type, const std::string& description, const std::string& date )
{
    Antecedent antecedent(m_nextIdAntecedent++, type, description, date, idPatient);
    DossierMedical* dossier = rechercherDossier(idPatient);
    if (dossier)
        dossier -> ajouterAntecedent(antecedent);
    // ... enregistrement optionnel vector antecedents global
    return antecedent.getIdAntecedent();
}



// ----Gestion des rendez-vous ----
void Systeme::ajouterRdvProfessionnel(int idPro)
{
    int idPatient;
    std::string date, heure, motif;
    std::cout << "\tPour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "ID du patient a programmer : ";
    std::cin >> idPatient;
    if (std::cin.fail())
    {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
    }
    std::cin.ignore();
    if (idPatient == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    Patient* patient = rechercherPatient(idPatient);

    if (!patient)
    {
        std::cout << "[ERREUR] Patient introuvable.\n";
        return;
    }
    bool dateValide = false;
    while (!dateValide)
    {
        try
        {
            std::cout << "Date (DD-MM-YYYY ou DD/MM/YYYY) : ";
            std::getline(std::cin, date);
            if (date == "0")
            {
                std::cout << "\nQuitter...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                return;
            }
            Date::validerFormat(date);
            dateValide = true;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERREUR] " << e.what() << " Reessayez.\n";
        }
    }
    bool heureValide = false;
    while(!heureValide)
    {
        try
        {
            std::cout << "Heure (HH:MM) : ";
            std::getline(std::cin, heure);
            if (heure == "0")
            {
                std::cout << "\nQuitter...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                return;
            }
            Date::validerHeure(heure);
            heureValide = true;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERREUR] " << e.what() << " Reessayez.\n";
        }
    }

    std::cout << "Motif : ";
    std::getline(std::cin, motif);
    if (motif == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    // Verification de la disponibilite ou non des creneaux

    for (const auto& rdv : m_rendezVous)
    {
        if (rdv.getIdProfessionnel() == idPro && rdv.getDate() == date && rdv.getHeure() == heure)
        {
            std::cout << "[ERREUR]  Ce creneau est deja pris.\n" << std::endl;
            pauseConsole();
            return;
        }
    }

    RendezVous nouveauRDV(m_nextIdRDV++, idPatient, idPro, date, heure, motif);
    m_rendezVous.push_back(nouveauRDV);
    sauvegarderRDV();
    std::cout << "[SUCCES] Nouveau Rendez-vous cree avec l'ID " << nouveauRDV.getIdRDV() <<". \n" << std::endl;
}




void Systeme::supprimerRdvProfessionnel(int idPro)
{
    int idRDV;
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "ID du rendez-vous a supprimer : ";
    std::cin >> idRDV;
    std::cin.ignore();
    if (idRDV == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    for (auto it = m_rendezVous.begin(); it != m_rendezVous.end(); ++it)
    {
        if (it -> getIdRDV() == idRDV && it -> getIdProfessionnel() == idPro)
        {
            m_rendezVous.erase(it);
            sauvegarderRDV();
            std::cout << "[SUCCES] Rendez-vous supprime.\n";
            return;
        }
    }
    std::cout << "[ERREUR] Rendez-vous introuvable ou non autorise.\n";
}


        // ----Affichage des stats
void Systeme::afficherStatistiques() const
{
    nettoyerEcran();
    std::cout << "\t\tAFFICHAGE DES STATISTIQUES DU SYSTEME\n" << std::endl;
    if (m_patients.size() == 0 && m_professionnels.size() == 0 && m_dossiers.size() == 0)
    {
        std::cout << "[INFO] Statistiques non disponibles.\n";
        return;
    }

    std::cout << "Nombre de patients : " << m_patients.size() << std::endl;
    std::cout << "Nombre de professionnels : " << m_professionnels.size() << std::endl;
    std::cout << "Nombre d'administrateurs : " << m_admins.size() << std::endl;
    int nbConsult = 0, nbAnt = 0;

    for (const auto& dossier : m_dossiers)
    {
        nbConsult += dossier.getConsultations().size();
        nbAnt += dossier.getAntecedents().size();
    }
    std::cout << "Nombre total de consultations : " << nbConsult << std::endl;
    std::cout << "Nombre total d'antecedents : " << nbAnt << std::endl;
}



        // utilitaires internes
int Systeme::genererIdPatient()
{
    return m_nextIdPatient++;
}



int Systeme::genererIdConsultation()
{
    return m_nextIdConsultation++;
}



int Systeme::genererIdAntecedent()
{
   return m_nextIdAntecedent++;
}




    // Menu administrateur
void Systeme::menuGestionUtilisateurs()
{
    bool sortir = false;

    while (!sortir)
    {
        nettoyerEcran();
        int choix = 0;
        std::cout << "\n==== GESTION DES UTILISATEURS ====\n";
        std::cout << "1. Creer un administrateur\n";
        std::cout << "2. Creer un professionnel de sante\n";
        std::cout << "3. Lister tous les utilisateurs\n";
        std::cout << "4. Retour au menu principal\n";

        while (choix <=0 || choix > 4)
        {
            std::cout << "Votre choix : ";
            std::cin >> choix;
            if (std::cin.fail())
            {
                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
                continue;
            }
        }
        std::cin.ignore();

        switch (choix)
        {
            case 1 :
            {
                nettoyerEcran();
                std::cout << "\t\tCREATION D'UN COMPTE ADMINISTRATEUR\n" << std::endl;
                std::string nom, prenom, login, password;
                std::cout << "\t Pour quitter entrez 0\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Nom du nouvel Administrateur : ";
                std::getline(std::cin, nom);
                if (nom == "0")
                {
                    std::cout << "\nQuitter...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    break;
                }
                std::cout << "Prenom du nouvel Administatrateur : ";
                std::getline(std::cin, prenom);
                if (prenom == "0")
                {
                    std::cout << "\nQuitter...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    break;
                }
                std::cout << "Username/Login : ";
                std::getline(std::cin, login);
                if (login == "0")
                {
                    std::cout << "\nQuitter...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    break;
                }
                std::cout << "Password par defaut (ce champ peut etre vide) : ";
                std::getline(std::cin, password);
                if (password == "0")
                {
                    std::cout << "\nQuitter...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    break;
                }

                Administrateur admin(genererIdPatient(), nom, prenom, login, password, false);
                ajouterAdministrateur(admin);
                std::cout << "[SUCCES] Nouvel Administrateur cree.\n";
                sauvegarderAdmins();
                std::cout << "" << std::endl;
                pauseConsole();
                break;
            }

            case 2:
                {
                    nettoyerEcran();
                    std::cout << "\t\tCREATION D'UN COMPTE PROFESSIONNEL DE SANTE\n" << std::endl;
                    std::string nom, prenom, login, password, role, specialite, grade;
                    std::cout << "\t Pour quitter entrez 0\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << "Nom : ";
                    std::getline(std::cin, nom);
                    if (nom == "0")
                    {
                        std::cout << "\nQuitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }
                    std::cout << "Prenom : ";
                    std::getline(std::cin, prenom);
                    if (prenom == "0")
                    {
                        std::cout << "\nQuitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }
                    std::cout << "Username : ";
                    std::getline(std::cin, login);
                    if (login == "0")
                    {
                        std::cout << "\nQuitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }
                    std::cout << "Password par defaut (ce champ peut etre vide) : ";
                    std::getline(std::cin, password);
                    if (password == "0")
                    {
                        std::cout << "Quitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }

                    afficherRoles();
                    bool continuer = true;
                    while (continuer)
                    {
                        int choice;
                        std::cout << "Entrer le numero du role (entre 1 et 8) : ";
                        std::cin >> choice;
                        if (std::cin.fail())
                        {
                            std::cin.clear();

                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
                            continue;
                        }
                        std::cin.ignore();
                        if (choice == 0)
                        {
                            std::cout << "\nQuitter...\n";
                            continuer = false;
                            std::this_thread::sleep_for(std::chrono::milliseconds(800));
                            break;
                        }
                        switch (choice)
                        {
                            case static_cast<int>(RolePro::MEDECIN_GENERALE) +1 :
                            {
                                role = "Medecin generale";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::MEDECIN_SPECIALISTE)+ 1 :
                            {
                                role = "Medecin Specialiste";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::INFIRMIER) + 1 :
                            {
                                role = "Infirmier(e)";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::PHARMACIEN) + 1 :
                            {
                                role = "Pharmacien";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::SAGE_FEMME) + 1 :
                            {
                                role = "Sage Femme";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::DENTISTE) + 1 :
                            {
                                role = "Dentiste";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::TECHNICIEN_LABORATOIRE)+1 :
                            {
                                role = "Technicien Laboratoire";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(RolePro::RADIOLOGUE) + 1 :
                            {
                                role = "Radiologue";
                                continuer = false;
                                break;
                            }
                            default :
                                {
                                    std::cout << "Entree invalide.\n";
                                    break;
                                }
                        }
                    }
                    afficherSpecialites();
                    continuer = true;
                    while (continuer)
                    {
                        int choice;
                        std::cout << "Entrer le numero de la specialite (entre 1 et 18) : ";
                        std::cin >> choice;
                        if (std::cin.fail())
                        {
                            std::cin.clear();

                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
                            continue;
                        }
                        std::cin.ignore();
                        if (choice == 0)
                        {
                            std::cout << "\nQuitter\n";
                            continuer = false;
                            std::this_thread::sleep_for(std::chrono::milliseconds(800));
                            break;
                        }
                        switch (choice)
                        {
                            case static_cast<int>(Specialite::MEDECINE_GENERALE) + 1 :
                            {
                                specialite = "MEDECINE GENERALE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::PEDIATRIE) +1  :
                            {
                                specialite = "PEDIATRIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::ORL) +1  :
                            {
                                specialite = "ORL";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::OPHTALMOLOGIE)+1 :
                            {
                                specialite = "OPHTAMOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::CARDIOLOGIE) + 1 :
                            {
                                specialite = "CARDIOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::GYNECOLOGIE) +1 :
                            {
                                specialite = "GYNECOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::NEUROLOGIE )+1 :
                            {
                                specialite = "NEUROLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::CHIRURGIE)+1 :
                            {
                                specialite = "CHIRURGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::PSYCHIATRIE)+1:
                            {
                                specialite = "PSYCHIATRIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::DENTISTE)+1 :
                            {
                                specialite = "DENTISTE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::ANESTHESIE)+1 :
                            {
                                specialite = "ANESTHESISTE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::PHARMACIE) +1 :
                            {
                                specialite = "PHARMACIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::ACCOUCHEMENT) +1  :
                            {
                                specialite = "ACCOUCHEMENT";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::DERMATOLOGIE) +1  :
                            {
                                specialite = "DERMATOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::PNEUMOLOGIE) +1 :
                            {
                                specialite = "PNEUMOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::ORTHOPEDIE) +1 :
                            {
                                specialite = "ORTHOPEDIE";
                                continuer =false;
                                break;
                            }
                            case (static_cast<int>(Specialite::RADIOLOGIE)+1):
                            {
                                specialite = "RADIOLOGIE";
                                continuer = false;
                                break;
                            }
                            case static_cast<int>(Specialite::ANALYSE_BIO_MEDICALE) + 1 :
                            {
                                specialite = "ANALYSE BIO-MEICALE";
                                continuer = false;
                                break;
                            }
                            default :
                            {
                                std::cout << "Choix invalide. Choisissez entre " << static_cast<int>(Specialite::MEDECINE_GENERALE) + 1 << " et " << static_cast<int>(Specialite::ANALYSE_BIO_MEDICALE)+1 << "\n";
                                break;
                            }

                        }
                    }
                    std::cout << "Grade : ";
                    std::getline(std::cin, grade);
                    if (grade == "0")
                    {
                        std::cout << "\nQuitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }

                    ProfessionnelDeSante pro(genererIdPatient(), nom, prenom, login, password, role, specialite, grade);
                    ajouterProfessionnel(pro);
                    std::cout << "[SUCCES] Nouveau Professionnel cree.\n";
                    sauvegarderProfessionnels();
                    std::cout << "" << std::endl;
                    pauseConsole();
                    break;
                }
            case 3 :
                {
                    nettoyerEcran();
                    std::cout << "\t\t === TOUS LES UTILISATEURS ===\n\n";
                    std::cout << "\n" << std::string(55, '=') + " Administrateurs " + std::string(55, '=') << "\n";

                    std::cout << std::left
                                 << std::setw(5) << "ID"
                                 << std::setw(15) << "Nom"
                                 << std::setw(20) << "Prenom(s)"
                                 << std::setw(15) << "Username"
                                 << "\n";
                        std::cout << std::string(60, '-') << "\n";

                    for (const auto& admin : m_admins)
                    {
                        std::cout << std::left
                                  << std::setw(5)  << admin.getIdUser()
                                  << std::setw(15) << admin.getNom()
                                  << std::setw(20) << admin.getPrenom()
                                  << std::setw(15) << admin.getLogin()
                                  << "\n";
                        std::cout << std::string(60, '-') << "\n";
                    }

                    std::cout << "\n" << std::string(48, '=') + " Pofessionnels de Sante " + std::string(48, '=') << "\n";

                    std::cout << std::left
                                 << std::setw(5) << "ID"
                                 << std::setw(15) << "Nom"
                                 << std::setw(20) << "Prenom(s)"
                                 << std::setw(20) << "Role"
                                 << std::setw(30) << "Specialite"
                                 << "\n";
                        std::cout << std::string(100, '-') << "\n";

                    for (const auto& pro : m_professionnels)
                    {
                        std::cout << std::left
                                  << std::setw(5)  << pro.getIdUser()
                                  << std::setw(15) << pro.getNom()
                                  << std::setw(20) << pro.getPrenom()
                                  << std::setw(20) << pro.getRole()
                                  << std::setw(30) << pro.getSpecialite()
                                  << "\n";
                        std::cout << std::string(100, '-') << "\n";
                    }
                    std::cout << " " << std::endl;
                    pauseConsole();
                    break;
                }
            case 4 :
                {
                    sortir = true;
                    break;
                }
            default :
                {
                    std::cout << "[ERREUR] Choix invalide.\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    break;
                }
        }
    }
}



// Menu administrateur : Inscription d'un patient
void Systeme::menuInscriptionPatient()
{
    nettoyerEcran();
    std::string nom, prenom, dateNaissance, genre, adresse, telephone, email;
    int numAssurance;
    std::cout << "\n===== INSCRIPTION D'UN PATIENT =====\n\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Nom : ";
    std::getline(std::cin, nom);
    if (nom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Prenom : ";
    std::getline(std::cin, prenom);
    if(prenom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    bool dateValide = false;
    while (!dateValide)
    {
        std::cout << "Date de naissance (DD-MM-YYYY ou DD/MM/YYYY) : ";
        std::getline(std::cin, dateNaissance);
        if (dateNaissance == "0")
        {
            std::cout << "\nQuitter...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            return;
        }
        Date::validerFormat(dateNaissance);
        dateValide = true;
    }
    bool numValide = false;
    while(!numValide)
    {
        std::cout << "Nunero d'assurance du patient (au moins 8 chiffres, sans letrre) : ";
        std::cin >> numAssurance;
        if (std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
            continue;
        }
        std::cin.ignore();
        if (numAssurance == 0)
        {
            std::cout << "\nQuitter...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            return;
        }
        numValide = numAssuranceEstValide(std::to_string(numAssurance));
    }

    std::cout << "Genre (M/F) : ";
    std::getline(std::cin, genre);
    if (genre == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Adresse : ";
    std::getline(std::cin, adresse);
    if (adresse == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Telephone : ";
    std::getline(std::cin, telephone);
    if (telephone == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Email : ";
    std::getline(std::cin, email);
    if (email == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    int idPatient = m_nextIdPatient++;

    Patient patient(idPatient, nom, prenom, dateNaissance,numAssurance, genre, adresse, telephone, email);
    creerPatient(patient);
    std::cout << "[SUCCES] Patient inscrit.\n ID du nouveau patient: " << idPatient << "\n";
}



// Menu administrateur : Consultation d'un dossier patient
void Systeme::menuConsultationDossier(Utilisateur* userConnecte)
{
    nettoyerEcran();
    // Si c'est un administrateur, verifier l'habilitation speciale
    Administrateur* admin = dynamic_cast<Administrateur*>(userConnecte);
    if (admin)
    {
        if (!admin -> getAutorisation())
        {
             std::cout << "[ACCES REFUSE] Desole ! Vous n'avez pas l'habilitation pour effectuer cette action.\n";
             return;
        }
    }

        int idPatient;
        std::cout << "\n===== CONSULTATION D'UN DOSSIER PATIENT =====\n";
        std::cout << "\t Pour quitter entrez 0\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "ID du patient : ";
        std::cin >> idPatient;
    if (std::cin.fail())
    {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
    }
    std::cin.ignore();
        if (idPatient == 0)
        {
            std::cout << "\nQuitter...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            return;
        }

        Patient* patient = rechercherPatient(idPatient);
        if (!patient)
        {
            std::cout << "[ERREUR] Patient non trouve.\n";
            return;
        }

        std::cout << "\n--- Informations du Patient ---\n";
        patient->afficherInfos();

        DossierMedical* dossier = rechercherDossier(idPatient);
        if (dossier)
        {
            std::cout << "\n--- Dossier Medical ---\n";
            dossier->afficherResumeDossier();
        }
        else
        {
            std::cout << "[ERREUR] Dossier non trouve.\n";
        }
}




// Menu professionnel : Rechercher un patient pour avoir ces infos et son ID
void Systeme::menuRechercherPatient()
{
    nettoyerEcran();
    std::string nom, prenom;
    std::cout << "\n===== RECHERCHE D'UN PATIENT =====\n\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Nom du patient a rechercher : ";
    std::getline(std::cin, nom);
    if (nom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Prenom du patient a rechercher : ";
    std::getline(std::cin, prenom);
    if (prenom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    std::cout << "\n" + std::string(10, '-') + " Resultats " + std::string(10, '-') + "\n";
    bool trouve = false;
    for (auto& patient : m_patients)
    {
        if (patient.getNomPatient() == nom && patient.getPrenomPatient() == prenom)
        {
            patient.afficherInfos();
            trouve = true;
        }
    }

    if (!trouve)
    {
        std::cout << "[ERREUR] Aucun patient trouve avec ce nom.\n";
    }
}




// Menu professionnel : Creer une consultation
void Systeme::menuCreerConsultation()
{
    nettoyerEcran();
    int idPatient;
    std::string date, motif, observations;

    std::cout << "\n===== CREATION D'UNE CONSULTATION =====\n\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "ID du patient : ";
    std::cin >> idPatient;
    if (std::cin.fail())
    {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
    }
    std::cin.ignore();
    if (idPatient == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    Patient* patient = rechercherPatient(idPatient);

    if (!patient)
    {
        std::cout << "Aucun patient trouve avec cet identifiant\n";
        return;
    }

    bool dateValide = false;
    while (!dateValide)
    {
        try
        {
            std::cout << "Date (DD-MM-YYYY ou DD/MM/YYYY) : ";
            std::getline(std::cin, date);
            if (date == "0")
            {
                std::cout << "\nQuitter...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                return;
            }
            Date::validerFormat(date);
            dateValide = true;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERREUR] " << e.what() << " Reessayez.\n";
        }
    }
    std::cout << "Motif : ";
    std::getline(std::cin, motif);
    if (motif == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Observations : ";
    std::getline(std::cin, observations);
    if (observations == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    int idConsult = creerConsultation(idPatient, m_utilisateurConnecte -> getNomComplet(), date, motif, observations);
    std::cout << "[SUCCES] Consultation creee. ID consultation : " << idConsult << "\n";
}




// Menu professionnel : Ajouter un antecedent
void Systeme::menuAjouterAntecedent()
{
    nettoyerEcran();
    int idPatient;
    std::string type, description, date;

    std::cout << "\n===== AJOUT D'ANTECEDENTS A UN DOSSIER PATIENT =====\n\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "ID du patient : ";
    std::cin >> idPatient;
    if (std::cin.fail())
    {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
    }
    std::cin.ignore();
    if (idPatient == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    Patient* patient = rechercherPatient(idPatient);

    if (!patient)
    {
        std::cout << "Aucun patient trouve avec cet identifiant\n";
        return;
    }

    std::cout << "Type (Allergie/Chirurgie/Pathologie/Autre) : ";
    std::getline(std::cin, type);
    if (type == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Description : ";
    std::getline(std::cin, description);
    if (description == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    bool dateValide = false;
    while (!dateValide)
    {
        std::cout << "Date (DD-MM-YYYY ou DD/MM/YYYY) : ";
        std::getline(std::cin, date);
        if (date == "0")
        {
            std::cout << "\nQuitter...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            return;
        }
        Date::validerFormat(date);
        dateValide = true;
    }


    int idAnt = ajouterAntecedent(idPatient, type, description, date);
    std::cout << "[SUCCES] Antecedent ajoute  avec l'ID : " << idAnt << "\n";
}





void Systeme::menuArchivageDossiers()
{
    nettoyerEcran();
    std::cout << "\n===== ARCHIVAGE D'UN DOSSIER PATIENT =====\n\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    int idPatient;
    std::cout << "Entrer l'ID du patient a archiver : ";
        std::cin >> idPatient;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
        }
        std::cin.ignore();
    if (idPatient == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    DossierMedical* dossier = rechercherDossier(idPatient);

    if (!dossier)
    {
        std::cout << "[ERREUR] Dossier non trouve !\n";
        return;
    }
    if (dossier -> estArchive())
    {
        std::cout << "[INFO] Ce dossier est deja archive.\n";
        return;
    }
    dossier->setArchive(true);
    std::cout << "[SUCCES] Dossier du patient #" << idPatient << " archive.\n";
}




void Systeme::menuAjouterPrescriptions()
{
    nettoyerEcran();
    int idPatient, idConsult;
    std::string contenu, remarque, date;
    std::cout << "\n===== AJOUT DE PRESCRIPTIONS A UN DOSSIER PATIENT =====\n";
    std::cout << "\t Pour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "ID du patient : ";
    std::cin >> idPatient;
    if (std::cin.fail())
    {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
    }
        std::cin.ignore();
    if (idPatient == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    Patient* patient = rechercherPatient(idPatient);

    if (!patient)
    {
        std::cout << "Aucun patient trouve avec cet identifiant\n";
        return;
    }

    std::cout << "ID de la consultation associee : ";
        std::cin >> idConsult;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
        }
        std::cin.ignore();
    if (idConsult == 0)
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Contenu (medicament/examen/dose) : ";
    std::getline(std::cin, contenu);
    if (contenu == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Remarques (facultatif) : ";
    std::getline(std::cin, remarque);
    if (remarque == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    bool dateValide = false;
    while (!dateValide)
    {
        try
        {
            std::cout << "Date (DD-MM-YYYY ou DD/MM/YYYY) : ";
            std::getline(std::cin, date);
            if (date == "0")
            {
                std::cout << "\nQuitter...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                return;
            }
            Date::validerFormat(date);
            dateValide = true;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERREUR] " << e.what() << " Reessayez.\n";
        }
    }

    Prescription prescription(m_nextIdPrescription++, idConsult, date, contenu, remarque);
    DossierMedical* dossier = rechercherDossier(idPatient);
    if (dossier)
    {
        dossier -> ajouterPrescription(prescription);
        std::cout << "[SUCCES] Prescription ajoutee\n";
    }
    else
    {
        std::cout << "[ERREUR] Dossier patient non trouve.\n";
    }
}



void Systeme::menuAgendaProfessionnel()
{
    auto* pro = dynamic_cast<ProfessionnelDeSante*>(m_utilisateurConnecte);

    if (!pro)
    {
        std::cout << "[ERREUR] Menu agenda reserve aux professionnels.\n";
        pauseConsole();
        return;
    }

    int idPro = pro -> getIdUser();
    bool quitter = false;
    while (!quitter)
    {
        nettoyerEcran();
        std::cout << "\n===== AGENDA PROFESSIONNEL =====\n";
        std::cout << "1. Afficher mes rendez-vous\n";
        std::cout << "2. Ajouter un rendez-vous\n";
        std::cout << "3. Supprimer un rendez-vous\n";
        std::cout << "4. Retour\n";
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
            continue;
        }
        std::cin.ignore();

        switch (choix)
        {
            case 1 :
                {
                    afficherRdvProfessionnel(idPro);
                    pauseConsole();
                    break;
                }
            case 2 :
                {
                    ajouterRdvProfessionnel(idPro);
                    pauseConsole();
                    break;
                }
            case 3 :
               {
                    supprimerRdvProfessionnel(idPro);
                    pauseConsole();
                    break;
               }
            case 4 :
                quitter = true;
                break;
            default :
                {
                    std::cout << "[ERREUR] Choix invalide.\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    break;
                }
        }
    }
}



void Systeme::menuImportExport()
{
    int choix;
    do
    {
        nettoyerEcran();
        std::cout << "\n===== IMPORT/EXPORT =====\n";
        std::cout << "1. Exporter dossier patient complet\n";
        std::cout << "2. Exporter statistiques globales\n";
        std::cout << "3. Exporter liste de tous les patients\n";
        std::cout << "4. Importer patients depuis un fichier CSV\n";
        std::cout << "5. Retour\n";
        std::cout << "Votre choix : ";
        std::cin >> choix;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
            continue;
        }
        std::cin.ignore();

        switch(choix)
        {
            case 1 :
                {
                    int choice;
                    do
                    {
                        afficherMenuExport();
                        std::cin >> choice;
                        std::cin.ignore();
                        switch (choice)
                        {
                            case 1 :
                                {
                                    int idPatient;
                                    std::string chemin;
                                    std::cout << "ID du patient : ";
                                    std::cin >> idPatient;
                                    std::cin.ignore();
                                    if (idPatient == 0)
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterDossierPatientEnTxt(idPatient, *this, chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 2 :
                                {
                                    int idPatient;
                                    std::string chemin;
                                    std::cout << "ID du patient : ";
                                    std::cin >> idPatient;
                                    std::cin.ignore();
                                    if (idPatient == 0)
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterDossierPatientEnCsv(idPatient, *this, chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 3 :
                                {
                                    break;
                                }
                            default :
                                {
                                    std::cout << "[ERREUR] Choix invalide.\n" << std::endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    break;
                                }
                        }

                    } while (choice != 3);
                    break;
                }
            case 2 :
                {
                    int choice;
                    do
                    {
                        afficherMenuExport();
                        std::cin >> choice;
                        std::cin.ignore();

                        switch (choice)
                        {
                            case 1 :
                                {
                                    std::string chemin;
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterStatistiquesEnTxt(*this,chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 2 :
                                {
                                    std::string chemin;
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterStatistiquesEnCsv(*this, chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 3 :
                                {
                                    break;
                                }
                            default :
                                {
                                    std::cout << "[ERREUR] Choix invalide.\n" << std::endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    break;
                                }
                        }
                    } while (choice != 3);
                    break;
                }
            case 3 :
                {
                    int choice;
                    do
                    {
                        afficherMenuExport();
                        std::cin >> choice;
                        std::cin.ignore();
                        switch (choice)
                        {
                            case 1 :
                                {
                                    std::string chemin;
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterTousLesPatientsEnTxt(*this, chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 2 :
                                {
                                    std::string chemin;
                                    std::cout << "Chemin d'expotation : ";
                                    std::getline(std::cin, chemin);
                                    if (chemin == "0")
                                    {
                                        std::cout << "\nQuitter...\n";
                                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                                        break;
                                    }
                                    ImportExport::exporterTousLesPatientsEnCsv(*this, chemin);
                                    pauseConsole();
                                    break;
                                }
                            case 3 :
                                {
                                    break;
                                }
                            default :
                                {
                                    std::cout << "[ERREUR] Choix invalide.\n" << std::endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    break;
                                }
                        }
                    } while (choice != 3);
                    break;
                }
            case 4 :
                {
                    nettoyerEcran();
                    std::cout << "\t Pour quitter entrez 0\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::string chemin;
                    std::cout << "Chemin du fichier CSV : ";
                    std::getline(std::cin, chemin);
                    if (chemin == "0")
                    {
                        std::cout << "\nQuitter...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                        break;
                    }
                    ImportExport::importerPatients(chemin, *this);
                    pauseConsole();
                    break;
                }
            case 5 :
                break;
            default :
                {
                    std::cout << "[ERREUR] Choix invalide.\n" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    break;
                }
        }
    } while (choix != 5);
}



void Systeme::afficherMenuExport()
{
    nettoyerEcran();
    std::cout << "\tPour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "1. Exporter au format .txt\n";
    std::cout << "2. Exporter au format .csv\n";
    std::cout << "3. Retour\n\n";
    std::cout << "Votre choix : ";
}


        // Accesseurs pour les statistiques
int Systeme::getNombrePatients() const
{
    return m_patients.size();
}



int Systeme::getNombreProfessionnels() const
{
    return m_professionnels.size();
}



int Systeme::getNombreAdmins() const
{
    return m_admins.size();
}



int Systeme::getNombreConsultations() const
{
    int total = 0;
    for (const auto& d : m_dossiers)
        total += d.getConsultations().size();
    return total;
}



int Systeme::getNombreAntecedents() const
{
    int total = 0;
    for (const auto& d : m_dossiers)
        total += d.getAntecedents().size();
    return total;
}



int Systeme::getNombrePrescriptions() const
{
    int total = 0;
    for (const auto& d : m_dossiers) total += d.getPrescriptions().size();
    return total;
}



const std::vector<Patient>& Systeme::getPatients() const
{
    return m_patients;
}




void Systeme::ajouterPatient(const Patient& p)
{
    m_patients.push_back(p);
    creerDossierMedical(p.getIdPatient());
}



void Systeme::afficherDossiersArchives() const
{
    nettoyerEcran();
    std::cout << "\n" + std::string(50, '=') + " Dossiers archives " + std::string (50, '=') << "\n";
    bool aucunDossier = true;
    for (const auto& dossier : m_dossiers)
    {
        if (dossier.estArchive())
        {
            std::cout << "Patient # " << dossier.getIdPatient() << "\n";
            dossier.afficherResumeDossier();
            std::cout << "\n--------------------------\n" << std::endl;
            aucunDossier = false;
        }
    }

    if (aucunDossier)
    {
        std::cout << "[INFO] Aucun dossier dans les archives.\n";
    }
}




 void Systeme::afficherRdvProfessionnel(int idPro) const
 {
     nettoyerEcran();
     std::cout << "\n--- Vos rendez-vous ---\n";
     bool aucunRDV = true;

     for (const auto& rdv : m_rendezVous)
     {
         if (rdv.getIdProfessionnel() == idPro)
         {
             rdv.afficherRDV();
             aucunRDV = false;
         }
     }
     if (aucunRDV)
     {
         std::cout << "Aucun rendez-vous planifie.\n";
     }
 }




void Systeme::accorderHabilitation()
{
    nettoyerEcran();
    std::cout << "\tPour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::string nom, prenom;
    char choix;
    std::cout << "Entrez le nom de l'admin : ";
    std::getline(std::cin,nom);
    if (nom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Entrez le prenom de l'admin : ";
    std::getline(std::cin, prenom);
    if (prenom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    for (Administrateur& admin : m_admins)
    {
        if (admin.getNom() == nom && admin.getPrenom() == prenom)
        {
            if (admin.getAutorisation())
            {
                std::cout << "Habilitation deja accordee a l'administrateur " << nom << " " << prenom << std::endl;
                return;
            }
            bool repeter = true;
            while (repeter)
            {
                std::cout << "Etes-vous sur(e) de vouloir accorder une habilitation a l'administrateur " << nom << " " << prenom << " ? (o/n) : ";
                std::cin >> choix;

                if (choix == 'o' || choix == 'O')
                {
                    admin.setAutorisation(true);
                    std::cout << "\nHabilitation accordee avec succes" << std::endl;
                    repeter = false;
                    return;
                }
                else if (choix == 'n' || choix == 'N')
                    repeter = false;
                else
                    continue;
            }
        }
        else
        {
            std::cout << "L' administrateur " << nom << " " << prenom << " n'est pas repertorie\n";
            return;
        }
    }
}



void Systeme::retirerHabilitation()
{
    nettoyerEcran();
    std::cout << "\tPour quitter entrez 0\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::string nom, prenom;
    char choix;
    std::cout << "Entrez le nom de l'admin : ";
    std::getline(std::cin,nom);
    if (nom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }
    std::cout << "Entrez le prenom de l'admin : ";
    std::getline(std::cin, prenom);
    if (prenom == "0")
    {
        std::cout << "\nQuitter...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        return;
    }

    for (Administrateur& admin : m_admins)
    {
        if (admin.getNom() == nom && admin.getPrenom() == prenom)
        {
            bool repeter = true;
            while (repeter)
            {
                std::cout << "Etes-vous sur(e) de vouloir retirer l'habilitation speciale a l'administrateur " << nom << " " << prenom << " ? (o/n) : ";
                std::cin >> choix;
                std::cin.ignore();

                if (choix == 'o' || choix == 'O')
                {
                    admin.setAutorisation(false);
                    std::cout << "\nHabilitation revoquer avec succes" << std::endl;
                    repeter = false;
                    return;
                }
                else if (choix == 'n' || choix == 'N')
                    repeter = false;
                else
                    continue;
            }
        }
    }
    std::cout << "L' administrateur " << nom << " " << prenom << " n'est pas repertorie\n";
}




void Systeme::afficherAdministrateursHabilites() const
{
    nettoyerEcran();
    std::cout << "LISTE DES ADMINISTRATEURS AYANT UNE HABILITATION SPECIALE\n";
    bool aucunAdmin = true;
    for (const auto& admin : m_admins)
    {
        if (admin.getAutorisation() == true)
        {
            std::cout << std::left
                      << std::setw(5)  << "Administrateur #"
                     << std::setw(40) << "Nom Complet"
                     << "\n";

            std::cout << std::string(100, '-') << "\n";

            // Lignes
            std::cout << std::left
                      << std::setw(5)  << admin.getIdUser()
                      << std::setw(40) << admin.getNomComplet()
                      << "\n";
            std::cout << std::string(100, '-') << "\n";
            aucunAdmin = false;
        }
    }
    if (aucunAdmin)
    {
        std::cout << "\nAucun administrateur n'a une habilitation speciale\n";
    }
}



void Systeme::afficherRoles() const
{
    std::cout << "\n";
    std::cout << "1. MEDECIN GENERALE\n";
    std::cout << "2. MEDECIN SPECIALISTE\n";
    std::cout << "3. INFIRMIER\n";
    std::cout << "4. PHARMACIEN\n";
    std::cout << "5. SAGE FEMME\n";
    std::cout << "6. DENTISTE\n";
    std::cout << "7. TECHNICIEN LABORATOIRE\n";
    std::cout << "8. RADIOLOGUE\n\n";
}


void Systeme::afficherSpecialites() const
{
    std::cout << "\n";
    std::cout << "1. MEDECINE GENERALE\n";
    std::cout << "2. PEDIATRIE\n";
    std::cout << "3. ORL\n";
    std::cout << "4. OPHTALMOLOGIE\n";
    std::cout << "5. CARDIOLOGIE\n";
    std::cout << "6. GYNECOLOGIE\n";
    std::cout << "7. NEUROLOGIE\n";
    std::cout << "8. CHIRURGIE\n";
    std::cout << "9. PSYCHIATRIE\n";
    std::cout << "10. DENTISTION\n";
    std::cout << "11. ANESTHESIE\n";
    std::cout << "12. PRHARMACIE\n";
    std::cout << "13. ACCOUCHEMENT\n";
    std::cout << "14. DERMATOLOGIE";
    std::cout << "15. PNEUMOLOGIE\n";
    std::cout << "16. ORTHOPEDIE\n";
    std::cout << "17. RADIOLOGIE\n";
    std::cout << "18. ANALYSE BIO MEDICALE\n\n";
}






 // ---Menu principal----
void Systeme::lancerMenu()
{
    if (!m_utilisateurConnecte)
    {
        std::cout << "Aucun utilisateur authentifie. Veuillez vous connecter.\n";
        pauseConsole();
        return;
    }

    bool quitter = false;

    while(!quitter)
    {
        m_utilisateurConnecte -> afficherMenu();
        std::cout << "Votre choix : ";
        int choix;
        std::cin >> choix;
        if (std::cin.fail())
        {
             std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERREUR] Entree invalide, veuillez entrer un chiffre." << std::endl;
            continue;
        }
        std::cin.ignore();

        // Dispatcing des fonctions metiers selon le rôle/menu
        if (m_utilisateurConnecte -> getRole() == "Administrateur")
        {
            switch (choix)
            {
                case 1 :
                    {
                        menuGestionUtilisateurs();
                        break;
                    }
                case 2 :
                    {
                        menuConsultationDossier(m_utilisateurConnecte);
                        pauseConsole();
                        break;
                    }
                case 3 :
                    {
                        menuArchivageDossiers();
                        pauseConsole();
                        break;
                    }
                case 4 :
                    {
                        afficherDossiersArchives();
                        pauseConsole();
                        break;
                    }
                case 5 :
                    {
                        afficherStatistiques();
                        pauseConsole();
                        break;
                    }
                case 6 :
                    {
                        menuImportExport();
                        break;
                    }
                case 0 :
                    {
                        quitter = true;
                        std::cout << "\n";
                        std::cout << "Deconnexion administrateur...\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    }
                default:
                    {
                        std::cout << "\n";
                        std::cout << "[ERREUR] Choix invalide.\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        break;
                    }
            }
        }
        else
        {
            switch (choix)
            {
                case 1 :
                    {
                        menuInscriptionPatient();
                        pauseConsole();
                        break;
                    }
                case 2 :
                    {
                        afficherTousPatients();
                        pauseConsole();
                        break;
                    }
                case 3 :
                    {
                        menuRechercherPatient();
                        pauseConsole();
                        break;
                    }
                case 4 :
                    {
                        menuConsultationDossier(m_utilisateurConnecte);
                        pauseConsole();
                        break;
                    }
                case 5:
                    {
                        menuCreerConsultation();
                        pauseConsole();
                        break;
                    }
                case 6:
                    {
                        menuAjouterAntecedent();
                        pauseConsole();
                        break;
                    }
                case 7 :
                    {
                        menuAjouterPrescriptions();
                        pauseConsole();
                        break;
                    }
                case 8:
                    {
                        afficherAdministrateursHabilites();
                        pauseConsole();
                        break;
                    }
                case 9 :
                    {
                        accorderHabilitation();
                        pauseConsole();
                        break;
                    }
                case 10 :
                    {
                        retirerHabilitation();
                        pauseConsole();
                        break;
                    }
                case 11 :
                    {
                        menuAgendaProfessionnel();
                        break;
                    }
                case 0 :
                    {
                        std::cout << "\n";
                        quitter = true;
                        std::cout << "Deconnexion professionnel...\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    }
                default :
                    {
                        std::cout << "\n";
                        std::cout << "[ERREUR] Choix invalide.\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        break;
                    }
            }
        }
    }
}
