#include "Robot.h"
#include <fmt/core.h>

void Robot::RobotInit() {
    // Initialize Xbox controller
    xboxController = std::make_unique<frc::XboxController>(0);
    xboxController2 = std::make_unique<frc::XboxController>(1);

    // Initialize Victor SPX motor controllers
    m_intake = std::make_unique<WPI_VictorSPX>(8); // CAN ID 1
    m_shoot = std::make_unique<WPI_VictorSPX>(3);  // CAN ID 3
    m_load = std::make_unique<WPI_VictorSPX>(1); 
    frc::CameraServer::StartAutomaticCapture(); 
      // CAN ID 4
/*
    // Initialize drive motors
    */
    
     m_rightMotor.SetInverted(true);
    // Initialize limit switch
    limitSwitch = std::make_unique<frc::DigitalInput>(0); // Digital Input port 0
    
}

 void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  timer.Reset();
}

void Robot::AutonomousPeriodic() {
    timer.Start();
    if (timer.Get() <=2_s) {
      m_robotDrive.ArcadeDrive(-0.5,0);
    } else if (timer.Get() <= 3.5_s) {
        m_shoot->Set(1.0);
        frc::Wait(.5_s);
        m_intake->Set(-0.5); // Set m_intake to 0.5 speed after 0.5 seconds delay
        m_load->Set(1.0);   // Turn on m_load at full speed
        frc::Wait(1_s);
        m_intake->Set(0.0); // Stop m_intake if the A button is not pressed or delay not reached
        m_load->Set(0.0);   // Stop m_load
        m_shoot->Set(0.0);
    
    } else if (timer.Get() <= 3.5_s) {

    }
      else {
      m_robotDrive.ArcadeDrive(0,0);
      m_shoot->Set(0.0);
    }
    
    /*if (m_timer.Get() <= 1_s){
      m_robotDrive.ArcadeDrive(0.5,0);
    }else if(m_timer.Get() <= 5.5_s){
      m_piston.Set(1);
      m_arm.Set(-0.25);
    }else if(m_timer.Get()<=8.5_s){
      m_gripper.Set(0.5);
      m_arm.Set(0.05);
    }else if(m_timer.Get()<=8.75_s){
      m_robotDrive.ArcadeDrive(-0.525,0);
      m_gripper.Set(-0.2);
      m_arm.Set(0.05);
    }else if(m_timer.Get()<=11.75_s){
      m_arm.Set(0.2);
      m_gripper.Set(-0.25);
    }else if(m_timer.Get()<=12.4_s) {
      m_robotDrive.ArcadeDrive(-0.6,0);
      m_gripper.Set(0);
      m_arm.Set(0.05);
    }else{
      m_robotDrive.ArcadeDrive(-0.7,0);
      m_arm.Set(0.05);
    }*/
}


void Robot::TeleopPeriodic() {
    // Get bumper values
    bool rightBumper = xboxController->GetRightBumper(); // Right bumper state
    bool leftBumper = xboxController->GetLeftBumper();  // Left bumper state
    
    // Get button status
    bool aButtonPressed = xboxController->GetAButton(); // A button state
    bool yButtonPressed = xboxController->GetYButton();
    bool xButtonPressed = xboxController->GetXButton();
    
    
    // Get trigger button status of the second controller
    /*
    bool leftTrigger = xboxController->GetLeftTriggerAxis();
    bool rightTrigger = xboxController->GetRightTriggerAxis();
    */
    bool leftTrigger = xboxController2->GetLeftTriggerAxis();
    bool rightTrigger = xboxController2->GetRightTriggerAxis();
    
    // Drive control using Xbox controller joysticks
    //double driveSpeed = xboxController->GetLeftY(); // Forward/backward control
   // double turnSpeed = xboxController->GetRightX(); // Turning control

    // Arcade drive for differential drive system
    
     m_robotDrive.ArcadeDrive(speed*m_driverController2.GetLeftY(), -speed*m_driverController2.GetRightX());


    // Shoot it! Incoporated the full thing into one, to avoid
    // two different if statements.
    //if (aButtonPressed && timer.Get() >= 0.5) {
      if (aButtonPressed)  {
        m_shoot->Set(1.0);
        frc::Wait(.5_s);
        m_intake->Set(-0.5); // Set m_intake to 0.5 speed after 0.5 seconds delay
        m_load->Set(1.0);   // Turn on m_load at full speed
    } else {
        m_shoot->Set(0.0);
        m_intake->Set(0.0); // Stop m_intake if the A button is not pressed or delay not reached
        m_load->Set(0.0);   // Stop m_load
    }

    // Control m_intake with top-bumpers
    //if (!aButtonPressed) {
      if (!aButtonPressed && !yButtonPressed) {
        //if (rightBumper && !limitSwitch->Get()) {
          if (rightBumper && limitSwitch->Get()) {
          // while (limitSwitch->Get()) {
          //if (rightBumper) {
          m_intake->Set(-0.7); // Spin m_intake forward at 0.5 speed if right bumper is pressed and limit switch is not activated
          
        } else if (leftBumper) {
            m_intake->Set(0.5); // Spin m_intake backward at -0.5 speed if left bumper is pressed
        } else {
            m_intake->Set(0.0); // Stop m_intake if no bumper is pressed
        }
      
    }

  // shoot into amp



    
  // Control m_shoot with the y button
    if (yButtonPressed) {
       
        m_shoot->Set(0.15); // shooter
        m_intake->Set(-0.5); // intake
        m_load->Set(0.4); // loader
    } 

    // Retrieve note from Source on X button press
    if (xButtonPressed) {
      if (xButtonPressed && limitSwitch->Get()) { // Loop until limit switch triggered
        m_shoot->Set(-0.4);
        m_load->Set(-0.3);
      }
    }
    
 

  // change speeds
    if (leftTrigger) {
      speed=slow;
    }
    else if (rightTrigger)  {
      speed = fast;
    }
    else {
          speed = reg;
    }
  }



int main() {
    return frc::StartRobot<Robot>();
}