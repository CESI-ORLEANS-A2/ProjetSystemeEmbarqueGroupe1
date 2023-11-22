#include "consts.hpp"
#include <ChainableLED.h>
#include "timer.hpp"
#include "mode.hpp"

/**
 * @brief Instance de la classe ChainableLED représentant la LED
*/
extern ChainableLED led;
/**
 * @brief Compteur de cycle d'activation de la LED
 * 
 * Quand on fait clignoter une LED, on veut que la LED soit d'une couleur autre que rouge
 * pendant un nombre de cycle de 1 seconde défini par cette variable.
 * 
 * Cette variable prend les valeurs :
 *  - 0 : Allumé en une couleur autre que rouge
 *  - 1 : Allumé en rouge
 * ou
 *  - 0 : Allumé en une couleur autre que rouge
 *  - 1 : On laisse la LED sur la couleur précédente (autre que rouge)
 *  - 2 : Allumé en rouge
*/
extern int LEDCounter;

/**
 * @brief Initialise la LED
*/
void initLED();
/**
 * @brief Allume la LED en rouge
*/
void switchLEDToRed();
/**
 * @brief Allume la LED en vert
*/
void switchLEDToGreen();
/**
 * @brief Allume la LED en bleu
*/
void switchLEDToBlue();
/**
 * @brief Allume la LED en jaune
*/
void switchLEDToYellow();
/**
 * @brief Allume la LED en orange
*/
void switchLEDToOrange();
/**
 * @brief Allume la LED en blanc
*/
void switchLEDToWhite();
/**
 * @brief Allume la LED en violet
*/
void switchLEDToPurple();
/**
 * @brief La LED passe successivement du rouge au bleu avec une fréquence de 1 seconde
 * 
 * Correspond à l'erreur d'accès à l'horloge.
 * 
 * L'erreur est bloquante.
*/
void switchLEDToRedBlue();
/**
 * @brief La LED passe successivement du rouge au jaune avec une fréquence de 1 seconde
 * 
 * Correspond à l'erreur d'accès au GPS.
 * 
 * L'erreur est bloquante.
*/
void switchLEDToRedYellow();
/**
 * @brief La LED passe successivement du rouge au vert avec une fréquence de 1 seconde
 * 
 * Correspond à l'erreur d'accès aux données d'un capteur.
 * 
 * L'erreur est bloquante. 
*/
void switchLEDToRedGreen();
/**
 * @brief La LED passe successivement du rouge au vert. La LED reste rouge pendant 1 seconde puis passe au vert pendant 2 seconde.
 * 
 * Correspond à la réception de données incohérentes d'un capteur.
 * 
 * L'erreur est bloquante.
*/
void switchLEDToRed2Green();
/**
 * @brief La LED passe successivement du rouge au blanc avec une fréquence de 1 seconde.
 * 
 * Correspond à l'erreur : carte SD pleine.
 * 
 * L'erreur est bloquante.
*/
void switchLEDToRedWhite();
/**
 * @brief La LED passe successivement du rouge au blanc. La LED reste rouge pendant 1 seconde puis passe au blanc pendant 2 seconde.
 * 
 * Correspond à l'erreur : Accès ou écriture sur la carte SD impossible.
 * 
 * L'erreur est bloquante.
*/
void switchLEDToRed2White();

/**
 * @brief Initialise la boucle de clignotement de la LED.
 * 
 * ⚠️ Cette fonction est bloquante. Elle ne retourne jamais.
 * TODO Faire en sorte que cette fonction ne soit pas bloquante
 * 
 * @param switchLED Fonction qui change la couleur de la LED (autre que rouge)
 * @param factor Nombre de cycle de 1 seconde avant de changer la couleur de la LED 
*/
void initLEDLoop(void (*switchLED)(), const int factor);

/**
 * @brief Nombre de cycle de 1 seconde avant de changer la couleur de la LED
 * 
 * Exemple : 
 * Si la fréquence est de 1 seconde et que le facteur est de 2, la LED sera allumée 
 * d'une couleur pendant 1 seconde puis d'une autre pendant 2 secondes.
*/
extern int LEDFactor;
/**
 * @brief Fréquence de clignotement de la LED
*/
extern unsigned long LEDfrequency;
/**
 * @brief Fonction qui change la couleur de la LED
*/
extern void (*color1)();
/**
 * @brief Fonction qui change la couleur de la LED
*/
extern void (*color2)();
/**
 * @brief Fonction appelée à la fin de la boucle de clignotement de la LED
*/
extern void (*LEDcallback)();

/**
 * @brief Fonction exécutée à chaque interruption du timer 2
*/
void LEDInterrupt();

/**
 * @brief Fait clignoter la LED en alternant entre deux couleurs avec une fréquence de 1 secondes pendant duration secondes.
 * 
 * @param switchLED1 Fonction qui change la couleur de la LED
 * @param switchLED2 Fonction qui change la couleur de la LED
 * @param factor Nombre de cycle de 1 seconde avant de changer la couleur de la LED
 * @param duration Durée en secondes pendant laquelle la LED clignote
 * @param frequency Fréquence de clignotement de la LED
*/
void initLEDTimer(void (*switchLED1)(), void (*switchLED2)(), int factor, unsigned long duration, unsigned long frequency);

/**
 * @brief Arrête le clignotement de la LED
*/
void stopLEDTimer();

#define LEDTimerIsRunning() isTimer2Running()