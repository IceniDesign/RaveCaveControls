#include <FastLED.h>

//~~~~~~~~~~ CONSTANTS ~~~~~~~~~~
#define buttonPin_BLACK   2
#define buttonPin_WHITE   3
#define buttonPin_RED   4
#define buttonPin_GREEN   5
#define buttonPin_BLUE   6
#define buttonPin_YELLOW   7
#define LED_PIN     8 // Arduino pin for LED strip
#define NUM_LEDS    12 // Number of LEDs in LED strip
#define BRIGHTNESS  30 // Percentage brightness of the LEDs
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BOUNCE 60 // twice the number of LEDs / time to go up and down
#define BUTTON_PAUSE 1000 //Pause for a some miliseconds to reduce stuttering
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

//~~~~~~~~~~ VARIABLES ~~~~~~~~~~
int buttonState_BLACK = 0;        // variable for reading the pushbutton status
int buttonState_WHITE = 0;        // variable for reading the pushbutton status
int buttonState_RED = 0;        // variable for reading the pushbutton status
int buttonState_GREEN = 0;        // variable for reading the pushbutton status
int buttonState_BLUE = 0;        // variable for reading the pushbutton status
int buttonState_YELLOW = 0;        // variable for reading the pushbutton status

String PATTERN = "BLACK"; //set the initial pattern

//Knightrider Variables
int DIRECTION = 1; // 1 is up 0 is down
int PIXEL = 0; // which Pixel are we affecting

//Pulse Variables
int fadeAmount = 3;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int PulseBright = 30; //Brightness to be used in the pulse pattern

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {
  // put your setup code here, to run once:
  delay( 1000 );                       // power-up safety delay

  // initialize the pushbutton pins as an input:
  pinMode(buttonPin_BLACK, INPUT);
  pinMode(buttonPin_WHITE, INPUT);
  pinMode(buttonPin_RED, INPUT);
  pinMode(buttonPin_GREEN, INPUT);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS ); // set the brightness

  currentPalette = PartyColors_p;
  currentBlending = LINEARBLEND;

}

void loop() {
  // read the state of the pushbutton values:
  buttonState_BLACK = digitalRead(buttonPin_BLACK);
  buttonState_WHITE = digitalRead(buttonPin_WHITE);
  buttonState_RED = digitalRead(buttonPin_RED);
  buttonState_GREEN = digitalRead(buttonPin_GREEN);
  buttonState_BLUE = digitalRead(buttonPin_BLUE);
  buttonState_YELLOW = digitalRead(buttonPin_YELLOW);

  // the pushbuttons select the patterns
  if (buttonState_BLACK == HIGH) { PATTERN = "BLACK"; }
  else if (buttonState_WHITE == HIGH) { PATTERN = "WHITE"; }
  else if (buttonState_RED == HIGH) { PATTERN = "RED"; }
  else if (buttonState_GREEN == HIGH) { PATTERN = "GREEN"; }
  else if (buttonState_BLUE == HIGH) { PATTERN = "BLUE"; }
  else if (buttonState_YELLOW == HIGH) { PATTERN = "YELLOW"; }

// ~~~~~~~~ What do the patterns do ~~~~~~~~
if(PATTERN == "BLACK"){
    currentPalette = RainbowStripeColors_p;
    currentBlending = NOBLEND;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors( startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  
  }  
else if (PATTERN == "WHITE") {
    currentPalette = PartyColors_p;
    currentBlending = LINEARBLEND;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors( startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
else if (PATTERN == "RED") {
    for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].r = 0xFF;  // Red
     leds[i].g = 0x00;  // Green
     leds[i].b = 0x00;  // Blue
    }
    FastLED.show();
  }
else if (PATTERN == "GREEN") {
    for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].r = 0x00;  // Red
     leds[i].g = 0xFF;  // Green
     leds[i].b = 0x00;  // Blue
    }
    FastLED.show();
  }
else if (PATTERN == "BLUE") {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i].r = 0x00;  // Red
      leds[i].g = 0x00;  // Green
      leds[i].b = 0xFF;  // Blue
    }
    FastLED.show();
  }
else if (PATTERN == "YELLOW") {
      currentPalette = CloudColors_p;
      currentBlending = LINEARBLEND;
    
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
  }

}
// ~~~~~~~~~~~~~~~~~~~~~~~~~ FAST LED PALETTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 10)  {
      currentPalette = RainbowStripeColors_p;
      currentBlending = NOBLEND;
    }
    if ( secondHand == 15)  {
      currentPalette = RainbowStripeColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 20)  {
      SetupPurpleAndGreenPalette();
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 25)  {
      SetupTotallyRandomPalette();
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 30)  {
      SetupBlackAndWhiteStripedPalette();
      currentBlending = NOBLEND;
    }
    if ( secondHand == 35)  {
      SetupBlackAndWhiteStripedPalette();
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 40)  {
      currentPalette = CloudColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 45)  {
      currentPalette = PartyColors_p;
      currentBlending = LINEARBLEND;
    }
    if ( secondHand == 50)  {
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = NOBLEND;
    }
    if ( secondHand == 55)  {
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = LINEARBLEND;
    }
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of black and red stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndRedStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Red;
  currentPalette[4] = CRGB::Red;
  currentPalette[8] = CRGB::Red;
  currentPalette[12] = CRGB::Red;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue
