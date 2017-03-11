/*
Layout:
 MOSI - pin 11
 MISO - pin 12
 CLK - pin 13
 CS - pin 4 
*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
  /* Setup Serial Coms
     
     Open serial communications and wait for port to open:
  */

  Serial.begin(9600);
  while (!Serial) {
    ; // arbitrary wait for serial port
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}
void loop(void){
  /* Open and write

     Writes dataString to the sdcard datalog.txt file, closes the file after every write.
     Writes to stdout for debugging.
  */	
  
  dataString = "test"
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  
  else {
    Serial.println("error opening datalog.txt");
  }
}
