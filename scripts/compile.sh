source ./scripts/consts.sh

# Vérifie si le compilateur avr-gcc est installé
if ! which avr-gcc >/dev/null 2>&1; then
    echo Le compilateur avr-gcc n\'est pas installé.
    exit 1
fi

# Création du dossier de sortie s'il n'existe pas
mkdir -p $OUTPUT_DIR
# Suppression des possibles anciens fichiers et dossiers
if [ -e "$OUTPUT_DIR/*" ]; then
    rm -r $OUTPUT_DIR/* 
fi

echo " ====> Étape 1 : Compilation des fichiers source..."

for LIB in $LIBS_DIR/**/*.cpp; do
    echo "-----> Compilation de ${LIB/$SOURCE_DIR/}..."

    if [ -e "$OUTPUT_DIR${LIB/$LIBS_DIR/}.o" ]; then
        echo "! ==> Attention : Le fichier ${LIB/$LIBS_DIR/}.o existe déjà !"
        echo "                  Le fichier sera écrasé."
    fi
    avr-gcc $AVR_GCC_COMPILE_ARGS $LIB -o $OUTPUT_DIR${LIB/$LIBS_DIR/}.o
    
    if [ $? -ne 0 ]; then
        echo
        echo "X ==> Erreur lors de compilation de $LIB !"
        exit 1
    fi
done

for CPP in $SOURCE_DIR/**/*.cpp; do
    echo "-----> Compilation de ${LIB/$SOURCE_DIR/}..."

    if [ -e "$OUTPUT_DIR${LIB/$LIBS_DIR/}.o" ]; then
        echo "! ==> Attention : Le fichier ${LIB/$LIBS_DIR/}.o existe déjà !"
        echo "                  Le fichier sera écrasé."
    fi

    avr-gcc $AVR_GCC_COMPILE_ARGS $LIB -o $OUTPUT_DIR${LIB/$LIBS_DIR/}.o
    
    if [ $? -ne 0 ]; then
        echo
        echo "X ==> Erreur lors de compilation de $LIB !"
        exit 1
    fi
done