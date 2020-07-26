# A-complete-management-of-a-flight-reservation-system-using-multi-thread-concept-with-proper-
A flight ticket booking system based on client - server communication
# Operating-Systems-Project
A flight ticket booking system based on client - server communication

This project focuses on the complete management of a flight reservation/booking system. Customers can make reservations/modifications/cancellations online through the main server. The server is able to handle many customers simultaneously at any time.

Customers are assumed to be the clients in the system, and they can make a booking by contacting the server.

This project involves working with threads, synchronization, and message passing in a client-server environment.

Machine Configuration information:
----------------------------------
OS: Unix
Compiler: CSX GCC compiler
Processor: Intel® Core™ i5-8250U CPU @ 1.60GHz (8 CPUs), ~1.8GHz
RAM: 8192MB
The architecture of the machine: x86_64
Number of CPUs: 24
Number of sockets: 2 
Byte ordering: Little Endian
Physical processors: 12
Logical processors: 24
Cache memory: It has 4 cache memory (32k,32k,256k,15360k)
Physical address size: 46 bits
Logical address size: 48 bits
Number of cores: 6

Steps to run the program:
-------------------------
This project has been done using C language. You may run this program in CSX machine. 

To run this code you have to press a key, you can press any key. Then you will be able to see a menu of 5 options come up in the screen.
Options:
1. Make Reservation 
2. Inquiry about the ticket
3. Modify the reservation
4. Cancel the reservation
5. Exit

Make Reservation:
----------------
- To make a reservation you have to press 1. 
- Then you have to enter the number of tickets you want to book.
- Then if you want to choose seats, press 1 otherwise press 2.
- If you go for choosing the seat yourself then you have to enter the seat number.
- Finally, you have to give the information of individual passengers with at least one person's contact details.
            
Inquiry about the ticket: 
-------------------------
- At first you have to press 2 to enter into this option.
- Then you have to enter the ticket number.
- If the ticket number is valid then the system will show all the information regarding the passengers.
            
Modify the reservation: 
-------------------------
- To modify a booked ticket you have to choose option number 3 from the menu.
- Then you have to put the ticket number. 
- If the ticket number is valid then the system will show all the information related to that ticket.
- To change the name of 1st passenger press:1 
- To change the date of birth press:2
- To change the gender press:3
- To change the government ID number press:4
- To change phone number press:5 
- To change mail address press:6
- If you don't want to change any information for this current person then press:7   
            
You will be able to see these options for the rest of the passengers except the phone number and the mail address. This is because in the reservation section
the program is just taking contact information of one passenger.

Cancel the reservation: 
-----------------------
- To cancel the reserved ticket you have to choose option 4 from the menu.
- Then you have to put the booked ticket number. Then the program will remove that ticket. 

Exit:
-----
- To exit choose option 5 form the menu.
