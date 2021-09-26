const int StepPin = 6;
const int DirPin = 7;

const byte NumChars = 128;

char ReceivedChars[NumChars];
boolean NewData = false;
boolean NewDataNotDealtWith = false;

int count;
unsigned long CurrentMillis;
unsigned long PreviousStepperMillis;

byte FastStepperInterval = 1;
byte SlowStepperInterval = 10; 
byte StepperInterval = 1;

boolean ForwardRotationFlag = false;
boolean BackwardRotationFlag = false;



void setup() {
  // put your setup code here, to run once:
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  Serial.begin(115200);
  Serial.print("<Arduino Is Ready>");
}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();
  ReceiveCharsWithStartAndEndMarkers();
  Decoder();
  ForwardRotationFunction();
  BackwardRotationFunction();



}

void ReceiveCharsWithStartAndEndMarkers() {

  static boolean ReceiveInProgress = false;
  static byte count = 0;
  char StartMarker = '<';
  char EndMarker = '>';
  char ReceivedCharacter;

  while (Serial.available() > 0 && NewData == false) {

    ReceivedCharacter = Serial.read();

    if (ReceiveInProgress == true) {

      if (ReceivedCharacter != EndMarker) {

        ReceivedChars[count] = ReceivedCharacter;
        count++;

        if (count >= NumChars) {

          count = NumChars - 1;

        }

      }
      else {
        ReceivedChars[count] = '\0';
        ReceiveInProgress = false;
        count = 0;
        NewData = true;
      }
    }
    else if (ReceivedCharacter == StartMarker) {

      ReceiveInProgress = true;

    }

  }

}

void Decoder(){

  if(NewData == true){
    
    String ReceivedString = ReceivedChars;

    
    if(ReceivedString == "Comm Check"){

      Serial.print("<Readback>");
      
    }
    else if(ReceivedString == "Forward"){

      ForwardRotationFlag = true;
      
    }
    else if(ReceivedString == "Backward"){

      BackwardRotationFlag = true;
      
    }

    else if(ReceivedString == "Stop"){

      ForwardRotationFlag = false;
      BackwardRotationFlag = false;
    }
   

    NewData = false;
    
  }


  
}

void ForwardRotationFunction(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && ForwardRotationFlag == true){
     
     digitalWrite(DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(StepPin, LOW);
      Status = LOW;
     }
     
  PreviousStepperMillis = CurrentMillis;

  }
  
  
}

void BackwardRotationFunction(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && BackwardRotationFlag == true){
     
     digitalWrite(DirPin, LOW);
     if(Status == LOW){
      digitalWrite(StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(StepPin, LOW);
      Status = LOW;
     }
     
  PreviousStepperMillis = CurrentMillis;

  }
  
  
}
