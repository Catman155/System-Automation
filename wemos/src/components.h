#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01
#define PILLAR_BUTTON 0x01
#define DOOR_BUTTON_1 0x01
#define DOOR_BUTTON_2 0x02


/////////////////////
/// Set Actuators ///
/////////////////////

void setBedActuators(bool);
void setChairActuators(bool, bool);
void writeActuators(int);
void setTableActuators(bool);
void setLamp(bool);
void setPillarActuators(bool, bool);
void setLed(bool state);
void setServo(int);

///////////////////
/// Get Sensors ///
///////////////////

unsigned int getForceSensor();
bool getButton();
unsigned int getMotionSensor();
bool getDoorButton1();
bool getDoorButton2();


int getGassensor();
bool getButtonPillar();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;
static bool pillar_button_state;
static bool static_button_1_state;
static bool static_button_2_state;

void initServo();
void componentCheckLoop();
void resetButton();
void resetPillarButton();

#endif
#include "time.h"

