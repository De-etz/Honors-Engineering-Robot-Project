#include <drivetrain.h>
#include <math.h>
#include <pid.h>
#include <FEHLCD.h>
#include <FEHSD.h>
#include <FEHRPS.h>

void Drivetrain::steer(double speed, double turn) {
    if (turn >= 0) { //Turning to the left
        left.SetPercent((1-turn)*speed*maxSpeed);
        right.SetPercent(speed*maxSpeed);
    } else { //Turning to the right
        left.SetPercent(speed*maxSpeed);
        right.SetPercent((1+turn)*speed*maxSpeed);
    }
}

void Drivetrain::independent(double lSpeed, double rSpeed) {
    left.SetPercent(lSpeed*maxSpeed);
    right.SetPercent(rSpeed*maxSpeed);
}

void Drivetrain::forback(double speed) {
    left.SetPercent(speed*maxSpeed);
    right.SetPercent(speed*maxSpeed);
}

void Drivetrain::rotate(double speed) {
    left.SetPercent(-speed*maxSpeed);
    right.SetPercent(speed*maxSpeed);
}

void Drivetrain::stop() {
    left.Stop();
    right.Stop();
}

int Drivetrain::angleToAlign() {
    float heading = RPS.Heading();
    float correct, err = 360;
    int angles[5] = {0, 90, 180, 270, 360};

    for (int i = 0; i < 5; i++) {
        float currErr = abs(angles[i] - heading);
        if (currErr < err) {
            correct = angles[i];
            err = currErr;
        }
    }

    return correct;
}

void Drivetrain::setMaxSpeed(double speed) {
    maxSpeed = speed;
}

void Drivetrain::driveFor(double distance, double speed) {
    double target = distance*revsPerInch;

    resetEncoders();

    while ((leftEncoder.Counts() + rightEncoder.Counts())/2. < target) {
        independent(speed, speed + 0.04);
    }
    stop();
}

void Drivetrain::dashAndSmash(double speed) {
    if (speed > 0) {
        forback(speed);
        while (front.Value());
    } else {
        while (backLeft.Value() || backRight.Value()) {
            double lSpeed = 0, rSpeed = 0;
            if (backLeft.Value()) lSpeed = speed;
            if (backRight.Value()) rSpeed = speed;
            independent(lSpeed, rSpeed);
        }
    }
    stop();
}

void Drivetrain::rotateFor(double angle, double speed) {
    double target = turnCircle * angle / 360.;
    resetEncoders();
    double startTime = TimeNow();

    while ((leftEncoder.Counts() + rightEncoder.Counts())/2. < target && TimeNow() - startTime < 3.0) {
        rotate(speed);
    }
    stop();
    if (TimeNow() - startTime >= 3.0) {
        driveFor(0.6, 0.5);
        startTime = TimeNow();
        while ((leftEncoder.Counts() + rightEncoder.Counts())/2. < target && TimeNow() - startTime < 3.0) {
            rotate(speed);
        }
    }
}

void Drivetrain::rotateTo(double heading) {
    const float speed = .3;
    const float tolerance = 1;

    float diff = RPS.Heading() - heading;
    LCD.Write(diff);
    if (diff < -tolerance) {
        //Left/right
        if (abs(diff) < 180) {
            rotateFor(abs(diff), speed);
        }
        else {
            diff = 360 + diff;
            rotateFor(diff, -speed);
        }
    } else if (diff > tolerance) {
        //Right/left
        if (abs(diff) < 180) {
            rotateFor(diff, -speed);
        }
        else {
            diff = 360 - diff;
            rotateFor(diff, speed);
        }
    }
    Sleep(0.2);
    check_heading(heading);
}

void Drivetrain::squiggle(double direction, bool forward) {
    double lSpeed, rSpeed;
    if (direction < 0) {
        lSpeed = 0.4;
        rSpeed = 0.8;
    } else {
        lSpeed = 0.8;
        rSpeed = 0.4;
    }
    if (!forward) {
        lSpeed *= -1;
        rSpeed *= -1;
    }
    independent(lSpeed, rSpeed);
    Sleep(0.5);
    independent(rSpeed, lSpeed);
    Sleep(0.5);
    stop();
}

void Drivetrain::bankToHelper(double heading, bool cwise) {
    const double speed = .3;
    const float tolerance = 1;
    const float dt = .07;

    float diff = RPS.Heading() - heading;
    if (cwise) {
        if (diff < -tolerance) {
            //Left/right
            if (abs(diff) < 180) independent(-speed, 0);
            else independent(speed, 0);
        } else if (diff > tolerance) {
            //Right/left
            if (abs(diff) < 180) independent(speed, 0);
            else independent(-speed, 0);
        }
    } else {
        if (diff < -tolerance) {
            //Left/right
            if (abs(diff) < 180) independent(0, -speed);
            else independent(0, speed);
        } else if (diff > tolerance) {
            //Right/left
            if (abs(diff) < 180) independent(0, speed);
            else independent(0, -speed);
        }
    }

    Sleep(dt);
    stop();
    Sleep(dt*2);
    if (abs(RPS.Heading() - heading) > 1) bankToHelper(heading, cwise);
}

void Drivetrain::bankTo(double heading, double speed) {
    const float tolerance = 1;
    const float dt = .07;
    bool cwise = true;

    float diff = RPS.Heading() - heading;
    if (diff < -tolerance) {
        if (abs(diff) > 180) cwise = false;
    } else if (diff > tolerance) {
        if (abs(diff) < 180) cwise = false;
    }
    Sleep(dt);
    stop();
    Sleep(dt*2);
    if (abs(RPS.Heading() - heading) > 1) bankToHelper(heading, cwise);
}

void Drivetrain::bankFor(double angle, double speed) {
    double target = turnCircle * abs(angle) / 360.;
    resetEncoders();

    while ((leftEncoder.Counts() + rightEncoder.Counts())/2. < target) {
        if (angle > 0) {
            independent(0, speed);
        } else {
            independent(speed, 0);
        }
    }
    stop();
}

/*void Drivetrain::driveStraight(double speed) {
    Sleep(2.);
    const double initHeading = RPS.Heading();
    PID pid(.005, 0, 0);
    while (!LCD.Touch(&x, &y)) {
        double correction = pid.output(RPS.Heading(), initHeading);
        LCD.WriteAt(correction, 0, 0);
    }
}*/

void Drivetrain::driveForPID(double distance, PID pid) {
    double target = distance*revsPerInch;
    int confidence = 0;

    resetEncoders();
}

void Drivetrain::rotateForPID(double angle, PID pid) {
    double target = turnCircle * angle / 360.;
    resetEncoders();

    double counts = (-leftEncoder.Counts() + rightEncoder.Counts())/2.;
    while (abs(target - counts) > 1) {
        double correction = pid.output(target, counts);
        rotate(correction);
    }
    stop();
}

void Drivetrain::printEncoders() {
    LCD.Write("LE: ");
    LCD.Write(leftEncoder.Counts());
    LCD.Write(", RE: ");
    LCD.WriteLine(rightEncoder.Counts());
}

void Drivetrain::resetEncoders() {
    leftEncoder.ResetCounts();
    rightEncoder.ResetCounts();
}

double Drivetrain::getEncoders() {
    return (leftEncoder.Counts() + rightEncoder.Counts())/2.;
}

void Drivetrain::disableLogging() {
    logging = false;
}

void Drivetrain::check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    const float lSpeed = .25;
    const float rSpeed = .3;
    const float dt = .2;

    while(RPS.X() < x_coordinate - .5 || RPS.X() > x_coordinate + .5)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            independent(-lSpeed, -rSpeed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            independent(lSpeed, rSpeed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
    }
}

void Drivetrain::check_x_plus_tight(float x_coordinate) //using RPS while robot is in the +x direction
{
    check_x_plus(x_coordinate);
    const float lSpeed = .25;
    const float rSpeed = .25;
    const float dt = .07;
    int fail = 0;

    while ((RPS.X() < x_coordinate - .05 || RPS.X() > x_coordinate + .05) && fail < 10)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            independent(-lSpeed, -rSpeed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            independent(lSpeed, rSpeed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        fail++;
    }
}

void Drivetrain::check_x_minus(float x_coordinate) //using RPS while robot is in the -x direction
{
    const float speed = .25;
    const float dt = .2;

    while(RPS.X() < x_coordinate - .5 || RPS.X() > x_coordinate + .5)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
    }
}

void Drivetrain::check_x_minus_tight(float x_coordinate) //using RPS while robot is in the -x direction
{
    check_x_minus(x_coordinate);
    const float speed = .25;
    const float dt = .07;
    int fail = 0;

    while ((RPS.X() < x_coordinate - .05 || RPS.X() > x_coordinate + .05) && fail < 10)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        fail++;
    }
}

void Drivetrain::check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    const float speed = .25;
    const float dt = .2;

    while(RPS.Y() < y_coordinate - .5 || RPS.Y() > y_coordinate + .5)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
    }
}

void Drivetrain::check_y_minus_tight(float y_coordinate) //using RPS while robot is in the -y direction
{
    check_y_minus(y_coordinate);
    const float speed = .25;
    const float dt = .07;
    int fail = 0;

    while ((RPS.Y() < y_coordinate - .05 || RPS.Y() > y_coordinate + .05) && fail < 10)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
    }
}

void Drivetrain::check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    const float speed = .25;
    const float dt = .2;

    while (RPS.Y() < y_coordinate - .5 || RPS.Y() > y_coordinate + .5)
    {
        if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
    }
}
void Drivetrain::check_y_plus_tight(float y_coordinate) //using RPS while robot is in the +y direction
{
    LCD.WriteLine("Loose");
    check_y_plus(y_coordinate);
    LCD.WriteLine("Tight");
    const float speed = .25;
    const float dt = .07;
    int fail = 0;

    while ((RPS.Y() < y_coordinate - .05 || RPS.Y() > y_coordinate + .05) && fail < 10)
    {
        if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        else if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            forback(-speed);
            Sleep(dt);
            stop();
            Sleep(dt*2);
        }
        fail++;
    }
}

void Drivetrain::check_heading(float heading) {
    const float speed = .2;
    const float tolerance = 1.5;
    const float dt = .1;

    float currHeading, diff;
    do {
        currHeading = RPS.Heading();
        diff = currHeading - heading;
    } while (currHeading < 0);
    if (diff < -tolerance) {
        //Left/right
        if (abs(diff) < 180) rotate(speed);
        else rotate(-speed);
    } else if (diff > tolerance) {
        //Right/left
        if (abs(diff) < 180) rotate(-speed);
        else rotate(speed);
    }
    LCD.Clear(WHITE);
    LCD.WriteLine(diff);
    Sleep(dt);
    stop();
    Sleep(dt*2);
    do {
        currHeading = RPS.Heading();
        diff = currHeading - heading;
    } while (currHeading < 0);
    if (abs(currHeading - heading) > tolerance) check_heading(heading);
}
