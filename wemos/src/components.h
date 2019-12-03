#include <Wire.h>
#include <Arduino.h>

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01

/////////////////////
/// Set Actuators ///
/////////////////////

void setBedActuators(bool);
void setChairActuators(bool, bool);
void writeActuators(int);

///////////////////
/// Get Sensors ///
///////////////////

unsigned int getForceSensor();
bool getButton();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;

void componentCheckLoop();
void resetButton();

bool getButton(int n);

#endif
