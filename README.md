SMART CAMPUS ENERGY & RESOURCE MONITOR - C++ DEMO

File: Smart_Campus_Energy_Resource_Demo.cpp

This is a console demonstration using simulated readings for campus buildings.
It displays electricity use, water use, temperature, occupancy, threshold
alerts, and a simple suggested action. It does not connect to physical sensors.

Compile with g++:
g++ -std=c++11 -Wall -Wextra -pedantic Smart_Campus_Energy_Resource_Demo.cpp -o campus_demo

Run on macOS or Linux:
./campus_demo

Run on Windows:
campus_demo.exe

Menu:
1 - View campus dashboard and alerts
2 - View details for one building
0 - Exit

To demonstrate different alerts, edit the example readings in the
CampusMonitor constructor, then compile and run again.
