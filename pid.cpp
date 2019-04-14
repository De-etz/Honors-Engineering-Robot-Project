#include <pid.h>
#include <FEHUtility.h>

void PID::setOutputRange(double min, double max) {
    minOut = min;
    maxOut = max;
}

void PID::setConstants(double p, double i, double d) {
    kP = p;
    kI = i;
    kD = d;
}

double PID::output(double target, double input) {
    //Get data for calculation
    double error = target - input;
    double dt = TimeNow()-prevTime;

    //Calculate correction
    integral += error*dt;
    double derivative = 0;
    if (active) {
        derivative = (error-prevError)/(dt);
    } else {
        active = true;
    }
    double correction = error*kP+integral*kI+derivative*kD;

    //Update previous values and return correction
    prevError = error;
    prevTime += dt;
    return correction;
}

//void PID::getConstants(float constants[3]) {
//    constants[0] = kP;
//    constants[1] = kI;
//    constants[2] = kD;
//}
