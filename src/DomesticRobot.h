//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<start of DomesticRobot.h
#ifndef DOMESTICROBOT_H
#define DOMESTICROBOT_H
#include "Robot.h"
#include <iostream>
#include <string>

using namespace std;

class DomesticRobot : public Robot {
private:
    string homeLocation;
    string primaryTask;

public:
    DomesticRobot(const string& sn, const string& loc, const string& task);
    
    void performTask() const override;
    void displayInfo() const override;
    
    friend istream& operator>>(istream& is, DomesticRobot& dr);
};
#endif 

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<end of DomesticRobot.h