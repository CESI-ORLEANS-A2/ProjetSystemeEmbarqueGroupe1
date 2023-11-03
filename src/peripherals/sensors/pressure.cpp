#include "peripherals/sensors/pressure.hpp"

void initPressureSensor() {
    // Initialisation du capteur de pression, de température et d'humidité
    initBME();
    // Initialise le capteur de pression sous la forme d'une structure Sensor ajoutée au tableau sensors[].
    sensors[PRESSURE_SENSOR] = {
        .name = PRESSURE_SENSOR_NAME,
        .enabled = SETTING_PRESSURE_ENABLED,
#if INTERPRETER
        .economy = SETTING_PRESSURE_ECONOMY_ENABLED,
#endif
        .measure = &measurePressure
    };
}

float measurePressure() {
    // Récupère la valeur de la pression
    const float pressure = readPressure() / 100; // conversion de Pa en hPa
    
    // Pour débugger le capteur de pression
    // Serial.println(pressure);
    // Serial.print("min="); Serial.print(getSetting(SETTING_PRESSURE_MIN)); Serial.print(" max="); Serial.println(getSetting(SETTING_PRESSURE_MAX));

    // Vérifie que la valeur est comprise entre les valeurs définies dans les paramètres
    if (pressure < getSetting(SETTING_PRESSURE_MIN) || pressure > getSetting(SETTING_PRESSURE_MAX))
        return ACQUISITION_ERROR_VALUE;

    // Si la valeur est correcte, on la retourne
    return pressure;
}