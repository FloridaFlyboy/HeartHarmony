#include <FastLED.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library

#define LED_PIN     5
#define NUM_LEDS    98  
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

const int PulseWire = 0;       // 'S' Signal pin connected to A0
const int LED13 = 13;          // The on-board Arduino LED
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore
                               
PulseSensorPlayground pulseSensor;  // Creates an object


CRGBPalette16 currentPalette;
TBlendType    currentBlending;



void setup() {
    delay( 3000 ); // power-up safety delay
    Serial.begin(9600);

  // Configure the PulseSensor object, by assigning our variables to it
    pulseSensor.analogInput(PulseWire);   
    pulseSensor.blinkOnPulse(LED13);       // Blink on-board LED with heartbeat
    pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and began seeing a signal
    if (pulseSensor.begin()) {
      Serial.println("51");
    }
      
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = CloudColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    int myBPM = pulseSensor.getBeatsPerMinute();      // Calculates BPM

    if (pulseSensor.sawStartOfBeat()) {               // Constantly test to see if a beat happened
      Serial.println(myBPM);                        // Print the BPM value
    }

    delay(20);
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    if (myBPM>100) {
      FillLEDsFromPaletteColors( startIndex);
    }
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
