#include "debugTools.hpp"

int freeRam() {
    // __heap_start : Adresse de début de le tas (heap)
    // __brkval : Adresse de fin du tas (heap)
    extern int __heap_start, * __brkval;

    // v : Variable locale, on utilise son adresse pour calculer la quantité de mémoire libre
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
    //                ^^^^^^^^^^^^^^ => Si le tas n'est pas initialisé, on utilise l'adresse de début du tas  
}