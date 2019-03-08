// MazeSolver

  //Initialize Pins
    // H-Bridge Pins
int ena = 2;
int in4 = 3;
int in3 = 4;
int in1 = 5;
int in2 = 6;
int enb = 7;

    // RangeFinder Pins
int echoF = 8;
int triggerF = 9;
int echoR = 10;
int triggerR = 11;
int echoL = 12;
int triggerL = 13;

// Constants
#define LEFT 3
#define RIGHT 2
#define STRAIGHT 1
#define OBSTACLE_CLOSE 10  // Determines how close to a wall the robot must get before turning. May be adjusted
#define TURN_TIME 750     // How long to turn 90 degrees. Will need to be calibrated for each team

// Initialize variables
float straightDistance = 0, rightDistance = 0, leftDistance = 0;

void setup() {
      // Sets the pins as input pins or output pins, according to role
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(triggerF, OUTPUT);
  pinMode(echoF, INPUT);
  pinMode(triggerR, OUTPUT);
  pinMode(echoR, INPUT);
  pinMode(triggerL, OUTPUT);
  pinMode(echoL, INPUT);
  Serial.begin(9600);        // Sets the baud rate
}

// Will work, but doesn't actually guarantee a solved maze as it is right now
void loop() {
  GoStraight();
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

void GoStraight() {
    // Sets all wheels to forward     -    these may need to be changed
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

    // PWM to slow down the maze solver 
  for (int i = 0; i < 10; i++) {
    analogWrite(enb, 225);
    analogWrite(ena, 205);
    delay(5);
    analogWrite(enb, 0);
    analogWrite(ena, 0);
    delay(10);
  }

  return;
}

void LeftTurn90() {
  
    // Sets right wheel to forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 205);
    // Left wheel is turned off
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 0);
    // Continues for enough time to turn 90 degrees. TURN_TIME (top of file) will need to be adjusted 
  delay(TURN_TIME);   

  return;
}

void RightTurn90() {
    // Sets left wheel to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 0);
    // Left wheel is turned off
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 205);
    // Continues for enough time to turn 90 degrees. TURN_TIME (top of file) will need to be adjusted
  delay(TURN_TIME);
  return;
}

double GetDistance(int directions) {
  double duration, distance;

  if (directions == STRAIGHT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerF, LOW);

    delayMicroseconds(2);
    digitalWrite(triggerF, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoF, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    //Serial.println("distance1 =  ");
    //Serial.println(distance);
  } else if (directions == RIGHT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerR, LOW);

    delayMicroseconds(2);
    digitalWrite(triggerR, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoR, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    //Serial.println("distance2 =  ");
    //Serial.println(distance);
  } else if (directions == LEFT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerL, LOW);

    delayMicroseconds(3);
    digitalWrite(triggerL, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoL, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    // Serial.println("distance3 =  ");
    //Serial.println(distance);
  }
  return distance;

}
