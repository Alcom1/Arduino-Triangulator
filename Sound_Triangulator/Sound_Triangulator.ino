/*
 * Volume measure code derived from:
 * https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 */

#include <toneAC.h>
#include "vect.h"

const int sampleWindow = 50; // Sample window for mics
unsigned int sample;         // Sample from mics

const int inPins[] = {A0, A1, A2};          //Pins for analog input (potes, mics)
const int outPins[] = {3, 5, 6, 11};        //Pins for LED outputs
const bool isMics[] = {false, false, true}; //If each input is a mic

//Vector location of the inputs
Vect inLocs[] = {
    {-0.866, 0.5},
    {0, -1},
    {0.866, 0.5}};

//Vector location of the outputs
Vect outLocs[] = {
    {0.707, -0.707},
    {0.707, 0.707},
    {-0.707, 0.707},
    {-0.707, -0.707}};

//Setup
void setup()
{
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
}

//Loop
void loop()
{
    unsigned long startMillis= millis();    // Start of sample window
    unsigned int maxs[] = {0, 0, 0};          // max value from mic
    unsigned int mins[] = {1024, 1024, 1024}; // min value from mic
    double volts[3];
    
    Vect inTots = {0, 0}; //Total positional vector of analog inputs.
    while (millis() - startMillis < sampleWindow)
    {
        for(int i = 0; i < 3; i++)
        {
            sample = analogRead(inPins[i]);
            if (sample < 1024)  // toss out spurious readings
            {
                if (sample > maxs[i])
                {
                    maxs[i] = sample;  // save just the max levels
                }
                else if (sample < mins[i])
                {
                    mins[i] = sample;  // save just the min levels
                }
            }
        }
    }

    //Set volts
    for(int i = 0; i < 3; i++)
    {
        volts[i] = ((maxs[i] - mins[i]) * 3.3) / 1024;  // convert to volts
    }
    
    //Add inputs to total.
    for(int i = 0; i < 3; i++)
    {
        if(isMics[i])
            inTots += inLocs[i] * mapFloat(max(volts[i], 0), 0.0, 2.25, 0, 1);
        else
            inTots += inLocs[i] * mapFloat(analogRead(inPins[i]), 0, 1023, 0, 1);
    }

    //If total is not close to zero, light up the LEDs in its direction.
    if(inTots.getLength() > 0.05)
    {
        //For each LED, write to it.
        for(int i = 0; i < 4; i++)
        {
            analogWrite(
              outPins[i],
              max(          //Ignore anything less than 0
                mapFloat(   //Map LED angle to output value.
                  outLocs[i].getAngleBetween(inTots),
                  0,
                  PI / 2,
                  255,
                  0),
                0));
        }
    }
    //Else, write nothing to the LEDs
    else
    {
        for(int i = 0; i < 4; i++)
        {
            analogWrite(outPins[i], 0);
        }
    }

    //Play tone
    toneAC(max(analogRead(A3), 0));
}

//Map method for floats.
float mapFloat(float x, float inMin, float inMax, float outMin, float outMax)
{
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

