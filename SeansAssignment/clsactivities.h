#pragma once
#include <string>

class clsactivities //A class called activities to store all activities that could be taken place on each separate holiday
{
private: //creating variables
    std::string _sActName;
    double _dCost;
    std::string _sActivities;
    bool _bVerified;
public: //creating gets & sets
    std::string GetActsName() { return _sActName; }
    void SetActsName(std::string sName) { _sActName = sName; }
    double GetdCost() { return _dCost; }
    void SetdCost(double dCost) { _dCost = dCost; }
    void SetsActivities(std::string sActivites) { _sActivities = sActivites; }
    std::string GetsActivities() { return _sActivities; }
    bool GetbVerified() { return _bVerified; }
    void SetbVerified(bool bVerified) { _bVerified = bVerified; }
    clsactivities() { _sActName = ""; _dCost = 0; _sActivities = ""; } //constructor
    clsactivities(std::string sActName, double dCost, std::string sActivities) { _sActName = sActName; _dCost = dCost; _sActivities = sActivities; }
};

