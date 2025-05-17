
//start of IndustrialRobot.h
#ifndef INDUSTRIALROBOT_H
#define INDUSTRIALROBOT_H
#include "Robot.h"
#include <string>
#include <sstream>

using namespace std;

class IndustrialRobot : public Robot {
private:
    string factoryLocation;
    double workCapacity;
    
    // Private helper method
    static string extractSerialNumber(const string& data);

public:
    // Constructors
    IndustrialRobot(const string& sn, const string& loc, double capacity);
    explicit IndustrialRobot(const string& data);  // Conversion constructor
    
    // Overridden virtual functions
    void performTask() const override;
    void displayInfo() const override;
    
    // Friend function declaration
    friend ostream& operator<<(ostream& os, const IndustrialRobot& robot);
};
#endif 

//end of IndustrialRobot.h