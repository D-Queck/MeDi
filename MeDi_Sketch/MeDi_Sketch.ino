/*
 Name:		MeDi_Sketch.ino
 Created:	08.01.2021 16:52:50
 Author:	queck
*/

#define TRIGGER_PIN 13 //Ultraschall Trigger
#define ECHO_PIN 12 //Ultraschall Echo
#define LED_ROT 11 //LED
#define LED_GRUEN 10 //LED

//Sensor Parameter
long timeSignal = 0;
long distance = 0;
long maxDistance = 500;
long minDistance = 0;

//LED Variable(n)
long grenzwert = 5; // 5cm -> dann Warnsiganl

void setup()
{
	Serial.begin(9600);
	pinMode(TRIGGER_PIN, OUTPUT); //Sensor
	pinMode(ECHO_PIN, INPUT); //Sensor
	pinMode(LED_ROT, OUTPUT); // LED
	pinMode(LED_GRUEN, OUTPUT); // LED
}

//Methode zur Steuerung der gr�nen LED
void ledGruen()
{
	if (distance >= grenzwert || distance >= maxDistance)
	{
		digitalWrite(LED_GRUEN, HIGH);
	}
	else
	{
		digitalWrite(LED_GRUEN, LOW);
	}
}

void loop()
{
	//----------------------Post Process----------------------------------------------------
	//Ultraschallsensor
	digitalWrite(TRIGGER_PIN, LOW); //Spannnung am Anfang rausnehmen f�r rauschfreies Signal
	delay(5);

	//LED
	digitalWrite(LED_ROT, LOW);
	ledGruen();

	//----------------------Begin Process---------------------------------------------------
	//Ultraschallsensor
	digitalWrite(TRIGGER_PIN, HIGH);
	delay(10); //Signal wird nach 10 m/s ausgesetzt
	digitalWrite(TRIGGER_PIN, LOW);
	timeSignal = pulseIn(ECHO_PIN, HIGH); //�pulseIn� z�hlt der Mikrokontroller die Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zur�ckkehrt
	distance = (timeSignal / 2) * 0.03432; //Berechnung Entfernung in cm, hin + zur�ck * SChallgeschwindigkeit (343,2 m/s)

	//Sensor
	//Definieren der Messgrenzen f�r Sensor
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
	if (distance <= grenzwert)
	{
		digitalWrite(LED_ROT, HIGH);
	}
	else
	{
		digitalWrite(LED_ROT, LOW);
	}

	delay(1000);
}
