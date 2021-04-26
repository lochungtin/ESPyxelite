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

// new color
void handleColor()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Set New Color");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	deserializeJson(jsonDocument, server.arg("plain"));
	String color = jsonDocument["payload"];
	jsonDocument.clear();

#ifdef DEBUG
	Serial.print("Received new color: ");
	Serial.println(color);
#endif
}

// new action
void handleAction()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Set New Action");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	deserializeJson(jsonDocument, server.arg("plain"));
	String action = jsonDocument["payload"];
	jsonDocument.clear();

#ifdef DEBUG
	Serial.print("Received new action: ");
	Serial.println(action);
#endif
}

// new speed
void handleSpeed()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Set New Speed");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	deserializeJson(jsonDocument, server.arg("plain"));
	int speed = jsonDocument["payload"];
	jsonDocument.clear();

#ifdef DEBUG
	Serial.print("Received new speed: ");
	Serial.println(speed);
#endif
}

// new brightness
void handleGamma()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Set New Brightness");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	deserializeJson(jsonDocument, server.arg("plain"));
	int gamma = jsonDocument["payload"];
	jsonDocument.clear();

#ifdef DEBUG
	Serial.print("Received new brightness: ");
	Serial.println(gamma);
#endif
}

// new config
void handleConfig()
{
	server.send(200, "OK");
#ifdef DEBUG
	Serial.println("Override Config");
#endif

	// handle empty post requests
	if (server.hasArg("plain") == false)
	{
#ifdef DEBUG
		Serial.println("No JSON arg, no config set");
#endif
		return;
	}

	deserializeJson(jsonDocument, server.arg("plain"));
	String color = jsonDocument["color"];
	String action = jsonDocument["action"];
	int speed = jsonDocument["speed"];
	int gamma = jsonDocument["gamma"];
	jsonDocument.clear();

#ifdef DEBUG
	Serial.println("New Config Data:");
	Serial.print("Color:\t");
	Serial.println(color);
	Serial.print("Action:\t");
	Serial.println(action);
	Serial.print("Speed:\t");
	Serial.println(speed);
	Serial.print("Brightness:\t");
	Serial.println(gamma);
#endif
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
	server.on("/on", lightsOn);					   // toggle on
	server.on("/off", lightsOff);				   // toggle off
	server.on("/color", HTTP_POST, handleColor);   // change color
	server.on("/action", HTTP_POST, handleAction); // change action
	server.on("/speed", HTTP_POST, handleSpeed);   // change speed
	server.on("/gamma", HTTP_POST, handleGamma);   // change brightness
	server.on("/config", HTTP_POST, handleConfig); // override everything with new config

	server.begin();
}

// handle http client
void loop()
{
	server.handleClient();
}
