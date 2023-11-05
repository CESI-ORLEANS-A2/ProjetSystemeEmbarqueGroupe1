#ifndef Consts_h
#define Consts_h

#include <Arduino.h>

/**
 * @brief Version du logiciel
*/
#define VERSION F("0.1.0")

// ACTIVER/DESACTIVER DES FONCTIONNALITES
/**
 * @brief Si l'interpréteur doit être activé
 *
 * Si cette variable est à true, l'interpréteur sera activé.
 * L'interpréteur permet d'envoyer des commandes à la station météo
 * depuis le port série.
 * Cependant, l'interpréteur prend beaucoup de place en mémoire
 * et peut donc être désactivé pour gagner de la place.
 *
 * Si l'interpréteur est désactivé, il ne sera pas compilé.
 */
#define INTERPRETER false 
/**
 * @brief Si la commande help doit afficher les détails des commandes
 *
 * Si cette variable est à true, la commande help affichera les détails
 * de chaque commande. Sinon, elle affichera uniquement la liste des
 * commandes disponibles.
 * Les détails d'une commande sont sa description, sa syntax et ses arguments.
 * Cependant, afficher les détails prend beaucoup de place en mémoire Flash.
 */
#define DETAILED_HELP_COMMAND false 
/**
 * @brief Si les paramètres de la station doivent être sauvegardés dans l'EEPROM.
 * 
 * Actuellement non fonctionnel.
*/
#define SETTINGS_IN_EEPROM false
/**
 * @brief Si le GPS doit être activé
*/
#define GPS_ENABLED false
/** 
 * @brief Le format de sortie dans le port série est du JSON 
*/
#define OUTPUT_JSON 0
/** 
 * @brief Le format de sortie dans le port série est du CSV 
*/
#define OUTPUT_CSV 1 
/**
 * @brief Format de sortie utilisé en mode live (OUTPUT_JSON ou OUTPUT_CSV)
 *
 * Si cette variable est à OUTPUT_JSON, les données seront affichées en JSON.
 * Si cette variable est à OUTPUT_CSV, les données seront affichées en CSV.
 *
 * Le format de sortie dépend de l'utilisation de la station météo en mode maintance.
 * Ce mode peut permettre de récupérer les données depuis un ordinateur et de les traiter
 * directement. Le format JSON est plus facile à traiter pour un ordinateur, mais prend
 * plus de place en mémoire Flash.
 * Le format CSV est plus difficile à traiter pour un ordinateur, mais prend moins de place.
 */
#define LIVE_MODE_SERIAL_OUTPUT OUTPUT_CSV
/**
 * @brief Si la commande last doit être activée
*/
#define COMMAND_LAST false
/**
 * @brief Si la commande get doit être activée
*/
#define COMMAND_GET false
/**
 * @brief Si les commandes enable et disable doivent être activées
*/
#define COMMAND_ENABLE false
/**
 * @brief Si la commande help doit être activée
*/
#define COMMAND_HELP false
/**
 * @brief Si la LED doit clingnoter pendant l'acquisition
 * 
 * Si cette variable est à true, la LED clignotera pendant l'acquisition.
 * Cependant, la durée d'acquisition est très courte donc la LED ne clignote pas 
 * et un simple flash discret est visible.
*/
#define LED_BLINK_ACQUISITION false

#if LED_BLINK_ACQUISITION
#define LED_STATIC_ACQUITISION false
#else
/**
 * @brief Si la LED doit être allumée avec une couleur continue pendant l'acquisition
*/
#define LED_STATIC_ACQUISITION true
#endif

// PARAMETRES
/**
 * @brief Valeur maximale pouvant être atteinte par le timer
 * 
 * Maximum : 65535, au delà, le timer overflow et recommence à 0.
 * 
 * Une plus grande valeur permet de limiter le nombre d'interruptions
*/
#define MAX_TIMER_VALUE 65535
/**
 * @brief Valeur maximale pouvant être atteinte par le timer
 * 
 * Maximum : 255, au delà, le timer overflow et recommence à 0.
 * 
 * Une plus grande valeur permet de limiter le nombre d'interruptions
*/
#define MAX_TIMER_2_VALUE 255
/**
 * @brief Fréquence de clignotement de la LED en microsecondes
*/
#define LED_BLINK_FREQUENCY 1e6
/**
 * @brief Fréquence de clignotement de la LED d'acquisition en microsecondes
*/
#define LED_ACQUISITION_BLINK_FREQUENCY 1e5
/**
 * @brief Nombre de décimale à afficher ou enregistrer pour les valeurs flottantes
*/
#define DECIMAL 4
/**
 * @brief Vitesse de communication du port série
 *
 * Cette variable contient la vitesse de communication du port série.
 * Elle doit être la même que celle utilisée par le logiciel de réception.
 */
#define SERIAL_BAUD_RATE 9600
/**
 * @brief Taille du buffer d'entrée de l'interpréteur
 *
 * Cette variable contient la taille du buffer d'entrée de l'interpréteur.
 * Une taille trop petite peut empêcher l'interpréteur de fonctionner correctement
 * car les commandes entrées seront tronquées.
 * Une taille trop grande peut prendre trop de place en mémoire.
 */
#define INPUT_BUFFER_SIZE 30
/**
 * @brief Délai nécessaire au déclenchement de l'action en microsecondes (par défaut 5s)
 *
 * Ce délai est utilisé pour les boutons. Si le bouton est appuyé pendant
 * ce délai, l'action sera déclenchée.
 */
#define BUTTON_DELAY 5e6
/**
 * @brief Délai entre chaque acquisition en mode maintenance en millisecondes (par défaut 5s)
 *
 * Ce délai est utilisé pour définir le temps entre chaque maintenance
 * en mode économique.
 */
#define ACQUISITION_DELAY_MANTENANCE 10e3
/**
 * @brief Durée d'inactivité avant de repasser au mode précédent.
 *
 * Ce délai est utilisé pour définir le temps d'inactivité avant de repasser
 * au mode précédent depuis le mode configuration.
 * Par défaut, ce délai est de 30 minutes.
 */
#define CONFIGURATION_MODE_TIMEOUT 18e5
/**
 * @brief Valeur utilisée pour représenter une erreur d'acquisition
 * 
 * La valeur NULL initialement utilisée pour représenter une erreur est équivalente à 0
 * donc elle ne peut pas être utilisée pour représenter une erreur car elle peut être
 * renvoyée normalement par un capteur.
 * 
 * La valeur NAN utilisée ensuite pour représenter une erreur ne permet pas de faire des 
 * comparaisons : NAN != NAN
*/
#define ACQUISITION_ERROR_VALUE -999
/**
 * @brief Taille maximale d'une ligne de données à enregistrer sur la carte SD ou à afficher dans le port série
*/
#define MAX_LINE_SIZE 100
/**
 * @brief Minimum d'espace libre sur la carte SD en octets
 * 
 * Si l'espace libre sur la carte SD est inférieur à cette valeur,
 * la station météo passera en mode erreur.
 * 
 * Par défaut, elle est définie à 2ko pour éviter de remplir la carte SD
 * au maximum et donc éviter la perte de données.
*/
#define MIN_SD_FREE_BYTES 2000
/**
 * @brief Longueur maximum d'une commande de l'interpréteur
*/
#define MAX_COMMAND_LENGTH 30
/**
 * @brief Longueur maximum du nom d'un paramètre 
*/
#define MAX_SETTING_LENGTH 20
/**
 * @brief Longueur maximum d'un nom de capteur
*/
#define MAX_NAME_LENGTH 20

// ERRORS
/** @brief Erreur de communication avec l'horloge RTC */
#define ERROR_RTC_ACCESS 0
/** @brief Erreur de communication avec le GPS */
#define ERROR_GPS_ACCESS 1
/** @brief Erreur de communication avec un capteur */
#define ERROR_SENSOR_ACCESS 2
/** @brief Données incohérentes provenant d'un capteur, une maintenance est nécessaire */
#define ERROR_INCONSISTENT_DATA 3
/** @brief La carte SD est pleine */
#define ERROR_SD_FULL 4
/** @brief La carte SD est indisponible */
#define ERROR_SD_ACCESS 5
/** @brief Le délai d'acquisition a été dépassé pour un des capteurs */
#define ERROR_ACQUISITION_TIMEOUT 6
/** @brief Erreur inconnue */
#define UNKNOWN_ERROR 7

// PINS
/** @brief Pin du bouton rouge, doit être une pin d'interruption */
#define RED_BUTTON_PIN PIN2
/** @brief Pin du bouton verte, doit être une pin d'interruption */
#define GREEN_BUTTON_PIN PIN3
/** @brief Pin data de la LED RGB grove */
#define LED_DATA_PIN PIN5
/** @brief Pin clock de la LED RGB grove */
#define LED_CLK_PIN PIN4
/** @brief Identifiant de la LED dans la chaine de LED (ChainableLED) */
#define LED_ID 0
/** @brief Nombre de LED dans la chaine de LED (ChainableLED) */
#define NUMBER_OF_LEDS 1
/** @brief Pin de la carte SD */
#define SD_PIN 4
/** @brief Pin de communication série du GPS */
#define GPS_RX_PIN 6
/** @brief Pin de communication série du GPS */
#define GPS_TX_PIN 7

// JOUR DE LA SEMAINE
enum DayOfWeek {
    NOT_A_DAY,
    /** @brief Lundi */
    MONDAY,
    /** @brief Mardi */
    TUESDAY,
    /** @brief Mercredi */
    WEDNESDAY,
    /** @brief Jeudi */
    THURSDAY,
    /** @brief Vendredi */
    FRIDAY,
    /** @brief Samedi */
    SATURDAY,
    /** @brief Dimanche */
    SUNDAY
};

// CAPTEURS
/** @brief Nombre de capteurs disponibles */
#define NUMBER_OF_SENSORS 4
/** @brief Position du capteur de température dans la liste de capteurs */
#define TEMPERATURE_SENSOR 0
/** @brief Position du capteur d'humidité dans la liste de capteurs */
#define HUMIDITY_SENSOR 1
/** @brief Position du capteur de pression dans la liste de capteurs */
#define PRESSURE_SENSOR 2
/** @brief Position du capteur de luminosité dans la liste de capteurs */
#define BRIGHTNESS_SENSOR 3

// CAPTEUR DE TEMPERATURE
/** @brief Nom du capteur de température (chaine de caractère sauvegardée dans la mémoire Flash) */
#define TEMPERATURE_SENSOR_NAME (char*) F("Temperature")
/** @brief Pin utilisé ou adresse du capteur de température */
#define TEMPERATURE_SENSOR_DEVICE PIN5
/** @brief Si le capteur de température est activé */
#define TEMPERATURE_SENSOR_ENABLED true
/** @brief Si le capteur de température est activé en mode économique */
#define TEMPERATURE_SENSOR_ECONOMY true 

// CAPTEUR D'HUMIDITE
/** @brief Nom du capteur d'humidité (chaine de caractère sauvegardée dans la mémoire Flash) */
#define HUMIDITY_SENSOR_NAME (char*) F("Humidity")
/** @brief Pin utilisé ou adresse du capteur d'humidité */
#define HUMIDITY_SENSOR_DEVICE PIN6
/** @brief Si le capteur d'humidité est activé */
#define HUMIDITY_SENSOR_ENABLED true
/** @brief Si le capteur d'humidité est activé en mode économique */
#define HUMIDITY_SENSOR_ECONOMY true

// CAPTEUR DE PRESSION
/** @brief Nom du capteur de pression (chaine de caractère sauvegardée dans la mémoire Flash) */
#define PRESSURE_SENSOR_NAME (char*) F("Pressure")
/** @brief Pin utilisé ou adresse du capteur de pression */
#define PRESSURE_SENSOR_DEVICE PIN7
/** @brief Si le capteur de pression est activé */
#define PRESSURE_SENSOR_ENABLED true
/** @brief Si le capteur de pression est activé en mode économique */
#define PRESSURE_SENSOR_ECONOMY true

// CAPTEUR DE LUMINOSITE
/** @brief Nom du capteur de luminosité (chaine de caractère sauvegardée dans la mémoire Flash) */
#define BRIGHTNESS_SENSOR_NAME (char*) F("Brightness")
/** @brief Pin utilisé ou adresse du capteur de luminosité. */
#define BRIGHTNESS_SENSOR_DEVICE A0 
/** @brief Si le capteur de luminosité est activé. */
#define BRIGHTNESS_SENSOR_ENABLED true
/** @brief Si le capteur de luminosité est activé en mode économique. */
#define BRIGHTNESS_SENSOR_ECONOMY true


// SETTINGS

#if INTERPRETER
/** @brief Nombre de paramètres modifiables disponibles */
#define NUMBER_OF_SETTINGS 19
#else 
/** @brief Nombre de paramètres modifiables disponibles */
#define NUMBER_OF_SETTINGS 15
#endif
/**
 * @brief Délai entre chaque acquisition en millisecondes (par défaut 1min)
 *
 * Ce délai est utilisé pour définir le temps entre chaque acquisition.
 * Il est utilisé en mode standard et en mode économique.
*/
#define SETTING_ACQUISITION_DELAY 0
#define SETTING_NAME_ACQUISITION_DELAY (char *) F("LOG_INTERVALL")
#define SETTING_DEFAULT_ACQUISITION_DELAY 30000 // 600000 // 10 minutes
#define SETTING_ACQUISITION_DELAY_MIN 1000 // 1 seconde
#define SETTING_ACQUISITION_DELAY_MAX 86400000 // 1 jour
/**
 * @brief Taille maximale du fichier de sortie en octets (par défaut 4ko)
 */
#define SETTING_FILE_MAX_SIZE 1
#define SETTING_NAME_FILE_MAX_SIZE (char *) F("FILE_MAX_SIZE")
#define SETTING_DEFAULT_FILE_MAX_SIZE  4096
#define SETTING_FILE_MAX_SIZE_MIN 1024 // 1ko
#define SETTING_FILE_MAX_SIZE_MAX 1048576 // 1Mo
/**
 * @brief Délai d'attente avant de passer en mode erreur en millisecondes (par défaut 30s)
 */
#define SETTING_ACQUISITION_TIMEOUT 2
#define SETTING_NAME_ACQUISITION_TIMEOUT (char *) F("TIMEOUT")
#define SETTING_DEFAULT_ACQUISITION_TIMEOUT 30000
#define SETTING_ACQUISITION_TIMEOUT_MIN 1000 // 1 seconde
#define SETTING_ACQUISITION_TIMEOUT_MAX 60000 // 1 minute
/**
 * @brief Si l'acquisition du capteur de luminosité est activé.
 */
#define SETTING_BRIGHTNESS_ENABLED 3
#define SETTING_NAME_BRIGHTNESS_ENABLED (char *) F("LUMIN")
#define SETTING_DEFAULT_BRIGHTNESS_ENABLED  true
#define SETTING_BRIGHTNESS_ENABLED_MIN 0
#define SETTING_BRIGHTNESS_ENABLED_MAX 1
/**
 * @brief Valeur de luminosité basse (par défaut 255)
 *
 * Une valeur plus basse engendre une erreur.
 * La valeur doit être comprise entre 0 et 1023 et inférieur à la valeur haute.
 */
#define SETTING_BRIGHTNESS_LOW 4
#define SETTING_NAME_BRIGHTNESS_LOW (char *) F("LUMIN_LOW")
#define SETTING_DEFAULT_BRIGHTNESS_LOW  255
#define SETTING_BRIGHTNESS_LOW_MIN 0
#define SETTING_BRIGHTNESS_LOW_MAX 1023
/**
 * @brief Valeur de luminosité haute (par défaut 768)
 *
 * Une valeur plus haute engendre une erreur
 * La valeur doit être comprise entre 0 et 1023 et supérieur à la valeur basse.
 */
#define SETTING_BRIGHTNESS_HIGH 5
#define SETTING_NAME_BRIGHTNESS_HIGH (char *) F("LUMIN_HIGH")
#define SETTING_DEFAULT_BRIGHTNESS_HIGH  768
#define SETTING_BRIGHTNESS_HIGH_MIN 0
#define SETTING_BRIGHTNESS_HIGH_MAX 1023
/**
 * @brief Si l'acquisition du capteur de température est activé.
 */
#define SETTING_TEMPERATURE_ENABLED 6
#define SETTING_NAME_TEMPERATURE_ENABLED (char *) F("TEMP_AIR")
#define SETTING_DEFAULT_TEMPERATURE_ENABLED  true
#define SETTING_TEMPERATURE_ENABLED_MIN 0
#define SETTING_TEMPERATURE_ENABLED_MAX 1
/**
 * @brief Valeur de température basse (par défaut -10)
 *
 * Une valeur plus basse engendre une erreur.
 * La valeur doit être comprise entre -40 et 85 et inférieur à la valeur haute.
 */
#define SETTING_TEMPERATURE_MIN 7
#define SETTING_NAME_TEMPERATURE_MIN (char *) F("TMIN_TEMP_AIR")
#define SETTING_DEFAULT_TEMPERATURE_MIN  -10
#define SETTING_TEMPERATURE_MIN_MIN -40
#define SETTING_TEMPERATURE_MIN_MAX 85
/**
 * @brief Valeur de température haute (par défaut 60)
 *
 * Une valeur plus haute engendre une erreur.
 * La valeur doit être comprise entre -40 et 85 et supérieur à la valeur basse.
 */
#define SETTING_TEMPERATURE_MAX 8
#define SETTING_NAME_TEMPERATURE_MAX (char *) F("TMAX_TEMP_AIR")
#define SETTING_DEFAULT_TEMPERATURE_MAX  60
#define SETTING_TEMPERATURE_MAX_MIN -40
#define SETTING_TEMPERATURE_MAX_MAX 85
/**
 * @brief Si l'acquisition du capteur d'humidité est activé.
 */
#define SETTING_HUMIDITY_ENABLED 9
#define SETTING_NAME_HUMIDITY_ENABLED (char *) F("HYGR")
#define SETTING_DEFAULT_HUMIDITY_ENABLED  true
#define SETTING_HUMIDITY_ENABLED_MIN 0
#define SETTING_HUMIDITY_ENABLED_MAX 1
/**
 * @brief Valeur d'humidité basse (par défaut 0)
 *
 * Une valeur plus basse engendre une erreur.
 * La valeur doit être comprise entre -40 et 85 et inférieur à la valeur haute.
 */
#define SETTING_HUMIDITY_MIN 10
#define SETTING_NAME_HUMIDITY_MIN (char *) F("HYGR_MINT")
#define SETTING_DEFAULT_HUMIDITY_MIN  0 
#define SETTING_HUMIDITY_MIN_MIN -40
#define SETTING_HUMIDITY_MIN_MAX 85
/**
 * @brief Valeur d'humidité haute (par défaut 50)
 *
 * Une valeur plus haute engendre une erreur.
 * La valeur doit être comprise entre -40 et 85 et supérieur à la valeur basse.
 */
#define SETTING_HUMIDITY_MAX 11
#define SETTING_NAME_HUMIDITY_MAX (char *) F("HYGR_MAXT")
#define SETTING_DEFAULT_HUMIDITY_MAX  50
#define SETTING_HUMIDITY_MAX_MIN -40
#define SETTING_HUMIDITY_MAX_MAX 85
/**
 * @brief Si l'acquisition du capteur de pression est activé.
 */
#define SETTING_PRESSURE_ENABLED 12
#define SETTING_NAME_PRESSURE_ENABLED (char *) F("PRESSURE")
#define SETTING_DEFAULT_PRESSURE_ENABLED  true
#define SETTING_PRESSURE_ENABLED_MIN 0
#define SETTING_PRESSURE_ENABLED_MAX 1
/**
 * @brief Valeur de pression basse (par défaut 850 hPa)
 *
 * Une valeur plus basse engendre une erreur.
 * La valeur doit être comprise entre 300 et 1100 et inférieur à la valeur haute.
 */
#define SETTING_PRESSURE_MIN 13
#define SETTING_NAME_PRESSURE_MIN (char *) F("PRESSURE_MIN")
#define SETTING_DEFAULT_PRESSURE_MIN  850
#define SETTING_PRESSURE_MIN_MIN 300
#define SETTING_PRESSURE_MIN_MAX 1100
/**
 * @brief Valeur de pression haute (par défaut 1080 hPa)
 *
 * Une valeur plus haute engendre une erreur.
 * La valeur doit être comprise entre 300 et 1100 et supérieur à la valeur basse.
 */
#define SETTING_PRESSURE_MAX 14
#define SETTING_NAME_PRESSURE_MAX (char *) F("PRESSURE_MAX")
#define SETTING_DEFAULT_PRESSURE_MAX  1080
#define SETTING_PRESSURE_MAX_MIN 300
#define SETTING_PRESSURE_MAX_MAX 1100

#if INTERPRETER
/**
 * @brief Si l'acquisition du capteur de luminosité est activé en mode économique.
*/
#define SETTING_BRIGHTNESS_ECONOMY_ENABLED 15
#define SETTING_NAME_BRIGHTNESS_ECONOMY_ENABLED (char *) F("LUMIN_ECO")
#define SETTING_DEFAULT_BRIGHTNESS_ECONOMY_ENABLED  true
#define SETTING_BRIGHTNESS_ECONOMY_ENABLED_MIN 0
#define SETTING_BRIGHTNESS_ECONOMY_ENABLED_MAX 1
/**
 * @brief Si l'acquisition du capteur de température est activé en mode économique.
*/
#define SETTING_TEMPERATURE_ECONOMY_ENABLED 16
#define SETTING_NAME_TEMPERATURE_ECONOMY_ENABLED (char *) F("TEMP_AIR_ECO")
#define SETTING_DEFAULT_TEMPERATURE_ECONOMY_ENABLED  true
#define SETTING_TEMPERATURE_ECONOMY_ENABLED_MIN 0
#define SETTING_TEMPERATURE_ECONOMY_ENABLED_MAX 1
/**
 * @brief Si l'acquisition du capteur d'humidité est activé en mode économique.
*/
#define SETTING_HUMIDITY_ECONOMY_ENABLED 17
#define SETTING_NAME_HUMIDITY_ECONOMY_ENABLED (char *) F("HYGR_ECO")
#define SETTING_DEFAULT_HUMIDITY_ECONOMY_ENABLED  true
#define SETTING_HUMIDITY_ECONOMY_ENABLED_MIN 0
#define SETTING_HUMIDITY_ECONOMY_ENABLED_MAX 1
/**
 * @brief Si l'acquisition du capteur de pression est activé en mode économique.
*/
#define SETTING_PRESSURE_ECONOMY_ENABLED 18
#define SETTING_NAME_PRESSURE_ECONOMY_ENABLED (char *) F("PRESSURE_ECO")
#define SETTING_DEFAULT_PRESSURE_ECONOMY_ENABLED  true
#define SETTING_PRESSURE_ECONOMY_ENABLED_MIN 0
#define SETTING_PRESSURE_ECONOMY_ENABLED_MAX 1
#endif

#endif