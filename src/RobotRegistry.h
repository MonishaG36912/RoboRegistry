// RobotRegistry.h
#ifndef ROBOTREGISTRY_H
#define ROBOTREGISTRY_H

#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>

#include "Robot.h"
#include "MilitaryRobot.h"
#include "IndustrialRobot.h"
#include "DomesticRobot.h"
#include "RobotComponent.h"

class PriceValidator {
public:
    bool operator()(double price) const;
};

class StringValidator {
public:
    bool operator()(const std::string& str) const;
};

struct HumanoidRobot {
    std::string company;
    std::string name;
    std::string version;
    double price;
    RobotComponent* mainComponent;

    HumanoidRobot();
    HumanoidRobot(std::string comp, std::string n, std::string ver, double p, RobotComponent* compnt = nullptr);
    ~HumanoidRobot();
    HumanoidRobot(HumanoidRobot&& other) noexcept;
    HumanoidRobot& operator=(HumanoidRobot&& other) noexcept;
    operator std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const HumanoidRobot& hr);
};

class RobotRegistry {
private:
    HumanoidRobot* robots;
    Robot** polymorphicRobots;
    int size, polySize, capacity;
    PriceValidator validatePrice;
    StringValidator validateString;

    void growArray();
    void computeColumnWidths(size_t& nameWidth, size_t& companyWidth, size_t& versionWidth) const;

public:
    RobotRegistry();
    ~RobotRegistry();
    void addRobot(std::string&& company, std::string&& name, std::string&& version, double price, RobotComponent* component = nullptr);
    void displayRobots() const;
    void displayPolymorphicRobots() const;
    void displayGreeting(); 
    void redirectOutputToFile();
    void readFromFile(const std::string& filename);
    void promptUserForRobot();
    std::function<void()> getExpensiveRobotsFilter(double minPrice);
};

#endif
