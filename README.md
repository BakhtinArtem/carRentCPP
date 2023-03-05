# Car Rent Server
Client-Server application, where users can connect to a server and rent a car. Number of cars will be automatically restarted, when the server is restarted. Mutliply user are able to connect to same server and place orders simultaneously.

## Login
The server allows client to authorize using a name and password. Not registred users can create new name-password pair. After the user logged in the system a session token is created. Session token is used for simplifing interaction between client and server.

## Database
All inforamtion about user, cars and orders is saved to txt file in DB/Files directory. Information is available after server restarting. 

## Features
Client is able to:

- Rent a car(s) from given list
- Finish/Submit/Cancel order(s)

## User profile
Profile consist of things such as:

- Current orders
- History of orders
- Budget Remaining
- Logout option

## Start
User and Client executable files can be generating using make command. CarRentalClient.exe can be used for starting new instance of client and CarRentalServer.exe for instantiating new server. Server can hold mutliply clients, but the server can be created only once. 
