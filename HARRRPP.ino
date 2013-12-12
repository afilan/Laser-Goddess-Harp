#include <SPI.h>

#include <SdFat.h>
#include <SdFatUtil.h>

#include <SFEMP3Shield.h>

#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
  #include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
  #include <SimpleTimer.h>
#endif

SdFat sd;

SFEMP3Shield MP3player;
int16_t last_ms_char; // milliseconds of last recieved character from Serial port.
int8_t buffer_pos; // next position to recieve character from Serial port.

char buffer[6]; // 0-35K+null

int ldrPin[8] = { 5, 10, 11, 12, 13, A5, A4, A3};
char* trackNames[8] = {"Saria.mp3", "Zelda.mp3", "Shiek.mp3", "Minuet.mp3", "Bolero.mp3", "Serenade.mp3", "Requiem.mp3", "Nocturne.mp3"};

void setup() {                

  
   uint8_t result; //result code from some function as to be tested at later time.

  Serial.begin(115200);

  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeRam(), DEC);  // FreeRam() is provided by SdFatUtil.h
  Serial.println(F(" Should be a base line of 1029, on ATmega328 when using INTx"));


  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  //Initialize the MP3 Player Shield
  result = MP3player.begin();
  //check result, see readme for error codes.
  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }
  
}


void loop() {
   
    for (int i = 0; i<8; i++) {
        if (ldrPin[i] == 0) {
          Mp3player.playTrack(trackNames[i]);
        }
    }
}

