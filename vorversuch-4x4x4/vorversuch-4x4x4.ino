//s f"ur s"aule, e f"ur ebene
int s[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A4, A5}; 
int e[4] = {A0, A1, A2, A3}; 
//vorversuch
void setup() 
{ 
  for(int i=0; i<16; i++) 
  {pinMode(s[i], OUTPUT);} 
  for(int i=0; i<4; i++) 
  {pinMode(e[i], OUTPUT);} 
}
//damit ne diode (i,j) aus [0,15]x[0,3] leuchtet, muss s"aule i an Plus und ebene j an Minus!
//so ist es zumindest beim behrendtschen prototyp 
void loop() 
{ 
  for(int i=0; i<4;i++)
  {digitalWrite(e[i], LOW);
  delay(1000);
  }
  for(int i=0; i<16;i++)
  {digitalWrite(s[i], HIGH);
  }
  
  for(int i=0; i<4;i++)
  {
  digitalWrite(e[i], HIGH);
  }
  delay(2000);
} 
