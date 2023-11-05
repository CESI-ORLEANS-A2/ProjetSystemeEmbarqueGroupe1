#ifndef Timer_h
#define Timer_h

#include <Arduino.h>
#include "consts.hpp"

/**
 * @brief Représente le nombre de fois que l'interruption du timer doit être déclenchée
 *
 * Cette variable est définie à une valeur calculée à partir de la fréquence d'horloge, du prédiviseur et du délais attendu?
 * Elle est décrémentée à chaque interruption du timer. Lorsqu'elle atteint 0, le timer est arrêté.
 */
extern int counter1;
/**
 * @brief Fonction exécutée à la fin du délais.
 */
extern void (*callback1)();
/**
 * @brief Représente le nombre de microsecondes restantes après les counter1 premières interruptions.
 * 
 * Cette variable déterminée à partir de la fréquence d'horloge, du prédiviseur, du délais attend et des counter1 interruptions.
 * Elle permet de créer une nouvelle instance du timer avec le délais restant.
 */
extern unsigned long remains1;

/** 
 * @brief Initialise le timer
 */
void initTimer1();
/**
 * @brief Crée une nouvelle instance du timer
 * 
 * @param delay Le délais en microsecondes
 * @param handler La fonction à exécuter à la fin du délais
 * 
 * Références : 
 * @ref callback1
 * @ref counter1
 * @ref remains1
 */
void createTimer1(long delay, void (*handler)());
/**
 * @brief Arrête le timer
 */
void stopTimer1();

/**
 * @brief Vérifie si le timer 1 est en cours d'exécution
*/
#define isTimer1Running() TIMSK1 & (1 << OCIE1A) != 0

/**
 * @brief Représente le nombre de fois que l'interruption du timer doit être déclenchée
 *
 * Cette variable est définie à une valeur calculée à partir de la fréquence d'horloge, du prédiviseur et du délais attendu?
 * Elle est décrémentée à chaque interruption du timer. Lorsqu'elle atteint 0, le timer est arrêté.
 */
extern int counter2;
/**
 * @brief Fonction exécutée à la fin du délais.
 */
extern void (*callback2)();
/**
 * @brief Représente le nombre de microsecondes restantes après les counter1 premières interruptions.
 * 
 * Cette variable déterminée à partir de la fréquence d'horloge, du prédiviseur, du délais attend et des counter1 interruptions.
 * Elle permet de créer une nouvelle instance du timer avec le délais restant.
 */
extern unsigned long remains2;

/** 
 * @brief Initialise le timer
 */
void initTimer2();
/**
 * @brief Crée une nouvelle instance du timer
 * 
 * @param delay Le délais en microsecondes
 * @param handler La fonction à exécuter à la fin du délais
 * 
 * Références : 
 * @ref callback1
 * @ref counter1
 * @ref remains1
 */
void createTimer2(long delay, void (*handler)());
/**
 * @brief Arrête le timer
 */
void stopTimer2();
/**
 * @brief Vérifie si le timer 2 est en cours d'exécution
*/
#define isTimer2Running() TIMSK2 & (1 << OCIE2A) != 0

#endif