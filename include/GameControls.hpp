#pragma once

#include <iostream>

/********************************
 *        Game Controls       *
 ********************************/

inline void displayControls()
{
	std::cout << std::endl;

	std::cout << "/////////////////////////////////////////////////" << std::endl;
    std::cout << "///////////////  COMMANDES DU JEU  //////////////" << std::endl;
    std::cout << "/////////////////////////////////////////////////" << std::endl;
    std::cout << "Déplacer la caméra :  - Haut    : Z" 	 			 << std::endl;
    std::cout << "                      - Bas     : S" 				 << std::endl;
    std::cout << "                      - Tourner : Souris"          << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "Déplacer le curseur : - Haut   : Flèche du haut"   << std::endl;
    std::cout << "                      - Bas    : Flèche du bas"    << std::endl;
    std::cout << "                      - Gauche : Flèche de gauche" << std::endl;
    std::cout << "                      - Droite : Flèche de droite" << std::endl;
    std::cout << "                      - Fond   : P"                << std::endl;
    std::cout << "                      - Avant  : M"                << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << "Manipuler les cubes : - Ajouter   : Barre espace"  << std::endl;
    std::cout << "                      - Supprimer : Suppr"         << std::endl;
    std::cout << "                      - Extrude   : E"             << std::endl;
    std::cout << "                      - Dig       : D"             << std::endl;
    std::cout << "/////////////////////////////////////////////////" << std::endl;

    std::cout << std::endl;
};