//
// Created by LarsLinux on 16-12-19.
//

#ifndef PILLAR_H
#define PILLAR_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Pillar : public domObject{
private:
    int gassensor;
    bool button;
    bool led;
    bool buzzer;
    Socket socket;
public:
    Pillar(const char*, webSocket*, TimeClass *);
    bool get_buzzer();
    char* wemosMessage();
    json pythonMessage();
    void update() override;
};
#endif //SOCKET_BED_H
