#pragma once
#include <string>
class clscustomerlocation //A class called location to store names, prices and the amount of travellers
{
private: //creating variables
    std::string _sLocName;
    double _dPrice;
    int _iTravellers;
public: //creating gets & sets
    std::string GetsName() { return _sLocName; }
    void SetsName(std::string sName) { _sLocName = sName; }
    double GetdPrice() { return _dPrice; }
    void SetdPrice(double dPrice) { _dPrice = dPrice; }
    int GetiTravellers() { return _iTravellers; }
    void SetiTravellers(int iTravellers) { _iTravellers = iTravellers; }
    clscustomerlocation() { _sLocName = ""; _dPrice = 0; _iTravellers = 0; } //constructor
    clscustomerlocation(std::string sLocName, double dPrice, int iTravellers) { _sLocName = sLocName; _dPrice = dPrice; _iTravellers = iTravellers; }
};
