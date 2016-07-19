#include <SD.h>                      // need to include the SD library
#include <TMRpcm.h>           //  also need to include this library...

#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328

File root;
 
TMRpcm tmrpcm;   // create an object for use in this sketch
 
void setup(){
 
 // Serial.begin(9600);
 
  tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  //  Serial.print("SD KArte nicht initialisiert");
  return;   // don't do anything more if not
  }
  
  root = SD.open("/");

  // printDirectory(root, 0);

  //Serial.println("done!");
 tmrpcm.setVolume(1);
 tmrpcm.quality(1); 
 tmrpcm.play("1.WAV"); //the sound file "1" will play each time the arduino powers up, or is reset
}
 
void loop(){
  tmrpcm.play("blunt.WAV");
  while (tmrpcm.isPlaying()){
  };
//  tmrpcm.play("3.WAV");
//  delay(2000);
//  tmrpcm.play("1.WAV");
//  delay(2000);
//  tmrpcm.play("TEST.WAV");
//  delay(2000);
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
