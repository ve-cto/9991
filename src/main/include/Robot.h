#ifndef ROBOT_H
#define ROBOT_H

#pragma once

#include <string>

#include <frc/TimedRobot.h>

#include <frc/XboxController.h>

#include <frc/drive/DifferentialDrive.h>

#include <frc/motorcontrol/PWMSparkMax.h>

#include <string>

#include <frc/TimedRobot.h>

#include <frc/XboxController.h>

#include <frc/drive/DifferentialDrive.h>

#include <ctre/Phoenix.h>

#include <frc/motorcontrol/MotorController.h>
#include <frc/motorcontrol/MotorControllerGroup.inc>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <cameraserver/CameraServer.h>
#include <frc/DigitalInput.h>
#include <frc/Timer.h>

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>
#include <memory>
#include <frc/motorcontrol/MotorControllerGroup.h>

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void TeleopPeriodic() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
    

private:
  // Create class for xBox Controllers 1 and 2
  std::unique_ptr<frc::XboxController> xboxController1;
  std::unique_ptr<frc::XboxController> xboxController2;

  std::unique_ptr<WPI_VictorSPX> m_intake; // Motor with CAN ID 8
  std::unique_ptr<WPI_VictorSPX> m_shoot;  // Motor with CAN ID 3
  std::unique_ptr<WPI_VictorSPX> m_load;   // Motor with CAN ID 1
  std::unique_ptr<WPI_VictorSPX> m_lift;
  std::unique_ptr<frc::DigitalInput> limitSwitch; // I/O 0
    
  //ctre::phoenix::motorcontrol::can::WPI_VictorSPX liftingMotor {2};
   
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontLeftMotor {7};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX rearLeftMotor {6};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontRightMotor {5};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX rearRightMotor {4};

  // Group the front and back motors of each side into m_rightMotor and m_leftMotor
  frc::MotorControllerGroup m_rightMotor {frontRightMotor, rearRightMotor};
  frc::MotorControllerGroup m_leftMotor {frontLeftMotor, rearLeftMotor};
  frc::DifferentialDrive m_robotDrive {m_leftMotor, m_rightMotor};
 
  // Initialise frc::Timer as timer
  frc::Timer timer;

  // Define speed multipliers
  double slow= 0.4;
  double fast=0.75;
  double reg=0.65;
  double speed=0.65;

  // define m_driverControllerX with the XBox Controllers
  frc::XboxController m_driverController1 {1};
  frc::XboxController m_driverController2 {0};



  // What is this even for?
  bool motor2Running = false; // Track if m_shoot is running


  //public:
  //void RobotInit() override;
  //void RobotPeriodic() override;
  /*void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;
*/

};



#endif // ROBOT_H


