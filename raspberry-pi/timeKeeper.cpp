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
    int localMultiplier = timeMultiplier * 60;

    time(&curTime);

    //Calculate time difference between current time and previous time.
    if(prevTime != 0 )
        diff_t = difftime(curTime,prevTime);

    totalTime = diff_t * localMultiplier;

    if(diff_t > 0) {
        hours += totalTime%3600;
        totalTime -= hours * 3600;

        minutes += totalTime%60;
        totalTime -= minutes * 60;

        seconds += totalTime%60;
        totalTime -= seconds;
    }

    //Debug purposes
    //        cout << "hours: "  << hours   << endl;
    //        cout << "Minutes: "<< minutes << endl;
    //        cout << "seconds: "<< seconds << endl;
    //        cout << " " << endl;
    prevTime = curTime;
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