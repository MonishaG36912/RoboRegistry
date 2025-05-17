//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<start of RobotComponent.cpp
#include "RobotComponent.h"
#include <string>

using namespace std;

RobotComponent::RobotComponent(const string& n, double w) 
    : name(n), weight(w) {}

#ifndef PERF
string RobotComponent::getName() const { 
    return name; 
}
#endif
double RobotComponent::getWeight() const { 
    return weight; 
}

RobotComponent::operator string() const {
    return name + " (" + to_string(weight) + "kg)";
}

ostream& operator<<(ostream& os, const RobotComponent& rc) {
    os << "Component: " << rc.name << " | Weight: " << rc.weight << "kg";
    return os;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<end of RobotComponent.cpp