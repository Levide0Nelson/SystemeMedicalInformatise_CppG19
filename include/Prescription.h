#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>

class Prescription
{
    public:
        Prescription(int idPrescription, int idConsultation, const std::string& date, const std::string& contenu, const std::string& remarque);

        // Accesseurs
        int getIdPrescription() const;
        int getIdConsultation() const;
        std::string getDate() const;
        std::string getContenu() const;
        std::string getRemarque() const;

        std::string toCSV() const;
        static Prescription fromCSV(const std::string& ligne);

        void afficherDetailsPrescription() const;

    protected:

    private:
        int m_idPrescription;
        int m_idConsultation;
        std::string m_date;
        std::string m_contenu;
        std::string m_remarque;  // Infos complémentaires comme la posologie,...
};

#endif // PRESCRIPTION_H
