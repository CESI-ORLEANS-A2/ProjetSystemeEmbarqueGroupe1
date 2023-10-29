MMCU="atmega328p"
DF_CPU="16000000L"

SOURCE_DIR="src"
LIBS_DIR="libs"

OUTPUT_DIR="build"
OUTPUT_HEX="firmware.hex"

AVR_GCC_BASE_ARGS="-Os -mmcu=$MMCU"
AVR_GCC_COMPILE_ARGS="$AVR_GCC_BASE_ARGS -c -DF_CPU=$DF_CPU -I$LIBS_DIR"

