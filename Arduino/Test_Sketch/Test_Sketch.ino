const int StepPin = 6;
const int DirPin = 7;
int count;
int DelayInterval = 450;

void setup() {
  // put your setup code here, to run once:  
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  digitalWrite(DirPin, HIGH);
  //delay(500);
  digitalWrite(StepPin, LOW);
  delayMicroseconds(DelayInterval);
  digitalWrite(StepPin, HIGH);
  delayMicroseconds(DelayInterval);
  */
  digitalWrite(DirPin, HIGH);
  for(count = 0; count<200; count++){
    
    digitalWrite(StepPin, LOW);
    delayMicroseconds(DelayInterval);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(DelayInterval);
  }
  digitalWrite(DirPin, LOW);
  //delay(500);
  for(count = 0; count<200; count++){
    
    digitalWrite(StepPin, LOW);
    delayMicroseconds(DelayInterval);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(DelayInterval);
  }
  
 
}
