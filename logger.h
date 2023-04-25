#ifndef logger_h
#define logger_h

// Logging levels for the logger
typedef enum {
    OFF,
    INFO,
    WARNING,
    ERROR
}LOGGING_LEVELS;

/* 
 *   Description: Logs a message to the output file.
 *
 *   level: The level of the message.
 *   message: The message to be logged.
 *
 *   returns: void
 */
void Logger(LOGGING_LEVELS level, char *message);

/* 
 * Function: LoggerSetOutputName
 * ----------------------------
 *   Description: Sets the name of the output file.
 *
 *   nam: The name of the output file.
 *
 *   returns: void
 */
void LoggerSetOutputName(char *nam);

/* 
 *   Description: Sets the level of the logger.
 *
 *   level: The level of the logger.
 *
 *   returns: void
 */
void LoggerSetLevel(LOGGING_LEVELS level);

#endif /* logger_h */