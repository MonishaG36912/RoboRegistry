//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<start of RobotComponent.h
#ifndef ROBOTCOMPONENT_H
#define ROBOTCOMPONENT_H
#include <iostream>
#include <string>

using namespace std;

class RobotComponent {
private:
#ifndef PERF
    string name;
    double weight;
#else
//Reduces padding between members
//Can save 4-8 bytes per object.this happens when we class object getting creted with differnt members
    double weight;
    string name;
#endif
public:
    RobotComponent(const string& n, double w);
    
#ifndef PERF
    string getName() const;
#else
    //Eliminates function call overhead
    //Proper handling of lvalue/rvalue contexts
    const string& getName() const & noexcept { return name; }
    string getName() && noexcept { return move(name); }
#endif
    double getWeight() const;
    
    operator string() const;
    friend ostream& operator<<(ostream& os, const RobotComponent& rc);
};

#endif // ROBOT_H
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<end of RobotComponent.h