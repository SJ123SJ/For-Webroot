#include <iostream>          // std::cout
#include <string>            // std::string
#include <vector>            // std::vector
#include <string.h>          // strcasecmp()
#include <termios.h>         // struct termios
#include "customer.h"        // Class customer
#include "misc.h"            // Function protos
#include "sha256.h"          // SHA256 cryptographic hash

#include <unistd.h>
#include <termios.h>
bool login( std::vector<Customer> & customerListVec, size_t *vecId );

/*----------------------------------------------------------------------------*
* Login to read the customers secret message
*-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
   //---------------------------------------------------------------------------
   // Check program syntax
   if( argc != 2 )
   {
       std::cout << "This program will prompt the user to login so that they " << std::endl;
       std::cout << "can read their secret message."                           << std::endl;
       std::cout << std::endl;
       std::cout << "Syntax: "       << argv[0] << " customerlist_pathname"    << std::endl;
       std::cout << std::endl;

       std::cout << "Compiled on " << __DATE__ << ", " << __TIME__ << std::endl;
       return EXIT_FAILURE;
   }

   std::string customerListFile = argv[1];

   //---------------------------------------------------------------------------
   std::vector<Customer> customerListVec;

   // Attempt to retrieve the contents of the customer list file.
   if( !customerReadFromFile( customerListFile, customerListVec ) )
   {
       return EXIT_FAILURE;
   }

    std::cout << std::endl << "The customer list contains " << customerListVec.size() << " customers: " << std::endl;

    #ifdef DEBUG
    // Display the entire list
    for( size_t ix=0; ix < customerListVec.size(); ix++ )
    {
       Customer temp = customerListVec.at( ix );
       temp.showCustomerData();
    }
    #endif

   //---------------------------------------------------------------------------
   // Prompt the user to login
   size_t vecId;

   // Allow the user at most 5 tries to login
   bool loggedIn = false;
   for( size_t ix=0; ix < 5; ix++ )
   {
      if( !login( customerListVec, &vecId ) )
          std::cout << std::endl << "Login username/password incorrect";
      else
      {
          std::cout << std::endl << "Login Successful";
          loggedIn = true;
          break;
      }
   }

   //---------------------------------------------------------------------------
   if( loggedIn == false )
   {
      std::cout << std::endl << "Maximum number of login attempts exceeded!";
   }
   else
   {
       Customer validUser = customerListVec.at( vecId );
       std::cout << std::endl << "Your secret message is: " << encryptDecrypt( validUser.getSecretMsg() );
   }

   //---------------------------------------------------------------------------
   std::cout << std::endl << "Program Completed" << std::endl;

   return EXIT_SUCCESS;
}


/*----------------------------------------------------------------------------*
* login
*
* Authenticates a prospective user.
*
* Inputs:
*   customerListVec    A vector containing the customer data.
*
* Output:
*   true               The user is authentic.
*   vecId              The vector index addresses the users info.
*
*   false              The user name/password was incorrect or could not be
*                      obtained from the terminal or ESC was pressed.
*   vecId              The vector index is not modified.
*-----------------------------------------------------------------------------*/
bool login( std::vector<Customer> & customerListVec, size_t *vecId )
{
   std::string firstName;
   std::string lastName;
   std::string password;
   size_t ix;

   std::cout << std::endl << "<<Enter sign-in credentials>>";
   std::cout << std::endl << "Enter first name: ";
   if( !getInput( firstName, false ) )
     return false;
   std::cout << "Enter last name: ";
   if( !getInput( lastName, false ) )
     return false;

   std::cout << "Enter password: ";
   if( !getInput( password, true ) )
     return false;

   bool found = false;
   Customer temp;
   for( ix=0; ix < customerListVec.size(); ix++ )
   {
      temp = customerListVec.at( ix );
      if( strcasecmp( firstName.c_str(), temp.getFirstName().c_str() ) == 0
       &&
          strcasecmp( lastName.c_str(), temp.getLastName().c_str() ) == 0 )
      {
          // A match was found!
          found = true;
          break;
      }
   }

   if( !found )
     return false;

   // Authenticate the password
   std::string combo( password + temp.getSalt() );
   std::string hashed = sha256( combo );
   if( hashed.compare( temp.getPasswordHash() ) != 0 )
   {
      return false;
   }

   // The password is authentic, provide the caller with the vector index.
   *vecId = ix;
   return true;
}


