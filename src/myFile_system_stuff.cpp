//File System Stuff
#include "Arduino.h"
#include "LittleFS.h"

#include "globals.h"
#include "myFile_system_stuff.h"
#include "myInterpreter.h"


void SaveDataToFile(String fileNameForSave, String DataToSave)
{
  //Serial.println(fileNameForSave);
  //SPIFFS.begin();
#ifdef ESP32
  File f = LittleFS.open(String("/data/" + fileNameForSave + ".dat"), "w");
#else
  fs::File f = LittleFS.open(String("/data/" + fileNameForSave + ".dat"), "w");
#endif

  if (!f)
  {
    sendContent("file open failed");
  }
  else
  {
    f.println(String(DataToSave + String('\r')));
    f.close();
  }
  return;
}

// void BasicProgramWriteLine(int LineNumberToLookUp, String DataToWriteForProgramLine);
String LoadDataFromFile(String fileNameForSave)
{
  String WhatIwillReturn;
  //LittleFS.begin();
#ifdef ESP32
  File f = LittleFS.open(String("/data/" + fileNameForSave + ".dat"), "r");
#else
  fs::File f = LittleFS.open(String("/data/" + fileNameForSave + ".dat"), "r");
#endif
  if (!f)
  {
    //Serial.print("file open failed  :");
    //Serial.println(fileNameForSave);
  }
  else
  {
    WhatIwillReturn =  f.readStringUntil('\r');
    WhatIwillReturn.replace("\n", "");
    f.close();
    return WhatIwillReturn;
  }
}

//////////// New file stuff by CiccioCB /////////////

#ifdef ESP32
static File BasicFileToSave;
#else
static fs::File BasicFileToSave;
#endif
//static int  program_nb_lines = 0;
//static uint16_t  line_seeks[256];

bool OpenToWriteOnFlash(String fileNameForWrite)
{
  //Serial.printf("Opening SPIFFS file %s\n",(char *)fileNameForWrite.c_str());
  BasicFileToSave = LittleFS.open(fileNameForWrite, "w");
  if (!BasicFileToSave)
  {
    Serial.println(F("file write open failed"));
	return false;
  }
  return true;
}

bool WriteBasicLineOnFlash(String codeLine)
{
	int ret;
  int i=1;
  int where=codeLine.lastIndexOf("\n");
  //Serial.printf("where = %d and length=%d\n",where,codeLine.length());
  while (codeLine.length()-where<=2) 
  {
    //Serial.printf("Dropped last line #%d\n",i++);
    codeLine=codeLine.substring(0,where);
    where=codeLine.lastIndexOf("\n");
    //Serial.printf("where = %d and length=%d\n",where,codeLine.length());
  }
  ret = BasicFileToSave.print(codeLine);
  if (ret == 0)
  {
    Serial.println(F("file write println failed"));
    return false; 
  } 
  return true;
}

void CloseWriteOnFlash(void)
{
	BasicFileToSave.close();
}


void LoadBasicProgramFromFlash(String fileNameForRead)
{
  fs::File f = LittleFS.open(fileNameForRead, "r");
  f.read((uint8_t *)&buf, BUFSIZE);    
  return;
}


String MakeSureFileNameStartsWithSlash(String FileNameToCheckForSlash)
{
  if (FileNameToCheckForSlash.startsWith("/"))
  {
    return FileNameToCheckForSlash;
  }
  else
  {
    return String("/" + FileNameToCheckForSlash);
  }
}
