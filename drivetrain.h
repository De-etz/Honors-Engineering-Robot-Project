#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <FEHMotor.h>
#include <FEHIO.h>
#include <pid.h>

/**
 * @brief The Drivetrain class
 *
 * Used to control drivetrain with two motors, one to
 * control both wheels on each side of the robot.
 */
class Drivetrain
{
private:
    FEHMotor left, right;
    double maxSpeed;
    double revsPerInch;
    double turnCircle;
    DigitalEncoder leftEncoder, rightEncoder;
    DigitalInputPin front, backLeft, backRight;
    bool logging;
public:
    /**
     * @brief Drivetrain
     *
     * Constructor to build drivetrain with the two motor ports and their voltage rating.
     *
     * @param lPort Port for the left motor.
     * @param rPort Port for the right motor.
     * @param voltage Voltage rating for both motors.
     */
    Drivetrain(FEHMotor::FEHMotorPort lPort, FEHMotor::FEHMotorPort rPort, double voltage,
               FEHIO::FEHIOPin lEncPort, FEHIO::FEHIOPin rEncPort,
               FEHIO::FEHIOPin frontPort, FEHIO::FEHIOPin backLPort, FEHIO::FEHIOPin backRPort) :
        left(lPort, voltage), right(rPort, voltage),
        leftEncoder(lEncPort), rightEncoder(rEncPort),
        front(frontPort), backLeft(backLPort), backRight(backRPort) {
        maxSpeed = 100;
        revsPerInch = 40.48901752;
        turnCircle = 990;
        logging = true;
    }

    /* Basic Driving */
    /**
     * @brief steer
     *
     * Drives the robot to either bank or point
     *
     * @param speed
     * @param turn
     */
    void steer(double speed, double turn);
    void squiggle(double direction, bool forward);

    /**
     * @brief independent
     *
     * Drives the left and  right motors at different speeds
     *
     * @param lSpeed
     * @param rSpeed
     */
    void independent(double lSpeed, double rSpeed);

    /**
     * @brief check_x_plus_Nick
     *
     * drives the robot to an x coordinate in the  positive direction
     *
     * @param x_coordinate
     */
    void check_x_plus_Nick(float x_coordinate);

    /**
     * @brief forback
     *
     * Drives the robot forward or backward only.
     *
     * @param speed Percent of max speed to drive (-1.:1.)
     */
    void forback(double speed);

    /**
     * @brief rotate
     *
     * Rotates the robot counterclockwise
     *
     * @param speed Percent of max speed to rotate (-1.:1.)
     */
    void rotate(double speed);

    /**
     * @brief stop
     *
     * Stops all motors.
     */
    void stop();

    /**
     * @brief setMaxSpeed
     *
     * Sets the max speed of the drivetrain.
     *
     * @param speed Speed from 0 to 100.
     */
    void setMaxSpeed(double speed);

    /* Encoder Driving */
    /**
     * @brief driveFor
     *
     * Drives the robot for a certain distance using encoders.
     *
     * @param distance Distance to travel in inches.
     * @param speed Percent of max speed to drive (-1.:1.)
     */
    void driveFor(double distance, double speed);

    /**
     * @brief rotateFor
     *
     * Rotates the robot for a certain angle using encoders.
     *
     * @param angle The angle to rotate the robot in the counterclockwise direction.
     * @param speed Percent of max speed to rotate (-1.:1.)
     */
    void rotateFor(double angle, double speed);

    /**
     * @brief bankFor
     *
     * Banks the robot for a certain angle using encoders.
     *
     * @param angle The angle to bank the robot in the counterclockwise direction.
     * @param speed Percent of max speed to rotate (-1.:1.)
     */
    void bankFor(double angle, double speed);

    /**
     * @brief printEncoders
     *
     * Prints the current left and right encoder values to the screen
     */
    void printEncoders();

    /**
     * @brief resetEncoders
     *
     * Resets the encoders.
     */
    void resetEncoders();

    /**
     * @brief getEncoders
     *
     * Gets the raw encoder value
     *
     * @return
     */
    double getEncoders();

    /* Bump Switch Driving */

    /**
     * @brief dashAndSmash
     *
     * Drives the robot until it runs into something.
     *
     * @param speed Percent of max speed to drive (-1.:1.)
     */
    void dashAndSmash(double speed);

    /* RPS Driving */

    /**
     * @brief rotateTo
     *
     * Rotates the robot to face the given heading.
     *
     * @param heading The heading target.
     */
    void rotateTo(double heading);
    void check_heading(float heading);

    /**
     * All check_*_tight methods call their respective check_* method first.
     */
    void check_x_plus(float x_coordinate);
    void check_x_minus(float x_coordinate);
    void check_y_minus(float y_coordinate);
    void check_y_plus(float y_coordinate);
    void check_x_plus_tight(float x_coordinate);
    void check_x_minus_tight(float x_coordinate);
    void check_y_minus_tight(float y_coordinate);
    void check_y_plus_tight(float y_coordinate);

    /* PID Driving */

    /**
     * @brief driveForPID
     *
     * Drives the robot for a certain distance using encoders and PID.
     *
     * @param distance Distance to travel in inches.
     * @param pid PIDController with preloaded constants.
     */
    void driveForPID(double distance, PID pid);

    /**
     * @brief rotateForPID
     *
     * Rotates the robot for a certain angle using encoders and PID.
     *
     * @param angle The angle to rotate the robot in the counterclockwise direction.
     * @param pid PIDController with preloaded constants.
     */
    void rotateForPID(double angle, PID pid);

    /* Incomplete */

    void bankToHelper(double angle, bool cwise);
    void bankTo(double angle, double speed);
    int angleToAlign();

    /**
     * @brief disableLogging
     *
     * Disables log writing to the SD card.
     */
    void disableLogging();

    /**
     * @brief driveTo
     *
     * Drives the robot to the given coordinates. If -1 is passed
     * for (ONLY) one of the coordinates, that axis will be ignored.
     *
     * @param x The x coordinate target.
     * @param y The y coordinate target.
     */
    void driveTo(double x, double y);
};

#endif // DRIVETRAIN_H
