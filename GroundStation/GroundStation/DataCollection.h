#pragma once

#include "C:\Users\jacob\Documents\Arduino\libraries\Data.h"
#include <string>
#include <stdio.h>

// Skal lægge alle de modtagne dataer i en vector og derefter i en fil
	// Dataerne skal lægges i filen løbende, i så fald programmet chrasher, gør det i samme loop som vectoren bliver tilskrevet værdier
// Constructoren skal lave en fil, med tidspunktet for "launch" i navnet (indtast i starten af programmet?) og gøre noget ved vectoren

// Format: TIME_STAMP,Air_Pressure,Air_Temp,(eventually GPS)

#define MAX_FILE_NUMBER 99

class DataCollection {

	std::string FileDATName;
	FILE* FileDAT;

public:
	DataCollection(std::string FileName);
	~DataCollection();

	bool CheckFile();

	int WriteToFile(mDATA source);

};



