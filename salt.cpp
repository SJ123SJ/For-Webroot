#include <iostream>
#include <string>
#include <random>
#include "misc.h"

/*----------------------------------------------------------------------------*
* genRandomSalt
*
* This function will create a 16-byte salt string from an array of characters.
*
* Inputs: A string to store the salt data.
*
* Output: None
*-----------------------------------------------------------------------------*/

// The following characters can be used in customer passwords
static const char alphaNumeric[] =
 "0123456789"
 "!@#$%^&*"
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 "abcdefghijklmnopqrstuvwxyz";

// There are 70 chars indexing from 0-69, don't include the '\0'.
#define ALPHALEN  (sizeof( alphaNumeric ) - 2)
#define SALTLEN   16

void genRandomSalt( std::string & salt )
{
    std::random_device rd;

    // A Mersenne Twister pseudo-random generator seeded with rd.
    std::mt19937 generator( rd() );

    // Create a uniformly-distributed integer random number generator that
    // produces non-deterministic random numbers between the specified range
    // inclusive.
    std::uniform_int_distribution<int> alphaIndex( 0, ALPHALEN );

    salt.clear();
    for( size_t ix=0; ix < SALTLEN; ix++ )
       salt += alphaNumeric[ alphaIndex( generator ) ];

    return;
}


/*----------------------------------------------------------------------------*
* encryptDecrypt
*
* Simple XOR Encryption/Decryption.  Adds a quick deterrent to data
* inspection but is NOT secure. It uses multiple keys to make it harder
* to break.
*
* Inputs
*   toEncrypt          A string to encrypt or decrypt
*
* Output
*   string             The result of encryption or decryption
*-----------------------------------------------------------------------------*/
std::string encryptDecrypt( std::string toEncrypt )
{
   char key[3] = {'J', 'Q', 'X'}; // Any chars will work
   std::string output = toEncrypt;

   for( size_t ix = 0; ix < toEncrypt.size(); ix++ )
      output[ ix ] = toEncrypt[ ix ] ^ key[ ix % (sizeof(key) / sizeof(char)) ];

   return output;
}
