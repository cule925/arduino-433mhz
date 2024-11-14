#include <RH_ASK.h>
#include <SPI.h>

// Maximum message buffer size
#define MAX_MSG_SIZE 20

const char msg1[MAX_MSG_SIZE] = "Hello?";                     // First message to be sent
const char msg2[MAX_MSG_SIZE] = "Anyone there?";              // Second message to be sent

// RadioHead amplitude shift keying driver instance (default TX pin is 12)
RH_ASK driver;

// Setup function, called before loop only once
void setup() {
  Serial.begin(9600);                                         // Serial debug
  if (!driver.init()) Serial.println("Init failed");          // Initialize driver instance
}

// Looping function, send mesasages to the receiver
void loop() {
  driver.send((uint8_t*)msg1, MAX_MSG_SIZE);                  // Send the first message
  driver.waitPacketSent();                                    // Waiting until message is sent
  delay(1000);                                                // Delay a second
  driver.send((uint8_t*)msg2, MAX_MSG_SIZE);                  // Send the second message
  driver.waitPacketSent();                                    // Waiting until message is sent
  delay(1000);                                                // Delay a second
}
