#ifndef FILE_SYSTEM_STUFF_H
#define FILE_SYSTEM_STUFF_H

#include "Arduino.h"
#include "LittleFS.h"

void SaveDataToFile(String fileNameForSave, String DataToSave);
// void BasicProgramWriteLine(int LineNumberToLookUp, String DataToWriteForProgramLine);
String LoadDataFromFile(String fileNameForSave);

bool OpenToWriteOnFlash(String fileNameForWrite);
bool WriteBasicLineOnFlash(String codeLine);
void CloseWriteOnFlash(void);
void LoadBasicProgramFromFlash(String fileNameForRead);
String MakeSureFileNameStartsWithSlash(String FileNameToCheckForSlash);

#endif // FILE_SYSTEM_STUFF_H
