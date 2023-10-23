#ifndef Consts_h
#define Consts_h

#include <Arduino.h>

// ENABLE/DISABLE FEATURES
#define INTERPRETER false // Si l'interpréteur doit être activé
#define DETAILED_HELP_COMMAND true // Si la commande help doit afficher les détails des commandes
#define LIVE_MODE_SERIAL_OUTPUT OUTPUT_JSON // Format de sortie utilisé en mode live (OUTPUT_JSON ou OUTPUT_CSV)

// COMMON SETTINGS
#define SERIAL_BAUD_RATE 9600 // Vitesse de communication du port série
#define INPUT_BUFFER_SIZE 100 // Taille du buffer d'entrée de l'interpréteur
#define INPUT_DO_ECHO true // Si l'interpréteur doit renvoyer la commande entrée
#define BUTTON_DELAY 5e6 // Délai nécessaire au déclenchement de l'action (par défaut 5s)
#define ACQUISITION_DELAY 60e3 // Délai entre chaque acquisition (par défaut 1min)
#define ACQUISITION_DELAY_MANTENANCE 5e3 // Délai entre chaque acquisition en mode économique (par défaut 5s)

// MODES
#define STANDARD_MODE 0
#define ECONOMY_MODE 1
#define CONFIGURATION_MODE 2
#define MAINTENANCE_MODE 3

// PROTOCOLS
#define I2C_PROTOCOL 0
#define ANALOG_PROTOCOL 1
#define UART_PROTOCOL 2
#define TWOWIRE_PROTOCOL 3
#define SPI_PROTOCOL 4

// SERIAL OUTPUT
#define OUTPUT_JSON 0 // Le format de sortie dans le port série est du JSON
#define OUTPUT_CSV 1 // Le format de sortie dans le port série est du CSV

// CONSTANTS
// PINS
#define RED_BUTTON_PIN PIN2 // Pin de la LED rouge, doit être une pin d'interruption
#define GREEN_BUTTON_PIN PIN3 // Pin de la LED verte, doit être une pin d'interruption

#define LED_DATA_PIN PIN5
#define LED_CLK_PIN PIN4
#define LED_ID 0
#define NUMBER_OF_LEDS 1

// SENSORS
#define NUMBER_OF_SENSORS 2 // TODO Mettre à jour en fonction du nombre de capteurs
#define TEMPERATURE_SENSOR 0
#define HUMIDITY_SENSOR 1
#define PRESSURE_SENSOR 2
#define BRIGHTNESS_SENSOR 3

// CAPTEUR DE TEMPERATURE
#define TEMPERATURE_SENSOR_NAME (const char*) F("Temperature")
#define TEMPERATURE_SENSOR_PROTOCOL I2C_PROTOCOL
#define TEMPERATURE_SENSOR_DEVICE PIN5
#define TEMPERATURE_SENSOR_ENABLED true
#define TEMPERATURE_SENSOR_ECONOMY true 

// CAPTEUR D'HUMIDITE
#define HUMIDITY_SENSOR_NAME (const char*) F("Humidity")
#define HUMIDITY_SENSOR_PROTOCOL I2C_PROTOCOL
#define HUMIDITY_SENSOR_DEVICE PIN6 // TODO Définir l'adresse du capteur d'humidité
#define HUMIDITY_SENSOR_ENABLED true
#define HUMIDITY_SENSOR_ECONOMY true

// CAPTEUR DE PRESSION
#define PRESSURE_SENSOR_NAME (const char*) F("Pressure")
#define PRESSURE_SENSOR_PROTOCOL I2C_PROTOCOL
#define PRESSURE_SENSOR_DEVICE PIN7 // TODO Définir le pin du capteur de pression
#define PRESSURE_SENSOR_ENABLED true
#define PRESSURE_SENSOR_ECONOMY true

// CAPTEUR DE LUMINOSITE
#define BRIGHTNESS_SENSOR_NAME (const char*) F("Brightness")
#define BRIGHTNESS_SENSOR_PROTOCOL ANALOG_PROTOCOL
#define BRIGHTNESS_SENSOR_DEVICE A0 // TODO Définir le pin du capteur de luminosité
#define BRIGHTNESS_SENSOR_ENABLED true
#define BRIGHTNESS_SENSOR_ECONOMY true

#endif