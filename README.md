# TODO
* Put all sensors and endstops on SmartDashboard
* Implement auto-selecting on SmartDashboard
* Make more autos
* ~~Chain stuff~~
* ~~Create logic and variables for the Lifting Mechanism~~

## Operation Notes
Connect the CAN identity of the motor controllers to motors as follows:
* 8 -> Intake Motor
* 7 -> Back-Left Drivechain Motor
* 6 -> Front-Left Drivechain Motor
* 5 -> Back-Right Drivechain Motor
* 4 -> Front-Right Drivechain Motor
* 3 -> Lifting Motor
* 2 -> Loading Motor
* 1 -> Firing Motor

Connect other devices and sensors as follows:
* Mechanical Endstop -> I/O 0
* Logitech Webcam -> Top-most port on the RoboRIO

* XBox controllers -> Any two ports on the Driver Station, the controller that is connected first controls functions of the robot, and the second controls driving.


To begin operation of the robot:
- Connect the XBox controller to the Driver Station
- Launch WPILib on the Driver Station 
  > It should open the code automatically, if not, open /28-8-24/, find a folder called "FINISHED CODE WORKING" or something like that, and open it.
- Press Control+Shift+P to open the command pallet, type "Git: Pull", and press enter. Press confirm on any following dialogue boxes.

- Turn on the robot by connecting a battery and pushing in the yellow switch on the Power Module
- When a light on the Wifi router turns orange,
  - Open the Driver Stations Wifi settings
  - Connect to the network labeled '9991' (#TEAMMAME#)
    
- Press the elipse (...) in the top-right corner of WPILib, and select "Deploy Robot Code" from the dropdown menu.
  > If the Deployment fails, either
  > - Turn the robot off and on
  > - Press the RESET button on the RoboRIO and reflash the code

- Open the FRC Driver Control Panel, and FIRST Dashboard Module
  - Select "Teleoperated" from the scroll menu
  - When ready, click "Enabled"
  > If during operation you lose control, with the Driver Station reporting "Emergency Stop", you need to reboot and reconnect to the robot.

  - To practice using automatic timings, go to the configuration window of the Driver Control Panel, and change the Practice timings to your liking. Then head back to the main menu and enable Practice.
