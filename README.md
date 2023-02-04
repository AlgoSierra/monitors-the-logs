# monitors-the-logs
a program in C that monitors the logs of my operating system for suspicious activity, such as login attempts from unauthorized IP addresses, and sends notifications in real-time when it detects something suspicious.

Explanation of each line of code:

#include <stdio.h> - Includes the standard input/output library.
#include <stdlib.h> - Includes the standard library.
#include <string.h> - Includes the string library.
#include <unistd.h> - Includes the Unix standard library.
#include <sys/types.h> - Includes the system types library.
#include <sys/stat.h> - Includes the system status library.
#include <fcntl.h> - Includes the file control library.
#define LOG_FILE "/var/log/auth.log" - Defines the path to the log file to be monitored.
#define IP_ADDRESSES_ALLOWED "127.0.0.1 10.0.0.0/8 192.168.0.0/16" - Defines the IP addresses that



