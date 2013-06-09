#include <Wire.h>
#include <LSM303.h>

#define GRAVITY 9.8 // m/s^2
#define ACCURACY 2.0
#define DEBOUNCE_TIME 600

#define X 0
#define Y 1
#define Z 2

char mode;

float accel[3];
float accel_offset[3];
int accel_sign[3] = {1,1,-1};

void accel_reset() {
   for(int i=0; i < 3; i++) {
       accel[i] = 0.0;
   }  
}

// Accelerometer board LSM303
#define ACCEL_LSM303
// Serial communication

// Set your accelerometer here
#ifdef ACCEL_LSM303
  #define GRAVITY_FACTOR 0.03828125 // 9.8/256
  LSM303 accel_dev;

  void accel_update() {
      accel_dev.readAcc();
      accel[X] = accel_sign[X] * accel_dev.a.x * GRAVITY_FACTOR  - accel_offset[X];
      accel[Y] = accel_sign[Y] * accel_dev.a.y * GRAVITY_FACTOR - accel_offset[Y];
      accel[Z] = accel_sign[Z] * accel_dev.a.z * GRAVITY_FACTOR - accel_offset[Z];
  } 
  
  void accel_bias() {
    int avg_num = 50; 
     for(int i = 0; i < 3; i++) {
          accel[i] = 0.0;
          accel_offset[i] = 0.0;
      }  
      float accel_sum[3] = {0.0,0.0,0.0};
      for(int i = 0; i < avg_num; i++){
           accel_update();
           for(int j=0; j<3; j++){
              accel_sum[j] += accel[j];
           }
      }
      for(int i=0; i < 3; i++) {
         accel_offset[i] = accel_sum[i]/avg_num; 
      }
      accel_offset[Z] += accel_sign[Z]*GRAVITY;    
  }

  void accel_init() {
      Wire.begin();
      accel_dev.writeAccReg(LSM303_CTRL_REG1_A, 0x27); // normal power mode, all axes enabled, 50 Hz
      accel_dev.writeAccReg(LSM303_CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11 on DLH, DLM
      accel_dev.init();
      accel_bias();
  }
#endif


void startSender() {
   Serial.begin(9600);
}
  
void sendMode() {
    //Serial.println((int)mode);   
    Serial.write(mode);   
} 


void setup() {
  mode = 0;
  startSender();
  accel_init();
}

int getMode() {
  int res = 0;
  
  if(accel[X] < -GRAVITY + ACCURACY){
      res = 1;
  } else if (accel[X] > GRAVITY - ACCURACY) {
      res = 2;
  } else if (accel[Y] < -GRAVITY + ACCURACY) {
      res = 3;
  } else if (accel[Y] > GRAVITY - ACCURACY) {
      res = 4;
  } else if (accel[Z] < -GRAVITY + ACCURACY) {
      res = 5;
  } else if (accel[Z] > GRAVITY - ACCURACY) {
      res = 6;
  }  
  
  return res;
}

int getModeWithDebounce() {
  int res = getMode();
  if(res != 0) {
    delay(DEBOUNCE_TIME);
    if(res == getMode()) {
       return res; 
    } else {
       return 0; 
    }
  }
}

void loop() {
  accel_update();
  
  int nmode = getModeWithDebounce(); 
  
  if(nmode != 0 && mode != nmode) {
    mode = nmode; 
    sendMode(); 
  }
}
