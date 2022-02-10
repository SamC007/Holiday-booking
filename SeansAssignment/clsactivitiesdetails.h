#pragma once
#include <string>
class clsactivitiesdetails //This class is for storing predetermined activities and their details
{
private: //creating variables
    std::string _sActDetName;
    double _dActDetCost;
    std::string _sActivitiesDetails;
public:
    std::string GetActDetName() { return _sActDetName; }
    void SetActDetName(std::string sName) { _sActDetName = sName; }
    double GetActDetdCost() { return _dActDetCost; }
    void SetActDetdCost(double dCost) { _dActDetCost = dCost; }
    void SetsActivitiesDetails(std::string sActivites) { _sActivitiesDetails = sActivites; }
    std::string GetsActivitiesDetails() { return _sActivitiesDetails; }
    clsactivitiesdetails() { _sActDetName = ""; _dActDetCost = 0; _sActivitiesDetails = ""; } //constructor
    clsactivitiesdetails(std::string sActName, double dCost, std::string sActivities) { _sActDetName = sActName; _dActDetCost = dCost; _sActivitiesDetails = sActivities; } //constructor to store all activity details
    ~clsactivitiesdetails() {} //destructor
};