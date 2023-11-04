#include "modes/economy.hpp"

void switchToEconomyMode() {
    previousMode = mode;
    mode = ECONOMY_MODE;

    switchLEDToBlue();
};
void quitEconomyMode() {
    
}
void runEconomyModeStep() {
    // Acquisition des données
    // Si l'acquisition est terminée (la fonction acquisition renvoie true), 
    // on sauvegarde les données dans un fichier
    if (acquisition()) saveData();
};

