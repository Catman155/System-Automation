#include "timeKeeper.h"

using namespace std;

TimeClass::TimeClass(int t, int h, int m, int s){
    timeMultiplier = t;
    hours = h;
    minutes = m;
    seconds = s;
}

void TimeClass::autoIncreaseTime(){
    time_t curTime;
    static time_t prevTime;
    double diff_t;
    int totalTime;
    int localMultiplier = timeMultiplier;

    time(&curTime);

    //Calculate time difference between current time and previous time.
    if(prevTime != 0 )
        diff_t = difftime(curTime,prevTime);

    totalTime = diff_t * localMultiplier;
    if(diff_t > 0) {
        if (totalTime >= 3600) {
            hours += (totalTime - totalTime % 3600) / 3600;
            totalTime -= (totalTime - totalTime % 3600);
        }
        if (totalTime >= 60) {
            minutes += (totalTime - totalTime % 60) / 60;
            if (minutes > 59) {
                hours++;
                minutes = 0;
            }
            totalTime -= (totalTime - totalTime % 60);
        }
        if (totalTime > 0) {
            seconds += totalTime;
            if (seconds > 59) {
                minutes++;
                seconds = 0;
                if (minutes > 59) {
                    hours++;
                    minutes = 0;
                }
            }
            totalTime -= totalTime;
        }
        if (hours > 23) {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }

        //Debug purposes
                cout << "hours: "  << hours   << endl;
                cout << "Minutes: "<< minutes << endl;
                cout << "seconds: "<< seconds << endl;
                cout << " " << endl;
        prevTime = curTime;
    }
}

void TimeClass::setTime(string TimeMultiplier, string Hours, string Minutes, string Seconds){
    //Cur means remain current value of given variable.
    if(TimeMultiplier == "cur" || Hours == "cur" || Minutes == "cur" || Seconds == "cur"){
        //Do nothing
    }
    if(TimeMultiplier != "cur")
        timeMultiplier = stod(TimeMultiplier);
    if(Hours != "cur")
        hours   = stoi(Hours);
    if(Minutes != "cur")
        minutes = stoi(Minutes);
    if(Seconds != "cur")
        seconds = stoi(Seconds);

}

int* TimeClass::getTime(){
    static int arr[3];
    arr[0] = hours;
    arr[1] = minutes;
    arr[2] = seconds;

    return arr;
}