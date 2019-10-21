#ifndef customer_h
#define customer_h

#include <string>            // std:string

class Customer
{
    private:
        std::string recordNumber;
        std::string firstName;
        std::string lastName;
        std::string salt;
        std::string passwordHash;
        std::string secretMsg;

    public:
        Customer();   // Default constructor

        // Setters
        void setRecordNumber( std::string rn );
        void setFirstName   ( std::string fn );
        void setLastName    ( std::string ln );
        void setSalt        ( std::string ss );
        void setPasswordHash( std::string pw );
        void setSecretMsg   ( std::string bal);

        // Getters
        std::string & getRecordNumber( void );
        std::string & getFirstName( void );
        std::string & getLastName( void );
        std::string & getSalt( void );
        std::string & getPasswordHash( void );
        std::string & getSecretMsg( void );

        // Methods
        void showCustomerData();
};

#endif
