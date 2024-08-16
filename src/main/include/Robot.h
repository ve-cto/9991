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
    std::unique_ptr<frc::XboxController> xboxController;
    std::unique_ptr<frc::XboxController> xboxController2;
    std::unique_ptr<WPI_VictorSPX> m_intake; // Motor with CAN ID 1
    std::unique_ptr<WPI_VictorSPX> m_shoot;  // Motor with CAN ID 3
    std::unique_ptr<WPI_VictorSPX> m_load;   // Motor with CAN ID 2
    std::unique_ptr<frc::DigitalInput> limitSwitch;
    
    //ctre::phoenix::motorcontrol::can::WPI_VictorSPX liftingMotor {2};
   
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontLeftMotor {7};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX rearLeftMotor {6};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX frontRightMotor {5};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX rearRightMotor {4};

    frc::MotorControllerGroup m_rightMotor {frontRightMotor, rearRightMotor};
    frc::MotorControllerGroup m_leftMotor {frontLeftMotor, rearLeftMotor};
     frc::DifferentialDrive m_robotDrive {m_leftMotor, m_rightMotor};
 
    
    frc::Timer timer;

    double slow= 0.55;
    double fast=0.70;
    double reg=0.65;
    double speed=0.65;

 //Controller
  frc::XboxController m_driverController1 {1};
  frc::XboxController m_driverController2 {0};


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


