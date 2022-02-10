#pragma once
#include <string>
class clslocationdetails //this class is for storing the predetermined locations and their details.
{
private: //creating variables
    std::string _sLocationName;
    double _dPricePerPerson;
    int _iMinTravellers;
public: //gets & set
    std::string GetsLocName() { return _sLocationName; }
    void SetsLocName(std::string sName) { _sLocationName = sName; }
    double GetdPersonPrice() { return _dPricePerPerson; }
    void SetdPersonPrice(double dPrice) { _dPricePerPerson = dPrice; }
    int GetiMinTravellers() { return _iMinTravellers; }
    void SetiMinTravellers(int iTravellers) { _iMinTravellers = iTravellers; }
    clslocationdetails() { _sLocationName = ""; _dPricePerPerson = 0; _iMinTravellers = 0; } //constructor
    clslocationdetails(std::string sLocation, double dPrice, int iMin) { _sLocationName = sLocation; _dPricePerPerson = dPrice; _iMinTravellers = iMin; } //constructor to store all location details
};