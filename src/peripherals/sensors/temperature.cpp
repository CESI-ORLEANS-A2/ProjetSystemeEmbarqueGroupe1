#include "peripherals/sensors/temperature.hpp"

void initTemperatureSensor() {
    // Initialise le capteur d'humidité, de température et de pression
    initBME();
    // Initialise le capteur de température sous la forme d'une structure Sensor ajoutée au tableau sensors[].
    sensors[TEMPERATURE_SENSOR] = {
        .name = TEMPERATURE_SENSOR_NAME,
        .enabled = SETTING_TEMPERATURE_ENABLED,
#if INTERPRETER
        .economy = SETTING_TEMPERATURE_ECONOMY_ENABLED,
#endif
        .measure = &measureTemperature
    };
}

float measureTemperature() {
    // Récupère la valeur de la température
    const float temperature = readTemperature();

    // Pour débugger le capteur de température
    // Serial.println(temperature);
    // Serial.print("min="); Serial.print(getSetting(SETTING_TEMPERATURE_MIN)); Serial.print(" max="); Serial.println(getSetting(SETTING_TEMPERATURE_MAX));

    // Vérifie que la valeur est comprise entre les valeurs définies dans les paramètres
    if (temperature < getSetting(SETTING_TEMPERATURE_MIN) || temperature > getSetting(SETTING_TEMPERATURE_MAX))
        return ACQUISITION_ERROR_VALUE;

    // Si la valeur est correcte, on la retourne
    return temperature;
}