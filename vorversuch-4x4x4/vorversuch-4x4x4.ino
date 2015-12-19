
int c[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A4, A5}; 
int z[4] = {A0, A1, A2, A3}; 
//vorversuch
void setup() 
{ 
  for(int i=0; i<16; i++) 
  {pinMode(c[i], OUTPUT);} 
  for(int i=0; i<4; i++) 
  {pinMode(z[i], OUTPUT);} 
}
void loop() 
{ 
  for(int i=0; i<16;i++)
  {digitalWrite(c[i], HIGH);
  }
  for(int i=0; i<4;i++)
  {digitalWrite(z[i], LOW);
  delay(1000);
  }
  for(int i=0; i<4;i++)
  {
  digitalWrite(z[i], HIGH);
  }
} 
