#include "peripherals/sensors/humidity.hpp"

void initHumiditySensor() {
    // Initialise le capteur d'humidité, de température et de pression
    initBME();
    // Initialise le capteur d'humidité sous la forme d'une structure Sensor ajoutée au tableau sensors[].
    sensors[HUMIDITY_SENSOR] = {
        .name = HUMIDITY_SENSOR_NAME,
        .enabled = SETTING_HUMIDITY_ENABLED,
#if INTERPRETER
        .economy = SETTING_HUMIDITY_ECONOMY_ENABLED,
#endif // INTERPRETER
        .measure = &measureHumidity
    };
}

float measureHumidity() {
    // Récupère la valeur de l'humidité
    const float humidity = readHumidity();

    // Pour débugger le capteur d'humidité
    // Serial.println(humidity);
    // Serial.print("min="); Serial.print(getSetting(SETTING_HUMIDITY_MIN)); Serial.print(" max="); Serial.println(getSetting(SETTING_HUMIDITY_MAX));

    // Vérifie que la valeur est comprise entre les valeurs définies dans les paramètres
    if (lastMeasurements[TEMPERATURE_SENSOR] < getSetting(SETTING_HUMIDITY_MIN) || lastMeasurements[TEMPERATURE_SENSOR] > getSetting(SETTING_HUMIDITY_MAX))
        return ACQUISITION_ERROR_VALUE;

    // Si la valeur est correcte, on la retourne
    return humidity;
}