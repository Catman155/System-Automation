//
// Created by Jasper
//

#include "wall.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for wall
Wall::Wall(const char* IP, webSocket* w, TimeClass *t): domObject(w, t, 5){
    led = 0;
    window = false;
    dimmer = 0;
    LDR = 0;
    Socket temp(5,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Wall::update(){

    string log;

    // char*'s for storing result and message
    char* result;
    char* message;

    // jsons for storing results in json format
    json pythonResult;
    json wemosResult;

    // check if a message has been received
    if(python->sendMessage(5)) {
        // receive result, change to json
        result = python->receiveActuators(5);
        pythonResult = toJson(result);

        // change actuator value
        if (led != pythonResult["actuators"]["led"]) {
            led = pythonResult["actuators"]["led"];
        }

        log += "led = ";
        log += to_string(led);
        log += " | ";
    }

    if ((LDR < 500) != window) {
        window = LDR < 500;

        log += "window = ";
        log += to_string(window);
        log += " | ";
    }

    result = nullptr;
    // make message for wemos and receive sensors
    message = wemosMessage();

    // send to wemos and receive sensors
    result = wemos.sendReceive(message);

    // check if wemos didnt send an empty message
    if (result == nullptr) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        wemosResult = toJson(result);
        if (wemosResult["error"] != "NoDataReceived") {
            int temp = wemosResult["sensors"]["dimmer"];
            if (temp < 10) {temp = 0;}
            if (dimmer != temp) {
                led = wemosResult["sensors"]["dimmer"];
                dimmer = wemosResult["sensors"]["dimmer"];
            }
            LDR = wemosResult["sensors"]["LDR"];
        }
    }

    //send all sensors and actuators to webserver
    python->sendAll(5, pythonMessage());

    logToFile(domObject::timeObj, log);
}

// make message for wemos
char* Wall::wemosMessage(){
    json message = {
            {"id", 5},
            {"actuators", {
                           {"led", led},
                           {"window", window}
                   }
            }
    };
    return toCharArray(message);
}

// make message for webserver
json Wall::pythonMessage(){
    json message = {
            {"actuators", {
                           {"led", led},
                           {"window", window}
                   }
            },
            {"sensors",{
                           {"dimmer", dimmer},
                           {"LDR", LDR}
                   }
            }
    };
    return message;
}

