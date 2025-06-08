#ifndef LOGS_H
#define LOGS_H

typedef enum {
  LOG_ALL,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_NONE
} LogType;

extern LogType log_level;

int log_out(LogType log_type, const char *format, ...);

int set_logtype(LogType log_type);

#endif  // LOGS_H
