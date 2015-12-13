//Allgemeine Einstellungen

//Wuerfelgroesse einstellen, 3x3x3 oder 4x4x4. Kein "=" und ";" bei "#define"!!
#define XYZ_SIZE 4
//Effektgeschwindigkeit
#define VELOCITY 1000
//Effektwiederhohlung
#define REPEATS 2


//Programmcode
int velocity = VELOCITY;
int isOn = HIGH;
int leds[] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,A4,A5};
int numLeds = sizeof(leds)/sizeof(int);
int levelPins[] = {A0,A1,A2,A3};
int levelMap[4]; // 4 layers of 16 bits each
byte level = 0; // Used by refreshCube
int frame = 0;
union{
  byte v4x4x4[XYZ_SIZE][XYZ_SIZE][XYZ_SIZE];
  byte v64[XYZ_SIZE*XYZ_SIZE*XYZ_SIZE];
}bitmap;

void loop() 
{
  constante_schraege_ebene();  
}

void constante_schraege_ebene()
{
   for (byte k=0; k<XYZ_SIZE; k++)
   {
    Clearbitmap();
     for (byte x=0; x<XYZ_SIZE; x++)
     {
      for (byte y=0; y<XYZ_SIZE; y++)
      {
        if(XYZ_SIZE+k-y<=4)
        {
        bitmap.v4x4x4[x][y][(XYZ_SIZE+k-y)]=1;
        }
      }
     }
     CopyToDisplay();
   delay(velocity);
   }
}


void CopyToDisplay()
{
  for (byte x=0; x < XYZ_SIZE; x++)
    for (byte y=0; y < XYZ_SIZE; y++)
      for (byte z=0; z < XYZ_SIZE; z++)
        if (bitmap.v4x4x4[x][y][z])
          bitSet(levelMap[ z ], x*XYZ_SIZE + y);
         else 
          bitClear(levelMap[ z ], x*XYZ_SIZE + y);
}

void RefreshCube()
{  
  //-- Turn off previous level before we mess with the 16 anodes --
  byte levelPin = levelPins[level];
  digitalWrite(levelPin, LOW);
  
  //-- Compute next level, but don't turn it on until we setup the 16 anodes for the new level --
  level++;
  if (level==XYZ_SIZE) level=0;
  
  //-- Setup the 16 anodes for this level --
  int thisLevel = levelMap[level];
  for (byte led=0; led < numLeds; led++)
  {
    byte ledPin = leds[led];
    byte ledState = bitRead( thisLevel, led );
    digitalWrite(ledPin, ledState);
  }

  //-- Now that the 16 anodes are set, turn on the layer (won't be turned off till next refresCube) --
  levelPin = levelPins[level];
  digitalWrite(levelPin, HIGH);
}


void setup() {
  for (byte pin=0; pin < 20; pin++)
  {
    pinMode(pin, OUTPUT);     
  }
  Clearbitmap(); SetupTimer(); CopyToDisplay();
}

void SetupTimer()
{
  cli(); // Stop global interrupt
  
  TCCR1A = 0; // Timer/Counter Control Register 1 A
  TCCR1B = 0; // Timer/Counter Control Register 1 B
  TCCR1B |= (1 << WGM12); // Configure Timer 1 for CTC mode
  OCR1A = 0xFF; // CTC Compare value
  TIMSK1 |= (1 << OCIE1A); // Tell CTC to call interrupt routine in addition to setting CTC flag
  TCCR1B |= (1 << CS10); // CS10, CS11, CS12 bits control prescaler. 
  TCCR1B |= (1 << CS11); // CS10, CS11, CS12 bits control prescaler. 
  
  sei(); // enable global interrupt again
}

ISR(TIMER1_COMPA_vect)
{
  RefreshCube();
}

void Clearbitmap()
{
  for (byte x=0; x < XYZ_SIZE; x++)
    for (byte y=0; y < XYZ_SIZE; y++)
      for (byte z=0; z < XYZ_SIZE; z++)
        bitmap.v4x4x4[x][y][z] = 0;
}


