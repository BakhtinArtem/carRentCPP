cmake_minimum_required (VERSION 3.8)

project ("CarRental")

add_executable (CarRentalServer "CarRentalServer.cpp" "CarRental.h"  "Sockets/WinSocket.cpp" "Sockets/ISocket.h" "Sockets/WinSocket.h" "Include/Errors.h" "DB/Database.h" "DB/Database.cpp" "Processor/Processor.h" "Processor/Processor.cpp" "Login/Login.h" "Login/Login.cpp" "DB/IDatabase.h" "Login/ILogin.h")

add_executable (CarRentalClient "CarRentalClient.cpp" "Client/Client.h" "Client/Client.cpp" "Client/IClient.h")