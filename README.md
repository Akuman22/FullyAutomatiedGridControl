# FullyAutomatiedGridControl
Full Description - www.docdroid.net/VR5kjSH/740-proposal.docx.html
This Project was a simulation of a complete Self Driving Car Traffic Grid City
I managed to create a scale down model for 2 cars simultaneously driving in a city while continuously interacting with each other and a Central Master to update traffic jams, accidents and blockages in the map.
The system used Arduino development boards with RF chips for communication. The Master used a Computer with a Python code that would continuously update the Global map and calculate the optimal path for the vehicles.
The Path Planning algorithm used was A*. 
The Communication Protocol was round robin polling with Emergency signal capabilities
To Set up the environment -
1) Purchase 
    a) 2 https://www.amazon.com/gp/product/B01MG905R2/ref=oh_aui_detailpage_o07_s00?ie=UTF8&psc=1
    b) 3 Arduino Uno
    c) 3 https://www.amazon.com/gp/product/B00O9O868G/ref=oh_aui_detailpage_o06_s00?ie=UTF8&psc=1 (Has a lot of glitches, so you can use any RF Chip available to you)
    d) 2 https://www.amazon.com/DZS-Elec-Channel-Protection-Expansion/dp/B06XRYGM2C/ref=sr_1_1_sspa?ie=UTF8&qid=1515113279&sr=8-1-spons&keywords=relay+board&psc=1
2) Install Arduino IDE 
3) Install Python 2.7 or above
4) Connect the RF chip and customize Receiver and Transmitter as per your specifications to the Car and Center Arduino Boards
5) Connect the Relay Boards to the motors for dual direction control
6) Upload the Code for Center in 1 Arduino connected to your PC 
7) Upload the Code Main for Car 1 and Car2/Main for Car 2
8) Start the Python Code after double checking the port where the Arduino is connected
9) Press Ctrl+C and create a map. This is done because the system is a low cost system and does not have Mapping capabilities.
