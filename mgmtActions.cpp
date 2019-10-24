#include <iostream>          // std::cout
#include <fstream>           // std::ofstream
#include <sstream>           // std:stringstream
#include <string>            // std::string
#include <vector>            // std::vector
#include <string.h>          // strcasecmp()
#include "customer.h"        // Class customer
#include "misc.h"            // Function prototypes
#include "sha256.h"          // SHA256 cryptographic hash

/*----------------------------------------------------------------------------*
* customerAdd
*
* Adds a new customer to the callers vector by prompting the user for the
* customer data.  A new salt is computed for the new customer and the hashed
* results are saved to the vector.  The customers secret message is also
* encrypted and saved to the vector.
*
* Inputs:
*   customerListVec    A vector containing the customer data.
*
* Output:
*   None
*-----------------------------------------------------------------------------*/
void customerAdd( std::vector<Customer> & customerListVec )
{
   size_t recNumVal;
   if( customerListVec.size() == 0 )
   {
      recNumVal = 1;
   }
   else
   {
      // Retrieve the last customer record in the list and obtain its customer
      // record number.
      Customer last = customerListVec.back();

      // Convert the record number string into a number and increment it.
      std::stringstream recNumStrLast( last.getRecordNumber() );
      recNumStrLast >> recNumVal;
      recNumVal++;
   }

   // Create the new customer record and fill in the members.
   Customer newCustomer;
   newCustomer.setRecordNumber( std::to_string( recNumVal )  );

   std::string firstName;
   std::cout << std::endl << "Enter the first name of the new customer (no spaces): ";
   if( !getInput( firstName, false ) )
     return;
   newCustomer.setFirstName( firstName );

   std::string lastName;
   std::cout << "Enter the last name of the new customer (no spaces): ";
   if( !getInput( lastName, false ) )
     return;
   newCustomer.setLastName( lastName );

   // Check for a duplicate user
   Customer temp;
   for( size_t ix=0; ix < customerListVec.size(); ix++ )
   {
      temp = customerListVec.at( ix );
      if( strcasecmp( firstName.c_str(), temp.getFirstName().c_str() ) == 0
       &&
          strcasecmp( lastName.c_str(), temp.getLastName().c_str() ) == 0 )
      {
          // A match was found!
          std::cout << std::endl << "==> A user with this name already exists!" << std::endl;
          return;
      }
   }

   std::string passWord;
   std::cout << "Enter a password for the new customer (no spaces): ";
   if( !getInput( passWord, true ) )
     return;

   std::string salt;
   genRandomSalt( salt );
   newCustomer.setSalt( salt );
   std::string combo( passWord + salt );
   std::string hashed = sha256( combo );
   newCustomer.setPasswordHash( hashed );

   std::string secretMsg;
   std::cout << "Enter a secret message: ";
   if( !getInput( secretMsg, false ) )
     return;
   newCustomer.setSecretMsg( encryptDecrypt( secretMsg ) );

   customerListVec.push_back( newCustomer );
   return;
}


/*----------------------------------------------------------------------------*
* customerRemove
*
* Removes a customer from the callers vector. The user is prompted for the
* first and last name of the customer to remove.
*
* Inputs:
*   customerListVec    A vector containing the customer data.
*
* Output:
*   None
*-----------------------------------------------------------------------------*/
void customerRemove( std::vector<Customer> & customerListVec )
{
   std::string firstName;
   std::string lastName;

   std::cout << std::endl << "Enter the first name of the customer to remove: ";
   std::cin >> firstName;
   std::cout << "Enter the last name of the customer to remove: ";
   std::cin >> lastName;


   for( size_t ix=0; ix < customerListVec.size(); ix++ )
   {
      Customer temp = customerListVec.at( ix );
      if( strcasecmp( firstName.c_str(), temp.getFirstName().c_str() ) == 0
       &&
          strcasecmp( lastName.c_str(), temp.getLastName().c_str() ) == 0 )
      {
          // A match was found!
          std::cout << std::endl << "Removing customer: " << firstName << " " << lastName << std::endl;
          customerListVec.erase( customerListVec.begin() + ix );
          return;
      }
   }

   std::cout << std::endl << "No customer match found" << std::endl;

   return;
}


/*----------------------------------------------------------------------------*
* customerWriteToFile
*
* Writes the callers vector to the callers pathName.
*
* Inputs
*   pathName           The system pathname to write to the customer data to.
*   customerListVec    The customer data to write.
*
* Output
*   true               The function was successful in writing all the
*                      data to the callers file.
*   false              The function was unsuccessful in writing all the
*                      data to the callers file.
*-----------------------------------------------------------------------------*/
bool customerWriteToFile( std::string pathName, std::vector<Customer> & customerListVec )
{
   // Open the output file
   std::cout << std::endl << std::endl << "Creating new customer list: '" << pathName << "'" << std::endl;
   std::ofstream outputFile( pathName.c_str() );

   // Check if the file was successfully opened
   if( !outputFile.is_open() )
   {
       std::cerr << std::endl << "Can't open the file: '" << pathName << "' because \"" << strerror( errno ) << "\"" << std::endl;
       return false;
   }

   for( size_t ix=0; ix < customerListVec.size(); ix++ )
   {
       Customer nextCust = customerListVec.at( ix );

       // Write the object's data to the file
       outputFile << nextCust.getRecordNumber() << std::endl;
       outputFile << nextCust.getFirstName()    << std::endl;
       outputFile << nextCust.getLastName()     << std::endl;
       outputFile << nextCust.getSalt()         << std::endl;
       outputFile << nextCust.getPasswordHash() << std::endl;
       outputFile << nextCust.getSecretMsg()    << std::endl;
       outputFile << std::endl;
   }

   return true;
}
