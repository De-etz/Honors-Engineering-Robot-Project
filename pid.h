#ifndef PID_H
#define PID_H


/**
 * @brief The PID class
 *
 * Essentially a calculator to calculate correction given error.
 */
class PID
{
private:
    //Constants
    double kP;
    double kI;
    double kD;
    double minOut;
    double maxOut;

    //Numbers for calculations
    bool active;
    double prevError;
    double prevTime;
    double integral;
public:

    /**
     * @brief PID
     *
     * Constructor that sets the values of the PID constants.
     *
     * @param p Proportional constant.
     * @param i Integral constant.
     * @param d Derivative constant.
     * @param tol Acceptable error from target.
     */
    PID(double p, double i, double d) {
        kP = p;
        kI = i;
        kD = d;
        minOut = 0;
        maxOut = 0;

        active = false;
        prevError = 0;
        prevTime = 0;
        integral = 0;
    }

    /**
     * @brief setOutputRange
     *
     * Sets the min and max values the controller can output
     *
     * @param min Minimum value that can be outputted.
     * @param max Maximum value that can be outputted.
     */
    void setOutputRange(double min, double max);

    /**
     * @brief setConstants
     *
     * Changes the constants for the controller.
     *
     * @param p
     * @param i
     * @param d
     */
    void setConstants(double p, double i, double d);

    /**
     * @brief output
     *
     * Calculates the amount to correct for the error.
     *
     * @param target The desired number.
     * @param input The current number.
     * @return The amount of correction to use to get to the target.
     */
    double output(double target, double input);

    /**
     * @brief getConstants
     *
     * Replaces the given array with the current PID contstants.
     *
     * @param constants Array to be replaced.
     */
    void getConstants(float *constants[3]);

};

#endif // PID_H
