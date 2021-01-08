/*
 Name:		MeDi_Sketch.ino
 Created:	08.01.2021 16:52:50
 Author:	queck
*/

#define TRIGGER_PIN 13 //Ultraschall Trigger
#define ECHO_PIN 12 //Ultraschall Echo
#define LED_RED 11 //LED
#define LED_GREEN 10 //LED

//Sensor Parameter
long timeSignal = 0;
long distance = 0;
long maxDistance = 500;
long minDistance = 0;

//LED Variable(n)
long limitDistance = 5; // 5cm -> dann Warnsiganl

//Methoden
void ledGreen();

void setup()
{
	Serial.begin(9600);
	pinMode(TRIGGER_PIN, OUTPUT); //Sensor
	pinMode(ECHO_PIN, INPUT); //Sensor
	pinMode(LED_RED, OUTPUT); // LED
	pinMode(LED_GREEN, OUTPUT); // LED
}

//Methode zur Steuerung der grünen LED
void ledGreen()
{
	if (distance >= limitDistance || distance >= maxDistance)
	{
		digitalWrite(LED_GREEN, HIGH);
	}
	else
	{
		digitalWrite(LED_GREEN, LOW);
	}
}

void loop()
{
	//----------------------Post Process----------------------------------------------------
	//Ultraschallsensor
	digitalWrite(TRIGGER_PIN, LOW); //Spannnung am Anfang rausnehmen für ein rauschfreies Signal
	delay(5);

	//LED
	digitalWrite(LED_RED, LOW);
	ledGreen();

	//----------------------Begin Process---------------------------------------------------
	//Ultraschallsensor
	digitalWrite(TRIGGER_PIN, HIGH);
	delay(10); //Signal wird nach 10 m/s ausgesetzt
	digitalWrite(TRIGGER_PIN, LOW);
	timeSignal = pulseIn(ECHO_PIN, HIGH); //pulseIn -> zählt der Mikrokontroller die Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zurückkehrt
	distance = (timeSignal / 2) * 0.03432; //Berechnung Entfernung in cm, hin + zurück * SChallgeschwindigkeit (343,2 m/s)

	//Sensor
	//Definieren der Messgrenzen für Sensor
	if (distance >= maxDistance || distance <= minDistance)
	{
		Serial.println("Messurement of Range");
	}
	else
	{
		Serial.print(distance);
		Serial.println(" cm");
	}

	//LED
	//Anzeige kritischer Abstand LED
	if (distance <= limitDistance)
	{
		digitalWrite(LED_RED, HIGH);
	}
	else
	{
		digitalWrite(LED_RED, LOW);
	}

	delay(1000);
}
