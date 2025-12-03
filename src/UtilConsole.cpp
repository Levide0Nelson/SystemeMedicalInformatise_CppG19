#include "UtilConsole.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <functional> // Pour le hachage des mots de passe qui est plus sécurisé
#include <cctype>    // Pour la verification entiere
#include <vector>

void pauseConsole()
{
    std::cout << "\nAppuyez sur <<Enter>> pour continuer...\n";
    std::string tmp;
    std::getline(std::cin, tmp);
}

void nettoyerEcran()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}


// std::hash n'est pas un vrai hash de mot de passe sécurisé.
// C'est une simplification que j'ai utilisé pour le stockage des mots de passe pour ce projet

std::string hashMotDePasse(const std::string& motDePasse)
{
    std::hash<std::string> hasher;
    auto h = hasher(motDePasse);
    return std::to_string(h);
}


bool numAssuranceEstValide(const std::string& numAssurance)
{
    for (char c : numAssurance)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    if (numAssurance.length() < 8)
    {
        return false;
    }
    return true;
}

