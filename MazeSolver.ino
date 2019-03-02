// MazeSolver

    //Initialize Pins
    
int ena = 2;
int in4 = 3;
int in3 = 4;
int in1 = 5;
int in2 = 6; 
int enb = 7;

int echoF = 8;
int triggerF = 9;
int echoR = 10;
int triggerR = 11;
int echoL = 12;
int triggerL = 13;

int directionPinRight = in3; 
int directionPinLeft = in1;
int pwmPin = ena;           
int pwmPin2 = enb;
int sleepPin = in4;
int sleepPin2 = in2;
int echo1 = echoF;
int trigger1 = triggerF;
int echo2 = echoR;
int trigger2 = triggerR;
int echo3 = echoL;
int trigger3 = triggerL;

    // Constants
// double wheelRadius = 2.6;
int LEFT = 3;
int RIGHT = 2;
int STRAIGHT = 1;
int OBSTACLE_CLOSE = 10;
int TURN_TIME = 1000; // Make relative to PWM 

    // Initialize variables    
float straightDistance = 0, rightDistance = 0, leftDistance = 0;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(trigger1, OUTPUT);
  pinMode(echoF,INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(trigger3, OUTPUT);
  pinMode(echo3,INPUT);
  Serial.begin(9600);
}

    // Doesn't actually guarantee a solved maze - need to adjust to left/right hand rule
void loop() {
  // TurnOnWheels();
  GoStraight();
//  straightDistance = (straightDistance*0.8) + (0.2*GetDistance(STRAIGHT));
//  rightDistance = (rightDistance*0.8) + (0.2*GetDistance(RIGHT));
//  leftDistance = (leftDistance*0.8) + (0.2*GetDistance(LEFT));
    straightDistance = GetDistance(STRAIGHT);
    rightDistance = GetDistance(RIGHT);
    leftDistance = GetDistance(LEFT);
    
    if (straightDistance < OBSTACLE_CLOSE) {
      if (leftDistance < OBSTACLE_CLOSE && rightDistance < OBSTACLE_CLOSE) {
        LeftTurn90();
        LeftTurn90();
      }
      else if (leftDistance > rightDistance) {
        LeftTurn90();
      }
      else if (rightDistance > leftDistance) {
        RightTurn90();
      }
    }
    
    
}

    // Incomplete. Can we do this with our motors? Seconds * velocity?
void inchesToTravel(int x) {
  
  return;
}

void GoStraight() {
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  
  for (int i = 0; i < 10; i++) {
  analogWrite(enb, 225); 
  analogWrite(ena, 205);
  delay(5);
  analogWrite(enb, 0);
  analogWrite(ena, 0);
  delay(14);
  }
  
  // digitalWrite(directionPinRight,HIGH);
  // digitalWrite(directionPinLeft,LOW);
  // analogWrite(pwmPin,127);
  // analogWrite(pwmPin2,127);
  return;
}

void RightTurn90() {
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  analogWrite(ena, 205); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enb, 0);
  
  delay(TURN_TIME);
  
  // digitalWrite(directionPinRight,LOW);
  // digitalWrite(directionPinLeft,LOW);
  // delay(TURN_TIME);
  return;
}

void LeftTurn90() {
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  analogWrite(ena, 0);
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enb, 205); 
  
  // digitalWrite(directionPinRight,HIGH);
  // digitalWrite(directionPinLeft,HIGH);
  delay(TURN_TIME);
  return;
}

// void TurnOnWheels () {
//       digitalWrite(sleepPin,HIGH);
//       digitalWrite(sleepPin2,HIGH);
//       analogWrite(pwmPin,205);
//       analogWrite(pwmPin2,205);
//       return;
// }

// void TurnOffWheels () {
//       digitalWrite(sleepPin,LOW);
//       digitalWrite(sleepPin2,LOW);
//       analogWrite(pwmPin,0);
//       analogWrite(pwmPin2,0);
//       return;
// }

double GetDistance(int directions) {
  double duration, distance;
  if (directions == STRAIGHT) {
  digitalWrite(trigger1,LOW);
  
  delayMicroseconds(2);
  digitalWrite(trigger1,HIGH);
  
  delayMicroseconds(10);
  duration = pulseIn(echoF,HIGH);
  distance = (duration/2)*0.0343;
 
  Serial.println("distance1 =  ");
 
  //Serial.println(distance);
  }
  else if (directions == RIGHT) {
  digitalWrite(trigger2,LOW);
  
  delayMicroseconds(2);
  digitalWrite(trigger2,HIGH);
  
  delayMicroseconds(10);
  duration = pulseIn(echo2,HIGH);
  distance = (duration/2)*0.0343;
 
  Serial.println("distance2 =  ");
 
  //Serial.println(distance);
  }

  else if (directions == LEFT) {
  digitalWrite(trigger3,LOW);
  
  delayMicroseconds(3);
  digitalWrite(trigger3,HIGH);
  
  delayMicroseconds(10);
  duration = pulseIn(echo3,HIGH);
  distance = (duration/2)*0.0343;
 
  Serial.println("distance3 =  ");
 
  //Serial.println(distance);
  }
  return distance;

}
