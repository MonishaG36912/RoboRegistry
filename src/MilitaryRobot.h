// start of MilitaryRobot.h 
#ifndef MILITARYROBOT_H
#define MILITARYROBOT_H
#include "Robot.h"
#include <string>

class MilitaryRobot : public Robot {
private:
    std::string missionType;
    int weaponPower;
    bool stealthMode;

public:
    MilitaryRobot(const std::string& sn, const std::string& mission, int power, bool stealth);
    
    // Override pure virtual functions from Robot
    void performTask() const override;
    void displayInfo() const override;
    
    // Military-specific methods
    void engageStealthMode();
    void fireWeapon() const;
    
    // Conversion operator to string
    operator std::string() const;
    
    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const MilitaryRobot& mr);
};
#endif // ROBOT_H

// end of MilitaryRobot.h