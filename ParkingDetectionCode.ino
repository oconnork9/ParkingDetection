
//Pin Configurations
#define pinLaser1 //Enter pin #
#define pinLaser2 //Enter pin #
#define pinLaser3 //Enter pin #
#define pinLaser4 //Enter pin #
#define pinLaser5 //Enter pin #
#define pinLaser6 //Enter pin #
#define pinLaser7 //Enter pin #
#define pinReceiver1 //Enter pin #
#define pinReceiver2 //Enter pin #
#define pinReceiver3 //Enter pin #
#define pinReceiver4 //Enter pin #
#define pinReceiver5 //Enter pin #
#define pinReceiver6 //Enter pin #
#define pinReceiver7 //Enter pin #
//Current State
int State = 0;
//Timers
int Cnts2 = 0;
int Cnts3 = 0;
int Cnts6 = 0;
int Cnts7 = 0;
int M = 0;
int AvgM = 0;

//Timer Comparisons
const int Thavl = 0;
const int THdpt = 0;
const int Ndpt1 = 0;
const int Ndpt2 = 0;
const int Navl1 = 0;
const int Navl2 = 0;
const int Tmin = 0;
const int Tmax = 0;

//Flags
bool Flginit = false;
bool Flgcn;
bool Flgcdm;
bool Flgcrf;
bool Statecrf;
bool Statecdm;
bool Statecrf;

void setup() {
  pinMode(pinLaser1, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser2, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser3, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser4, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser5, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser6, OUTPUT); // set the laser pin to output mode
  pinMode(pinLaser7, OUTPUT); // set the laser pin to output mode
  pinMode(pinReceiver1, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver2, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver3, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver4, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver5, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver6, INPUT); // set the laser pin to output mode
  pinMode(pinReceiver7, INPUT); // set the laser pin to output mode
  digitalWrite(pinLaser1, HIGH); // emit red laser
  digitalWrite(pinLaser2, HIGH); // emit red laser
  digitalWrite(pinLaser3, HIGH); // emit red laser
  digitalWrite(pinLaser4, HIGH); // emit red laser
  digitalWrite(pinLaser5, HIGH); // emit red laser
  digitalWrite(pinLaser6, HIGH); // emit red laser
  digitalWrite(pinLaser7, HIGH); // emit red laser
  Serial.begin(9600); // Setup serial connection for print out to console
}

void loop() {
//  int value = digitalRead(pinReceiver); // receiver/detector send either LOW or HIGH (no analog values!)
//  Serial.println(value); // send value to console
//  delay(1000); // wait for 1000ms
switch(State){
  case '0':
while(State == 0)
  {
    if(Flginit){
      State = 1;
    }
    else
    {
     State = 0;
    }
  }
  break;
  
  case '1':
 while(State == 1)
  {
    if(M < Thavl)
    {
      State = 1;
    }
    else if(M >= Thavl)
    {
      State = 2;
    }
  } 
  break;
  
  case '2':
while(State == 2)
  {
    if(Cnts2<Navl1)
    {
      State = 2;
    }
    else if(Cnts2 >= Navl1 && AvgM < Tmax)
    {
      State = 4;
    }
    else if(M < Thavl)
    {
      State = 3;
    }
    else if(Cnts2 >= Navl1 && AvgM >= Tmax)
    {
      State = 5;
    }
  } 
  break;
  
  case '3':
while(State == 3)
  {
    if(Cnts3 =< Navl2)
    {
      State = 3;
    }
    else if(M >= Thavl)
    {
      State = 2;
    }
    else if(Cnts3 > Navl2)
    {
      State = 1;
    }
  }
  break;
  
  case '4':
while(State == 4)
  {
    if(Flgcdm == 0)
    {
      State = 4;
    }
    else if(Flgcdm == true && Statecdm == true)
    {
      State = 5;
    }
    else if(Flgcrf == true && Statecrf == false)
    {
      State = 1;
    }
  }
  break;
  
  case '5':
while(State == 5)
  {
    if(M >= Thadpt)
    {
      State = 5;
    }
    else if(M < Thadpt)
    {
      State = 6;
    }
  }
  break;
  
  case '6':
 while(State == 6)
  { 
    if(Cnts6 < Ndpt1)
    {
      State = 6;
    }
    else if(M >= Thdpt)
    {
      State = 7;
    }
    else if(Cnts6 >= Ndpt1 && AvgM >= Tmin)
    {
      State = 8;
    }
    else if(Cnts6 >= Ndpt1 && AvgM < Tmin)
    {
      State = 1;
    }
  }
  break;
  
  case '7':
while(State == 7)
  {
    if(Cnts7 < Ndpt2)
    {
      State = 7;
    }
    else if(M < Thdpt)
    {
      State = 6;
    }
    else if(Cnts >= Npdt2)
    {
      State = 5;
    }
  }
  break;
  
  case '8':
  while(State == 8)
  {
    if(Flgcdm == false)
    {
      State = 8;
    }
    else if(Flgcrf == true && Statecrf == true)
    {
      State = 5;
    }
    else if(Flgcdm == true && Statecdm == false)
    {
      State == 1;
    }
  }
  break;
}
}
