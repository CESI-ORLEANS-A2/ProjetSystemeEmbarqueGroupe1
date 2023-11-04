#include "modes/standard.hpp"

void switchToStandardMode() {
    previousMode = mode;
    mode = STANDARD_MODE;
    switchLEDToGreen();
};
void quitStandardMode() {

}
void runStandardModeStep() {
    // Acquisition des données
    // Si l'acquisition est terminée (la fonction acquisition renvoie true),
    // on sauvegarde les données dans un fichier
    if (acquisition()) saveData();
};
