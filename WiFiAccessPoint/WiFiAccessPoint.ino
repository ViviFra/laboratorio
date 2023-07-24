#include <dummy.h>




#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

const char *ssid = "Automa";
const char *password = "12345678";

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  Serial.println();
  Serial.println("Configuring access point...");
  Serial.print("SSID=");
  Serial.print(ssid);
  Serial.print("\n");

  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial2.begin(115200);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port

    String currentLine = "";                // make a String to hold incoming data from the client
    String acquiredData = "";
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        currentLine = client.readString();        // read a byte, then
        Serial.println(currentLine);
       // client.println(currentLine);
        Serial2.print(currentLine);
      }
      if (currentLine.equals("dND\n")) {
        Serial.println("INIZIO ACQUISIZIONE...");
        acquiredData = Serial2.readString();
        Serial.println("Ricevuto dalla scheda: "+ acquiredData);
        Serial.println("FINE ACQUISIZIONE.");
        client.println(acquiredData);
        client.stop();
      }
    }

    Serial.println("Client Disconnected.");
  }
}
