#ifndef Consts_h
#define Consts_h

#include <Arduino.h>

// ACTIVER/DESACTIVER DES FONCTIONNALITES
/*!
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
/*!
 * @brief Si la commande help doit afficher les détails des commandes
 *
 * Si cette variable est à true, la commande help affichera les détails
 * de chaque commande. Sinon, elle affichera uniquement la liste des
 * commandes disponibles.
 * Les détails d'une commande sont sa description, sa syntax et ses arguments.
 * Cependant, afficher les détails prend beaucoup de place en mémoire Flash.
 */
#define DETAILED_HELP_COMMAND true 
/*!
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
#define LIVE_MODE_SERIAL_OUTPUT OUTPUT_JSON 
#define MAX_NAME_LENGTH 20

// PARAMETRES
/*!
 * @brief Vitesse de communication du port série
 *
 * Cette variable contient la vitesse de communication du port série.
 * Elle doit être la même que celle utilisée par le logiciel de réception.
 */
#define SERIAL_BAUD_RATE 9600
/*!
 * @brief Taille du buffer d'entrée de l'interpréteur
 *
 * Cette variable contient la taille du buffer d'entrée de l'interpréteur.
 * Une taille trop petite peut empêcher l'interpréteur de fonctionner correctement
 * car les commandes entrées seront tronquées.
 * Une taille trop grande peut prendre trop de place en mémoire.
 */
#define INPUT_BUFFER_SIZE 100
/*!
 * @brief Si l'interpréteur doit renvoyer la commande entrée
 *
 * Si cette variable est à true, l'interpréteur renverra la commande entrée
 * dans le port série.
 * Cela peut être utile pour vérifier que la commande a bien été interprétée.
 */
#define INPUT_DO_ECHO true
/*!
 * @brief Délai nécessaire au déclenchement de l'action en microsecondes (par défaut 5s)
 *
 * Ce délai est utilisé pour les boutons. Si le bouton est appuyé pendant
 * ce délai, l'action sera déclenchée.
 */
#define BUTTON_DELAY 5e6
/*!
 * @brief Délai entre chaque acquisition en mode maintenance en millisecondes (par défaut 5s)
 *
 * Ce délai est utilisé pour définir le temps entre chaque maintenance
 * en mode économique.
 */
#define ACQUISITION_DELAY_MANTENANCE 5e3
/*!
 * @brief Durée d'inactivité avant de repasser au mode précédent.
 *
 * Ce délai est utilisé pour définir le temps d'inactivité avant de repasser
 * au mode précédent depuis le mode configuration.
 * Par défaut, ce délai est de 30 minutes.
 */
#define CONFIGURATION_MODE_TIMEOUT 18e5

// MODES
/*! @brief Mode standard */
#define STANDARD_MODE 0
/*! @brief Mode économique */
#define ECONOMY_MODE 1
/*! @brief Mode configuration */
#define CONFIGURATION_MODE 2
/*! @brief Mode maintenance */
#define MAINTENANCE_MODE 3
/*! @brief Mode erreur */
#define ERROR_MODE 4

// ERRORS
/*! @brief Erreur de communication avec l'horloge RTC */
#define ERROR_RTC_ACCESS 0
/*! @brief Erreur de communication avec le GPS */
#define ERROR_GPS_ACCESS 1
/*! @brief Erreur de communication avec un capteur */
#define ERROR_SENSOR_ACCESS 2
/*! @brief Données incohérentes provenant d'un capteur, une maintenance est nécessaire */
#define ERROR_INCONSISTENT_DATA 3
/*! @brief La carte SD est pleine */
#define ERROR_SD_FULL 4
/*! @brief La carte SD est indisponible */
#define ERROR_SD_ACCESS 5
/*! @brief Le délai d'acquisition a été dépassé pour un des capteurs */
#define ERROR_ACQUISITION_TIMEOUT 6

// PROTOCOLES
/*! @brief Récupération des données grâce au protocole I2C */
#define I2C_PROTOCOL 0
/*! @brief Récupération des données par les ports analogiques */
#define ANALOG_PROTOCOL 1
/*! @brief Récupération des données grâce au protocole UART (Serial) */
#define UART_PROTOCOL 2
/*! @brief Récupération des données par les ports digitaux */
#define TWOWIRE_PROTOCOL 3
/*! @brief Récupération des données grâce au protocole SPI */
#define SPI_PROTOCOL 4

// FORMATS DE SORTIE
/*! @brief Le format de sortie dans le port série est du JSON */
#define OUTPUT_JSON 0
/*! @brief Le format de sortie dans le port série est du CSV */
#define OUTPUT_CSV 1 

// PINS
/*! @brief Pin du bouton rouge, doit être une pin d'interruption */
#define RED_BUTTON_PIN PIN2
/*! @brief Pin du bouton verte, doit être une pin d'interruption */
#define GREEN_BUTTON_PIN PIN3
/*! @brief Pin data de la LED RGB grove */
#define LED_DATA_PIN PIN5
/*! @brief Pin clock de la LED RGB grove */
#define LED_CLK_PIN PIN4
/*! @brief Identifiant de la LED dans la chaine de LED (ChainableLED) */
#define LED_ID 0
/*! @brief Nombre de LED dans la chaine de LED (ChainableLED) */
#define NUMBER_OF_LEDS 1

// CAPTEURS
/*! @brief Nombre de capteurs disponibles */
#define NUMBER_OF_SENSORS 2
/*! @brief Position du capteur de température dans la liste de capteurs */
#define TEMPERATURE_SENSOR 0
/*! @brief Position du capteur d'humidité dans la liste de capteurs */
#define HUMIDITY_SENSOR 1
/*! @brief Position du capteur de pression dans la liste de capteurs */
#define PRESSURE_SENSOR 2
/*! @brief Position du capteur de luminosité dans la liste de capteurs */
#define BRIGHTNESS_SENSOR 3

// CAPTEUR DE TEMPERATURE
/*! @brief Nom du capteur de température (chaine de caractère sauvegardée dans la mémoire Flash) */
#define TEMPERATURE_SENSOR_NAME (const char*) F("Temperature")
/*! @brief Protocole utilisé par le capteur de température */
#define TEMPERATURE_SENSOR_PROTOCOL I2C_PROTOCOL
/*! @brief Pin utilisé ou adresse du capteur de température */
#define TEMPERATURE_SENSOR_DEVICE PIN5
/*! @brief Si le capteur de température est activé */
#define TEMPERATURE_SENSOR_ENABLED true
/*! @brief Si le capteur de température est activé en mode économique */
#define TEMPERATURE_SENSOR_ECONOMY true 

// CAPTEUR D'HUMIDITE
/*! @brief Nom du capteur d'humidité (chaine de caractère sauvegardée dans la mémoire Flash) */
#define HUMIDITY_SENSOR_NAME (const char*) F("Humidity")
/*! @brief Protocole utilisé par le capteur d'humidité */
#define HUMIDITY_SENSOR_PROTOCOL I2C_PROTOCOL
/*! @brief Pin utilisé ou adresse du capteur d'humidité */
#define HUMIDITY_SENSOR_DEVICE PIN6
/*! @brief Si le capteur d'humidité est activé */
#define HUMIDITY_SENSOR_ENABLED true
/*! @brief Si le capteur d'humidité est activé en mode économique */
#define HUMIDITY_SENSOR_ECONOMY true

// CAPTEUR DE PRESSION
/*! @brief Nom du capteur de pression (chaine de caractère sauvegardée dans la mémoire Flash) */
#define PRESSURE_SENSOR_NAME (const char*) F("Pressure")
/*! @brief Protocole utilisé par le capteur de pression */
#define PRESSURE_SENSOR_PROTOCOL I2C_PROTOCOL
/*! @brief Pin utilisé ou adresse du capteur de pression */
#define PRESSURE_SENSOR_DEVICE PIN7
/*! @brief Si le capteur de pression est activé */
#define PRESSURE_SENSOR_ENABLED true
/*! @brief Si le capteur de pression est activé en mode économique */
#define PRESSURE_SENSOR_ECONOMY true

// CAPTEUR DE LUMINOSITE
/*! @brief Nom du capteur de luminosité (chaine de caractère sauvegardée dans la mémoire Flash) */
#define BRIGHTNESS_SENSOR_NAME (const char*) F("Brightness")
/*! @brief Protocole utilisé par le capteur de luminosité */
#define BRIGHTNESS_SENSOR_PROTOCOL ANALOG_PROTOCOL
/*! @brief Pin utilisé ou adresse du capteur de luminosité */
#define BRIGHTNESS_SENSOR_DEVICE A0 
/*! @brief Si le capteur de luminosité est activé */
#define BRIGHTNESS_SENSOR_ENABLED true
/*! @brief Si le capteur de luminosité est activé en mode économique */
#define BRIGHTNESS_SENSOR_ECONOMY true


// SETTINGS

/*! @brief Nombre de paramètres modifiables disponibles */
#define NUMBER_OF_SETTINGS 15

#define SETTING_ACQUISITION_DELAY 0
/*!
 * @brief Délai entre chaque acquisition en millisecondes (par défaut 1min)
 *
 * Ce délai est utilisé pour définir le temps entre chaque acquisition.
 * Il est utilisé en mode standard et en mode économique.
*/
#define SETTING_DEFAULT_ACQUISITION_DELAY 1e3 // 60e3
#define SETTING_FILE_MAX_SIZE 1
/*!
 * @brief Taille maximale du fichier de sortie en octets (par défaut 4ko)
 */
#define SETTING_DEFAULT_FILE_MAX_SIZE 4096
#define SETTING_ACQUISITION_TIMEOUT 2
 /*!
  * @brief Délai d'attente avant de passer en mode erreur en millisecondes (par défaut 30s)
  */
#define SETTING_DEFAULT_ACQUISITION_TIMEOUT 3e4

#define SETTING_BRIGHTNESS_ENABLED 3
  /*!
   * @brief Si l'acquisition du capteur de luminosité est activé
   */
#define SETTING_DEFAULT_BRIGHTNESS_ENABLED true
#define SETTING_BRIGHTNESS_LOW 4
   /*!
    * @brief Valeur de luminosité basse (par défaut 255)
    *
    * Une valeur plus basse engendre une erreur.
    * La valeur doit être comprise entre 0 et 1023 et inférieur à la valeur haute.
    */
#define SETTING_DEFAULT_BRIGHTNESS_LOW 255
#define SETTING_BRIGHTNESS_HIGH 5
    /*!
     * @brief Valeur de luminosité haute (par défaut 768)
     *
     * Une valeur plus haute engendre une erreur
     * La valeur doit être comprise entre 0 et 1023 et supérieur à la valeur basse.
     */
#define SETTING_DEFAULT_BRIGHTNESS_HIGH 768

#define SETTING_TEMPERATURE_ENABLED 6
     /*!
      * @brief Si l'acquisition du capteur de température est activé
      */
#define SETTING_DEFAULT_TEMPERATURE_ENABLED true
#define SETTING_TEMPERATURE_MIN 7
      /*!
       * @brief Valeur de température basse (par défaut -10)
       *
       * Une valeur plus basse engendre une erreur.
       * La valeur doit être comprise entre -40 et 85 et inférieur à la valeur haute.
       */
#define SETTING_DEFAULT_TEMPERATURE_MIN -10
#define SETTING_TEMPERATURE_MAX 8
       /*!
        * @brief Valeur de température haute (par défaut 60)
        *
        * Une valeur plus haute engendre une erreur.
        * La valeur doit être comprise entre -40 et 85 et supérieur à la valeur basse.
        */
#define SETTING_DEFAULT_TEMPERATURE_MAX 60

#define SETTING_HUMIDITY_ENABLED 9
        /*!
         * @brief Si l'acquisition du capteur d'humidité est activé
         */
#define SETTING_DEFAULT_HUMIDITY_ENABLED true
#define SETTING_HUMIDITY_MIN 10
         /*!
          * @brief Valeur d'humidité basse (par défaut 0)
          *
          * Une valeur plus basse engendre une erreur.
          * La valeur doit être comprise entre -40 et 85 et inférieur à la valeur haute.
          */
#define SETTING_DEFAULT_HUMIDITY_MIN 0 
#define SETTING_HUMIDITY_MAX 11
          /*!
           * @brief Valeur d'humidité haute (par défaut 50)
           *
           * Une valeur plus haute engendre une erreur.
           * La valeur doit être comprise entre -40 et 85 et supérieur à la valeur basse.
           */
#define SETTING_DEFAULT_HUMIDITY_MAX 50

#define SETTING_PRESSURE_ENABLED 12
           /*!
            * @brief Si l'acquisition du capteur de pression est activé
            */
#define SETTING_DEFAULT_PRESSURE_ENABLED true
#define SETTING_PRESSURE_MIN 13
            /*!
             * @brief Valeur de pression basse (par défaut 850)
             *
             * Une valeur plus basse engendre une erreur.
             * La valeur doit être comprise entre 300 et 1100 et inférieur à la valeur haute.
             */
#define SETTING_DEFAULT_PRESSURE_MIN 850
#define SETTING_PRESSURE_MAX 14
             /*!
              * @brief Valeur de pression haute (par défaut 1080)
              *
              * Une valeur plus haute engendre une erreur.
              * La valeur doit être comprise entre 300 et 1100 et supérieur à la valeur basse.
              */
#define SETTING_DEFAULT_PRESSURE_MAX 1080

              /*!
               * @brief Valeurs par défaut des paramètres
               *
               * Ces valeurs sont modifiables grâce à l'interface série par la commande set.
               * Syntaxe: set <paramètre> <valeur>
               * Exemple: set ACQUISITION_DELAY 1000
               */
const double DEFAULT_SETTINGS[NUMBER_OF_SETTINGS] = {
    SETTING_DEFAULT_ACQUISITION_DELAY,
    SETTING_DEFAULT_FILE_MAX_SIZE,
    SETTING_DEFAULT_ACQUISITION_TIMEOUT,
    SETTING_DEFAULT_BRIGHTNESS_ENABLED,
    SETTING_DEFAULT_BRIGHTNESS_LOW,
    SETTING_DEFAULT_BRIGHTNESS_HIGH,
    SETTING_DEFAULT_TEMPERATURE_ENABLED,
    SETTING_DEFAULT_TEMPERATURE_MIN,
    SETTING_DEFAULT_TEMPERATURE_MAX,
    SETTING_DEFAULT_HUMIDITY_ENABLED,
    SETTING_DEFAULT_HUMIDITY_MIN,
    SETTING_DEFAULT_HUMIDITY_MAX,
    SETTING_DEFAULT_PRESSURE_ENABLED,
    SETTING_DEFAULT_PRESSURE_MIN,
    SETTING_DEFAULT_PRESSURE_MAX
};

#endif