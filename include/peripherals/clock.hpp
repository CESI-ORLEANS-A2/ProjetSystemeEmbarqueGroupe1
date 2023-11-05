#ifndef Clock_h
#define Clock_h

#include <DS1307.h>

/**
 * @brief Instance de la classe DS1307 représentant l'horloge
*/
extern DS1307 clock;

/**
 * @brief Initialise l'horloge
*/
#define initClock() clock.begin()
/**
 * @brief Lit l'heure et la date actuelle de l'horloge
*/
#define readClock() clock.getTime()

/**
 * @brief Récupère l'heure actuelle
*/
#define getHour() clock.hour
/**
 * @brief Récupère les minutes actuelles
*/
#define getMinute() clock.minute
/**
 * @brief Récupère les secondes actuelles
*/
#define getSecond() clock.second
/**
 * @brief Récupère le jour actuel
*/
#define getDay() clock.dayOfMonth
/**
 * @brief Récupère le mois actuel
*/
#define getMonth() clock.month
/**
 * @brief Récupère l'année actuelle
*/
#define getYear() clock.year
/**
 * @brief Récupère l'année actuelle (format complet : 2020 au lieu de 20)
*/
#define getYearFull() clock.year + 2000
/**
 * @brief Récupère le jour de la semaine actuel
 * 
 * 1 = Lundi, 2 = Mardi, ..., 7 = Dimanche
*/
#define getDayOfWeek() clock.dayOfWeek

/**
 * @brief Définit l'heure actuelle
*/
void setHour(int hour);
/**
 * @brief Définit les minutes actuelles
*/
void setMinute(int minute);
/**
 * @brief Définit les secondes actuelles
*/
void setSecond(int second);
/**
 * @brief Définit le jour actuel
*/
void setDay(int day);
/**
 * @brief Définit le mois actuel
*/
void setMonth(int month);
/**
 * @brief Définit l'année actuelle
*/
void setYear(int year);
/**
 * @brief Définit l'année actuelle (format complet : 2020 au lieu de 20)
*/
void setYearFull(int year);
/**
 * @brief Définit le jour de la semaine actuel
 * 
 * 1 = Lundi, 2 = Mardi, ..., 7 = Dimanche
*/
void setDayOfWeek(int dayOfWeek);

#endif // Clock_h