#include <SoftwareSerial.h>
#include "consts.hpp"
#include "modes/error.hpp"

/**
 * @brief Port série utilisé pour communiquer avec le GPS
*/
extern SoftwareSerial GPSSerial;

/**
 * @brief Contient la dernière valeur de lattitude acquise par le GPS. 
*/
extern char lastLatitude[12];
/**
 * @brief Contient la dernière valeur de longitude acquise par le GPS.
*/
extern char lastLongitude[12];

/**
 * @brief Initialise le GPS
*/
void initGPS();
/**
 * @brief Lit les données GPS
 * 
 * Le GPS renvoie les données sous la forme :
 * 
 * $GPRMC,092032.000,A,4449.7378,N,00033.9614,W,0.00,33.10,130617,,,A*49\n
 * $GPGGA,092033.000,4449.7378,N,00033.9614,W,1,04,2.6,100.0,M,47.6,M,,*5F\n
 * $GPGSA,A,3,25,15,32,24,12,19,14,06,29,10,02,1.07*01\n
 * $GPGSV,3,1,12,02,63,038,20,06,18,275,21,10,11,314,18,12,44,228,25*7C\n
 * $GPGSV,3,2,12,14,19,060,18,15,44,308,25,19,26,145,18,24,11,042,18*7A\n
 * $GPGSV,3,3,12,25,76,177,30,29,11,104,18,32,11,270,18*7D\n
 * $GPGSV,4,4,13,38,,,*70\n
 * $GPRMC,092033.000,A,4449.7378,N,00033.9614,W,0.00,33.10,130617,,,A*4A\n
 * $GPGGA,092034.000,4449.7378,N,00033.9614,W,1,04,2.6,100.0,M,47.6,M,,*5E\n
 * 
 * Dans ces lignes, seul les lignes commençant par $GPRMC ou $GPGGA nous intéressent.
 * Et dans ces lignes, seul les champs de le forme xxxxx.xxxx,N,xxxxx.xxxx,W .
 * 
 * @return true si les données ont été acquises, false sinon
*/
bool readGPS();