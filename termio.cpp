#include <stdio.h>           // perror()
#include <termios.h>         // struct termios, tcgetattr(), tcsetattr()
#include <string>            // std::string
#include <unistd.h>          // read()
#include <ctype.h>           // isprint()

#include <iostream>
/*----------------------------------------------------------------------------*
* getch
*
* Gets a single character from the terminal and returns.
*
* Inputs:
*  ch                Where to save the read character
*  echo              true to echo the character that was read
*                    false will NOT echo the character that was read
*
* Output:
*  true              A character was successfully read
*  false             A character was not able to be read
*-----------------------------------------------------------------------------*/
bool getch( char *ch, bool echo )
{
    struct termios old;

    fflush( stdout );   // Make sure any cout type data is flushed to the term.

    if( tcgetattr( 0, &old ) < 0 )
    {
       perror( "Unable to retrieve terminal settings" );
       return false;
    }

    old.c_lflag &= ~(ICANON | ECHO);  // Clear both
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;

    if( tcsetattr( 0, TCSANOW, &old ) < 0 )
    {
       perror( "Unable to set the terminal to single character mode" );
       return false;
    }

    // Read 1 character from the terminal.
    if( read( 0, ch, 1 ) < 0 )
    {
       perror( "Could not read() from terminal in single character mode" );
       return false;
    }

    old.c_lflag |= ICANON | ECHO;

    // Make the change after waiting until all queued output has been written.
    if( tcsetattr( 0, TCSADRAIN, &old ) < 0 )
      perror( "tcsetattr TCSADRAIN" );

    if( echo )
      putchar( *ch );

    return true;
}


/*----------------------------------------------------------------------------*
* getInput
*
* Reads characters from the terminal and echos back what was read or '*'
* until <ENTER> or ESC is read. The characters are saved to the callers string.
*
* Inputs:
*  Input             Where to store the retrieved input data.
*  hidden            true to echo back a '*' instead of what was read (for passwords)
*                    false to echo back what was read.
*
* Output:
*  true              A character was successfully read
*  false             A character was not able to be read or ESC was pressed.
*-----------------------------------------------------------------------------*/
#define BACKSPACE 127
#define ESC        27
bool getInput( std::string & input, bool hidden )
{
   char ch;             // Used to read character
   char cnt=0;          // Valid character count

   input.clear();
   while( true )
   {
      if( !getch( &ch, false ) )
        return false;   // Term failure of some kind

      if( ch == '\n' )
      {
         putchar( '\n' );   // Echo back the <ENTER>
         return true;       // Successful.
      }

      if( ch == ESC )
      {
         return false;      // Aborted.
      }

      if( ch == BACKSPACE )   // Backspace was read
      {
         if( cnt != 0 ) // Make sure at least 1 valid char has been read.
         {
            putchar( '\b' );  // Erase the term character that was read.
            putchar( ' '  );
            putchar( '\b' );
            input.pop_back(); // Remove the last char from the string.
            --cnt;
         }
         continue;             // Continue reading chars
      }

      if( isprint(ch ) )   // Only permit ASCII 0x32 to 0x126
      {
         input += ch;      // Save the char read from the terminal
         ++cnt;            // Indicate a character was read.
         if( hidden )
           putchar( '*' );   // Echo back an asterisk
         else
           putchar( ch );    // Echo back what was read
      }
   }
}
