#include "peripherals/gps.hpp"

SoftwareSerial GPSSerial(GPS_RX_PIN, GPS_TX_PIN);

char lastLatitude[12];
char lastLongitude[12];

void initGPS() {
    GPSSerial.begin(9600);
}
bool readGPS() {
    int data; // Contient le caractère lu sur le port série
    char buf[15]; // Contient les données lues sur le port série
    char* bufPointer = buf; // Pointeur sur le buffer pour pouvoir faire des concaténations facilement
    int bufLength = 0; // Longueur du buffer
    int counter = 0; // Compteur pour savoir à quelle donnée on en est
    char* lastLatitudePointer = lastLatitude; // Pointeur sur la dernière latitude acquise pour pouvoir faire des concaténations facilement
    char* lastLongitudePointer = lastLongitude; // Pointeur sur la dernière longitude acquise pour pouvoir faire des concaténations facilement
    bool success = false; // Indique si les données ont été acquises

    while (GPSSerial.available()) {
        data = GPSSerial.read();

        if (data == '$') { // Si on lit le début d'une ligne
            while ((data = GPSSerial.read()) != '\n') { // On lit les données jusqu'à la fin de la ligne
                if (counter == -1) continue;
                // Si la donnée lue est une virgule, on interprète les données lues et stockées dans le buffer
                if (data == ',') {
                    // Si le compteur est à 0, alors on est sur le début de la ligne
                    if (counter == 0) {
                        // On ne s'interesse qu'aux lignes GPGGA
                        // Si la ligne ne commence pas par GPGGA, on passe à la ligne suivante en mettant le compteur
                        // à -1 pour ne pas interpréter les données jusqu'à la fin de la ligne
                        if (bufLength == 6 && strcmp(buf, "GPGGA") == 0) {
                            counter++;
                            bufLength = 0;
                        }
                        else counter = -1;
                    }
                    // On ne s'interesse pas à la deuxième donnée
                    else if (counter == 1) counter++;
                    // La troisième donnée est la latitude
                    else if (counter == 2) {
                        // Si la donnée est vide, on met la latitude à N/A, on passe la ligne et on active le mode erreur
                        // ERROR_GPS_ACCESS
                        if (bufLength < 3) {
                            (*(lastLatitudePointer++)) = 'N';
                            (*(lastLatitudePointer++)) = 'A';
                            (*(lastLatitudePointer++)) = 'N';
                            (*(lastLongitudePointer++)) = 'N';
                            (*(lastLongitudePointer++)) = 'A';
                            (*(lastLongitudePointer++)) = 'N';
                            counter = -1;

                            switchToErrorMode(ERROR_GPS_ACCESS);
                        }
                        // Sinon on stocke la latitude dans la variable lastLatitude
                        else {
                            // Cette instruction permet d'écrire dans la variable lastLatitude en écrasant les données
                            // précédentes
                            // On place les caractères présents dans le buffer dans la variable lastLatitude un par un grâce
                            // au pointeur lastLatitudePointer et bufPointer
                            // Exemple : 
                            // i  | bufPointer + i  | lastLatitudePointer | buf         | lastLatitude
                            // 0  | 340             | 546                 | 4449.7378   | 4
                            // 1  | 341             | 547                 | 4449.7378   | 44
                            // 2  | 342             | 548                 | 4449.7378   | 444
                            // 3  | 343             | 549                 | 4449.7378   | 4449
                            // 4  | 344             | 550                 | 4449.7378   | 4449.
                            // 5  | 345             | 551                 | 4449.7378   | 4449.7
                            // 6  | 346             | 552                 | 4449.7378   | 4449.73
                            // 7  | 347             | 553                 | 4449.7378   | 4449.737
                            // 8  | 348             | 554                 | 4449.7378   | 4449.7378
                            for (int i = 0; i < bufLength; i++) (*(lastLatitudePointer++)) = (*(bufPointer + i));
                            counter++;
                        }
                    }
                    // La quatrième donnée est la direction : N (nord) ou S (sud)
                    else if (counter == 3) {
                        // Ajoute à la variable lastLatitude
                        (*(lastLatitudePointer++)) = ',';
                        (*(lastLatitudePointer++)) = buf[0];
                        // Réinitialisation du pointeur sur le buffer
                        lastLatitudePointer = lastLatitude;
                        counter++;
                    }
                    // La cinquième donnée est la longitude
                    else if (counter == 4) {
                        // Cette instruction permet d'écrire dans la variable lastLatitude en écrasant les données
                        // précédentes
                        for (int i = 0; i < bufLength; i++) (*(lastLongitudePointer++)) = (*(bufPointer + i));
                        counter++;
                    }
                    // La sixième donnée est la direction : E (est) ou W (ouest)
                    else if (counter == 5) {
                        // Ajoute à la variable lastLongitude
                        (*(lastLongitudePointer++)) = ',';
                        (*(lastLongitudePointer++)) = buf[0];
                        // Réinitialisation du pointeur sur le buffer
                        lastLongitudePointer = lastLongitude;
                        counter = -1;
                        // À ce stade, la longitude et la latitude ont été acquises
                        // Donc l'acquistion est un succès
                        success = true;
                    }
                }
                // Si la donnée lue n'est pas une virgule, on l'ajoute au buffer
                else (*(bufPointer + bufLength++)) = data;

            }
            bufLength = 0;
            counter = 0;
        }
    }

    return success;
}