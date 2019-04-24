#include "DataCollection.h"

DataCollection::DataCollection(std::string FileName) {
	char __NAME[MAX_PATH];
	sprintf(__NAME, "%s.dat", FileName.c_str());
	FileDATName = __NAME;

	FileDAT = fopen(FileDATName.c_str(), "wx"); // Creates a new file, and if a file with the name already exists, it will throw error;
	if (FileDAT == NULL) { // If the file already exists
		for (int i = 1; i < MAX_FILE_NUMBER; i++) {
			char temp_name[MAX_PATH];
			memset(temp_name, 0, MAX_PATH);
			sprintf(temp_name, "%s_%d.dat", FileName.c_str(), i);
			FileDATName = temp_name;
			FileDAT = fopen(FileDATName.c_str(), "wx");

			if (FileDAT != NULL)
				break;
		}
	}
	const char first_line[] = "TIME_STAMP,Air_Pressure,Air_Temp\n";
	fputs(first_line, FileDAT);
	fflush(FileDAT);
}

DataCollection::~DataCollection() {
	fclose(FileDAT);
}

bool DataCollection::CheckFile() {
	return FileDAT != NULL;
}

int DataCollection::WriteToFile(mDATA source) {
	int rValue = 0;

	rValue = fprintf(FileDAT, "%d,%d,%d\n", source.TIME_STAMP, source.Air_Pressure, source.Air_Temperature);
	if (rValue > 0) {
		fflush(FileDAT);
		return rValue;
	}

	return -1;
}