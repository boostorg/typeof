time /T

g++ -I C:\boost\boost_1_32_0 -I ..\..\..\.. ..\main.cpp test_compliant.cpp odr1.cpp odr2.cpp

time /T

g++ -I C:\boost\boost_1_32_0 -I ..\..\..\.. -D BOOST_TYPEOF_COMPLIANT ..\main.cpp test_compliant.cpp odr1.cpp odr2.cpp 

time /T
