/*

 Author: Allen Downey

 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain

 Reference websites:

 http://playground.arduino.cc/Code/BitMath#registers
 http://www.instructables.com/id/Arduino-Timer-Interrupts/
 http://arduino.cc/en/Tutorial/DueSimpleWaveformGenerator#.Uxc_I3VdVBs
 http://arduino.cc/en/Reference/attachInterrupt

 */

/*
 * Global Variables
 */

int ledPin = 5;     // select the pin for the LED

// Changed for my circuit
//int buttonPin1 = 2;
//int buttonPin2 = 3;
int buttonPin1 = 3;
int buttonPin2 = 2;

int low = 36;
int high = 255;
//int stride = 5;
int stride = 3;
int counter = low;

#define ENABLE_BITWISE_OPERATION

/*
 * printPORT()
 */
void printPORT(int v)
{
    // Function for debugging
    Serial.print("v: ");
    Serial.print(v, DEC);
    Serial.print(" / ");
    Serial.println(v, BIN);
    Serial.println("=====");
    Serial.print("D: ");
    Serial.print(PORTD, DEC);
    Serial.print(" / ");
    Serial.println(PORTD, BIN);
    Serial.print("B: ");
    Serial.print(PORTB, DEC);
    Serial.print(" / ");
    Serial.println(PORTB, BIN);
    Serial.println("");
}

/*
 * writeByte()
 */
#ifdef ENABLE_BITWISE_OPERATION

void writeByte(int x)
{
    // my circuit has reversed order of R2R DAC physically,
    // so don't need to care about reverse-bit.

    // 7 ~ 0  (7, 6)
    PORTD = (PORTD & B00111111) | (x << 6);

    // 15 ~ 8 (13, 12, 11, 10, 9, 8)
    PORTB = x >> 2;
}

#else

void writeByte(int x)
{
    int pin;

    //for (pin=13; pin>=6; pin--) {
    for (pin=6; pin<=13; ++pin) {
        // 6: x&1       bit 0
        // 7: (x>>1)&1  bit 1
        digitalWrite(pin, x&1);
        x >>= 1;
    }
}

#endif

void buttonFunc()
{
    OCR0A += 10;
}

/*
 * setup()
 */
void setup()
{
    int i;

    Serial.begin(9600);

    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);

    pinMode(ledPin, OUTPUT);

    for (i = 6; i <= 13; ++i) {
        pinMode(i, OUTPUT);
    }

    // external interrupt

    attachInterrupt(0, buttonFunc, FALLING);

    // timer interrupt

    cli();//stop interrupts

    //set timer0 interrupt at 2kHz
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B
    TCNT0  = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR0A = 100;// = (16*10^6) / (2000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);

    sei();//allow interrupts
}

ISR(TIMER0_COMPA_vect)
{
    counter += stride;
    if (counter > high) {
        counter = low;
    }
    writeByte(counter);
}

/*
 * loop()
 */
void loop()
{
/*
    int button1 = digitalRead(buttonPin1);
    digitalWrite(ledPin, LOW);
    if (button1) return;

    digitalWrite(ledPin, HIGH);

    counter += stride;
    if (counter > high) {
        counter = low;
    }

    // write to the digital pins
    writeByte(counter);
*/

    // To compare PORTD and PORTB
    //printPORT(counter);
}
