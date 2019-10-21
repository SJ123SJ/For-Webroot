#include <iostream>          // std::cout
#include <string>            // std::string
#include <vector>            // std::vector
#include <string.h>          // strcasecmp()
#include "customer.h"        // Class customer
#include "misc.h"            // Function protos

/*----------------------------------------------------------------------------*
* Main Customer Management Code
*-----------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{
   //---------------------------------------------------------------------------
   // Check program syntax
   if( argc < 2 || argc > 3 )
   {
       std::cout << "This program will allow an admin to manage customer records."   << std::endl;
       std::cout << "The admin will be able to create a new customer file or read"   << std::endl;
       std::cout << "from an existing file."                                         << std::endl;
       std::cout << std::endl;
       std::cout << "Syntax: "       << argv[0] << " customerlist_pathname [create]" << std::endl;
       std::cout << std::endl;
       std::cout << "Example 1 - Read from an existing file"                         << std::endl;
       std::cout << "         " << argv[0] << " ./customerlist1.txt"                 << std::endl;
       std::cout << std::endl;
       std::cout << "Example 2 - Create a new customer file"                         << std::endl;
       std::cout << "         " << argv[0] << " ./customerlist2.txt create"          << std::endl;
       std::cout << std::endl;

       std::cout << "Compiled on " << __DATE__ << ", " << __TIME__ << std::endl;
       return EXIT_FAILURE;
   }

   std::string customerListFile = argv[1];

   //---------------------------------------------------------------------------
   std::vector<Customer> customerListVec;
   if( argc == 2 )
   {
       // Attempt to retrieve the contents of the customer list file.
       if( !customerReadFromFile( customerListFile, customerListVec ) )
       {
           return EXIT_FAILURE;
       }

        std::cout << std::endl << "The customer list contains " << customerListVec.size() << " customers" << std::endl;

        #ifdef DEBUG
        // Display the entire list
        for( size_t ix=0; ix < customerListVec.size(); ix++ )
        {
           Customer temp = customerListVec.at( ix );
           temp.showCustomerData();
        }
        #endif
   }
   else if( argc == 3 && strcasecmp( argv[2], "create" ) == 0 )
   {
      // A new customer record file will be created.
      std::cout << std::endl << "Creating new customer file" << std::endl;

   }
   else
   {
      std::cout << std::endl << "Invalid program parameter: " << argv[2] << std::endl;
      return EXIT_FAILURE;
   }



   //---------------------------------------------------------------------------
   mgmtMenu( customerListFile, customerListVec );

   #ifdef DEBUG
   std::cout << std::endl << "The customer list contains " << customerListVec.size() << " customers: " << std::endl;
   for( size_t ix=0; ix < customerListVec.size(); ix++ )
   {
      Customer temp = customerListVec.at( ix );
      temp.showCustomerData();
   }
   #endif

   //---------------------------------------------------------------------------
   std::cout << std::endl << "Program Completed" << std::endl;

   return EXIT_SUCCESS;
}
