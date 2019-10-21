#include <termios.h>         // struct termios, tcgetattr(), tcsetattr()
#include <stdio.h>           // perror()
#include <unistd.h>          // STDIN_FILENO

/*----------------------------------------------------------------------------*
* setTermToSingleChar
*
* Set the terminal to single character mode and no echo
* Details here:
* https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_17.html
*
* Inputs
*   oldTerm            Where to save the current terminal settings.
*
*  Output:
*   true               Successful
*   false              Unsuccessful
*-----------------------------------------------------------------------------*/
bool setTermToSingleChar( struct termios *oldTerm )
{
    struct termios newTerm;

    // Save the parameters of the current stdin terminal to oldTerm.
    tcgetattr( STDIN_FILENO, oldTerm );

    // Copy the settings
    newTerm = *oldTerm;

    // ICANON normally takes care that one line at a time is processed,
    // that means it will return if it sees a "\n" or an EOF or an EOL
    // ECHO normally takes care of echoing the input char.
    newTerm.c_lflag &= ~(ICANON | ECHO);  // Clear both
    newTerm.c_cc[VMIN] = 1;
    newTerm.c_cc[VTIME] = 0;

    // Apply the new terminal settings after all queued output has been written.
    if( tcsetattr( STDIN_FILENO, TCSAFLUSH, &newTerm ) < 0 )
    {
        perror( "Unable to set terminal to single character mode" );
        return false;
    }

    return true;
}


/*----------------------------------------------------------------------------*
* restoreTermMode
*
* Restore terminal settings to those specified by the caller.
*
* Inputs
*   savedTerm          Contains terminal settings to restore.
*
*  Output:
*   true               Successful
*   false              Unsuccessful
*-----------------------------------------------------------------------------*/
bool restoreTermMode( struct termios *savedTerm )
{
   if( tcsetattr( STDIN_FILENO, TCSANOW, savedTerm ) < 0 )
   {
        perror( "Unable to restore terminal mode" );
        return false;
   }

   return true;
}
