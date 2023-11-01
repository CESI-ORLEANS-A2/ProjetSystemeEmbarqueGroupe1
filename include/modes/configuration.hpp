#ifndef ConfigurationMode_h
#define ConfigurationMode_h

#include "main.hpp"

extern unsigned long* lastActivity;

#if !INTERPRETER
extern char configurationInputBuffer[INPUT_BUFFER_SIZE];
extern int configurationInputLength;

void configurationRunCommand(char* command);
#endif

void switchToConfigurationMode();
void quitConfigurationMode();
void runConfigurationModeStep();

void updateLastActivity();

void printInvalidValue();

#endif