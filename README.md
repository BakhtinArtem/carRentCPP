# Car Rent Server
Client-Server application, where users can connect to a server and rent a car. Number of cars will be automatically restarted, when the server is restarted. Mutliply user are able to connect to same server and place orders simultaneously.

## Login
The server allows client to authorize using a name. The name is a unique token, using to access own profile. If a name is entered for the first time, than the new user is created, otherwise the user is logged in his profile. 

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
User and Client executable files can be generating using make command.
