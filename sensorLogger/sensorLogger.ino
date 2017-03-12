/*
Layout:
 MOSI - pin 11
 MISO - pin 1
 CLK - pin 13
 CS - pin 4
*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 8;
int count;

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
  
  count = countFiles(SD.open("/", FILE_READ));
  Serial.println(count);
}

void loop(){
  /* Open and write

     Writes pressureString to the sdcard log.txt file, closes the file after every write.
     Writes to stdout for debugging.
  */

  
  Serial.println(count);
 
  String file_name;
  String current_file;
  file_name = "dataLog";
  current_file = file_name + count + ".txt";  
  
  float pressure = readSensorValues();
  //String data = millis() + "," + pressure;
  
  // Creates new file in absence of existing files
  //current_file is passed to SD.open and gets made into a new file
  File dataFile = SD.open(current_file, FILE_WRITE);
 
  if (dataFile){
    dataFile.print(millis());
    dataFile.print(',');
    dataFile.println(pressure);
    dataFile.close();
  }
  
  else {
    Serial.println("error opening datafile");
  }
}

int countFiles(File f){
  int file_count = 0;
  while (true) {
    // f.openNextFile() is a method of File types from the SD card library
    File entry =  f.openNextFile();
    if (! entry) {
      return(file_count);
    }
    //File class has a method 'name()' that returns the name of one file
    Serial.println(entry.name());
    file_count++;
    entry.close();
    }
}

float readSensorValues(){
  int sensorValue = analogRead(A0);
  float voltage = sensorValue*(5.0/1023.0);
  Serial.println(voltage);
  return voltage;
}


