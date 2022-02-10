#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "common.h"
#include "clsactivities.h"
#include "clsactivitiesdetails.h"
#include "clsadmindetails.h"
#include "clscustomerlocation.h"
#include "clsfamilydetails.h"
#include "clslocationdetails.h"

std::string GetALine(std::string sLine) //this function gets the reply to a line and then returns it, so it can be stored
{
    std::string sUnwanted = "0123456789!£$%^&*()-_=+[{]}~¬,.<>/?;:"; //This is all stuff that isn't wanted
    while (true)
    {
        getline(std::cin, sLine);
        try {
            if (std::size_t found = sLine.find_first_of(sUnwanted.c_str())) //This command looks at the string and tries to find the first of anything in sUnWanted.
            {
                return sLine;
            }
            else
            {
                std::cout << "Enter letters only" << std::endl;
            }
        }
        catch (std::exception) //if the code errors
        {
            std::cout << "Error" << std::endl; //console will output this line
        }
    }


}

int GetALineConvert(int iReturn) //this function gets the reply to a line and then converts it to an int, then returns it
{
    std::string sLine;
    while (true) {
        try
        {
            getline(std::cin, sLine);
            iReturn = stoi(sLine); //This converts sLine into an integer, and stores it in iReturn
            if (iReturn > 0 && iReturn < 150)
            {
                return iReturn;
            }
            std::cout << "Enter a number that is bigger than 0 and smaller than 150 please" << std::endl;
        }
        catch (std::exception) //if the code errors
        {
            std::cout << "This isn't a number" << std::endl << "Enter a number" << std::endl;
        }
    }
}

double GetALineDouble(double dReturn) //this function gets the reply to a line and then converts it to a double, then returns it
{
    std::string sLine;
    while (true) {
        try
        {
            getline(std::cin, sLine);
            dReturn = stod(sLine); //This converts sLine into an double, and stores it in dReturn
            if (dReturn > 0 && dReturn < 150)
            {
                return dReturn;
            }
            std::cout << "Enter a number that is bigger than 0 and smaller than 150 please" << std::endl;
        }
        catch (std::exception) //if the code errors
        {
            std::cout << "This isn't a number" << std::endl << "Enter a number" << std::endl;
        }
    }
}

int Choice(int iLogin) //This function presents the choice of loading a file or creating a new one, depending on their response it shall return a different value
{
    int iResponse = 0;
    std::cout << std::endl << "Select an Option" << std::endl; //shows the user all the options
    std::cout << "Option 1: Book a Holiday" << std::endl;
    std::cout << "Option 2: Show Holiday Locations" << std::endl;
    std::cout << "Option 3: Show Holiday Activities" << std::endl;
    std::cout << "Option 4: Load a Booking" << std::endl;
    std::cout << "Option 5: Exit the program" << std::endl;
    std::cout << "Option 6: Re-Enter Family Details" << std::endl;
    std::cout << "Option 8: Add a Custom Activity" << std::endl;
    if (iLogin == 2)//This option is only if you are an admin
    {
        std::cout << "Option 7: Verify a user suggested activity" << std::endl; 
    }
    iResponse = GetALineConvert(iResponse); //This gets the user input, and converts it into an integer. if it isn't possible, will ask the user again.
    return iResponse;
}

int Admin(std::vector <clsadmindetails> vAdmin) //This function forces the user to login as an administrator if they want to access any part of the program
{
    std::string sUsername = "";
    std::string sPassword = "";
    std::cout << "Please enter your login details." << std::endl;
    std::cout << "Username: " << std::endl;
    sUsername = GetALine(sUsername);
    std::cout << "Password: " << std::endl;
    sPassword = GetALine(sPassword);
    for (int iCount = 0; iCount < vAdmin.size(); iCount++) //loop to compare both user username & password and admin username & password
    {
        std::string sRealUsername = vAdmin.at(iCount).GetsUsername();
        std::string sRealPassword = vAdmin.at(iCount).GetsPassword();
        if (sUsername == sRealUsername && sPassword == sRealPassword)
        {
            return vAdmin.at(iCount).GetsAccess(); //returns access level
        }

    }

}

double LoadFile(std::vector <clscustomerlocation>& vCustLoc, std::vector <clsactivities>& vCustAct, std::vector <clsfamilydetails>& vFamily, std::string sFileName) //THis is for loading & displaying a file
{
    double dTotal = 0;
    std::vector <std::string> vLines(0); //calls a vector to hold the details in case they want to be changed later on.
    std::string sReturn = "";
    bool booLooper = true;
    int iCount = 0;
    sFileName = sFileName + ".csv"; //adds .csv to it, which is what files saved from this program end in as they become excel spreadsheets.
    std::string sLine = "";
    int iMaxActs = 0;
    std::ifstream File(sFileName); //calls the file using the filename + .csv
    while (File.is_open()) //loop to get everything in the file while it is open.
    {
        vLines.resize(0);
        while (std::getline(File, sLine)) //loop
        {
            std::stringstream ssSplit(sLine);
            getline(ssSplit, sReturn, ',');
            vLines.push_back(sReturn);
        }
        vFamily.at(0).SetFamsName(vLines.at(0)); //These pieces of code just take whatever is on each line of the file and store them into different variables.   
        vFamily.at(0).SetiAdults(stoi(vLines.at(1)));
        vFamily.at(0).SetiChildren(stoi(vLines.at(2)));
        vCustLoc.at(0).SetsName(vLines.at(3));
        vCustLoc.at(0).SetdPrice(stod(vLines.at(4)));
        iCount = 5;
        while (booLooper == true) //loop for activities, as there can be more than 1 activity, unlike everything before.
        {
            try
            {

                if (vLines.at(iCount).find("Theme Park") != std::string::npos || vLines.at(iCount).find("Guided Tours") != std::string::npos || vLines.at(iCount).find("Sky Diving") != std::string::npos)
                { //long if statement to try and find "Theme Park", "Guided Tours" & "Sky Diving" in the line selected.
                    vCustAct.push_back(clsactivities()); //vector push back to make room
                    vCustAct.at(0).SetActsName(vLines.at(iCount));
                    vCustAct.at(0).SetbVerified(true);
                    iCount++;

                }
                else
                {
                    booLooper = false;
                }
            }
            catch (std::exception) { //error catch just in case
                booLooper = false;
            }
        }
        dTotal = std::stod(vLines.at(iCount)); //converts into a double so it can be stored in dTotal
        File.close();
    }


    vLines.clear(); //clears the vector vLines.
    return dTotal;

}

void LoadFileDisplay(std::vector <clscustomerlocation>& vCustLoc, std::vector <clsactivities>& vCustAct, std::vector <clsfamilydetails>& vFamily, std::string sFileName, double dTotal)
{
    //These variables are then displayed, some with extra labels to make them easier for the user to read.
    std::cout << vFamily.at(0).GetFamsName() << std::endl;
    std::cout << "Adults: " << vFamily.at(0).GetiAdults() << std::endl;
    std::cout << "Children: " << vFamily.at(0).GetiChildren() << std::endl;
    std::cout << "Location Name: " << vCustLoc.at(0).GetsName() << std::endl;
    std::cout << "Location price: " << vCustLoc.at(0).GetdPrice() << std::endl;
    std::cout << "Activities: " << vCustAct.at(0).GetActsName() << std::endl;
    std::cout << "The price without VAT: " << dTotal << std::endl;
    dTotal = dTotal * 1.2;
    std::cout << "The price with VAT: " << dTotal << std::endl;
}

void ProgramWelcome() //Welcomes the user to the program
{
    std::cout << "Welcome to the program!" << std::endl;
}

void AdminConstructor(std::vector <clsadmindetails>& vAdmin) //Constructor for the admin class
{
    vAdmin.push_back(clsadmindetails("admin", "admin", 2));
    vAdmin.push_back(clsadmindetails("user", "user", 1));
}

void ActivityConstructor(std::vector <clsactivities>& vCustAct) //Constructor for the activities class
{
    vCustAct.push_back(clsactivities());
}

void CustLocConstructor(std::vector <clscustomerlocation>& vCustLoc) //Constructor for the customerlocation class
{
    vCustLoc.push_back(clscustomerlocation(" ", 1, 1));
}

void FamilyConstructor(std::vector <clsfamilydetails>& vFamily) //Constructor for the familydetails class
{
    vFamily.push_back(clsfamilydetails("", 1, 2));
}

void clslocationdetailsPopulation(std::vector <clslocationdetails>& vDetails) //Constructor for the locationdetails class
{
    vDetails.push_back(clslocationdetails("Florida", 1300, 4));
    vDetails.push_back(clslocationdetails("Paris", 600, 2));
    vDetails.push_back(clslocationdetails("Milan", 950, 2));
    vDetails.push_back(clslocationdetails("Tokyo", 1800, 4));
}




std::string FileName() //This function is for grabbing a file name
{
    std::cout << "What is the file name?" << std::endl; //asks the user what the file name is
    std::string sFileName = "";
    getline(std::cin, sFileName); //gets the file name
    return sFileName;
}


void LoadActivityDetails(std::vector <clsactivitiesdetails>& vActivities) //Constructor for the activitiesdetails class
{

    std::vector <std::string> vLines(0); //calls a vector to hold the details in case they want to be changed later on.
    std::string sLine = "";
    std::string sReturn = "";
    int iCount = 0;
    int iMaxActs = 0;
    std::fstream File("activities.csv"); //calls the file using the filename + .csv
    while (File.is_open())
    {
        while (std::getline(File, sLine)) //loop to split each line, as well as storing multiple activities
        {
            std::stringstream ssSplit(sLine);
            while (getline(ssSplit, sReturn, ','))
            {
                vLines.push_back(sReturn);
            }
            vActivities.push_back(clsactivitiesdetails()); //push back so I can store the activities
            vActivities.at(iCount).SetActDetName(vLines.at(0));
            vActivities.at(iCount).SetActDetdCost(stod(vLines.at(1)));
            vActivities.at(iCount).SetsActivitiesDetails(vLines.at(2));
            vLines.resize(0);
            iCount++; //iCount is useful for storing multiple activities
        }
        File.close();
    }
}

void LoadCustomActivityDetails(std::vector <clsactivities>& vCustAct) //Constructor for the activitiesdetails class
{

    std::vector <std::string> vLines(0); //calls a vector to hold the details in case they want to be changed later on.
    std::string sLine = "";
    std::string sReturn = "";
    int iCount = 0;
    int iVerified = 0;
    std::fstream File("customactivities.csv"); //calls the file using the filename + .csv
    try {
        while (File.is_open())
        {
            while (std::getline(File, sLine)) //loop to split each line
            {
                std::stringstream ssSplit(sLine);
                while (getline(ssSplit, sReturn, ','))
                {
                    vLines.push_back(sReturn);
                }
                vCustAct.push_back(clsactivities()); //gets what was in the file
                vCustAct.at(iCount).SetActsName(vLines.at(0));
                vCustAct.at(iCount).SetdCost(stod(vLines.at(1)));
                vCustAct.at(iCount).SetsActivities(vLines.at(2));
                iVerified = stoi(vLines.at(3));
                if (iVerified == 1) { vCustAct.at(iCount).SetbVerified(true); }
                else { vCustAct.at(iCount).SetbVerified(false); }
                vLines.resize(0);
                iCount++;
            }
            File.close();
        }
    }
    catch (std::exception) //in case something goes wrong
    {
        std::cout << "Error, please restart program" << std::endl;
    }
}


void SaveActivityDetails(std::vector <clsactivitiesdetails>& vActivities) //function for saving verified activity details.
{
    std::vector <std::string> vLines(0); //calls a vector to hold the details in case they want to be changed later on.
    std::string sLine = "";
    int iMaxActs = 0;
    std::ofstream File("activities.csv"); //calls the file using the filename + .csv
    while (File.is_open()) //loop to get everything in the file while it is open.
    {
        for (int iCount = 0; iCount < vActivities.size(); iCount++)
        {
            File << vActivities.at(iCount).GetActDetName() << ",";
            File << vActivities.at(iCount).GetActDetdCost() << ",";
            File << vActivities.at(iCount).GetsActivitiesDetails() << std::endl;
        }
        File.close();
    }
}

void SaveCustomActivityDetails(std::vector <clsactivities>& vCustAct) //function for saving unverified activity details.
{
    std::vector <std::string> vLines(0); //calls a vector to hold the details in case they want to be changed later on.
    std::string sLine = "";
    int iMaxActs = 0;
    std::ofstream File("customactivities.csv"); //calls the file using the filename + .csv
    while (File.is_open()) //loop to get everything in the file while it is open.
    {
        for (int iCount = 0; iCount < vCustAct.size(); iCount++)
        {
            File << vCustAct.at(iCount).GetActsName() << ",";
            File << vCustAct.at(iCount).GetdCost() << ",";
            File << vCustAct.at(iCount).GetsActivities() << ",";
            File << vCustAct.at(iCount).GetbVerified() << std::endl;
        }
        File.close();
    }
}

void LocationOutput(std::vector <clslocationdetails>& vLocation) //function to output all potential locations
{
    for (int iCounter = 0; iCounter < vLocation.size(); iCounter++)
    {
        std::cout << (iCounter + 1) << std::endl;
        std::cout << vLocation.at(iCounter).GetsLocName() << std::endl;
        std::cout << "The price (per person):" << vLocation.at(iCounter).GetdPersonPrice() << std::endl;
        std::cout << "Minimum travellers: " << vLocation.at(iCounter).GetiMinTravellers() << std::endl;
    }
}


void Location(std::vector <clslocationdetails>& vLocation, std::vector <clscustomerlocation>& vCustLoc, std::vector <clsfamilydetails>& vFamily) //gets the users holiday location
{
    bool bLoop = false;
    int iLine = 0;
    int iPeople_in_fam = vFamily.at(0).GetiAdults() + vFamily.at(0).GetiChildren();
    std::cout << "Which country are you planning on going to?" << std::endl;
    for (int iCounter = 0; iCounter < vLocation.size(); iCounter++) //loop for outputting all locations so they can be compared with each other.
    {
        std::cout << (iCounter + 1) << std::endl;
        std::cout << vLocation.at(iCounter).GetsLocName() << std::endl;
        std::cout << "The price (per person):" << vLocation.at(iCounter).GetdPersonPrice() << std::endl;
        std::cout << "Minimum travellers: " << vLocation.at(iCounter).GetiMinTravellers() << std::endl;
    }
    while (bLoop == false) //loop for getaline in case the user inputs wrong.
    {
        std::cout << "Select the number for the country you want to choose" << std::endl;
        iLine = GetALineConvert(iLine);
        while (iLine < 1 || iLine > 4) //if the number is lower than 1 or higher than 4, it doesn't represent a location
        {
            std::cout << "This number does not represent a location, please enter a number between 1 & 4.";
            iLine = GetALineConvert(iLine);
        }

        if (iLine == 1 || iLine == 4)
        {
            if (iPeople_in_fam < 4) //if there is less than 4 family members, there isn't enough people
            {
                std::cout << "You do not have enough people to go to this location. " << std::endl;
            }
            else
            {
                bLoop = true;
            }
        }
        else if (iLine == 2 || iLine == 3)
        {
            if (iPeople_in_fam < 2) //if there is less than 2 family members, there isn't enough people
            {
                std::cout << "You do not have enough people to go to this location. " << std::endl;
            }
            else
            {
                bLoop = true;
            }
        }
    }
    iLine = iLine - 1;

    std::string sName = vLocation.at(iLine).GetsLocName(); //Storing user details in vectors
    double dPrice = vLocation.at(iLine).GetdPersonPrice();
    int iMax = vLocation.at(iLine).GetiMinTravellers();
    std::cout << vLocation.at(iLine).GetsLocName();
    vCustLoc.at(0).SetsName(sName);
    vCustLoc.at(0).SetdPrice(dPrice);
    vCustLoc.at(0).SetiTravellers(iMax);
}

void Activities(std::vector <clsactivitiesdetails>& vActivities, std::vector <clsactivities>* vActivityStorage, std::vector <clscustomerlocation>& vCustLoc) //populates the activities class
{
    int iLine = 0; //defining variables
    int iActivities = 0;
    bool bVerified = true;
    bool bLoop = false;
    std::cout << "Here's a list of activities you could potentially go to: " << std::endl;
    for (int iCounter = 0; iCounter < vActivities.size(); iCounter++) //loop to show all available activities
    {
        std::cout << iCounter + 1 << std::endl;
        std::cout << "Name: " << vActivities.at(iCounter).GetActDetName() << std::endl;
        std::cout << "The price:" << vActivities.at(iCounter).GetActDetdCost() << std::endl;
        std::cout << "Countries available: " << vActivities.at(iCounter).GetsActivitiesDetails() << std::endl;
    }
    while (bLoop == false) //loop for user input
    {
        std::cout << "How many activities are you planning on going to? " << std::endl;
        iActivities = GetALineConvert(iActivities); //user input
        if (iActivities < 4 && iActivities > 0) //the user cannot have more than 3 activities at a time
        {
            bLoop = true;
        }
        else
        {
            std::cout << "Please enter a number between 1 and 3." << std::endl;
        }
    }

    for (int iCounter = 0; iCounter < iActivities; iCounter++) //loop for choosing activities
    {
        bool bLoop = false;
        while (bLoop != true)
        {
            std::cout << "Select the number for each activity you want to choose" << std::endl;
            iLine = GetALineConvert(iLine) - 1;
            std::string sName = vActivities.at(iLine).GetActDetName();
            double dPrice = vActivities.at(iLine).GetActDetdCost();
            std::string sActivityPlaces = vActivities.at(iLine).GetsActivitiesDetails();
            if (sActivityPlaces.find(vCustLoc.at(0).GetsName()) != std::string::npos)
            {
                vActivityStorage->push_back(clsactivities());
                vActivityStorage->at(iCounter).SetActsName(sName);
                vActivityStorage->at(iCounter).SetdCost(dPrice);
                vActivityStorage->at(iCounter).SetsActivities(sActivityPlaces);
                vActivityStorage->at(iCounter).SetbVerified(bVerified);
                bLoop = true;
            }
            else
            {
                std::cout << "Activity is not in an available location" << std::endl;
            }
        }

    }
}

void ActivitiesOutput(std::vector <clsactivitiesdetails>& vActivities) { //this function is for outputting verified activities
    for (int iCounter = 0; iCounter < vActivities.size(); iCounter++)
    {
        std::cout << iCounter + 1 << std::endl;
        std::cout << "Name: " << vActivities.at(iCounter).GetActDetName() << std::endl;
        std::cout << "The price:" << vActivities.at(iCounter).GetActDetdCost() << std::endl;
        std::cout << "Countries available: " << vActivities.at(iCounter).GetsActivitiesDetails() << std::endl;
    }
}

void CustomActivitiesOutput(std::vector <clsactivities>& vCustAct) //this function is for outputting unverified activities
{
    for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++)
    {
        std::cout << iCounter + 1 << std::endl;
        std::cout << "Name: " << vCustAct.at(iCounter).GetActsName() << std::endl;
        std::cout << "The price:" << vCustAct.at(iCounter).GetdCost() << std::endl;
        std::cout << "Countries available: " << vCustAct.at(iCounter).GetsActivities() << std::endl;
    }
}

void clsfamilydetails::FamName() //This function is to populate the families class
{
    std::string sName = "";
    std::cout << "What is your family surname?" << std::endl;
    sName = GetALine(sName);
    SetFamsName(sName);
}

void clsfamilydetails::Ages() //This function gets the ages of everyone in the family, and decides if they are an adult or a child.
{
    int iFamily = 0; //defining variables
    int iAge = 0;
    int iChildren = 0;
    int iAdults = 0;
    std::cout << "How many people are in your family? " << std::endl; //This is to get the amount of people in the family, so we can determine how long the loop is running for
    iFamily = GetALineConvert(iFamily);
    for (int iCounter = 0; iCounter < iFamily; iCounter++)  //The loop is running for however many people there are in the family
    {
        std::cout << "How old are you? " << std::endl; //Gets the age
        iAge = GetALineConvert(iAge);
        if (iAge < 18) //Sorts the age into adult or child depending on whether they are above or below 18.
        {
            iChildren++;

        }
        else
        {
            iAdults++;

        }
    }
    SetiChildren(iChildren); //stores iChildren and iAdults in a vector
    SetiAdults(iAdults);
}

bool CustomerActivites() //Gets customer activities
{
    std::string sResponse = "";
    std::cout << "Would you like to add your own custom activities?" << std::endl; //query, if yes, return true, if false, return false
    sResponse = GetALine(sResponse);
    if (sResponse == "Yes" || sResponse == "yes" || sResponse == "YES" || sResponse == "yEs" || sResponse == "y" || sResponse == "ye" || sResponse == "yeah" || sResponse == "Yeah" || sResponse == "Y")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GetCustomerclsactivities(std::vector <clsactivities>* vActivityStorage, std::vector <clsactivities>& vUnverifiedActs) //This function is for creating custom customer activities
{
    int iMaxLoops = 0; //defining variables
    std::string sActivityName = "";
    double dCost = 0;
    std::string sActivityDetail = "";
    bool bUnverified = false;
    bool bCommaChecker = true;
    std::cout << "How many custom activities would you like to add?" << std::endl; //asks the user how many custom activities they want
    iMaxLoops = GetALineConvert(iMaxLoops);
    for (int iCounter = 0; iCounter != iMaxLoops; iCounter++) //loop for naming custom activities, as the user can create more than 1 at a time.
    {
        std::cout << "What would you name your custom activity?" << std::endl;
        sActivityName = GetALine(sActivityName);

        std::cout << "How much would it cost?" << std::endl;
        dCost = GetALineDouble(dCost);
        while (bCommaChecker) { //while for checking in case the user puts commas, as this screws up excel so I have to make sure they aren't in the string
            std::cout << "Locations this activity would be available in?" << std::endl;
            sActivityDetail = GetALine(sActivityDetail);
            if (sActivityDetail.find(",") != std::string::npos) { std::cout << "Don't separate your locations with commas, just leave spaces." << std::endl; }
            else { bCommaChecker = false; }
        }
        bCommaChecker = true;
        vActivityStorage->push_back(clsactivities()); //storing variables in vectors
        vActivityStorage->at(vActivityStorage->size() - 1).SetActsName(sActivityName);
        vActivityStorage->at(vActivityStorage->size() - 1).SetdCost(dCost);
        vActivityStorage->at(vActivityStorage->size() - 1).SetsActivities(sActivityDetail);
        vActivityStorage->at(vActivityStorage->size() - 1).SetbVerified(bUnverified);
        vUnverifiedActs.push_back(clsactivities());
        vUnverifiedActs.at(vUnverifiedActs.size() - 1).SetActsName(sActivityName);
        vUnverifiedActs.at(vUnverifiedActs.size() - 1).SetdCost(dCost);
        vUnverifiedActs.at(vUnverifiedActs.size() - 1).SetsActivities(sActivityDetail);
        vUnverifiedActs.at(vUnverifiedActs.size() - 1).SetbVerified(bUnverified);
    }
}

void LoadActPrices(std::vector <clsactivities>& vCustAct, std::vector <clsactivitiesdetails>& vActivities) //this function is for loading activity prices
{
    std::string sName = "";
    double dThemePark = vActivities.at(0).GetActDetdCost();
    double dGuidedTours = vActivities.at(1).GetActDetdCost();
    double dSkyDiving = vActivities.at(2).GetActDetdCost();
    double dZero = 0;
    bool bVerified = true;
    for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++) //this function is because there could potentially be more than 1 activity
    {
        sName = vCustAct.at(iCounter).GetActsName();
        if (sName == "Theme Park")
        {
            vCustAct.at(iCounter).SetdCost(dThemePark); //Setting variables to vectors
            vCustAct.at(iCounter).SetActsName(sName);
            vCustAct.at(iCounter).SetbVerified(bVerified);
        }
        else if (sName == "Guided Tours")
        {
            vCustAct.at(iCounter).SetdCost(dGuidedTours);
            vCustAct.at(iCounter).SetActsName(sName);
            vCustAct.at(iCounter).SetbVerified(bVerified);
        }
        else if (sName == "Sky Diving")
        {
            vCustAct.at(iCounter).SetdCost(dSkyDiving);
            vCustAct.at(iCounter).SetActsName(sName);
            vCustAct.at(iCounter).SetbVerified(bVerified);
        }
        else
        {
            vCustAct.at(iCounter).SetdCost(dZero);
            vCustAct.at(iCounter).SetActsName(sName);
            bVerified = false;
            vCustAct.at(iCounter).SetbVerified(bVerified);
        }
    }
}

double TotalPrice(std::vector <clscustomerlocation>& vCustLoc, std::vector <clsactivities>& vCustAct, std::vector <clsfamilydetails>& vFamily)
//This function calculates the total price of all the calculations so far
{
    double dTotalPrice = 0;
    double dLocationPrice = vCustLoc.at(0).GetdPrice();
    double dActPrice = 0;
    int iChildren = vFamily.at(0).GetiChildren();
    int iAdults = vFamily.at(0).GetiAdults();
    std::string sFamName = vFamily.at(0).GetFamsName();
    std::string sLocName = vCustLoc.at(0).GetsName();
    for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++) //loop for calculating activity prices
    {
        dTotalPrice = dLocationPrice + vCustAct.at(iCounter).GetdCost();
    }
    std::cout << "You are going to: " << sLocName << std::endl;
    std::cout << "You will be paying " << dLocationPrice << " to go there." << std::endl;
    std::cout << "The verified activity/ies you will be going to are: " << std::endl;
    for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++) //loop for verifying activities
    {
        if (vCustAct.at(iCounter).GetbVerified() == true)
        {
            std::cout << iCounter + 1 << ": " << vCustAct.at(iCounter).GetActsName() << std::endl;
            dActPrice = dActPrice + vCustAct.at(iCounter).GetdCost();
        }
    }
    dTotalPrice = dTotalPrice + dActPrice;
    if (iChildren == 2 && iAdults == 2)
    {
        std::cout << std::endl << "You get the family discount! (10% off)" << std::endl; //family discount if statement
        dTotalPrice = dTotalPrice - (dTotalPrice * 0.1);
    }
    std::cout << "Without VAT, this is the total price: " << dTotalPrice << std::endl;
    return dTotalPrice;
}

double PlusVAT(double dTotalPrice) //This function calculates the total price plus the VAT and displays it.
{
    double dPlusVAT = dTotalPrice * 1.2;
    std::cout << "This is the total price plus VAT: " << dPlusVAT << std::endl;
    return dPlusVAT;
}

void SaveReport(std::vector <clsfamilydetails>& vFamily, std::vector <clscustomerlocation>& vLocation, std::vector <clsactivities>& vCustAct, double dTotalPrice, double dPlusVAT) 
//function to save a report
{
    std::cout << vFamily.at(0).GetFamsName();
    std::string sFamilyDetails = vFamily.at(0).GetFamsName() + ".csv";
    std::ofstream File(sFamilyDetails);
    while (File.is_open())
    {
        File << vFamily.at(0).GetFamsName() << std::endl; //Saves family name
        File << vFamily.at(0).GetiAdults() << std::endl << vFamily.at(0).GetiChildren() << std::endl; //Saves amount of adults & children
        File << vLocation.at(0).GetsName() << std::endl << vLocation.at(0).GetdPrice() << std::endl;  //
        for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++)
        {
            if (vCustAct.at(iCounter).GetbVerified() == true)
            {
                File << vCustAct.at(iCounter).GetActsName() << std::endl;
            }
        }
        File << dTotalPrice << std::endl;
        File << dPlusVAT << std::endl;
        File.close();
    }
    std::cout << "Booking Successfully Saved!" << std::endl;
}

void VerifyActivity(std::vector <clsactivitiesdetails>& vActivities, std::vector <clsactivities>& vCustAct) //This function allows admins to verify user submitted activities
{
    bool bLoop = true;
    int iActivityChoice = 0;
    while (bLoop) {
        CustomActivitiesOutput(vCustAct);
        std::cout << "Please pick the activity you want to verify." << std::endl;
        iActivityChoice = GetALineConvert(iActivityChoice);
        iActivityChoice = iActivityChoice - 1;
        vActivities.push_back(clsactivitiesdetails());
        vActivities.at(vActivities.size() - 1).SetActDetName(vCustAct.at(iActivityChoice).GetActsName());
        vActivities.at(vActivities.size() - 1).SetActDetdCost(vCustAct.at(iActivityChoice).GetdCost());
        vActivities.at(vActivities.size() - 1).SetsActivitiesDetails(vCustAct.at(iActivityChoice).GetsActivities());
        vCustAct.erase(vCustAct.begin() + iActivityChoice);
        std::cout << "Activity Verified." << std::endl;
        bLoop = false;
    }
}

int main()
{
    double dTotalPrice = 0; //creating variables
    int iTest = 0;
    double dPlusVAT = 0;
    int iLoad = 0;
    int iLogin = 0;
    bool bEdit = false;
    bool bLoop = true;
    bool bCustom = false;
    std::string sFileName = "";
    std::string sResponse = "";
    std::vector <clsadmindetails> vAdmin(0); //vectors
    std::vector <clsfamilydetails> vFamily(0);
    std::vector <clscustomerlocation> vCustLoc;
    std::vector <clslocationdetails> vLocation;
    std::vector <clsactivitiesdetails> vActivities;
    std::vector <clsactivities> vCustAct;
    std::vector <clsactivities> vUnverifiedActs;
    bool bChoice = false;
    ProgramWelcome(); //calling functions
    AdminConstructor(vAdmin);
    CustLocConstructor(vCustLoc);
    FamilyConstructor(vFamily);
    clslocationdetailsPopulation(vLocation);
    LoadActivityDetails(vActivities);
    LoadCustomActivityDetails(vUnverifiedActs);
    while (bLoop) { //while for user input in case they get the incorrect username + password
        try {
            iLogin = Admin(vAdmin);
            if (iLogin == 0)
            {
                std::cout << "This username/password is incorrect" << std::endl;
            }
            if (iLogin == 1 || iLogin == 2) {
                bLoop = false;
            }
        }
        catch (std::exception)
        {
            std::cout << "Error, please try again" << std::endl;
        }
    }
    bLoop = true;
    vFamily.push_back(clsfamilydetails());
    vFamily.at(0).FamName();
    vFamily.at(0).Ages();
    while (bLoop) { //loop for when a case is finished, so you can do more than 1 thing at a time in the program.
        try {
            iLoad = Choice(iLogin);
            switch (iLoad)
            {
            case 1: //create a user
                Location(vLocation, vCustLoc, vFamily);
                Activities(vActivities, &vCustAct, vCustLoc);
                bChoice = CustomerActivites();
                if (bChoice == true) //this is only if the user wants to create their own activities
                {
                    GetCustomerclsactivities(&vCustAct, vUnverifiedActs);
                    SaveCustomActivityDetails(vUnverifiedActs);
                }
                dTotalPrice = TotalPrice(vCustLoc, vCustAct, vFamily);
                dPlusVAT = PlusVAT(dTotalPrice);
                for (int iCounter = 0; iCounter < vCustAct.size(); iCounter++) //loop for activities
                {
                    std::cout << "Activity " << iCounter + 1 << std::endl;
                    std::cout << vCustAct.at(iCounter).GetActsName() << std::endl;
                }
                SaveReport(vFamily, vCustLoc, vCustAct, dTotalPrice, dPlusVAT);
                break;
            case 2: //output all locations
                LocationOutput(vLocation);
                break;
            case 3: //output all activities
                ActivitiesOutput(vActivities);
                break;
            case 4: //loading files
                vCustLoc.push_back(clscustomerlocation());
                vCustAct.push_back(clsactivities());
                vFamily.push_back(clsfamilydetails());
                sFileName = FileName();
                dTotalPrice = LoadFile(vCustLoc, vCustAct, vFamily, sFileName);
                LoadFileDisplay(vCustLoc, vCustAct, vFamily, sFileName, dTotalPrice);
                break;
            case 5: //for exiting the program
                return 0;
                break;
            case 6: //in case the user messed up while entering family details
                std::cout << "Please re-enter your family details." << std::endl;
                vFamily.push_back(clsfamilydetails());
                vFamily.at(0).FamName();
                vFamily.at(0).Ages();
                break;
            case 7: //verifying activities (admin only)
                if (iLogin == 1) { throw std::exception("User not authorized"); }
                VerifyActivity(vActivities, vUnverifiedActs);
                SaveActivityDetails(vActivities);
                SaveCustomActivityDetails(vCustAct);
                break;
            case 8: //allows the user to create a custom activity
                bCustom = CustomerActivites();
                GetCustomerclsactivities(&vCustAct, vUnverifiedActs);
                SaveCustomActivityDetails(vUnverifiedActs);
                break;
            }
        }
    

        catch (std::exception) { //in case there are errors
            std::cout << "Error, please try again" << std::endl;
        }
    }
}