all: custmgmt getsecret testcode

objects1 = custmgmt.o customerReadFromFile.o customer.o sha256.o salt.o mgmtMenu.o mgmtActions.o termio.o
objects2 = getsecret.o customerReadFromFile.o customer.o sha256.o salt.o termio.o
objects3 = testcode.o customerReadFromFile.o customer.o sha256.o salt.o

#########################################################
# Compiler
#########################################################
CC = g++

#flags = -Wall -O2 -DDEBUG
flags = -Wall -O2


#########################################################
# Targets
#########################################################
custmgmt : $(objects1)
		$(CC) -o custmgmt $(flags) $(objects1)

getsecret: $(objects2)
		$(CC) -o getsecret $(flags) $(objects2)

testcode : $(objects3)
		$(CC) -o testcode $(flags) $(objects3)

#########################################################
# Objects
#########################################################
testcode.o : testcode.cpp misc.h customer.h
		$(CC) -c $(flags) testcode.cpp

getsecret.o : getsecret.cpp misc.h customer.h
		$(CC) -c $(flags) getsecret.cpp

custmgmt.o : custmgmt.cpp misc.h customer.h
		$(CC) -c $(flags) custmgmt.cpp

customerReadFromFile.o : customerReadFromFile.cpp misc.h customer.h
		$(CC) -c $(flags) customerReadFromFile.cpp

customer.o : customer.cpp customer.h
		$(CC) -c $(flags) customer.cpp

salt.o : salt.cpp misc.h
		$(CC) -c $(flags) salt.cpp

mgmtMenu.o : mgmtMenu.cpp misc.h customer.h
		$(CC) -c $(flags) mgmtMenu.cpp

mgmtActions.o : mgmtActions.cpp misc.h customer.h
	        $(CC) -c $(flags) mgmtActions.cpp

termio.o : termio.cpp misc.h
	        $(CC) -c $(flags) termio.cpp

sha256.o : sha256.cpp sha256.h
		$(CC) -c $(flags) sha256.cpp

.PHONY : clean
clean :
	rm -f custmgmt.exe getsecret.exe testcode.exe getsecret.o testcode.o $(objects1)
