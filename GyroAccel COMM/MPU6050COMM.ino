#include <Wire.h> // I2C library

// Consider converting this to a header

#define MPU6050_ADDRESS 0b1101000
#define MPU6050_PWR_MGMT 0x6B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_ACCEL_MEASUREMENTS 0x3B
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_GYRO_MEASUREMENTS 0x43


#define TIMEOUT 120 // ms
#define TIMEOUT_CYCLES 10

typedef struct {
  
  float Accel_X;
  float Accel_Y;
  float Accel_Z;

  int Gyro_X;
  int Gyro_Y;
  int Gyro_Z;

} mGYRO_ACC_DATA;

void setup() {
  Serial.begin(9600);
}

void loop() {
  SetupI2C();
  mGYRO_ACC_DATA data = GetMPU6050Data();
  Serial.print("Acceleration on X = ");
  Serial.print(data.Accel_X);
  Serial.print("; Acceleration on Y = ");
  Serial.print(data.Accel_Y);
  Serial.print("; Acceleration on Z = ");
  Serial.print(data.Accel_Z);
  Serial.print("; Gyro on X = ");
  Serial.print(data.Gyro_X);
  Serial.print("; Gyro on Y = ");
  Serial.print(data.Gyro_Y);
  Serial.print("; Gyro on Z = ");
  Serial.print(data.Gyro_Z);
  Serial.print("\n");

  delay(200);

}

void SetupI2C(){

  Wire.begin();

  Wire.beginTransmission(MPU6050_ADDRESS); // Specifies the device
  Wire.write(MPU6050_PWR_MGMT); // Specifies the register, in this case the power
  Wire.write(0b00000000); // Wake up!
  Wire.endTransmission(); // END

  Wire.beginTransmission(MPU6050_ADDRESS); // The device
  Wire.write(MPU6050_ACCEL_CONFIG); // The accelerator configuration
  Wire.write(0b00000000); // Sets the full range to 2g
  Wire.endTransmission();

  Wire.beginTransmission(MPU6050_ADDRESS); // The device
  Wire.write(MPU6050_GYRO_CONFIG); // The accelerator configuration
  Wire.write(0b00000000); // Sets the full range to 250/s
  Wire.endTransmission();

}


mGYRO_ACC_DATA GetMPU6050Data() {
  
  mGYRO_ACC_DATA rValue;

    //  Reads the accelerator data
 
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(MPU6050_ACCEL_MEASUREMENTS); // Register to start reading from
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADDRESS, 6);
  for(int i = 0; i < TIMEOUT_CYCLES; i++) {
    if(Wire.available() >= 6) { 
      
      int RAW_ACCEL_X = Wire.read() << 8 | Wire.read(); // Reads the return value into the buffer, shifts it by 8 bits, and then read the rest
      rValue.Accel_X = RAW_ACCEL_X / 16384.0;
      int RAW_ACCEL_Y = Wire.read() << 8 | Wire.read();
      rValue.Accel_Y = RAW_ACCEL_Y / 16384.0;
      int RAW_ACCEL_Z = Wire.read() << 8 | Wire.read();
      rValue.Accel_Z = RAW_ACCEL_Z / 16384.0;

      break;
    }
    delay(TIMEOUT / TIMEOUT_CYCLES);
  }

  // Reads the gyro data

  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(MPU6050_GYRO_MEASUREMENTS); // Register to start reading from
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADDRESS, 6);
  for(int i = 0; i < TIMEOUT_CYCLES; i++) {
    if(Wire.available() >= 6) { 
      
      int RAW_GYRO_X = Wire.read() << 8 | Wire.read(); // Reads the return value into the buffer, shifts it by 8 bits, and then read the rest
      rValue.Gyro_X = RAW_GYRO_X / 131.0;
      int RAW_GYRO_Y = Wire.read() << 8 | Wire.read();
      rValue.Gyro_Y = RAW_GYRO_Y / 131.0;
      int RAW_GYRO_Z = Wire.read() << 8 | Wire.read();
      rValue.Gyro_Z = RAW_GYRO_Z / 131.0;

      break;
    }
    delay(TIMEOUT / TIMEOUT_CYCLES);
  }

  return rValue;
}