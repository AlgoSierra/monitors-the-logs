#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_FILE "/var/log/auth.log"
#define IP_ADDRESSES_ALLOWED "127.0.0.1 10.0.0.0/8 192.168.0.0/16"

int main(int argc, char** argv) {
  int log_file = open(LOG_FILE, O_RDONLY);
  char buffer[1024];
  int bytes_read;
  char* token;

  while (1) {
    lseek(log_file, 0, SEEK_END); // move to the end of the log file
    while ((bytes_read = read(log_file, buffer, 1024)) > 0) {
      buffer[bytes_read] = '\0'; // null-terminate the buffer
      char* line = strtok(buffer, "\n");
      while (line != NULL) {
        if (strstr(line, "Failed password for") != NULL ||
            strstr(line, "Invalid user") != NULL) {
          // Extract the IP address
          token = strtok(line, " ");
          int count = 0;
          while (token != NULL) {
            if (count == 9) {
              char* ip_address = token;
              // Check if the IP address is allowed
              if (strstr(IP_ADDRESSES_ALLOWED, ip_address) == NULL) {
                // Send a notification
                printf("Suspicious activity detected from IP address: %s\n", ip_address);
              }
            }
            count++;
            token = strtok(NULL, " ");
          }
        }
        line = strtok(NULL, "\n");
      }
    }
    sleep(1);
  }
  close(log_file);
  return 0;
}
