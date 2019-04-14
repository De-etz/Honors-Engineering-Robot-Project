#ifndef COINRAMP_H
#define COINRAMP_H
#include <FEHServo.h>

/**
 * @brief The CoinRamp class
 *
 * Used to control coinramp with a Futaba servo.
 */
class CoinRamp
{
private:
    FEHServo servo;
    float lower, reset;
public:
    CoinRamp(FEHServo::FEHServoPort servoPort) :
        servo(servoPort) {
        servo.SetMin(1000);
        servo.SetMax(2400);
        lower = 0;
        reset = 180;
    }

    /**
     * @brief lower
     *
     * Lowers the coinramp.
     */
    void lowerRamp();

    /**
     * @brief reset
     *
     * Brings servo back to its start position.
     */
    void resetRamp();

    /**
     * @brief set
     *
     * Manually set the angle of the servo.
     *
     * @param degree Degree of the servo to set the arm to.
     */
    void set(float degree);

    /**
     * @brief touchCalibrate
     *
     * Runs the FEH TouchCalibrate() program.
     */
    void touchCalibrate();
};

#endif // COINRAMP_H
