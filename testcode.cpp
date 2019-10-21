#include <iostream>
#include <string>            // std::string
#include "misc.h"            // Function prototypes
#include "sha256.h"          // SHA256 cryptographic hash
using std::cout;
using std::cerr;
using std::endl;

int main()
{
   cout << "Testing Salt output" << endl;
   for( size_t ix=0; ix < 20; ix++ )
   {
       std::string salt;
       genRandomSalt( salt );
       cout << salt << endl;

       if( salt.size() != 16 )
       {
          cerr << "Salt size not 16: Detected: " << salt.size() << endl;
          return EXIT_FAILURE;
       }

       for( size_t jx=0; jx < salt.size(); jx++ )
       {
          if( std::isprint( salt[ jx ] ) == 0 )
          {
             // All the chars should be printable
             cerr << "Unprintable salt char detected" << endl;
             return EXIT_FAILURE;
          }
       }
   }
   cout << "Salt testing complete" << endl << endl;

   //--------------------------------------------------------------------------
   cout << "Testing Encrypt/Decrypt" << endl;

   std::string ins;
   for( size_t ix=0; ix < 10; ix++ )
   {
      ins.clear();
      std::string ins = std::to_string( ix ) + " ";
      std::string str( "^This i$ a t3st string! !@#$%^&*){}[]0123456789" );
      str.insert( 0, ins );
      cout << "Encrypt: " << str << endl;
      std::string enc = encryptDecrypt( str );
      cout << "Decrypt: " << enc << endl;
      std::string org = encryptDecrypt( enc );

      if( org.compare( str ) != 0 )
      {
         cerr << "Failure in encrypt/decrypt" << endl;
         cerr << "Decrypting: " << org << endl;
         return EXIT_FAILURE;
      }
   }

   cout << "Encrypt/Decrypt complete" << endl << endl;

   //--------------------------------------------------------------------------
   cout << "Testing record reads" << endl;

   std::vector<Customer> customerList;
   if( customerReadFromFile( "test1", customerList ) == true )
   {
      cerr << "Record should have failed as record number is a a letter" << endl;
      return EXIT_FAILURE;

   }

   customerList.clear();
   if( customerReadFromFile( "test2", customerList ) == true )
   {
      cerr << "Record should have failed as record 6 is missing last name field" << endl;
      return EXIT_FAILURE;

   }

   customerList.clear();
   if( customerReadFromFile( "test3", customerList ) == false )
   {
      cerr << "Record should have passed with 4 valid customers" << endl;
      return EXIT_FAILURE;
   }

   cout << endl << "Record reading complete" << endl << endl;

   //--------------------------------------------------------------------------
   cout << "Testing customer class methods" << endl;

   Customer test;
   test.setRecordNumber( "srn" );
   test.setFirstName   ( "sfn" );
   test.setLastName    ( "fln" );
   test.setSalt        ( "ssa" );
   test.setPasswordHash( "sph" );
   test.setSecretMsg   ( "ssm" );

   if( test.getRecordNumber().compare( "srn" ) != 0 )
   {
      cerr << "Customer class set/get RecordNumber methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   if( test.getFirstName().compare( "sfn" ) != 0 )
   {
      cerr << "Customer class set/get FirstName methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   if( test.getLastName().compare( "fln" ) != 0 )
   {
      cerr << "Customer class set/get LastName methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   if( test.getSalt().compare( "ssa" ) != 0 )
   {
      cerr << "Customer class set/get Salt methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   if( test.getPasswordHash().compare( "sph" ) != 0 )
   {
      cerr << "Customer class set/get Hash methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   if( test.getSecretMsg().compare( "ssm" ) != 0 )
   {
      cerr << "Customer class set/get SecretMsg methods incorrect" << endl;
      return EXIT_FAILURE;
   }

   cout << "Class methods complete" << endl << endl;

   //--------------------------------------------------------------------------
   cout << "Testing SHA256" << endl;
   std::string hash( "test" );
   std::string hashed = sha256( hash );
   cout << "Hash: " << hashed;

   cout << endl << "SHA256 method complete" << endl << endl;

   //--------------------------------------------------------------------------

   return EXIT_SUCCESS;
}

