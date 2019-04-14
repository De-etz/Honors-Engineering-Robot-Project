#include "hammer.h"
#include <FEHUtility.h>

void Hammer::raise() {
    servo.SetDegree(raiseAngle);
}

void Hammer::lowerClaw() {
    servo.SetDegree(clawAngle);
}

void Hammer::lowerFoos() {
    servo.SetDegree(foosAngle);
}

void Hammer::lowerRPS() {
    servo.SetDegree(rpsAngle);
}

void Hammer::set(float degree) {
    servo.SetDegree(degree);
}

void Hammer::touchCalibrate() {
    servo.TouchCalibrate();
}

void Hammer::smite() {
    lowerClaw();
    Sleep(2.);
    raise();
    Sleep(2.);
}
