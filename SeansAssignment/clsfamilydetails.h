#pragma once
#include <string>
class clsfamilydetails //A class called families to store all family information that is necessary for the program
{
private: //creating variables
    std::string _sFamName;
    int _iChildren;
    int _iAdults;

public: //creating gets & sets
    std::string GetFamsName() { return _sFamName; }
    void SetFamsName(std::string sName) { _sFamName = sName; }
    int GetiChildren() { return _iChildren; }
    void SetiChildren(int iChildren) { _iChildren = iChildren; }
    int GetiAdults() { return _iAdults; }
    void SetiAdults(int iAdults) { _iAdults = iAdults; }
    void FamName();
    void Ages();
    clsfamilydetails() { _sFamName = ""; _iChildren = 0; _iAdults = 0; } //constructor
    clsfamilydetails(std::string sFamName, int iChildren, int iAdults) { _sFamName = sFamName; _iChildren = iChildren; _iAdults = iAdults; }

};

