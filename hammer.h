#ifndef HAMMER_H
#define HAMMER_H

#include <FEHServo.h>

/**
 * @brief The Hammer class
 *
 * A servo-controller arm that rotates between
 * straight up and extended out.
 */
class Hammer
{
private:
    FEHServo servo;
    float raiseAngle, clawAngle, foosAngle,  rpsAngle;
public:
    /**
     * @brief Hammer
     *
     * Constructor to set up hammer arm.
     *
     * @param port Port for the servo.
     */
    Hammer(FEHServo::FEHServoPort port) :
        servo(port) {
        servo.SetMin(510);
        servo.SetMax(2410);
        raiseAngle = 0;
        clawAngle = 70;
        foosAngle = 80;
        rpsAngle = 85;
    }

    /**
     * @brief raise
     *
     * Brings the hammer up.
     */
    void raise();

    /**
     * @brief lower
     *
     * Brings the hammer down upon the claw.
     */
    void lowerClaw();

    /**
     * @brief lower
     *
     * Brings the hammer down upon the foosball disks.
     */
    void lowerFoos();

    /**
     * @brief lowerRPS
     *
     * Brings the hammer down upon the RPS button.
     */
    void lowerRPS();

    /**
     * @brief set
     *
     * Manually set the angle of the arm.
     *
     * @param degree Degree of the servo to set the arm to.
     */
    void set(float degree);

    /**
     * @brief smite
     *
     * Brings the hammer down upon thy lever.
     */
    void smite();

    /**
     * @brief touchCalibrate
     *
     * Runs the FEH TouchCalibrate() program.
     */
    void touchCalibrate();
};

#endif // HAMMER_H
