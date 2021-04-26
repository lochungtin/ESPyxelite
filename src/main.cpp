#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include "env.h"

#define DEBUG

// server object
WebServer server(80);

// post request json buffer
StaticJsonDocument<250> jsonDocument;

// turn on all RGB components
void lightsOn()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Lights On");
#endif
}

// turn off all RGB components
void lightsOff()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Lights Off");
#endif
}

// new config
void handleConfig()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Set New Config");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	String data = server.arg("plain");
	deserializeJson(jsonDocument, data);

	int test = jsonDocument["test"];

	Serial.println(test);
}

// initial setup procedure
void setup()
{
#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Connecting to WiFi");
#endif

	// Connect to access point
	WiFi.begin(ENV_SSID, ENV_PSWD);
	while (WiFi.status() != WL_CONNECTED)
		;

#ifdef DEBUG
	Serial.print("Connected - Local IP: ");
	Serial.println(WiFi.localIP());
#endif

	// Rest API routing setup
	server.on("/on", lightsOn);	  // toggle on
	server.on("/off", lightsOff); // toggle off
	server.on("/config", HTTP_POST, handleConfig);

	server.begin();
}

// handle http client
void loop()
{
	server.handleClient();
}
