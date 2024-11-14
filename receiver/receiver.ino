#include <RH_ASK.h>
#include <SPI.h>

// Maximum message buffer size
#define MAX_MSG_SIZE 20

// RadioHead amplitude shift keying driver instance (default RX pin is 11)
RH_ASK driver;
uint8_t buf[MAX_MSG_SIZE];                                    // Buffer for message
uint8_t buflen = MAX_MSG_SIZE;                                // Size of buffer

// Setup function, called only once before loop
void setup() {
  Serial.begin(9600);                                         // Serial debug
  if (!driver.init()) Serial.println("Init failed");          // Initialize driver instance
}

// Looping function, receive message from the transmitter
void loop() {
  if (driver.recv(buf, &buflen)) {                            // Receive the message
    buf[buflen] = '\0';                                       // Add null terminator to the end of the message
    Serial.print("Received message: ");                       // Print the message
    Serial.println((char *)buf);
  }
}
