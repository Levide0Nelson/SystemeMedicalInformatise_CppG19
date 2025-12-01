#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>


/** Classe Consultation : Contient toutes les infos liées à une consultation médicale
*/

class Consultation
{
    public:
        // Constructeurs
        Consultation(int idConsultation, const std::string& date, const std::string& motif,
                     const std::string& observations, int idPatient, const std::string& nomCompletPro);

        // Accesseurs
        int getIdConsultation() const;
        std::string getDate() const;
        std::string getMotif() const;
        std::string getObservations() const;
        int getIdPatient() const;
        std::string getNomCompletPro() const;
        // Mutateurs
        void setDate(const std::string& date);
        void setMotif(const std::string& motif);
        void setObservations(const std::string& observations);

        std::string toCSV() const;
        static Consultation fromCSV(const std::string& line);

        void afficherDetailsConsultation() const;

    protected:

    private:
        int m_idConsultation;
        std::string m_dateConsultation;
        std::string m_motif;
        std::string m_observations;
        int m_idPatient;
        std::string m_nomCompletPro;
};

#endif // CONSULTATION_H
