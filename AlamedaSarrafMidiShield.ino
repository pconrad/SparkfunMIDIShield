/*
  MIDI Instrument Board
  By Alex Sarraf and Austin Alameda

 Board contains the following:
 Instrument LED display
 Tempo control knob
 Mode control knob
 Instrument incrementer
 Flex Sensor note control
 Piezo Element Drum Pad
 Musical Instrument Shield
 Arduino
 3.3V Supply
 5V Supply


 */
  int instrument=0; //Instrument number
  int beat=0;  //Beat number
  int mode=0; //Reads mode pin
  int sensorPin=0; //Tempo pin number
  int modeSelect=0; //Selects mode/beat to choose, default 0
  const int flexPin=1; //Flex sensor pin
  int beatPin=3; //Beat/mode pin
  int drum1=2; //Piezo pin
  int threshold=200; //Piezo threshold

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator

void setup() {
  pinMode(6, OUTPUT);  //Bottom
  pinMode(7, OUTPUT);  //Bottom Right
  pinMode(8, OUTPUT);  //Middle
  pinMode(9, OUTPUT);  //Top Right
  pinMode(10, OUTPUT); //Top Left
  pinMode(11, OUTPUT); //Top
  pinMode(5, OUTPUT);  //Bottom Left

  Serial.begin(57600);
  pinMode(2, INPUT); //Instrument selection
  pinMode(12, INPUT); //Mode selection

  //Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); //0xB0 is channel message, set channel volume to near max (127)
}

void loop() {
  int sensorValue;
  int trueValue;
  int flexposition; //Flex sensor value
  int state;
  int beat;

  beat=analogRead(beatPin);
   if(beat>1000){
    modeSelect=1;}
   else{
     modeSelect=0;
       }
  sensorValue=analogRead(sensorPin);
  state=digitalRead(2);

      if(state==HIGH)
        {
          while(state==HIGH)
          {
            state=digitalRead(2);
          }
          Serial.println("IF STATEMENT");
          if(instrument>29){
            instrument=-1;}
            note = 30;
            instrument++;

        }

  Serial.print("Mode: ");
  Serial.println(mode, DEC);



if(instrument>29)
  instrument=0;
    if(instrument%10==0)
    {
        digitalWrite(8, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(11, HIGH);
    }
else if(instrument%10==1)   {
        digitalWrite(8, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(5, LOW);
        digitalWrite(11, LOW);
    }
else if(instrument%10==2)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(11, HIGH);
    }
else if(instrument%10==3)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(5, LOW);
        digitalWrite(11, HIGH);
    }
else if(instrument%10==4)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(11, LOW);
    }
else if(instrument%10==5)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(11, HIGH);
    }
else if(instrument%10==6)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(11, HIGH);
    }
    else if(instrument%10==7)    {
        digitalWrite(8, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(5, LOW);
        digitalWrite(11, HIGH);
    }
    else if(instrument%10==8)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(11, HIGH);
    }
    else if(instrument%10==9)    {
        digitalWrite(8, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(11, HIGH);
    }


    //Read flex sensor
     flexposition=readFlex(flexPin);
     Serial.print("Flex value: ");
     Serial.println(flexposition, DEC);

  //Demo Basic MIDI instruments, GM1
  //=================================================================
  Serial.println("Basic Instruments");
  talkMIDI(0xB0, 0, 0x00); //Default bank GM1

 if(modeSelect==0)
  {

    beat=analogRead(beatPin);

  //Change to different instrument

    Serial.print(" Instrument: ");
    Serial.println(instrument, DEC);

    talkMIDI(0xC0, instrument, 0); //Set instrument number. 0xC0 is a 1 data byte command

      Serial.print("N:");
      Serial.println(note, DEC);
      //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):

      if(beat<250)
      {
        noteOn(0, 40+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 40+flexposition, 60);
      }

      if(beat>250 && beat<500)
      {
        delay(4*sensorValue/10);
      noteOn(0, 40+flexposition, 60);
      delay(sensorValue/10);
        noteOff(0, 40+flexposition, 60);
      delay(5*sensorValue/10);
      noteOn(0, 40+flexposition, 60);
      delay(sensorValue/10);
      noteOff(0, 40+flexposition, 60);
      delay(5*sensorValue/10);
      noteOn(0, 50+flexposition, 90);
      delay(6*sensorValue/10);
      noteOff(0, 50+flexposition, 90);
      }

      if(beat>500 && beat <750)
      {
       delay(4*sensorValue/10);
       noteOn(0, 60+flexposition, 60);
       delay(sensorValue/10);
        noteOff(0, 60+flexposition, 60);
         delay(4*sensorValue/10);
       noteOn(0, 80+flexposition, 60);
       delay(sensorValue/10);
        noteOff(0, 80+flexposition, 60);
         delay(4*sensorValue/10);
       noteOn(0, 90+flexposition, 60);
       delay(sensorValue/10);
        noteOff(0, 90+flexposition, 60);

      }

      if(beat>750 && beat <1000)
      {
        delay(8*sensorValue/10);
        noteOn(0, 60+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 60+flexposition, 60);
        delay(sensorValue/10);
        noteOn(0, 60+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 60+flexposition, 60);
        delay(sensorValue/10);
        noteOn(0, 30+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 30+flexposition, 60);
        delay(sensorValue/10);
        noteOn(0, 30+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 30+flexposition, 60);
        delay(sensorValue/10);
        noteOn(0, 50+flexposition, 70);
        delay(sensorValue/10);
        noteOff(0, 50+flexposition, 70);
        delay(sensorValue/10);
        noteOn(0, 50+flexposition, 70);
        delay(4*sensorValue/10);
        noteOff(0, 50+flexposition, 70);


      }


    delay(100); //Delay between instruments

  //=================================================================

  }
  else
  {
    int val=analogRead(drum1);
     //Change to different instrument

    Serial.print(" Instrument: ");
    Serial.println(instrument, DEC);

    talkMIDI(0xC0, instrument, 0); //Set instrument number. 0xC0 is a 1 data byte command

      Serial.print("N:");
      Serial.println(note, DEC);
      //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):



      if(val>threshold)
      {
        noteOn(0, 40+flexposition, 60);
        delay(sensorValue/10);
        noteOff(0, 40+flexposition, 60);
      }
  }



}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
int readFlex(int flexpin)
{
  int flex=analogRead(flexpin);
  return flex/5-150;
}
