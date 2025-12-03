#include "Date.h"
#include <regex>



void Date::validerFormat(const std::string& date)
{
    if (date.length() != 10)
    {
        throw std::invalid_argument("La date doit etre au format DD-MM-YYYY ou DD/MM/YYYY");
    }

    if (date[2] != '-' || date[2] != '/' || date[5] != '-' || date[5] != '/')
    {
        throw std::invalid_argument("Separateurs invalides. Format attendu : DD-MM-YYYY ou DD/MM/YYYY.");
    }

    std::string jour = date.substr(0,2);
    std::string mois = date.substr(3,2);
    std::string annee = date.substr(6,4);

    if (!estValide(jour) || !estValide(mois) || !estValide(annee))
    {
        throw std::invalid_argument("La date contient des caracteres non numeriques. Veuillez respecter le format préciser");
    }

    int an = std::stoi(annee);
    int m = std::stoi(mois);
    int j = std::stoi(jour);

    if (an < 1900 || an > 2100)
    {
        throw std::invalid_argument("Annee invalide (doit etre entre 1900 et 2100).");
    }
    if (m < 1 || m > 12)
    {
        throw std::invalid_argument("Mois invalide (doit etre entre 01 et 12).");
    }

    int joursParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Gestion des années bissextile
    if ((an % 4 == 0 && an % 100 != 0) || (an % 400 == 0))
    {
        joursParMois[1] = 29;
    }

    if (j < 1 || j > joursParMois[m-1])
    {
        throw std::invalid_argument("Jour invalide pour ce mois.");
    }
}



void Date::validerHeure(const std::string& heure)
{
    if (heure.length() != 5)
    {
        throw std::invalid_argument("L'heure doit etre au format HH:MM.");
    }

    if (heure[2] != ':')
    {
        throw std::invalid_argument("Separateur invalide. Format attendu : HH:MM");
    }

    std::string heures = heure.substr(0,2);
    std::string minutes = heure.substr(3,2);

    if (!estValide(heures) || !estValide(minutes))
    {
        throw std::invalid_argument("L'heure contient des caracteres non numeriques. Veuillez respecter le format impose.");
    }

    int h = std::stoi(heures);
    int mint = std::stoi(minutes);

    if (h < 0 || h > 23)
        throw std::invalid_argument("Heures invalides (doit etre entre 00 et 23).");

    if (mint < 0 || mint > 59)
    {
        throw std::invalid_argument("Minutes invalides (doit etre entre 00 et 59).");
    }
}



bool Date::estValide(const std::string& str)
{
    if (str.empty())
        return false;
    for (char c : str)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}
