//
// Created by Zep on 16-12-19.
//
#include "fridge.h"

#include "../Socket/Socket.h"
#include "domObject.h"
#include <fstream>

#define doorIsOpen 0
#define doorIsClosed 1

using json = nlohmann::json ;

Fridge::Fridge(const char * IP, webSocket *s, TimeClass *t) : domObject(s, t, 6){
    cooling = false;
    thermometer1 = 0;
    thermometer2 = 0;
    openClose = 0 ;
    Socket temp(6,"Fridge",IP);
    wemos = temp;
    state = false;
    start_time = 0;
}

char* Fridge::wemosMessage(){
    json Message = {
            {"id",6},
            {"actuators", {
                          {"cooling", cooling}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

json Fridge::pythonMessage() {
    json Message = {
            {"actuators", {
                           {"cooling", cooling}
                   }
            },
            {"sensors", {
                           {"thermometer1", thermometer1},
                           {"thermometer2", thermometer2},
                           {"openClose", openClose}
                   }
            }
    };
    char *message = toCharArray(Message);
    return Message;
}

void Fridge::update(){
    //Logic for the fridge
    char *result;
    json jsonResult;
    int cur_time;

    domObject::timeObj->autoIncreaseTime();

    //Ask for current time in seconds
    cur_time = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60  + domObject::timeObj->getTime()[2];

    result = wemos.sendReceive(wemosMessage());
    jsonResult = toJson(result);
    updateAttributes(jsonResult);

    if (openClose == doorIsClosed){
        start_time = cur_time;
        cooling = true;
    }

    if((cur_time-start_time) > (5 * 60)){
        cooling = false;
        json message = {
                {"type", 4},
                {"id", 4}
        };
        python->sendNotification(toCharArray(message));

    }

    toLogFile();
}

void Fridge::updateAttributes(json result){
    thermometer1 = result["sensors"]["thermometer1"];
    thermometer2 = result["sensors"]["thermometer2"];
    openClose = result["sensors"]["openClose"] == 1;
    python->sendAll(6,pythonMessage());
}

void Fridge::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTime()[0] << ":" << domObject::timeObj->getTime()[1] << ":"
               << domObject::timeObj->getTime()[2] << "Fridge: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}