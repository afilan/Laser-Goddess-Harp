#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

//create and name the library object
SFEMP3Shield MP3player;

byte temp;
byte result;

int ldrPin[8] = {5, A1, A2, 12, 13, A5, A4, A3};
char* trackNames[8] = {"\"Saria.mp3\"", "\"Zelda.mp3\"", "\"Shiek.mp3\"", "\"Minuet.mp3\"", "\"Bolero.mp3\"", "\"Serenade.mp3\"", "\"Requiem.mp3\"", "\"Nocturne.mp3\""};

void setup() {
  Serial.begin(115200);
  
  //boot up the MP3 Player Shield
  result = MP3player.begin();
  //check result, see readme for error codes.
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }
  
  for (int i = 0; i < 8; i++) {
    pinMode(ldrPin[i], INPUT);
  }

  MP3player.SetVolume(0,0);
}

void loop() {
 
   /* for (int i = 3; i< 5; i++) {
      if (digitalRead(ldrPin[0]) == 0 && i != 3 && i !=4) {
         MP3player.playMP3(trackNames[i]);
        }
    }
   */
   if (digitalRead(ldrPin[0]) == 0) {
     MP3player.playMP3("Zelda.mp3");  
   }

}
  
  /*for (int i = 0; i < 8; i++) {
    Serial.print("LDR pin ");
    switch (ldrPin[i]) {
      case 19:
        Serial.print("A5");
        break;
      case 18:
        Serial.print("A4");
        break;
      case 17:
        Serial.print("A3");
        break;
      default:
        Serial.print(ldrPin[i]);
        break;
    }
    Serial.print(" - ");
    if (digitalRead(ldrPin[i]) == 0) {
      Serial.println("off");
    } else {
      Serial.println("on");
    }
    delay(500);
  }
  Serial.println("_____________________________________");
}*/
