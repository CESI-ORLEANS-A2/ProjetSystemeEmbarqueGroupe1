#ifndef Acquisition_h
#define Acquisition_h

#include "main.hpp"

/**
 * @brief Stocke le timestamp du début de la dernière acquisition
 * 
 * Cette variable permet à la fois de savoir si la dernière acquisition
 * est a plus de x secondes pour pouvoir en relancer une et de savoir si 
 * l'acquisition en cours ne dépasse pas une durée maximale.
*/
extern unsigned long previousAcquisition;
/**
 * @brief Nombre d'erreur restantes dans l'acquisition en cours.
 * 
 * L'acquisition démarre avec un nombre d'erreur équivalent au nombre de capteurs disponibles.
 * À chaque fois qu'un capteur réussi à acquérir une donnée, le nombre d'erreur est décrémenté. 
 * Lorsque le nombre d'erreur atteint 0, l'acquisition est terminée. 
*/
extern int numberOfErrors;
#if GPS_ENABLED
/**
 * @brief Indique si le GPS est en erreur.
*/
extern bool GPSError;
#endif
/**
 * @brief Indique si l'horloge est en erreur.
*/
extern bool clockError;
/**
 * @brief Tableau de booléens indiquant si un capteur a réussi à acquérir une donnée.
 * 
 * Ce tableau est initialisé à true pour chaque capteur au début de l'acquisition.
 * L'acquisition continue tant qu'il reste au moins une erreur sauf si la durée d'acquisition
 * dépasse une valeur maximale.
 * 
 * La taille de ce tableau est repportée dans la variable 
 * @ref numberOfSensors
 * .
*/
extern bool errors[NUMBER_OF_SENSORS];
/**
 * @brief Indique si une acquisition est en cours.
 * 
 * La fonction acquisition est exécutée à chaque cycle de la boucle 
 * @ref loop
 * , peut importe si une acquisition est en cours ou non et si des capteurs sont en erreur.
 * Cette variable permet alors de faire la distinction entre une acquisition en cours et 
 * une acquisition finie.
*/
extern bool underAcquisition;

#if GPS_ENABLED
/**
 * @brief Compteur pour le GPS. Permet de ne pas acquérir le GPS à chaque cycle en mode économique.
*/
extern int GPSCounter;
#endif

/**
 * @brief Fonction d'acquisition des données.
 * 
 * Cette fonction est exécutée à chaque cycle de la boucle. 
 * Elle permet d'acquérir les données de chaque capteur et de les stocker dans le tableau
 * @ref lastMeasurements
 * . 
 * 
 * L'acquisition est réalisée uniquement si 
 * @ref underAcquisition
 * est à true sinon la fonction démarre une autre acquisition si le delais avec la précédente est assez
 * long.
 * 
 * L'acquisition continue tant qu'il reste au moins une erreur sauf si la durée d'acquisition
 * dépasse une valeur maximale.
*/
void acquisition(void (*callback)());

#endif