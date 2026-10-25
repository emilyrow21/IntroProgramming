#include "ASSP.h"

// Define the array of device names
#define NUMNAMES 26
const char* names[NUMNAMES] = {
   "ANN", "BOB", "CAT", "DEL",
   "END", "FAX", "GYM", "HUB",
   "INK", "JUG", "KEN", "LEO",
   "MAX", "NIA", "OAK", "PEN",
   "QAZ", "ROB", "SUN", "TEA",
   "USB", "VAN", "WEB", "XIS",
   "YES", "ZIP"
};

#define LED_BLUE 11
#define LED_GREEN 10
#define LED_WHITE 9
#define LED_PINK 6
#define LED_YELLOW 5

// this function checks if a device is on a specific port
boolean isDeviceOnPort(const char name[], int port) {
   SerialShield.setMessageSender("ARDUINO");
   SerialShield.setMessageDestination(name);
   SerialShield.setMessageContent("ping");

   // retrys sending the message until successful
   for (int i = 0; i < 50; i++) {
       if (SerialShield.sendASSPMessage(port)) {
           break;
       }
       delay(100); 
   }

   
   for (int i = 0; i < 50; i++) {
       if (SerialShield.fetchASSPMessage()) {

           const char* destination = SerialShield.getMessageDestination();
           const char* sender = SerialShield.getMessageSender();
           const char* content = SerialShield.getMessageContent();

           Serial.print("Destination: ");
           Serial.println(destination);
           Serial.print("Sender: ");
           Serial.println(sender);
           Serial.print("Content: ");
           Serial.println(content);

           if (strcmp(destination, "ARDUINO") == 0 &&
               strcmp(sender, name) == 0 &&
               strcmp(content, "You pinged me") == 0) {
               return true;
           }
       }
       delay(100); 
   }

   return false;
}

// this function is to measure the time taken to send and receive a message
unsigned long getTimeToDevice(const char name[], int port) {
   SerialShield.setMessageSender("ARDUINO");
   SerialShield.setMessageDestination(name);
   SerialShield.setMessageContent("ping");

   unsigned long startTime = millis();

   // Retry sending the message until successful
   for (int i = 0; i < 50; i++) {
       if (SerialShield.sendASSPMessage(port)) {
           break;
       }
       delay(100); 
   }

   // Check for the response message
   for (int i = 0; i < 50; i++) {
       if (SerialShield.fetchASSPMessage()) {
           const char* destination = SerialShield.getMessageDestination();
           const char* sender = SerialShield.getMessageSender();
           const char* content = SerialShield.getMessageContent();

           if (strcmp(destination, "ARDUINO") == 0 &&
               strcmp(sender, name) == 0 &&
               strcmp(content, "You pinged me") == 0) {
               unsigned long endTime = millis();
               return endTime - startTime;
           }
       }
       delay(100); 
   }

   return 0; 
}

// Function to find the port a device is connected to
int getPortForDevices(const char name[]) {
   for (int port = 1; port <= 4; port++) {
       if (isDeviceOnPort(name, port)) {
           return port;
       }
   }
   return 0;
}

// Function to display a letter using LEDs
void displayLetter(char letter) {
   int value = letter - 'A' + 1;
   digitalWrite(LED_BLUE, (value & 0b10000) ? HIGH : LOW);
   digitalWrite(LED_GREEN, (value & 0b01000) ? HIGH : LOW);
   digitalWrite(LED_WHITE, (value & 0b00100) ? HIGH : LOW);
   digitalWrite(LED_PINK, (value & 0b00010) ? HIGH : LOW);
   digitalWrite(LED_YELLOW, (value & 0b00001) ? HIGH : LOW);
   delay(1000); 
}


void task1() {
   Serial.println("Enter port number: ");
   while (!Serial.available()) {}
   int port = Serial.parseInt();

   Serial.print("Checking devices on port ");
   Serial.println(port);

   for (int i = 0; i < NUMNAMES; i++) {
       Serial.print("Device ");
       Serial.print(names[i]);
       Serial.print(" Port ");
       Serial.print(port);
       Serial.print("? ");
       Serial.println(isDeviceOnPort(names[i], port) ? "YES" : "NO");
   }
}


void task2() {
   Serial.println("Checking devices on port 3...");

   unsigned long totalResponseTime = 0;
   int connectedDevicesCount = 0;

   Serial.println("Device\tPort 3 Time");

   for (int i = 0; i < NUMNAMES; i++) {
       unsigned long responseTime = getTimeToDevice(names[i], 3);
       Serial.print(names[i]);
       Serial.print("\t");
       if (responseTime > 0) {
           Serial.println(responseTime);
           totalResponseTime += responseTime;
           connectedDevicesCount++;
       } else {
           Serial.println("NC");
       }
   }

   if (connectedDevicesCount > 0) {
       unsigned long averageResponseTime = totalResponseTime / connectedDevicesCount;
       Serial.print("The average response time of devices connected to port 3 is: ");
       Serial.println(averageResponseTime);
   } else {
       Serial.println("No devices connected to port 3.");
   }
}


void task3() {
   Serial.println("Checking devices connected to port 4...");

   for (int i = 0; i < NUMNAMES; i++) {
       int port = getPortForDevices(names[i]);
       if (port == 4) {
           Serial.print("Device ");
           Serial.print(names[i]);
           Serial.println(" is connected to port 4");

           for (int j = 0; j < strlen(names[i]); j++) {
               char letter = names[i][j];
               int value = letter - 'A' + 1;
               Serial.print(letter);
               Serial.print(": ");
               Serial.println(value, BIN);
               displayLetter(letter);
           }
       }
   }
}


void task4() {
   // arrays to store devices connected to each port
   const char* port1Devices[NUMNAMES];
   const char* port2Devices[NUMNAMES];
   const char* port3Devices[NUMNAMES];
   const char* port4Devices[NUMNAMES];
   const char* ncDevices[NUMNAMES];

   // counters for each array
   int port1Count = 0;
   int port2Count = 0;
   int port3Count = 0;
   int port4Count = 0;
   int ncCount = 0;

   int portChecks = 0;

   // this iterates over each device
   for (int i = 0; i < NUMNAMES; i++) {
       int port = 0;
       for (int p = 1; p <= 4; p++) {
           portChecks++;
           if (isDeviceOnPort(names[i], p)) {
               port = p;
               break;
           }
       }

       // stores the device in the corresponding array
       if (port == 1) {
           port1Devices[port1Count++] = names[i];
       } else if (port == 2) {
           port2Devices[port2Count++] = names[i];
       } else if (port == 3) {
           port3Devices[port3Count++] = names[i];
       } else if (port == 4) {
           port4Devices[port4Count++] = names[i];
       } else {
           ncDevices[ncCount++] = names[i];
       }
   }

   // this prints the results 
   Serial.println("Port Devices");
   Serial.print("1 ");
   for (int i = 0; i < port1Count; i++) {
       Serial.print(port1Devices[i]);
       Serial.print(" ");
   }
   Serial.println();
   Serial.print("2 ");
   for (int i = 0; i < port2Count; i++) {
       Serial.print(port2Devices[i]);
       Serial.print(" ");
   }
   Serial.println();
   Serial.print("3 ");
   for (int i = 0; i < port3Count; i++) {
       Serial.print(port3Devices[i]);
       Serial.print(" ");
   }
   Serial.println();
   Serial.print("4 ");
   for (int i = 0; i < port4Count; i++) {
       Serial.print(port4Devices[i]);
       Serial.print(" ");
   }
   Serial.println();
   Serial.print("NC ");
   for (int i = 0; i < ncCount; i++) {
       Serial.print(ncDevices[i]);
       Serial.print(" ");
   }
   Serial.println();
   Serial.print("Port checks = ");
   Serial.println(portChecks);
}

void setup() {
   Serial.begin(57600);
   SerialShield.setEmuMode(6);
   
   pinMode(LED_BLUE, OUTPUT);
   pinMode(LED_GREEN, OUTPUT);
   pinMode(LED_WHITE, OUTPUT);
   pinMode(LED_PINK, OUTPUT);
   pinMode(LED_YELLOW, OUTPUT);
}

void loop() {
   task1();
  // task2();
   //task3();
  // task4();
   delay(10000); 
}
