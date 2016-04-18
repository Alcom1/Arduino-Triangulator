#include "vect.h"

const int inPins[] = {A0, A1, A2};
const int outPins[] = {3, 5, 6, 9};

Vect inLocs[] = {
  {-0.866, -0.5},
  {0, 1},
  {0.866, -0.5}};

Vect outLocs[] = {
  {0.707, -0.707},
  {0.707, 0.707},
  {-0.707, 0.707},
  {-0.707, -0.707}};

const float outAngles[] = {
  -45,
  45,
  135,
  225};

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup()
{
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
}

void loop()
{
    Vect inTots = {0, 0};

    for(int i = 0; i < 3; i++)
    {
        sensorValue = analogRead(inPins[i]);
        outputValue = map(sensorValue, 0, 1023, 0, 108);
        inTots += inLocs[i] * mapFloat(sensorValue, 0, 1023, 0, 1);
    }

    if(inTots.getLength() > 0.05)
    {
        for(int i = 0; i < 4; i++)
        {
            analogWrite(
              outPins[i],
              max(
                mapFloat(
                  outLocs[i].getAngleBetween(inTots),
                  0,
                  PI / 2,
                  255,
                  0),
                0));
        }
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            analogWrite(outPins[i], 0);
        }
    }
        
    delay(2);
}

float dist(Vect a, Vect b)
{
    return sqrt(
      (a.x - b.x) *(a.x - b.x) +
      (a.y - b.y) *(a.y - b.y));
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

