# Phoenix-Embedded-System-Tester
This project consists of a series of GUIs that allow interaction with BK
Precision products such as the 2831E DMM, 9201 power supply, 9205 power supply,
as well as a dac, and a series of relays. 

The purpose of these GUI's is to allow easy automated testing of each piece
of the equipment.

------------------------------------------------------------------------------------

# Equipment
The equipment folder contains the following files:
-bk.cpp / bk.h
-bk2831e.cpp / bk2831e.h
-bk9200.cp / bk9200.h
-GSerial.cpp / GSerial.h
-SerialDevice.cpp / SerialDevice.h
-serialrxthread.cpp serialrxthread.h
-types.h

BK.cpp is the parent class to both bk2831e and bk9200.
The bk files handle construction, methods, and data for BK Precision equipment.

GSerial and the following handle the setup of individual serial devices and
communication with the equipment.

types.h holds important data constants for equipment and serial communication.
This data includes default ttyUSB serial ports, BK baud rate, and termination chars.

------------------------------------------------------------------------------------

# Pi2c-master
the pi2c-master folder contains the following files:
-mcp2317.cpp
-pi2x.cpp

These files handle construction, methods, and data for DAC and relay equipment.

------------------------------------------------------------------------------------

# Project Files
The main project files consist of the following :
-can.cpp / can.h
-capitalequipment.cpp / capitalequipment.h
-dac.cpp / dac.h
-dactest.cpp / dactest.h
-lib.c / lib.h
-main.cpp / main.h
-mainwindow.cpp / mainwindow.h
-popup.cpp / popup.h
-powersupply2.cpp / powersupply2.h
-probe.cpp / probe.h
-relay.cpp / relay.h
-relaydriver.cpp / relaydriver.h
-testmenu.cpp / testmenu.h
-vars.cpp / vars.h

capitalequipment handles the creation of all project equipment / objects and setup of ports.
probe handles finding available serial ports and works directly with capitalequipment

mainwindow handles the UI for the DMM
powersupply2 handles the UI for both power supplies
relay and relaydriver handle the UI for the relays
testmenu handles the UI for the hub to switch between UIs
dac and dactest handle the UI for the DAC

------------------------------------------------------------------------------------

# Forms (UIs)
The Forms folder contains the following files:
dactest.ui
mainwindow.ui
popup.ui
powersupply2.ui
relaydriver.ui
testmenu.ui

These .ui files are auto-created by Qt and consist the front end info for each UI

------------------------------------------------------------------------------------

# Project Summary
The purpose of this project is to have multiple user interfaces that interact with each
piece of equipment within the Phoenix motor controller system in order to  automate testing
of each part of the system wihtin the product.







