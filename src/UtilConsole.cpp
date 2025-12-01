#include "UtilConsole.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <functional> // Pour le hachage des mots de passe qui est plus sécurisé

void pauseConsole()
{
    std::cout << "\nAppuyez sur <<Enter>> pour continuer...";
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
