#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "env.h"

#define DEBUG
WebServer server(80);

// turn on all RGB components
void lightsOn()
{
#ifdef DEBUG
	Serial.println("Lights On");
#endif

	server.send(200, "OK");
}

// turn off all RGB components
void lightsOff()
{
#ifdef DEBUG
	Serial.println("Lights Off");
#endif

	server.send(200, "OK");
}

// initial setup procedure
void setup()
{
// put your setup code here, to run once:
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
	server.on("/on", lightsOn);			// toggle on
	server.on("/off", lightsOff);		// toggle off

	server.begin();
}

// handle http client
void loop()
{
	server.handleClient();
}
