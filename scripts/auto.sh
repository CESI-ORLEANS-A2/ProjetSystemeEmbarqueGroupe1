#! /bin/bash

CPU="-DF_CPU=16000000UL"
Target="-mmcu=atmega328p"



printf "########################\n"
printf "#    COMPIL ARDUINO    #\n"
printf "########################\n"

printf "spécidier le dossier : "
read -r f
ArduinoCores=/home/jean-broche/Libraries/ArduinoCore-avr-master/cores/arduino

MY_PATH="$(dirname -- "${BASH_SOURCE[0]}")"
MY_PATH="$(cd -- "$MY_PATH" && pwd)"

#création des fichier 
if test -d "$f";then
    cd $f
    if test -d ".tmp";then
        rm -rf .tmp/*
    else
        mkdir .tmp
    fi
    if test -d ".tmp/src";then
        rm -rf .tmp/src/*
    else
        mkdir .tmp/src
    fi
    if test -d "build";then
        rm -rf build/*
    else
        mkdir build
    fi
    echo "\nenv ready\n"

elif  test $f != "";then
    echo "le dossier $f n'existe pas"
    exit

else
    echo "pas de dossier spécifié"
    exit
fi

#compilation des fichier cpp de la librairie arduino cores
absf=$MY_PATH/$f
cd $ArduinoCores
for cppArd in *.cpp;do
    avr-g++ -Os $CPU $Target -I/home/jean-broche/Libraries/ArduinoCore-avr-master/cores/arduino -I/home/jean-broche/Libraries/ArduinoCore-avr-master/variants/standard -c $cppArd -o $absf/.tmp/${cppArd%.*}.o
done


#compilation des fichier c de la librairie arduino cores
for cArd in *.c;do
    avr-gcc -Os $CPU $Target -I/home/jean-broche/Libraries/ArduinoCore-avr-master/cores/arduino -I/home/jean-broche/Libraries/ArduinoCore-avr-master/variants/standard -c $cArd -o $absf/.tmp/${cArd%.*}.o
done

cd $MY_PATH/$f

#On place tous les fichier objets de la librairie dans un ficier archive
for Ol in .tmp/*.o;do
    filesOl="$filesOl $Ol"
done
avr-gcc-ar rc build/libframeworkarduino.a  $filesOl 

#création d'un fichier elf contenant l'archive de la librairie et le fichier source cpp
avr-g++ -o build/firmware.elf $Target $CPU -Os -I/home/jean-broche/Libraries/ArduinoCore-avr-master/variants/standard -I/home/jean-broche/Libraries/ArduinoCore-avr-master/cores/arduino main.cpp build/libframeworkarduino.a 

#création du fichier hexa à partir du fichier elf
avr-objcopy -O ihex -R .eeprom build/firmware.elf build/$f.hex

#téléversement du ficheir hex vers l'arduino
echo "procéder au téléversement ? [Y/N] :\n"
read T
if test $T=='Y';then
    echo "début du téléversement"
    avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/$f.hex
else 
    echo "Pas de téléversement"
fi


exit