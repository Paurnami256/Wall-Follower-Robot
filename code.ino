// Ultrasonic sensor pins
#define TRIG_PIN_LEFT 9
#define ECHO_PIN_LEFT 8
#define TRIG_PIN_FRONT 7
#define ECHO_PIN_FRONT 2
#define TRIG_PIN_RIGHT 13
#define ECHO_PIN_RIGHT 12

// Threshold distance for obstacle detection
#define OBSTACLE_THRESHOLD 20

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(MOTOR1_EN, OUTPUT);
  pinMode(MOTOR1A, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2_EN, OUTPUT);
  pinMode(MOTOR2A, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);

  // Set motor speed
  analogWrite(MOTOR1_EN, 255);
  analogWrite(MOTOR2_EN, 255);
}

void loop() {
  // Read distances from ultrasonic sensors
  int leftDist = getDistance(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
  int frontDist = getDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
  int rightDist = getDistance(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);

  // Check for obstacles
  if (leftDist > OBSTACLE_THRESHOLD) {
    // No obstacle on the left, turn left
    turnLeft();
    delay(500); // Adjust turn duration as needed
  } else if (frontDist > OBSTACLE_THRESHOLD) {
    // Obstacle on the left, but not in front, go forward
    goForward();
  } else {
    // Obstacle on the left and front, turn right
    turnRight();
    delay(500); // Adjust turn duration as needed
  }
}

void goForward() {
  digitalWrite(MOTOR1A, HIGH);
  digitalWrite(MOTOR1B, LOW);
  digitalWrite(MOTOR2A, HIGH);
  digitalWrite(MOTOR2B, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR1A, LOW);
  digitalWrite(MOTOR1B, HIGH);
  digitalWrite(MOTOR2A, HIGH);
  digitalWrite(MOTOR2B, LOW);
}

void turnRight() {
  digitalWrite(MOTOR1A, HIGH);
  digitalWrite(MOTOR1B, LOW);
  digitalWrite(MOTOR2A, LOW);
  digitalWrite(MOTOR2B, HIGH);
}

int getDistance(int trigPin, int echoPin) {
  // Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read pulse duration
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance
  int distance = duration * 0.034 / 2;
  
  return distance;

}
