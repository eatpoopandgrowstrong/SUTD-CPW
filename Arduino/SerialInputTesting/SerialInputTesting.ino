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
byte SlowStepperInterval = 3; 
byte StepperInterval = 1;

boolean ForwardRotationFlag = false;
boolean BackwardRotationFlag = false;

byte CurrentLevel = 1;
byte SelectedLevel = 0;
boolean LevelSelectionFlag = false;


const int StepsBetween1and2 = 220;
const int StepsBetween2and3 = 450; 

boolean UpwardsMovementFlag = false;
boolean DownwardsMovementFlag = false;

int StepperCount;


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
  LevelCalculator();
  UpwardsMovement();
  DownwardsMovement();



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

    else if(ReceivedString == "Fast"){

      StepperInterval = FastStepperInterval;  
    
    }

   else if(ReceivedString == "Slow"){

      StepperInterval = SlowStepperInterval;
    
   }

   else if(ReceivedString == "Level1"){

      SelectedLevel = 1;
      LevelSelectionFlag = true;

   }

   else if(ReceivedString == "Level2"){

      SelectedLevel = 2;
      LevelSelectionFlag = true;

   }

   else if(ReceivedString == "Level3"){

      SelectedLevel = 3;
      LevelSelectionFlag = true;

   }


    NewData = false;
    
  }


  
}

void ForwardRotationFunction(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && ForwardRotationFlag == true){
     
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

void BackwardRotationFunction(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && BackwardRotationFlag == true){
     
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


void LevelCalculator(){

  /*
  Question is how to lay this out, if 1, move X amount of steps to that location?
  Start with from Level 1?
  */
  /*
   * 
   *  This function is a piece of garbage
   */
  if(LevelSelectionFlag == true){

    if(CurrentLevel != SelectedLevel){

      if(CurrentLevel == 1 && SelectedLevel == 2){

        StepperCount = StepsBetween1and2;
        UpwardsMovementFlag = true;
        
        
      }

      else if(CurrentLevel == 1 && SelectedLevel == 3){

        StepperCount = StepsBetween1and2 + StepsBetween2and3;
        UpwardsMovementFlag = true;
        
      }

      else if(CurrentLevel == 2 && SelectedLevel == 1){

        StepperCount = StepsBetween1and2;
        DownwardsMovementFlag = true;
        
      }

      else if(CurrentLevel == 2 && SelectedLevel == 3){

        StepperCount = StepsBetween2and3;
        UpwardsMovementFlag = true;
        
      }

      else if(CurrentLevel == 3 && SelectedLevel == 1){

        StepperCount = StepsBetween1and2 + StepsBetween2and3;
        DownwardsMovementFlag = true;
        
      }

      else if(CurrentLevel == 3 && SelectedLevel == 2){

        StepperCount = StepsBetween2and3;
        DownwardsMovementFlag = true;
        
      }
      
    } 

  LevelSelectionFlag = false;

  }
  

} 

void UpwardsMovement(){

  static boolean Status = LOW;
  static int count;

  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && UpwardsMovementFlag == true){

    if (count < StepperCount) {

      digitalWrite(DirPin, LOW);
      if (Status == LOW) {

        digitalWrite(StepPin, HIGH);
        Status = HIGH;

      }
      else if (Status == HIGH) {

        digitalWrite(StepPin, LOW);
        Status = LOW;
        count++;

      }


    }
    else if (count == StepperCount) {
      count = 0;
      UpwardsMovementFlag = false;
      CurrentLevel = SelectedLevel;
     

    }
  PreviousStepperMillis = CurrentMillis;
  }
  
}

void DownwardsMovement(){
  
  static boolean Status = LOW;
  static int count;

  if(CurrentMillis - PreviousStepperMillis >= StepperInterval && DownwardsMovementFlag == true){

    if (count < StepperCount) {

      digitalWrite(DirPin, HIGH);
      if (Status == LOW) {

        digitalWrite(StepPin, HIGH);
        Status = HIGH;

      }
      else if (Status == HIGH) {

        digitalWrite(StepPin, LOW);
        Status = LOW;
        count++;

      }


    }
    else if (count == StepperCount) {
      count = 0;
      DownwardsMovementFlag = false;
      CurrentLevel = SelectedLevel;
      

    }
  PreviousStepperMillis = CurrentMillis;
  }

}



 
