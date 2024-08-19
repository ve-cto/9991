# TODO
* Create logic and ~~variables~~ for the Lifting Mechanism
* Fine tune the relation between rotating the robot on a single point, and rotating the robot while driving
* ~~Enable logic for picking NOTE's up from the SOURCE, auto-stopping with an endstop.~~

## Github integration
The document is now integrated with github. This means that any changes (commits) that are made and published are reflected on all other versions.

## Operation Notes
Connect the CAN identity of the motor controllers to motors as follows:
* 8 -> Intake Motor
* 7 -> Back-Left Drivechain Motor
* 6 -> Front-Left Drivechain Motor
* 5 -> Back-Right Drivechain Motor
* 4 -> Front-Right Drivechain Motor
* 3 -> *Unnasigned*
* 2 -> Loading Motor
* 1 -> Firing Motor

Connect other devices and sensors as follows:
* Mechanical Endstop -> I/O 0
* Logitech Webcam -> Top-most port on the RoboRIO

* XBox controller -> Any port on the Driver Station, given that it can transfer data.


To begin operation of the robot:
- Connect the XBox controller to the Driver Station
- Launch WPILib on the Driver Station 
  > It should open the code automatically, if not, navigate to /9991/src/main/cpp and open Robot.ccp, and /9991/src/main/include/ and open Robot.h
  
- Turn on the robot by connecting a battery and pushing in the yellow switch on the Power Module
- When a light on the Wifi router turns orange,
  - Open the Driver Stations Wifi settings
  - Connect to the network labeled '9991' (#TEAMMAME#)
    
- Press the elipse (...) in the top-right corner of WPILib, and select "Deploy Robot Code" from the dropdown menu.
  > If the Build fails, go over Robot.ccp, checking for formatting and logic issues. (They should be underlined in red)
  
  > If the Deployment fails, either
  > - Turn the robot off and on
  > - Press the RESET button on the RoboRIO and reflash the code

- Open the FRC Driver Control Panel
  - Select "Teleoperated" from the scroll menu
  - When ready, click "Enabled"
  > If during operation you lose control, with the Driver Station reporting "Emergency Stop", you need to reboot and reconnect to the robot.
