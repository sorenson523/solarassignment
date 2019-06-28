#include <Servo.h>

const int servopin=6;
const int swpin=4;
const int basepin=7;
const int photo1=A5;
const int photo2=A4;
const int threshold=600;
int power;
int state;
int photoval1;
int photoval2;
int avgval;
Servo servo;

void setup()
{
  pinMode (swpin, INPUT_PULLUP);
  pinMode (basepin, OUTPUT);
  servo.attach(servopin);
  digitalWrite(basepin, HIGH);
  servo.write(0);
  delay(1000);
  digitalWrite (basepin, LOW);
  Serial.begin(9600);
}

int calculateval()
{
  photoval1=analogRead(photo1);
  photoval2=analogRead(photo2);
  avgval=(photoval1+photoval2)/2;
  Serial.println(avgval);
  return avgval;
}

void turnservo(int avgval)
{
  if (avgval >= threshold)
  {
    digitalWrite(basepin, HIGH);
    servo.write(90);
    delay (1000);
    digitalWrite (basepin, LOW);
  }
  else
  {
    digitalWrite(basepin, HIGH);
    servo.write(0);
    delay (1000);
    digitalWrite (basepin, LOW);
  }
}

void loop()
{
  power=digitalRead(swpin);
  if (power==HIGH && state==0)
  {
    avgval=calculateval();
    turnservo(avgval);
    state=1;
  }
  else if (power==LOW && state==1)
  {
    digitalWrite(basepin, HIGH);
    servo.write(0);
    delay(1000);
    digitalWrite(basepin, LOW);
    delay(50);
  }
  else if (power==HIGH && state==1)
  {
    avgval=calculateval();
    turnservo(avgval);
  }
  
}
