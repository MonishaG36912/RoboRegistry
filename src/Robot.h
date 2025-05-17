//start of Robot.h
// Abstract Base Class for all robots
#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <iostream>

using namespace std;

class Robot {
protected:
    string serialNumber;

    // Private method to demonstrate friend function
    void logDiagnostics() const {
        std::cout << "[DIAGNOSTICS] Robot " << serialNumber << " systems nominal\n";
    }
public:
    explicit Robot(const std::string& sn);
    virtual ~Robot() = default;
    
    // Pure virtual functions making this an ABC
    virtual void performTask() const = 0;
    virtual void displayInfo() const = 0;
    
    // Conversion operator to string
    operator string() const;
    
    // Friend function declaration
    friend void debugRobot(const Robot& robot);

     // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Robot& robot);
};
#endif // ROBOT_H
