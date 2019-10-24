#ifndef misc_h
#define misc_h

#include <string>            // std:string
#include <vector>            // std::vector
#include "customer.h"


// Function Prototypes
bool customerReadFromFile( std::string pathName, std::vector<Customer> & customerListVec );
bool customerWriteToFile(  std::string pathName, std::vector<Customer> & customerListVec );
void showError( std::string & recordNumber );
void genRandomSalt( std::string & salt );
void mgmtMenu( std::string pathName, std::vector<Customer> & customerListVec );
bool setTermToSingleChar( struct termios *t_saved );
bool restoreTermMode( struct termios *t_saved );
bool getch( char *ch, bool echo );
bool getInput( std::string & passwd, bool hidden );
void customerAdd( std::vector<Customer> & customerListVec );
void customerRemove( std::vector<Customer> & customerListVec );
std::string encryptDecrypt( std::string toEncrypt );

#endif
