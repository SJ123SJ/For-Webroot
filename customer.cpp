#include <iostream>
#include <string>
#include "customer.h"

// Default Constructor
// By design, there is no record '0'. The first record is '1'.
// This info can be used to detect when no records are valid.
Customer::Customer()
{
    recordNumber = "0";
}


// Setters
void Customer::setRecordNumber( std::string rn )
{
    recordNumber = rn;
}

void Customer::setFirstName   ( std::string fn )
{
    firstName = fn;
}

void Customer::setLastName    ( std::string ln )
{
    lastName = ln;
}

void Customer::setSalt        ( std::string salt_ )
{
    salt = salt_;
}

void Customer::setPasswordHash( std::string pwh )
{
    passwordHash = pwh;
}

void Customer::setSecretMsg   ( std::string sm )
{
    secretMsg = sm;
}

// ----------------------------------------------------------
// Getters
std::string & Customer::getRecordNumber( void )
{
    return recordNumber;
}

std::string & Customer::getFirstName( void )
{
    return firstName;
}

std::string & Customer::getLastName( void )
{
    return lastName;
}

std::string & Customer::getSalt( void )
{
    return salt;
}

std::string & Customer::getPasswordHash( void )
{
    return passwordHash;
}

std::string & Customer::getSecretMsg( void )
{
    return secretMsg;
}


// ----------------------------------------------------------
// Methods
void Customer::showCustomerData()
{
    std::cout << "#         : " << recordNumber << std::endl;
    std::cout << "First Name: " << firstName    << std::endl;
    std::cout << "Last  Name: " << lastName     << std::endl;
    std::cout << "Salt      : " << salt         << std::endl;
    std::cout << "PW Hash   : " << passwordHash << std::endl;
    std::cout << "Secret Msg: " << secretMsg    << std::endl;
    std::cout << std::endl;
}
