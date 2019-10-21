#include <iostream>          // std::cout, std::cin
#include <string>            // std::string
#include <vector>            // std::vector
#include <termios.h>         // struct termios
#include "customer.h"        // Class customer
#include "misc.h"            // Function prototypes

/*----------------------------------------------------------------------------*
* mgmtMenu
*
* Displays a menu of choices to the user and waits for them to make a
* selection.  The terminal is placed in single character mode so that the
* user doesn't have to press <enter> after making a selection.  A corresponding
* action is taken per the users choice.
*
* Inputs
*   pathName           The system pathname to the customer file.
*   customerListVec    A vector containing the customer data.
*
*  Output: None
*-----------------------------------------------------------------------------*/
void mgmtMenu( std::string pathName, std::vector<Customer> & customerListVec )
{
    char choice;
    struct termios t_saved;

    while( true )
    {
        std::cout << std::endl << "Select An Option: ";
        std::cout << std::endl << "a) Add a new customer";
        std::cout << std::endl << "r) Remove a customer";
        std::cout << std::endl << "s) Save changes";
        std::cout << std::endl << "e) Exit";
        std::cout << std::endl << "Enter a, r, s, e: ";

        // Read a single character from the keyboard and display it
        // immediately on the output screen without waiting for the enter key.
        if( !setTermToSingleChar( &t_saved ) )
        {
            return;
        }
        std::cin >> choice;
        std::cout << choice;
        if( !restoreTermMode( &t_saved ) )
        {
            return;
        }

        switch( choice )
        {
           case 'a':
              customerAdd( customerListVec );
              break;

           case 'r':
              customerRemove( customerListVec );
              break;

           case 's':
              customerWriteToFile( pathName, customerListVec );
              break;

           case 'e':
              return;

           default:
              std::cout << " <-- Invalid choice" << std::endl;
        }
    };

    return;
}
