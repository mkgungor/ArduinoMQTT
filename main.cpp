#include <Arduino.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

#include "config.h"

void connectWiFi()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi..");
        WiFi.begin(SSID, PASSWORD);
        delay(500);
    }

    Serial.println("Connected!");
} 


WiFiClient wifiClient;
PubSubClient client(wifiClient);

void clientCallback(char *topic, uint8_t *payload, unsigned int length)
{
    char buff[length + 1];
    for (int i = 0; i < length; i++)
    {
        buff[i] = (char)payload[i];
    }
    buff[length] = '\0';

    Serial.print("Message received:");
    Serial.println(buff);
    String message = buff;
    Serial.println(message);

    if (message == "TurnOnLight")
        digitalWrite(LED_BUILTIN, HIGH);
    else
        digitalWrite(LED_BUILTIN, LOW);
}



void reconnectMQTTClient()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect(CLIENT_NAME.c_str()))
        {
            Serial.println("connected");     
            client.subscribe(CLIENT_TELEMETRY_TOPIC.c_str());
        }
        else
        {
            Serial.print("Retying in 5 seconds - failed, rc=");
            Serial.println(client.state());            
            delay(5000);
        }
    }
}

void createMQTTClient()
{
    client.setServer(BROKER.c_str(), TCP_PORT);
    client.setCallback(clientCallback);
    reconnectMQTTClient();
}

void setup() {
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  pinMode(LED_BUILTIN, OUTPUT);
  connectWiFi();
  createMQTTClient();
}

void loop() {
  reconnectMQTTClient();
  client.loop();
 /*
  string telemetry = "TurnOnLight";

  client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
  Serial.println("Turn On - Message Sent");
  delay(2000);


  telemetry = "TurnOffLight";
  client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
  Serial.println("Turn Off - Message Sent");
  delay(2000);
  */
}