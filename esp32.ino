#include <dummy.h>

/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point named in ssid
  2. Run PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for esp32-DEVKIT V1 on 2021/03/29
  by: Fernando Negozi
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "drone";
const char *password = "12345678";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  
  //Configure UART2
  Serial2.begin(115200,SERIAL_8N1, 16, 17);

  Serial.print("SSID=");
  Serial.print(ssid);
  Serial.print("\n");

  // with password parameter if you want the AP to be open.
/*  WiFi.softAP(ssid, password);
  Serial.print("PW=");
  Serial.print(password);
  Serial.print("\n");
*/
  // with AP open.
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      unsigned int dly;
      if(Serial.available()){
        client.write(Serial.read());
        Serial.flush();                       //erase any data
        dly=1000;
      }
      
      if(Serial1.available()){
        client.write(Serial1.read());
        Serial1.flush();                       //erase any data
        dly=1000;
      }

      if(Serial2.available()){
        client.write(Serial2.read());
        //Serial.println(Serial2.read());
        Serial2.flush();                       //erase any data
        dly=1000;
      }
      
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out
        Serial1.write(c);                   // print it out
        Serial2.write(c);                   // print it out
        
        dly=1000;
      }

      //led manage
      if(dly>0)
      {
        dly--;
         digitalWrite(LED_BUILTIN, HIGH);             //turns the LED on
      }
      else
        digitalWrite(LED_BUILTIN, LOW);               //LED off      
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
