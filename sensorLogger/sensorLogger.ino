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

String file_name;
String current_file;
String header;

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

  file_name = "dL";
  int newFileNum = count + 1;
  current_file = file_name + newFileNum + ".csv";
  header = "Time, P1, P2";
  File dataFile = SD.open(current_file, FILE_WRITE);

  Serial.println(count);
 
  if (dataFile){
    dataFile.println(header);
    dataFile.close();
    }  
}

void loop(){
  /* Open and write

     Writes pressureString to the sdcard log.txt file, closes the file after every write.
  */  
  float p1 = readSensor1();
  float p2 = readSensor2();

  // Creates new file in absence of existing files
  //current_file is passed to SD.open and gets made into a new file

  Serial.println(current_file);
  
  File dataFile = SD.open(current_file, FILE_WRITE);
 
  if (dataFile){
    dataFile.print(millis());
    dataFile.print(',');
    dataFile.print(p1, 4);
    dataFile.print(',');
    dataFile.println(p2, 4);
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
    Serial.print("file name = ");
    Serial.println(entry.name());
    if(!entry.isDirectory()) {
      file_count++;
    }
    else {
      Serial.println("Directory!");
    }
    entry.close();
    }
}

float readSensor1(){
  int sensorValue1 = analogRead(A0);
  float v1 = sensorValue1*(5.0/1023.0);
  Serial.println(v1);
  return v1;
}

float readSensor2(){
  int sensorValue2 = analogRead(A1);
  float v2 = sensorValue2*(5.0/1023.0);
  Serial.println(v2);
  return v2;
}


