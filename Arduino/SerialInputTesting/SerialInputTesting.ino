const int StepPin = 6;
const int DirPin = 7;

const byte NumChars = 128;

char ReceivedChars[NumChars];
boolean NewData = false;
boolean NewDataNotDealtWith = false;

int count;
unsigned long CurrentMillis;
int DelayInterval = 450;


void setup() {
  // put your setup code here, to run once:
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  Serial.begin(115200);
  Serial.print("<Arduino Is Ready>");
}

void loop() {
  // put your main code here, to run repeatedly:

  ReceiveCharsWithStartAndEndMarkers();
  Decoder();
  CurrentMillis = millis();



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
    else if(){

      
    }
   

    NewData = false;
    
  }


  
}
