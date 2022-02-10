#pragma once
#include <string>
class clsadmindetails
{
private:
    std::string _sUsername;
    std::string _sPassword;
    int _iAccess;
public:
    std::string GetsUsername() { return _sUsername; }
    void SetsUsername(std::string sUsername) { _sUsername = sUsername; }
    std::string GetsPassword() { return _sPassword; }
    void SetsPassword(std::string sPassword) { _sPassword = sPassword; }
    int GetsAccess() { return _iAccess; }
    void SetsAccess(int iAccess) { _iAccess = iAccess; }
    clsadmindetails() { _sUsername = ""; _sPassword = ""; }//constructor
    clsadmindetails(std::string sUsername, std::string sPassword, int iAccess) { _sUsername = sUsername; _sPassword = sPassword; _iAccess = iAccess; }
    ~clsadmindetails() {} //destructor
};