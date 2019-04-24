#include "ArduinoSerial.h"
#include "DataCollection.h"

#include <vector>
// TJEK VED ALLE PUNKTER FOR AT PROGRAMMET IKKE CHRASHER ELLER FEJLER


// overvej hvilken GUI løsning
int main() {

	DWORD initTime = GetTickCount(); // bare en timer

	mDATA buffer; 

	ArduinoSerial* t = new ArduinoSerial();
	int it = t->ConnectToArduino("COM4"); 
	DataCollection* d = new DataCollection("DATA"); 

	std::vector<mDATA> data_collection;


	while (true) {

		buffer = t->ReadFromSerial();
		if (buffer.nTest == TEST_NUMBER) {
			data_collection.push_back(buffer);
			d->WriteToFile(buffer);
		}
		if (t->GetElementsInReadQue() < 2) { // Important ##DONT DELETE## makes it reliable, it makes sure the queue never gets to long
			Sleep(UPLOAD_INTERVAL);
		}

	}




	return 0;
}