//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<start of DomesticRobot.cpp
#include "DomesticRobot.h"
#include <iostream>

using namespace std;

DomesticRobot::DomesticRobot(const string& sn, const string& loc, const string& task)
    : Robot(sn), homeLocation(loc), primaryTask(task) {}

void DomesticRobot::performTask() const {
    cout << "Domestic robot " << serialNumber << " performing " << primaryTask 
              << " at " << homeLocation << endl;
}

void DomesticRobot::displayInfo() const {
    cout << "Domestic Robot | SN: " << serialNumber 
              << " | Home: " << homeLocation 
              << " | Task: " << primaryTask << "\n";
}

#ifndef PERF
istream& operator>>(istream& is, DomesticRobot& dr) {
    getline(is, dr.serialNumber, ',');
    getline(is, dr.homeLocation, ',');
    getline(is, dr.primaryTask);
    return is;
}
#else
istream& operator>>(istream& is, DomesticRobot& dr) {
    string buffer;
    if (getline(is, buffer, ',')) {
        dr.serialNumber = move(buffer);
        if (getline(is, buffer, ',')) {
            dr.homeLocation = move(buffer);
            if (getline(is, buffer)) {
                dr.primaryTask = move(buffer);
                return is;
            }
        }
    }
    is.setstate(ios::failbit);
    return is;
}
#endif
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<end of DomesticRobot.cpp