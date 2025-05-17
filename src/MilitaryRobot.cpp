//start of MilitaryRobot.cpp
#include "MilitaryRobot.h"
#include <iostream>

MilitaryRobot::MilitaryRobot(const std::string& sn, const std::string& mission, 
                           int power, bool stealth)
    : Robot(sn), missionType(mission), weaponPower(power), stealthMode(stealth) {}

void MilitaryRobot::performTask() const {
    std::cout << "Military Robot " << serialNumber 
              << " executing " << missionType << " mission" 
              << (stealthMode ? " (STEALTH MODE)" : "") << "\n";
}

void MilitaryRobot::displayInfo() const {
    std::cout << "Military Robot | SN: " << serialNumber 
              << " | Mission: " << missionType
              << " | Weapon Power: " << weaponPower
              << " | Stealth: " << (stealthMode ? "ON" : "OFF") << "\n";
}

void MilitaryRobot::engageStealthMode() {
    stealthMode = !stealthMode;
    std::cout << "Stealth mode " << (stealthMode ? "activated" : "deactivated") << "\n";
}

void MilitaryRobot::fireWeapon() const {
    std::cout << "Firing weapon with power " << weaponPower << "!\n";
}

MilitaryRobot::operator std::string() const {
    return "Military Robot " + serialNumber + " (" + missionType + ")";
}

std::ostream& operator<<(std::ostream& os, const MilitaryRobot& mr) {
    mr.displayInfo();
    return os;
}
//end of  MilitaryRobot.cpp