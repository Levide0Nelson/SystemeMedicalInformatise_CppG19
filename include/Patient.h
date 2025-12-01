#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>

/** Classe Patient : Représente  un patient du système
*/


class Patient
{
    public:
        // Constructeur
        Patient(int idPatient, const std::string& nomPatient, const std::string& prenomPatient, const std::string& dateNaissance,
                 const std::string& genre, const std::string& adresse, const std::string& telephone, const std::string& email);

        ~Patient();

        // Acesseurs
        int getIdPatient() const;
        std::string getNomPatient() const;
        std::string getPrenomPatient() const;
        std::string getDateDeNaissance() const;
        std::string getGenre() const;
        std::string getAdresse() const;
        std::string getTelephone() const;
        std::string getEmail() const;

        // Mutateurs
        void setNomPatient(const std::string& nom);
        void setPrenomPatient(const std::string& prenom);
        void setDateDeNaissance(const std::string& date);
        void setGenre(const std::string& genre);
        void setAdresse(const std::string& adresse);
        void setTelephone(const std::string& telephone);
        void setEmail(const std::string& email);

        std::string toCSV() const;
        static Patient fromCSV(const std::string& line);

        void afficherInfos() const;

    protected:

    private:
        int m_idPatient;
        std::string m_nomPatient;
        std::string m_prenomPatient;
        std::string m_dateDeNaissance; // Format JJ/MM/AAAA
        std::string m_genre;
        std::string m_adresse;
        std::string m_telephone;
        std::string m_email;

};

#endif // PATIENT_H
