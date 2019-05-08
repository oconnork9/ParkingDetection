//Pin Configurations
#define buttonPin 52//Button Pin number
#define trigPin 12
#define echoPin 11

//Current State
int State = 0; //Current State Initiallized to first state

//Timers
int Cnts2 = 0; //Counter in State 2
int Cnts3 = 0; //Counter in State 3
int Cnts6 = 0; //Counter in State 4
int Cnts7 = 0; //Counter in State 5
int M; //Sensor distance reading
int D = 1; //Denominator Value for Averager
int AvgM = 0; //Average Value from Sensor used in states 2 and 6
int buttonState = 0; //Used for Button activation starting state machine
int Navl1 = 7000; //Constant keeping system in State 2 for 7 seconds
int Navl2 = 5000; //Constant keeping system in State 3 for 5 seconds
int Ndpt1 = 7000; //Constant keeping system in State 6 for 7 seconds
int Ndpt2 = 5000; //Constant keeping system in State 7 for 5 seconds
int x;
long lecture_echo;

//Distance Comparison Constants
const int Thavl = 2300 - 10;
const int Thdpt = 2300 - 13;
const int Tmin = 2300 - 15;
const int Tmax = 2300 - 6;

//Flags
bool Flginit = false;
bool Flgcn;
bool Flgcdm;
bool Flgcrt;
bool Statecrt;
bool Statecdm;

void setup() {
  pinMode(buttonPin, INPUT); //Sets Button Input pin
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Setup serial connection for print out to console
}

void loop() {
  switch (State) { //Switches between states
    case 0:

      Serial.println("State 0"); //Initial State
      while (State == 0) //Stays in loop until State Change
      {
        M = distance(M); //Ultrasonic distance reading
        buttonState = digitalRead(buttonPin);

        if (buttonState == HIGH) { //Determines if button is pressed

          Flginit = true;

        }
        else {

          Flginit = false;
        }
        if (Flginit) { //Determines button was changed State change
          State = 1;
        }
        else
        {
          State = 0;
        }
      }
      break;

    case 1:
      Serial.println("State 1"); //Vacant State
      while (State == 1) //Keeps in state til state change
      {
        M = distance(M); //Measurement reading
        if (M < Thavl) //Compares Distance value to constant
        {

          State = 1; //Arrival not detected
        }
        else if (M >= Thavl)
        {
          State = 2; //Arrival detected
        }
      }
      break;

    case 2:
      Serial.println("State 2"); //Interim Arrival 1
      Navl1 = Navl1 + millis(); //Sets time til
      while (State == 2)
      {
        Cnts2 = millis(); //Sets current time

        M = distance(M); //Takes measurement reading
        if (M < Thavl) //Compares Distance value to constant
        {
          State = 3; //Arrival no longer detected
        }
        else if ((Cnts2 >= Navl1) && (AvgM < Tmax))
        {
          State = 4; //Arrival detected with noise
        }
        else if ((Cnts2 >= Navl1) && (AvgM >= Tmax))
        {
          State = 5; //Arrival detected complete
        }
        else if (Cnts2 < Navl1)
        {
          State = 2; //Stays in state until times match
        }
        if (AvgM == 0) //Takes first sample
        {
          AvgM = M;
        }
        else {
          D = D + 1;
          AvgM = (AvgM + M) / D; //Averages samples taken for 7 seconds filtering noise
        }
      }
      AvgM = 0;
      Navl1 = 7000; //Change this to the original Navl1 value
      D = 1;
      break;

    case 3:
      Serial.println("State 3"); //Interim Arrival 2
      M = distance(M); //Measurement reading
      Navl2 = Navl2 + millis(); //Sets time til

      while (State == 3) //Keeps in state til state change
      {
        Cnts3 = millis(); //Sets current time
        M = distance(M); //Takes distance measurement
        if (Cnts3 > Navl2) //Compares time in state
        {
          State = 1; //Changes to Vacant
        }
        else if (M >= Thavl) //Checks change in distance
        {
          State = 2;
        }
        else if (Cnts3 <= Navl2) //Stays in state until timer or change in distance
        {
          State = 3;
        }

      }
      Cnts3 = 0;
      Navl2 = 5000;
      break;

    case 4:
      Serial.println("State 4"); //Critical Arrival

      while (State == 4) //Keeps in state til state change
      {
        Flgcdm = false;
        Statecdm = false;
        Flgcdm = true;
        Flgcrt = false;
        Statecrt = true;
        M = distance(M); //Measurement reading
        if ((M >= 2294) && (M <= 2300)) //Changes to Occupied
        {
          Flgcdm = true;
          Statecdm = true;
        }
        else if ((M >= 2287) && (M < 2294)) //Stays Critical
        {
          Flgcdm = false;
        }
        else if (M < 2287)
        {
          Flgcrt = true;
          Statecrt = false;

        }
        if (Flgcdm == false)
        {
          State = 4;
        }
        else if ((Flgcdm == true) && (Statecdm == true))
        {
          State = 5;
        }
        else if ((Flgcrt == true) && (Statecrt == false))
        {
          State = 1;
        }
      }
      Navl2 = 5000;
      break;

    case 5:
      Serial.println("State 5"); //Occupied State
      while (State == 5) //Keeps in state til state change
      {
        M = distance(M); //Measurement reading
        if (M >= Thdpt)
        {
          State = 5;
        }
        else if (M < Thdpt)
        {
          State = 6;
        }
      }
      break;

    case 6:
      Serial.println("State 6"); //Interim of Departure 1
      Ndpt1 = millis() + Ndpt1;
      while (State == 6) //Keeps in state til state change
      {
        Cnts6 = millis();
        M = distance(M); //Measurement reading
        if ((Cnts6 >= Ndpt1) && (AvgM < Tmin)) //Departure detected complete
        {
          State = 1;
        }
        else if (M >= Thdpt) //No longer departing
        {
          State = 7;
        }
        else if ((Cnts6 >= Ndpt1) && (AvgM >= Tmin)) //Departure detected with noise
        {
          State = 8;
        }
        else if (Cnts6 < Ndpt1) //Compares times stays in state
        {
          State = 6;
        }
        if (AvgM == 0) //Takes first sample
        {
          AvgM = M;
        }
        else {
          D = D + 1; //Changes dividing factor
          AvgM = (AvgM + M) / D; //Averages samples taken for 7 seconds filtering noise
        }
      }
      AvgM = 0;
      Ndpt1 = 7000; //Set value to initial
      D = 1;
      break;

    case 7:
      Serial.println("State 7"); //Interim Deparure 2
      Ndpt2 = Ndpt2 + millis(); //Sets timer
      while (State == 7) //Keeps in state til state change
      {
        Cnts7 = millis(); //Current time
        M = distance(M); //Measurement reading
        if (Cnts7 < Ndpt2)
        {
          State = 7;
        }
        else if (M < Thdpt)
        {
          State = 6;
        }
        else if (Cnts7 >= Ndpt2)
        {
          State = 5;
        }
      }
      Ndpt2 = 5000; //Reverts initial value
      break;

    case 8:
      Serial.println("State 8");//Critical Departure
      while (State == 8) //Keeps in state til state change
      {
        Flgcrt = false;
        Statecrt = true;
        Flgcdm = false;
        Flgcdm = false;
        Statecdm = true;
        M = distance(M);
        if ((M >= 2285) && (M <= 2300)) //Changes to Occupied
        {
          Flgcrt = true;
          Statecrt = true;
          Flgcdm = true;
        }
        else if ((M >= 2283) && (M < 2285)) //Stays Critical
        {
          Flgcdm = false;
        }
        else if (M < 2283) //Change to Vacant
        {
          Flgcdm = true;
          Statecdm = false;

        }
        if (Flgcdm == false) //Changes State
        {
          State = 8;
        }
        else if ((Flgcrt == true) && (Statecrt == true))
        {
          State = 5;
        }
        else if ((Flgcdm == true) && (Statecdm == false))
        {
          State = 1;
        }
      }
      break;
  }

}
int distance(int M) //Measures distance from Utrasonic sensor
{
  int distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  lecture_echo = pulseIn(echoPin, HIGH);
  distance = 2300 - (lecture_echo / 58); //Converts measurements inorder to better correspond to state machine
  //Serial.println(2300-distance); //Displayed distance from sensor for debugging
  delay(1000);
  if (distance < 2282) { //Greatly decreases noise sensor sometimes screw measurement gives range of 18cm
    return M;
  }
  else {
    return distance;
  }
}
