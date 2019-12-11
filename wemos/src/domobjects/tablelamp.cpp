#include "domobject.h"
#include "components.h"

int TableLamp::getId() {
    return 3;
}

void TableLamp::getSensors(JsonArray& arr) {
    JsonObject motionSensor = arr.createNestedObject();
    motionSensor["name"] = "motionSensor";
    motionSensor["value"] = getMotionSensor();
}

void TableLamp::writeActuators(JsonArray& actuators) {
    JsonObject lamp = actuators[0];
    int l = lamp["value"];
    setTableActuators(l);
}
