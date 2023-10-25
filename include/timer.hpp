#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

/**
 * @brief Représente le nombre de fois que l'interruption du timer doit être déclenchée
 *
 * Cette variable est définie à une valeur calculée à partir de la fréquence d'horloge, du prédiviseur et du délais attendu?
 * Elle est décrémentée à chaque interruption du timer. Lorsqu'elle atteint 0, le timer est arrêté.
 */
extern int counter;
/**
 * @brief Fonction exécutée à la fin du délais.
 */
extern void (*callback)();
/**
 * @brief Représente le nombre de microsecondes restantes après les counter premières interruptions.
 * 
 * Cette variable déterminée à partir de la fréquence d'horloge, du prédiviseur, du délais attend et des counter interruptions.
 * Elle permet de créer une nouvelle instance du timer avec le délais restant.
 */
extern unsigned long remains;

/** 
 * @brief Initialise le timer
 */
void initTimer();
/**
 * @brief Crée une nouvelle instance du timer
 * 
 * @param delay Le délais en microsecondes
 * @param handler La fonction à exécuter à la fin du délais
 * 
 * @ref callback
 * @ref counter
 * @ref remains
 */
void createTimer(long delay, void (*handler)());
/**
 * @brief Arrête le timer
 */
void stopTimer();

#endif