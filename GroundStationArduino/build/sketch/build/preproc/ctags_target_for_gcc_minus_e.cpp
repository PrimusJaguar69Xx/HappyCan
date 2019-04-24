# 1 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino"
# 1 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino"



# 5 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino" 2


// BUFFER ReadFromSat
mINSTRUCTION ReadPcBuffer; // BUFFER ReadFromPC

mDATA WritePcBuffer; // BUFFER WriteToPC
// BUFFER WriteToSatelite




void setup()
{
 Serial.begin(9600);
}

void loop()
{
    int bytesRecieved = 0;
    if ((Serial.available() / sizeof(mINSTRUCTION)) >= 1) {
        bytesRecieved += Serial.available();
        byte tempBuffer[sizeof(mINSTRUCTION)];
        for(int i = 0; i < sizeof(mINSTRUCTION); i++)
            tempBuffer[i] = Serial.read();

        WritePcBuffer.bOtherMsg = 1;

        memcpy(&ReadPcBuffer, tempBuffer, 8);
        WritePcBuffer.Air_Temperature = ReadPcBuffer.Instruction;
    }

   // In reality all of this has to be done on the satelite, but this is for testing the Serial connection

    WritePcBuffer.TIME_STAMP = 35000; // millis();
    WritePcBuffer.Air_Pressure = sizeof(mINSTRUCTION);
    WritePcBuffer.nTest = 25835019;
    Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA));

    delay(200);
}

// Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA)); // The way to send data to the program running on the PC
