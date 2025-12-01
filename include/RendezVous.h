#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <string>

/** Classe RendezVous : Permet l'affichage, la création, la modification ou la suppression des rendez-vous par les professionnels de santé
*/

class RendezVous
{
    public:
        // Constructeur
        RendezVous(int idRDV, int idPatient, int idProfessionnel, const std::string& date, const std::string& heure, const std::string& motif);

        // Acccesseurs
        int getIdRDV() const;
        int getIdPatient() const;
        int getIdProfessionnel() const;
        std::string getDate() const;
        std::string getHeure() const;
        std::string getMotif() const;

        // Mutateurs
        void setDate(const std::string& date);
        void setHeure(const std::string& heure);
        void setMotif(const std::string& motif);

        // Méthodes pour l'écriture et la lecture dans le fichier CSV correspondant
        std::string toCSV() const;
        static RendezVous fromCSV(const std::string& ligne);

        // Méthode pour l'affichage
        void afficherRDV() const;

    protected:

    private:
        int m_idRDV;
        int m_idPatient;
        int m_idProfessionnel;
        std::string m_date;
        std::string m_heure;
        std::string m_motif;
};

#endif // RENDEZVOUS_H
