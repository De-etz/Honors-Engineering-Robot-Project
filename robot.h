#ifndef ROBOT_H
#define ROBOT_H
#include <drivetrain.h>
#include <hammer.h>
#include <robotmap.h>
#include <coinramp.h>
#define SCREEN_HEIGHT 239
#define SCREEN_WIDTH 319

/**
 * @brief The Robot class
 *
 * Used the control the entire robot as a whole.
 */
class Robot
{
private:
    Drivetrain drive;
    Hammer ham;
    AnalogInputPin cds;
    CoinRamp coin;
    double start_x, start_y, start_heading;
    double off_x, off_y;

    void convertToCharArray(char[], int);
    void convertToCharArray(char[], float);
public:
    char region;
    Robot(struct Map m) :
        cds(m.cdsPort),
        ham(m.hammerServo),
        coin(m.coinServo),
        drive(m.leftMotor, m.rightMotor, m.voltage, m.leftEncoder, m.rightEncoder,
                         m.frontBumper, m.backLeftBumper, m.backRightBumper) {
        region = 'z';
        start_x = 7,  start_y = 12.8, start_heading = 47.12;
        off_x = 0, off_y = 0;
//        ham.raise();
//        coin.resetRamp();
    }

    /* Performance Tests and Final Run */

    /**
     * @brief PT1
     *
     * Drives to the claw machine, drops the lever,
     * then drives back to the lower area.
     */
    void PT1();

    /**
     * @brief PT2
     *
     * Drives to the DDR machine, presses the red or blue button
     * depending on the button, then drives to the foosball discs.
     */
    void PT2();

    /**
     * @brief PT3
     *
     *
     */
    void PT3();

    void PT4v2();

    /**
     * @brief PT4
     *
     *
     */
    void PT4();
    void testNewClaw();

    /**
     * @brief bigBoiTime
     *
     */
    void bigBoiTime();

    /**
     * @brief testFoosball
     *
     */
    void testFoosball();

    void maxKross();

    /* Tests */

    /**
     * @brief testDrivetrain
     *
     * Runs all basic drivetrain control methods.
     */
    void testDrivetrain();

    /**
     * @brief testHammerarm
     *
     * Lowers and raises the hammerarm.
     */
    void testHammerarm();

    /**
     * @brief testRPSDrive
     *
     * Test functionality of all fine RPS drive methods.
     */
    void testRPSDrive();

    /**
     * @brief testDriveForPID
     *
     * Runs the method.
     */
    void testDriveForPID();

    /**
     * @brief calibrateTurnConstant
     *
     * Rotates the robot at .3 speed until the screen is tapped
     */
    void calibrateTurnConstant();

    /**
     * @brief straightForward
     *
     * Drives the robot straight at half speed until the screen is tapped.
     */
    void straightForward();

    /**
     * @brief readCdS
     *
     * Prints the CdS cell readings until the screen is tapped.
     */
    void readCdS();

    /* Utilities */

    /**
     * @brief calibrateRPS
     *
     * Launches the InitializeTouchMenu() program given by FEH to set up RPS.
     */
    void calibrateRPS();

    /**
     * @brief calibrateRPSOffset
     *
     * Calculates the difference in course variation and sets it.
     */
    void calibrateRPSOffset();

    /**
     * @brief confirm
     *
     * Prompts the user to continue or not.
     *
     * @param query The prompt to display to the screen.
     * @return The user's response.
     */
    bool confirm(const char query[]);

    /**
     * @brief checkRegion
     *
     * Checks if the robot is connected to a region.
     *
     * @return Whether the user decides to continue.
     */
    bool checkRegion();

    /**
     * @brief manualAlignment
     *
     * Prints the RPS values and displays whether the current
     * position adheres to the set starting position.
     */
    void manualAlignment();

    /**
     * @brief waitTilStart
     *
     * Loops until the starting light turns on.
     *
     * @return Whether to continue or not.
     */
    bool waitTilStart();

    /**
     * @brief calibrateServo
     *
     * Launches the TouchCalibrate() program given by FEH for Servo0.
     */
    void calibrateServo();

    /* Incomplete */

    void testAngleToAlign();

    void calibratePID();

    /**
     * @brief nickTest
     *
     * Tests new driving method
     *
     */
    void nickTest();

    /**
     * @brief coinDeposit
     *
     *
     */
    void coinDeposit();

    /**
     * @brief nickAndNatalieAreBetterThanDeetzAtCoding
     *
     * Ihy guys.
     */
    void nickAndNatalieAreBetterThanDeetzAtCoding();

};

#endif // ROBOT_H
