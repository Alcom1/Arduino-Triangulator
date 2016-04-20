#include "vect.h"

const int inPins[] = {A0, A1, A2};  //Pins for analog input (potes, mics)
const int outPins[] = {3, 5, 6, 11}; //Pins for LED outputs

//Vector location of the inputs
Vect inLocs[] = {
  {0.866, -0.5},
  {0, 1},
  {-0.866, -0.5}};

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
    Vect inTots = {0, 0}; //Total positional vector of analog inputs.

    //Add inputs to total.
    for(int i = 0; i < 3; i++)
    {
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
        
    delay(2);
}

//Map method for floats.
float mapFloat(float x, float inMin, float inMax, float outMin, float outMax)
{
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

