#include <dummy.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
 
const char *ssid = "Automa";

WiFiServer server(80);
 
void setup() {
 
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

  WiFiClient client = server.available();  

  if (client) {                            

    Serial.println("New Client.");          
    String currentLine = "";              
    String acquiredData = "";
    while (client.connected()) {          

      if (client.available()) {              
        currentLine = client.readString();        
        Serial.println(currentLine);             
        //client.println(currentLine);        
        Serial2.print(currentLine);             

      }
      if (currentLine.equals("dSE\n")) {
        Serial.println("INIZIO ACQUISIZIONE...");                  
        acquiredData = Serial2.readStringUntil('\n');                     
        Serial.println("Ricevuto dalla scheda: "+ acquiredData);  
        client.println(acquiredData);
                
      }

      if (currentLine.equals("dND\n")) {
      //  Serial.println("FINE ACQUISIZIONE.");
        client.stop();
      }

    }
    Serial.println("Client Disconnected.");
  }

 

}