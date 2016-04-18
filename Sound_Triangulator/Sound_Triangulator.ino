#include "vect.h"

const int inPins[] = {A0, A1, A2};
const int outPins[] = {3, 5, 6, 9};

Vect inLocs[] = {{0, 0}, {1, 0}, {0, 1}};
Vect outLocs[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup()
{
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
}

void loop()
{
    for(int i = 0; i < 3; i++)
    {
        sensorValue = analogRead(inPins[i]);
        outputValue = map(sensorValue, 0, 1023, 0, 108);
        analogWrite(outPins[i], outputValue);

        if(i == 1)
        {
            Serial.println((inLocs[1] + outLocs[1]).x);
            /*
            Serial.print("sensor = ");
            Serial.print(sensorValue);
            Serial.print("\t output = ");
            Serial.println(outputValue);
            */
        }
    }
    
    delay(2);
}

