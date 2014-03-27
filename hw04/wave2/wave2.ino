/*

 Author: Allen Downey

 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain

 */

/*
 * Global Variables
 */

int ledPin = 5;     // select the pin for the LED
//int buttonPin1 = 2;
//int buttonPin2 = 3;
int buttonPin1 = 3;
int buttonPin2 = 2;

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

/*
 * writeByte()
 */
void writeByte(int x)
{
    int pin;

    //for (pin=13; pin>=6; pin--) {
    for (pin = 6; pin <= 13; ++pin) {
        digitalWrite(pin, x&1);
        x >>= 1;
    }
}

/*
 * setup()
 */
void setup()
{
    Serial.begin(9600);

    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);

    pinMode(ledPin, OUTPUT);

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
}

/*
 * loop()
 */
void loop()
{
    int button1 = digitalRead(buttonPin1);
    if (button1) return;

    counter += stride;
    if (counter > high) {
        counter = low;
        //Serial.println(counter);
    }

    // write to the digital pins
    writeByte(counter);
}
