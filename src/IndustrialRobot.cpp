//start of IndustrialRobot.cpp
#include "IndustrialRobot.h"
#include <iostream>
using namespace std;

// Constructor implementation
IndustrialRobot::IndustrialRobot(const string& sn, const string& loc, double capacity)
    : Robot(sn), factoryLocation(loc), workCapacity(capacity) {}

// Conversion constructor implementation
IndustrialRobot::IndustrialRobot(const string& data) 
    : Robot(extractSerialNumber(data)) {
    istringstream iss(data);
    // Skip serial number (already handled by base constructor)
    iss.ignore(data.find(',') + 1);  
    getline(iss, factoryLocation, ','); //extracts factory location and updates factoryLocation string var
    iss >> workCapacity;
}

// Helper method implementation
string IndustrialRobot::extractSerialNumber(const string& data) {
    //extracting serial number(base root calss Robot with Conversion constructor)
    //out of 3 strings,index 0 extracted.  
    return data.substr(0, data.find(','));
}

// Virtual function implementations
void IndustrialRobot::performTask() const {
    cout << "Industrial robot " << serialNumber 
              << " assembling products at " << factoryLocation << "\n";
}

void IndustrialRobot::displayInfo() const {
    cout << "Industrial Robot | SN: " << serialNumber 
              << " | Location: " << factoryLocation 
              << " | Capacity: " << workCapacity << " units/year\n";
}

// Friend function implementation
ostream& operator<<(ostream& os, const IndustrialRobot& robot) {
    robot.displayInfo();  // Reuse existing function
    return os;
}
//end of IndustrialRobot.cpp