#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "logger.h"

char *name = NULL;
LOGGING_LEVELS LOG_LEVEL = OFF;
LOGGING_LEVELS log_level_user = OFF;

// This function sets the name of the log file
void LoggerSetOutputName(char *nam) {
    name = malloc(strlen(nam) + 1);
    strcpy(name, nam);
}

// This function logs the message to the file
void Logger(LOGGING_LEVELS level, char *message) {
    if (LOG_LEVEL == OFF) {
        return;
    }
    log_level_user = level;
    if (log_level_user < LOG_LEVEL) {
        return;
    }
    else{
    FILE *fp = fopen(name, "a");
    if (fp == NULL) {
        printf("Error opening file %s for writing log", name);
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (log_level_user == OFF) {
        fprintf(fp, "OFF");
    }
    else if (log_level_user == INFO) {
        fprintf(fp, "INFO");
    }
    else if (log_level_user == WARNING) {
        fprintf(fp, "WARNING");
    }
    else if (log_level_user == ERROR) {
        fprintf(fp, "ERROR");
    }
    fprintf(fp, " %d-%d-%d %d:%d:%d %s", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, message);
    fprintf(fp, "\n");
    
    fclose(fp);
    }
}


// This function sets the log level
void LoggerSetLevel(LOGGING_LEVELS level) {
   LOG_LEVEL = level;
}


