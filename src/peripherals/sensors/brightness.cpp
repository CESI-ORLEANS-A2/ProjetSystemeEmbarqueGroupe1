#include "peripherals/sensors/brightness.hpp"

void initBrightnessSensor() {
    // Initialise le capteur de luminosité sous la forme d'une structure Sensor ajoutée au tableau sensors[].
    sensors[BRIGHTNESS_SENSOR] = {
        .name = BRIGHTNESS_SENSOR_NAME,
        .enabled = SETTING_BRIGHTNESS_ENABLED,
#if INTERPRETER
        .economy = SETTING_BRIGHTNESS_ECONOMY_ENABLED,
#endif // INTERPRETER
        .measure = &measureBrightness
    };
}

float measureBrightness() {
    // Récupère la valeur de la luminosité
    const float brightness = analogRead(BRIGHTNESS_SENSOR_DEVICE);

    // Pour débugger le capteur de luminosité
    // Serial.println(brightness);
    // Serial.print("min="); Serial.print(getSetting(SETTING_BRIGHTNESS_LOW)); Serial.print(" max="); Serial.println(getSetting(SETTING_BRIGHTNESS_HIGH));
    
    // Vérifie que la valeur est comprise entre les valeurs définies dans les paramètres
    if (brightness < getSetting(SETTING_BRIGHTNESS_LOW) || brightness > getSetting(SETTING_BRIGHTNESS_HIGH))
        return ACQUISITION_ERROR_VALUE;

    // Si la valeur est correcte, on la retourne
    return brightness;
}