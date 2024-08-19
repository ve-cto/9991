#include "Robot.h"
#include <fmt/core.h>

void Robot::RobotInit() {
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
  intakeLimitSwitch = std::make_unique<frc::DigitalInput>(0); // Digital Input port 0
  liftingLimitSwitch = std::make_unique<frc::DigitalInput>(1); // Digital Input port 1

 
  
}

 void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  timer.Reset();
}

void Robot::AutonomousPeriodic() {
  timer.Start();
  if (timer.Get() <=2_s) {
    m_robotDrive.ArcadeDrive(-0.5,0);
  } else if (timer.Get() <= 2.5_s) {
      m_shoot->Set(1.0);
  } else if (timer.Get() <= 4.5_s) {
      m_intake->Set(-0.5); // Set m_intake to 0.5 speed after 0.5 seconds delay
      m_load->Set(1.0);   // Turn on m_load at full speed
  } else if (timer.Get() <= 5_s) {
      m_intake->Set(0.0); // Stop m_intake if the A button is not pressed or delay not reached
      m_load->Set(0.0);   // Stop m_load
      m_shoot->Set(0.0);
  } else {
    m_robotDrive.ArcadeDrive(0,0);
    m_shoot->Set(0.0);
  }
  // Last-Years automonous routine
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

void Robot::TeleopInit() {
  while (!liftingLimitSwitch) {
    m_lift->Set(0.3);
  }
  m_lift->Set(-0.3);
  frc::Wait(0.5_s);
  while (!liftingLimitSwitch) {
    m_lift->Set(0.2);
  }
}

void Robot::TeleopPeriodic() {
  // Get bumper values
  bool rightBumper = xboxController1->GetRightBumper(); // Right bumper state
  bool leftBumper = xboxController1->GetLeftBumper();  // Left bumper state
  
  // Get button status
  bool aButtonPressed = xboxController1->GetAButton(); // A button state
  bool yButtonPressed = xboxController1->GetYButton();
  bool xButtonPressed = xboxController1->GetXButton();
  bool bButtonPressed = xboxController1->GetBButton();
  
  // Get trigger status from either controller (commented out)
  /*
  bool leftTrigger = xboxController2->GetLeftTriggerAxis();
  bool rightTrigger = xboxController2->GetRightTriggerAxis();
  */
  bool leftTrigger = xboxController1->GetLeftTriggerAxis();
  bool rightTrigger = xboxController1->GetRightTriggerAxis();

  // Arcade drive for differential drive system
  m_robotDrive.ArcadeDrive(speed*m_driverController1.GetLeftY(), -speed*m_driverController1.GetRightX());
  // m_robotDrive.ArcadeDrive(speed*m_driverController2.GetLeftY(), -speed*m_driverController2.GetRightX());


  // Start lifting on bButtonPressed
  if (bButtonPressed) {
    if (bButtonPressed && !liftingLimitSwitch) {
      m_lift->Set(0.8);
    } else if (bButtonPressed && liftingLimitSwitch) {
      
    } else {
      
    }
  }
  // Shoot the note on aButtonPressed
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
  if (!aButtonPressed && !yButtonPressed) {
    if (rightBumper && intakeLimitSwitch->Get()) {
      m_intake->Set(-0.7); // Spin intake forward if the limit switch is not pressed while holding right bumper
    } else if (leftBumper) {
        m_intake->Set(0.5); // Spin m_intake backward at -0.5 speed if left bumper is pressed
    } else {
        m_intake->Set(0.0); // Stop m_intake if no bumper is pressed
    }
  }

// Drop into amp and trap with Y button
  if (yButtonPressed) {
    m_shoot->Set(0.15); // shooter
    m_intake->Set(-0.5); // intake
    m_load->Set(0.4); // loader
  } 

  // Retrieve note from Source on X button press (also useful for testing)
  if (xButtonPressed) {
    if (xButtonPressed && intakeLimitSwitch->Get()) { // Only run if limit switch is not depressed
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

} // this is the end of TeleOperatedPeriodic() {}


int main() {
    return frc::StartRobot<Robot>();
}
