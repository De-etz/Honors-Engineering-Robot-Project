#include "coinramp.h"

void CoinRamp::lowerRamp() {
    servo.SetDegree(lower);
}

void CoinRamp::resetRamp() {
    servo.SetDegree(reset);
}

void CoinRamp::set(float degree) {
    servo.SetDegree(degree);
}

void CoinRamp::touchCalibrate() {
    servo.TouchCalibrate();
}
