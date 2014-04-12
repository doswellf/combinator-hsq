
export CPPFLAGS='-I. -I.. -I/usr/local/sysc230/include -I/usr/include/c++/4.6.3 -I/usr/include -std=c++11 -std=gnu++11'

export LDFLAGS='-L/usr/lib64 -L/usr/local/eda/sysc230/lib-linux64 -L/usr/lib64 -lsystemc -lm -std=c++11 -std=gnu++11'

for sf in `ls -1d *.cpp | grep driver_test.cpp`;
do
g++ -c $sf -I. -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 -I/usr/include 
done 

# this line attempts to link every object file into one executable
# this will need to be tuned and used in sub-directories
# manual makefiles will be called in scripts until all the parts compile and run
# 
# once all parts build manually, the full library can be built then an executable can be linked to it
# using the current automake framework that contains this project
#  

g++ -o scsb101 -I. -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 	\
  -I/usr/include   *.o -L/usr/lib64 				\
  -L/usr/local/eda/sysc230/lib-linux64 -lm -lsystemc


# COMPILE ONE TEST USING 2 FILES
#
# to compile one file (driver_test.cpp)
# g++ -c driver.cpp      -I. -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 -I/usr/include
# g++ -c driver_test.cpp -I. -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 -I/usr/include

# to link the 2 object files for the driver test
# g++ -o driver_test -I. -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 	\
#  -I/usr/include   driver_test.o -L/usr/lib64 				\
#   -L/usr/local/eda/sysc230/lib-linux64 -lm -lsystemc
#
# to run just type ./driver_test at the shell prompt
#

