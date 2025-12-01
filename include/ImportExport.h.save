#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <string>


class Systeme;

class ImportExport
{
    public:
        // Export en .txt
        static void exporterDossierPatientEnTxt(int idPatient, Systeme& systeme, const std::string& chemin);
        static void exporterStatistiquesEnTxt(Systeme& systeme, const std::string& chemin);
        static void exporterTousLesPatientsEnTxt(Systeme& systeme, const std::string& chemin);

        // Export en .csv
        static void exporterDossierPatientEnCsv(int idPatient, Systeme& systeme, const std::string& chemin);
        static void exporterStatistiquesEnCsv(Systeme& systeme, const std::string& chemin);
        static void exporterTousLesPatientsEnCsv(Systeme& systeme, const std::string& chemin);

        // Import
        static void importerPatients(const std::string& cheminFichier, Systeme& systeme);

    protected:

    private:

        static std::string obtenirDateActuelle();
        static bool fichierExiste(const std::string& chemin);
};

#endif // IMPORTEXPORT_H
