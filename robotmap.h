#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHIO.h>

/**
 * @brief The Map struct
 *
 * Holds all the port mappings for the robot.
 */
struct Map {
    FEHMotor::FEHMotorPort leftMotor, rightMotor;
    float voltage;
    FEHIO::FEHIOPin leftEncoder, rightEncoder;
    FEHIO::FEHIOPin frontBumper, backLeftBumper, backRightBumper;
    FEHServo::FEHServoPort hammerServo;
    FEHServo::FEHServoPort coinServo;
    FEHIO::FEHIOPin cdsPort;

    Map() {
        //Drivetrain motors
        leftMotor = FEHMotor::Motor0, rightMotor = FEHMotor::Motor1;
        voltage = 9.;
        //Drivetrain encoders
        leftEncoder = FEHIO::P0_0, rightEncoder = FEHIO::P0_1;
        //Bump switches
        frontBumper = FEHIO::P3_0, backLeftBumper = FEHIO::P3_1, backRightBumper = FEHIO::P3_2;
        //Hammer servo
        hammerServo = FEHServo::Servo0;
        //Coin ramp servo
        coinServo = FEHServo::Servo6;
        //CdS cell port
        cdsPort = FEHIO::P1_0;
    }
};

#endif // ROBOTMAP_H
