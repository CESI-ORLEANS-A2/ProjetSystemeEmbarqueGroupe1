#include "consts.hpp"
#include "main.hpp"

extern char inputBuffer[INPUT_BUFFER_SIZE];
extern int inputLength;

void initInterpreter();
void runInterpreterStep();

void runCommand(char* command);

void printPrompt();
void printHelpCommand();
void printHelpNeededMode();
void printHelpDesciption();
void printHelpSyntax();
void printHelpArguments();
void printHelpListDash();
void printMode();
void printUnknownCommand();
void printBuffer();
void printModeAlreadyEnabled();
void printSpaces(int n);

void commandHelp(char* command);
void commandList();
void commandLive();
void commandMode(char* mode);