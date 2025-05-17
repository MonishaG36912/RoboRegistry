//start of Robot.cpp
#include "Robot.h"

Robot::Robot(const string& sn) : serialNumber(sn) {}

// Conversion operator to string
Robot::operator string() const {
    return "Robot SN: " + serialNumber;
}

// Friend function definition (can access private members)
void debugRobot(const Robot& robot) {
    cout << "=== DEBUG INFORMATION ===\n";
    cout << "Serial Number: " << robot.serialNumber << "\n";
    robot.logDiagnostics();  // Accessing private method
    cout << "========================\n";
}

// Stream insertion operator
ostream&  operator<<(ostream& os, const Robot& robot) {
  robot.displayInfo();
return os;
}
//end of Robot.cpp