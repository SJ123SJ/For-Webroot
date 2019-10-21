#include <iostream>
#include <string>
#include <string.h>  // For strerror
#include <fstream>
#include <vector>
#include <regex>
#include "misc.h"

/*----------------------------------------------------------------------------*
* customerReadFromFile
*
* This function will attempt to open the callers file and retrieve customer
* data.  The customer data will be saved to the callers vector.  The callers
* file will be closed upon exit.
*
* Inputs
*   pathName           The system pathname to the customer file.
*   customerListVec    The customer data is saved to this vector.
*
* Output
*   true               The function was successful in retrieving all the
*                      data from the callers file.
*   false              The function was unsuccessful in retrieving all the
*                      data from the callers file.
*-----------------------------------------------------------------------------*/
bool customerReadFromFile( std::string pathName, std::vector<Customer> & customerListVec )
{
    // Open the input file
    std::cout << std::endl << "Opening customer list: '" << pathName << "'";
    std::ifstream inputFile( pathName.c_str() );

    // Check if the file was successfully opened
    if( !inputFile.is_open() )
    {
        std::cerr << std::endl << "Can't open the file: '" << pathName << "' because \"" << strerror( errno ) << "\"" << std::endl;
        return false;
    }

    // Read each customer record into a customer object and save the object
    // to the callers vector.
    std::string tmpRecord;
    std::string tmpStr;
    bool retCode = true;
    Customer tempCust;
    while( inputFile >> tmpRecord )
    {
        // Verify that the record number for this customer is a positive value.
        if( std::regex_match( tmpRecord, std::regex("[0-9]+") ) )
          tempCust.setRecordNumber( tmpRecord );
        else
        {
           std::cerr << std::endl << std::endl << "==> Error: A customer record number is invalid: " << tmpRecord;
           if( tempCust.getRecordNumber().compare( "0" ) == 0 )
              std::cerr << std::endl << "The last valid record is: NONE";
           else
              std::cerr << std::endl << "The last record read is: " << tempCust.getRecordNumber();
           std::cerr << std::endl;
           retCode = false;
           break;
        }

        // Retrieve the firstName
        if( inputFile >> tmpStr )
        {
           tempCust.setFirstName( tmpStr );
        }
        else
        {
           showError( tmpRecord );
           retCode = false;
           break;
        }

        // Retrieve the lastName
        if( inputFile >> tmpStr )
        {
           tempCust.setLastName( tmpStr );
        }
        else
        {
           showError( tmpRecord );
           retCode = false;
           break;
        }

        // Retrieve the salt string
        if( inputFile >> tmpStr )
        {
           tempCust.setSalt( tmpStr );
        }
        else
        {
           showError( tmpRecord );
           retCode = false;
           break;
        }

        // Retrieve the password hash string
        if( inputFile >> tmpStr )
        {
           tempCust.setPasswordHash( tmpStr );
        }
        else
        {
           showError( tmpRecord );
           retCode = false;
           break;
        }

        // Retrieve the secret message string
        if( inputFile >> tmpStr )
        {
           tempCust.setSecretMsg( tmpStr );
        }
        else
        {
           showError( tmpRecord );
           retCode = false;
           break;
        }

        // Save the customer object to the callers vector
        customerListVec.push_back( tempCust );
    }

    // Clear the stream state and close the input file.
    inputFile.clear();
    inputFile.close();
    return retCode;
}

// Common error reporting handler.
void showError( std::string & recordNumber )
{
    std::cerr << std::endl << std::endl << "==> Error reading the customer list";
    std::cerr << std::endl << "==> Customer record '" << recordNumber << "' is invalid";
    std::cerr << std::endl;
    return;
}
