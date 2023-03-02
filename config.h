#pragma once
#include<string>
using namespace std;

// WiFi credentials
const char * SSID =  "ChamplainPSK";
const char * PASSWORD = "letusdare";

// MQTT settings
const string ID = "Murat"; //Putt something different
const string BROKER = "broker.hivemq.com";
const string CLIENT_NAME = ID + "remotelight_client";
const int TCP_PORT = 1883;


const string CLIENT_TELEMETRY_TOPIC =  "testtopic/temp";
