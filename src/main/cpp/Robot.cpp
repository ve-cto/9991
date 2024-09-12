#include "Robot.h"
#include <fmt/core.h>

void Robot::RobotInit() {
  // frc::SmartDashboard::PutBoolean("Note Endstop Status", limitSwitch->Get());
  // Initialize Xbox controllers
  xboxController1 = std::make_unique<frc::XboxController>(0);
  xboxController2 = std::make_unique<frc::XboxController>(1);

  // Initialize Victor SPX motor controllers
  m_intake = std::make_unique<WPI_VictorSPX>(8);
  m_shoot = std::make_unique<WPI_VictorSPX>(3);
  m_load = std::make_unique<WPI_VictorSPX>(1);
  m_lift = std::make_unique<WPI_VictorSPX>(2);
  // Invert the motors on the Right-hand side
  m_rightMotor.SetInverted(true);

  // Initialize limit switch
  limitSwitch = std::make_unique<frc::DigitalInput>(0); // Digital Input port 0
  liftLimitSwitch = std::make_unique<frc::DigitalInput>(2);

  

  frc::CameraServer::StartAutomaticCapture();

  

  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}


void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  timer.Reset();
  timer.Start();

  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);
  
  m_liftVar = 0.0;
  m_intakeVar = 0.0;
  m_shootVar = 0.0;
  m_loadVar = 0.0;
}

void Robot::AutonomousPeriodic() {
  m_lift->Set(m_liftVar);
  m_intake->Set(m_intakeVar);
  m_shoot->Set(m_shootVar);
  m_load->Set(m_loadVar);
  
if (m_autoSelected == "Centre Automonous") {
  if (timer.Get() <= 2_s) { // Spin up shooter
    m_shootVar = 1.0;
  } else if (timer.Get() <= 4_s) { // Shoot!
    m_loadVar = 1.0;
    m_intakeVar = -0.7;
  } else if (timer.Get() <= 4.5_s) { // Stop
    m_loadVar = 0.0;
    m_shootVar = 0.0;
    m_intakeVar = 0.0;
  } else if (timer.Get() <= 5_s) { // Rotate a bit
    m_robotDrive.ArcadeDrive(0.0, -0.35);
  } else if (timer.Get() <= 7.5_s) { // Start to go forward with the intake
    m_robotDrive.ArcadeDrive(0.59, 0);
    if (limitSwitch->Get()) { // Stop for limit switch
      m_intakeVar = -0.85;
    }
    m_shootVar = 1.0;
  } else if (timer.Get() <= 11_s) { // Go backwards and spin up shooter
    m_intakeVar = -0.8;
    m_robotDrive.ArcadeDrive(-0.58, 0);
    m_shootVar = 1.0;
  } else if (timer.Get() <= 12.5_s) {
    m_intakeVar = 0.55;
  } else if (timer.Get() <= 14.7_s) { // Shoot!
    m_intakeVar = -0.7;
    m_loadVar = 1.0;
  } else { // Stop
    m_robotDrive.ArcadeDrive(0.0,0.0);
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
    m_shootVar = 0.0;
  }
} else if (m_autoSelected == "Left-sided Automonous") {
    if (timer.Get() <= 1_s) {
      m_robotDrive.ArcadeDrive(-0.4, 0.4);
    if (timer.Get() <= 3_s) { // Spin up shooter
    m_shootVar = 1.0;
  } else if (timer.Get() <= 6_s) { // Shoot!
    m_loadVar = 1.0;
    m_intakeVar = -0.7;
  } else if (timer.Get() <= 6.5_s) { // Stop
    m_loadVar = 0.0;
    m_shootVar = 0.0;
    m_intakeVar = 0.0;
  } else if (timer.Get() <= 8_s) {
    m_robotDrive.ArcadeDrive(-0.5, 0.0);
  } else if (timer.Get() <= 8.7_s) {
    m_robotDrive.ArcadeDrive(0.0, 0.5);
  } else if (timer.Get() <= 11_s) {
    if (limitSwitch->Get()) { // Stop for limit switch
      m_intakeVar = -0.85;
    }
    m_shootVar = 1.0;
  } else if (timer.Get() <= 12_s) { // Go backwards and spin up shooter
    m_intakeVar = -0.8;
    m_robotDrive.ArcadeDrive(0.8, 0.0);
  } else {
    m_robotDrive.ArcadeDrive(0.0,0.0);
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
    m_shootVar = 0.0;
  }

} else if (m_autoSelected == "Shoot and Drive out") {
    if (timer.Get() <= 2_s) { // Spin up shooter
    m_shootVar = 1.0;
  } else if (timer.Get() <= 4_s) { // Shoot!
    m_loadVar = 1.0;
    m_intakeVar = -0.7;
  } else if (timer.Get() <= 4.5_s) { // Stop
    m_loadVar = 0.0;
    m_shootVar = 0.0;
    m_intakeVar = 0.0;
  } else if (timer.Get() <= 5_s) { // Rotate a bit
    m_robotDrive.ArcadeDrive(0.0, -0.35);
  } else if (timer.Get() <= 8_s) { // Go forward
    m_robotDrive.ArcadeDrive(0.59, 0);
  } else {
    m_robotDrive.ArcadeDrive(0.0,0.0);
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
    m_shootVar = 0.0;
  }


} else if (m_autoSelected == "Do Nothing") {
    m_robotDrive.ArcadeDrive(0.0,0.0);
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
    m_shootVar = 0.0;
} else {
    m_robotDrive.ArcadeDrive(0.0,0.0);
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
    m_shootVar = 0.0;
}

// Commented for testing purposes
  
}


void Robot::TeleopPeriodic() {

  m_lift->Set(m_liftVar);
  m_intake->Set(m_intakeVar);
  m_shoot->Set(m_shootVar);
  m_load->Set(m_loadVar);

  frc::SmartDashboard::PutBoolean("Note Endstop Status", limitSwitch->Get());
// DUAL CONTROLLER CONTROL
/*
  // Get bumper values
  bool rightBumper = xboxController1->GetRightBumper(); // Right bumper state
  bool leftBumper = xboxController1->GetLeftBumper();  // Left bumper state
  
  // Get button status
  bool aButtonPressed = xboxController1->GetAButton(); // A button state
  bool yButtonPressed = xboxController1->GetYButton();
  bool xButtonPressed = xboxController1->GetXButton();
  bool bButtonPressed = xboxController1->GetBButton();

  bool backButtonPressed = xboxController1->GetBackButton();
  bool startButtonPressed = xboxController1->GetStartButton();
  // Get trigger status from either controller (commented out)
  
  bool leftTrigger = xboxController2->GetLeftTriggerAxis();
  bool rightTrigger = xboxController2->GetRightTriggerAxis();

  bool secondRightTrigger = xboxController1->GetLeftTriggerAxis();
  bool secondLeftTrigger = xboxController1->GetRightTriggerAxis();
*/
// SINGLE CONTROLLER CONTROl

  // Get bumper values
  bool rightBumper = xboxController1->GetRightBumper(); // Right bumper state
  bool leftBumper = xboxController1->GetLeftBumper();  // Left bumper state
  
  // Get button status
  bool aButtonPressed = xboxController1->GetAButton(); // A button state
  bool yButtonPressed = xboxController1->GetYButton();
  bool xButtonPressed = xboxController1->GetXButton();
  bool bButtonPressed = xboxController1->GetBButton();

  bool backButtonPressed = xboxController1->GetBackButton();
  bool startButtonPressed = xboxController1->GetStartButton();
  // Get trigger status from either controller (commented out)
  
  bool leftTrigger = xboxController2->GetLeftTriggerAxis();
  bool rightTrigger = xboxController2->GetRightTriggerAxis();
  
 /*
  bool leftTrigger = xboxController2->GetLeftTriggerAxis();
  bool rightTrigger = xboxController2->GetRightTriggerAxis();
*/
  bool secondRightTrigger = xboxController1->GetLeftTriggerAxis();
  bool secondLeftTrigger = xboxController1->GetRightTriggerAxis();



  // Arcade drive for differential drive system
  // m_robotDrive.ArcadeDrive(speed*m_driverController1.GetLeftY(), -speed*m_driverController1.GetRightX());
  m_robotDrive.ArcadeDrive(speed*m_driverController2.GetLeftY(), -speed*m_driverController2.GetRightX());

  
  if (aButtonPressed)  {
      m_shootVar = 1.0;
  } else {
    m_shootVar = 0.0;
    m_loadVar = 0.0;
  }
  if (aButtonPressed) {
    if (secondLeftTrigger) {
      m_intakeVar = -0.5; // Set m_intake to 0.5 speed after 0.5 seconds delay
      m_loadVar = 1.0;   // Turn on m_load at full speed
    } else {
      m_intakeVar = 0.0;
      m_loadVar = 0.0;
    }
  } else {
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
  }

  
  
  if (startButtonPressed && liftLimitSwitch->Get()) {
    m_liftVar = 0.6;
  } else if (backButtonPressed) {
    m_liftVar = -0.6;
  } else {
    m_liftVar = 0.0;
  }




/* if (bButtonPressed) {
  if (aButtonPressed) {
      m_intakeVar = -0.5; // Set m_intake to 0.5 speed after 0.5 seconds delay
      m_loadVar = 1.0;   // Turn on m_load at full speed
  } else {
    m_intakeVar = 0.0;
    m_loadVar = 0.0;
  }
} else {
  m_shootVar = 0.0;
  m_loadVar = 0.0;
} */
/*
  // Shoot the note on aButtonPressed
  if (aButtonPressed)  {
    // if (timer.Get() <= 1_s) {
      m_shootVar = 1.0;
      
    
  } else {
    m_shootVar = 0.0;
    m_loadVar = 0.0;
    // m_intakeVar = 0.0; // Stop m_intake if the A button is not pressed or delay not reached
   //  m_loadVar = 0.0;   // Stop m_load
  }
  */
  // Control m_intake with top-bumpers
  if (!aButtonPressed && !yButtonPressed) {
    if (rightBumper && limitSwitch->Get()) {
      m_intakeVar = -0.7; // Spin intake forward if the limit switch is not pressed while holding right bumper
    } else if (leftBumper) {
        m_intakeVar = 0.7; // Spin m_intake backward at -0.5 speed if left bumper is pressed
    } else {
      m_intakeVar = 0.0; // Stop m_intake if no bumper is pressed
    }
  }

// Drop into amp and trap with Y button
  if (yButtonPressed) {
    m_shootVar = 0.15; // shooter
    m_intakeVar = -0.5; // intake
    m_loadVar = 0.48; // loader
  } 

  // Retrieve note from Source on X button press (also useful for testing)
  if (xButtonPressed) {
    if (xButtonPressed && limitSwitch->Get()) { // Loop until limit switch triggered
      m_shootVar = -0.4;
      m_loadVar = -0.3;
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

} // this is the end of TeleOperatedPeriodic() {}


int main() {
    return frc::StartRobot<Robot>();
}