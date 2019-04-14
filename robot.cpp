#include "robot.h"
#include <drivetrain.h>
#include <hammer.h>
#include <FEHLCD.h>
#include <FEHRPS.h>
#include <math.h>

void Robot::bigBoiTime() {
    coin.resetRamp();
    ham.raise();

    LCD.WriteLine("Starting");
    drive.check_y_plus_tight(off_y+13.8); //CHANGE COORDINATES
    LCD.WriteLine("Ended");

    drive.rotateTo(0);
    drive.resetEncoders();

    //New DDR
    drive.forback(.6);
    Sleep(0.3);
    drive.stop();
    drive.check_heading(0);
    drive.forback(.6);
    Sleep(0.4);
    drive.check_heading(0);
    drive.check_x_plus_tight(off_x+21.7); //Over light
    bool red = false;
    if (cds.Value() < .35) red = true;
    if (red) {
        drive.driveFor(.15, -.3); //From .15 to .3
        drive.bankFor(-40, .4);
        drive.forback(0.2);
        Sleep(0.2);
        Sleep(5.3);
    } else {
        drive.driveFor(2, .4);
        drive.check_heading(0);
        drive.driveFor(2, .4);
        drive.check_heading(0);
        drive.check_x_plus_tight(off_x+25.95); //From .95 to .75

        drive.bankFor(-35, .4);
        drive.forback(0.2);
        Sleep(0.2);
        Sleep(5.3);
    }
    drive.driveFor(.5, -.3);

    //RPS Button
    drive.rotateTo(0);
    if (red) {
        drive.driveFor(2, 0.7);
    }
    drive.check_x_plus_tight(off_x+28.8);
    ham.lowerRPS();
    Sleep(4.);
    ham.raise();
    Sleep(0.5);
    drive.driveFor(7.2, -.7);
    drive.bankFor(-45, -.8);
    drive.driveFor(6, .9); //changed from 6.5 to 6
    Sleep(0.4);
    drive.rotateTo(0);

    drive.driveFor(3, 0.8); //changed from 3 to 2
    drive.check_x_plus_tight(off_x+29);
    drive.rotateTo(90);

    //ascend
    drive.driveFor(7, .95);
    drive.independent(0.86, 0.94);
    float initTime = TimeNow();
    while (RPS.Y() < 49 && (TimeNow() - initTime) < 2.0); //orignally 51 and 2.5
    drive.stop();
    drive.squiggle(-9, true);

    //After ramp
    drive.check_heading(95);

    //Start rewrite
    int distanceLeft = RPS.Y() - 62.05;
    double speed = -0.6;
    if (distanceLeft < 0) {
        speed *= -1;
        distanceLeft *= -1;
    }
    drive.driveFor(distanceLeft, speed);
    //End

    drive.check_y_plus_tight(off_y+61.05);
    drive.bankFor(60, 0.7);
    Sleep(0.5);
    drive.rotateTo(180);

    drive.driveFor(1.0, -0.4);
    drive.check_x_minus_tight(off_x+25.8);
    drive.check_heading(182);

    //does foosball discs
    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.2, .35);
    Sleep(1.2);
    drive.stop();

    ham.raise();
    Sleep(.2);
    drive.rotateTo(182);
    drive.driveFor(1.5, -.6);
    drive.check_x_minus(off_x+25.8);

    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.6, 0.89);
    Sleep(0.4);
    drive.independent(.3, 0.43);
    Sleep(.2);
    drive.stop();
    ham.raise();
    Sleep(.2);

    //CLAW

    drive.check_heading(195);
    drive.check_x_minus_tight(off_x+20.8);
    //SAVE THIS ISH CAUSE IT WORKS
    drive.driveFor(4, 0.3);
    drive.independent(0.2, 0.35);
    Sleep(0.75);
    drive.bankFor(30, 0.5);
    drive.stop();
    ham.lowerClaw();
    Sleep(0.6);
    ham.raise();
    Sleep(0.3);

    //new claw
//    drive.independent(0.4, 0.8);
//    Sleep(0.35);
//    drive.independent(0.6, 0.4);
//    Sleep(0.2);
//    drive.stop();
//    Sleep(0.5);
//    drive.driveFor(2, 0.7);
//    Sleep(0.5);
//    drive.bankFor(25, 0.6);
//    Sleep(0.5);
//    drive.driveFor(0.8, -0.7);
//    ham.lowerClaw();
//    Sleep(0.6);
//    ham.raise();
//    Sleep(0.3);
    drive.driveFor(4, 0.8);
    drive.independent(0.3, 0.7);
    Sleep(0.6);
    drive.stop();
    drive.rotateTo(270);

    //drive to ramp
    int gottaGo = RPS.Y() - 41.9 + off_y; //Natalie moved from 41.8 to 41.9
    drive.driveFor(gottaGo, 0.99);
    drive.check_y_minus(off_y+40.3);
    drive.forback(.2);
    Sleep(.5);

    //RAMP
    drive.bankFor(80, -0.8);
    drive.driveFor(0.5, -0.5);
    Sleep(0.2);
    drive.rotateTo(180);
    drive.check_x_minus(off_x+9.799); //decreased by 0.3
    coin.lowerRamp();
    Sleep(2.);
    coin.resetRamp();

    //get back
    drive.driveFor(.5, -.7);
    drive.independent(0.8, 0.2);
    Sleep(0.65);
    drive.stop();
    Sleep(0.2);
//    drive.check_x_minus(3);
//    drive.bankFor(40, -0.5);
    drive.rotateTo(90);
//    drive.independent(-0.6, -0.54);
//    Sleep(1.5);
//    drive.independent(-0.3, -0.5);
//    Sleep(15.0);
    drive.forback(-.7);
    Sleep(0.5);
//    drive.independent(0, -.6);
//    Sleep(3.);
    drive.stop();
    drive.independent(-0.7, -0.4);
    Sleep(0.65);
    drive.independent(-0.3, -0.8);
    Sleep(0.4);
    drive.forback(-0.5);
    Sleep(1.0);
    drive.driveFor(1, 0.99);
    drive.independent(0.2, -0.7);
    Sleep(2.0);
    drive.stop();
    drive.independent(0, -0.6);
    Sleep(2.);
    drive.stop();
    drive.rotateFor(20, -0.7);
    drive.independent(0.9, 0.4);
    Sleep(0.8);
    drive.rotateFor(70, 0.7);
    drive.forback(-0.7);
    Sleep(3.0);
    drive.stop();
    LCD.WriteLine("Ya fucked it");
    Sleep(10.);
}

void Robot::testNewClaw() {
    int distanceLeft = RPS.Y() - 62.05;
    double speed = -0.6;
    if (distanceLeft < 0) {
        speed *= -1;
        distanceLeft *= -1;
    }
    drive.driveFor(distanceLeft, speed);
    //End

    drive.check_y_plus_tight(61.05);
    drive.bankFor(60, 0.7);
    Sleep(0.5);
    drive.rotateTo(180);

    drive.driveFor(1.0, -0.4);
    drive.check_x_minus_tight(25.8);
    drive.check_heading(182);

    //does foosball discs
    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.2, .35);
    Sleep(1.2);
    drive.stop();

    ham.raise();
    Sleep(.2);
    drive.rotateTo(182);
    drive.driveFor(1.5, -.6);
    drive.check_x_minus(25.8);

    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.6, 0.89);
    Sleep(0.4);
    drive.independent(.3, 0.43);
    Sleep(.2);
    drive.stop();
    ham.raise();
    Sleep(.2);

    //CLAW

    drive.check_heading(195);
    drive.check_x_minus_tight(20.8);
    //SAVE THIS ISH CAUSE IT WORKS
//    drive.driveFor(4, 0.3);
//    drive.independent(0.2, 0.35);
//    Sleep(0.75);
//    drive.bankFor(30, 0.5);
//    drive.stop();
//    ham.lowerClaw();
//    Sleep(0.6);
//    ham.raise();
//    Sleep(0.3);

    //START NEW CLAW
    drive.independent(0.4, 0.8);
    Sleep(0.35);
    drive.independent(0.6, 0.4);
    Sleep(0.2);
    drive.stop();
    Sleep(0.5);
    drive.driveFor(2, 0.7);
    Sleep(0.5);
    drive.bankFor(25, 0.6);
    Sleep(0.5);
    drive.driveFor(0.8, -0.7);
    ham.lowerClaw();
    Sleep(0.6);
    ham.raise();
    Sleep(0.3);
    drive.driveFor(8, 0.8);
    drive.rotateTo(270);
}

bool Robot::confirm(const char query[]) {
    bool cont = false;
    LCD.SetFontColor(RED);
    LCD.Write("WARNING: ");
    LCD.SetFontColor(BLACK);
    LCD.WriteLine(query);
    LCD.WriteLine("Continue?");
    //Draw user options
    FEHIcon::Icon options[2];
    char labels[2][20] = {"Yes", "No"};
    FEHIcon::DrawIconArray(options, 1, 2, 100, 60, 20, 20, labels, BLACK, RED);
    float x, y, xTemp, yTemp;
    bool done = false;
    while (!done) {
        while (!LCD.Touch(&x, &y));
        if (options[0].Pressed(x, y, 0)) {
            cont = true;
            done = true;
        } else if (options[1].Pressed(x, y, 0)) {
            done = true;
        }
    }
    LCD.Clear(WHITE);
    Sleep(.2);
    return cont;
}

void Robot::calibrateRPS() {
    RPS.InitializeTouchMenu();
    region = RPS.CurrentRegionLetter();
    LCD.Clear(WHITE);
    LCD.SetFontColor(BLACK);
}

void Robot::maxKross() {
    //drive.check_heading_tight(195);
    LCD.WriteLine(RPS.X());
    Sleep(10);
}

bool Robot::checkRegion() {
    bool run = true;
    //Check if connected to a region:
    if (region == 'z') {
        run = confirm("Robot is not connected to any region.");
    }
    return run;
}

void Robot::convertToCharArray(char result[], int num) {

}

void Robot::convertToCharArray(char result[], float numF) {
    int num = ((int)(numF*1000))/1000;
}

void Robot::manualAlignment() {
    bool done = false;
    //Button display stuff
    FEHIcon::Icon readings[3];
    FEHIcon::Icon cont[1];
    char readingsLabel[3][20] = {"", "", ""};
    char continueLabel[1][20] = {"Continue"};
    FEHIcon::DrawIconArray(readings, 1, 3, 40, 120, 25, 25, readingsLabel, BLACK, RED);
    FEHIcon::DrawIconArray(cont, 1, 1, 120, 40, 25, 25, continueLabel, BLACK, RED);
    LCD.SetBackgroundColor(WHITE);
    float x, y;
    while (!done) {
//        readings[0].SetProperties("", 25, 40, 90, 80, BLACK, RED);
//        readings[1].SetProperties("", 115, 40, 90, 80, BLACK, RED);
//        readings[2].SetProperties("", 205, 40, 90, 80, BLACK, RED);
        bool aligned = false;
        while (!LCD.Touch(&x, &y)) {
            //Update coordinates
            float xCoord = RPS.X(), yCoord = RPS.Y(), heading = RPS.Heading();
            aligned = false;
            readings[0].ChangeLabelFloat(xCoord);
            readings[1].ChangeLabelFloat(yCoord);
            readings[2].ChangeLabelFloat(heading);
            if (abs(xCoord - start_x) < .5 && abs(yCoord - start_y) < .5
                    && abs(heading - start_heading) < .5) aligned = true;
        }
        if (cont[0].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y));
            done = true;
        }
    }
    LCD.Clear(WHITE);
}

bool Robot::waitTilStart() {
    //The other line Nick typed:
    float x, y;
    while (cds.Value() > .75);
    return true;
}

void Robot::calibratePID() {
    bool done = false;
    FEHIcon::Icon increase[3], constants[3], decrease[3];
    char incLabel[3][20] = {"+", "+", "+"}, cLabel[3][20] = {"0", "0", "0"}, decLabel[3][20] = {"-", "-", "-"};
    FEHIcon::DrawIconArray(increase, 1, 3, 40, 180, 25, 25, incLabel, BLACK, RED);
    FEHIcon::DrawIconArray(constants, 1, 3, 100, 100, 25, 25, cLabel, BLACK, RED);
    FEHIcon::DrawIconArray(decrease, 1, 3, 180, 40, 25, 25, decLabel, BLACK, RED);

    double kP = 0, kI = 0, kD = 0;
    PID pid(kP, kI, kD);
    double initHeading = RPS.Heading();
    while (!done) {
        double correction = pid.output(initHeading, RPS.Heading());
        LCD.WriteAt(correction, 0, 0);
        drive.independent(.3+correction, .3-correction);
        float x,y,xTemp,yTemp;

        while (!LCD.Touch(&x, &y));
        if (increase[0].Pressed(x, y, 1)) {
            while (LCD.Touch(&x, &y)) {
                kP += .01;
                pid.setConstants(kP, kI, kD);
                constants[0].ChangeLabelFloat(kP);
                Sleep(.1);
            }
        } else if (increase[1].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y)) {
                kI += .005;
                pid.setConstants(kP, kI, kD);
                constants[1].ChangeLabelFloat(kI);
                Sleep(.1);
            }
        } else if (increase[2].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y)) {
                kD += .005;
                pid.setConstants(kP, kI, kD);
                constants[2].ChangeLabelFloat(kD);
                Sleep(.1);
            }
        } else if (decrease[0].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y)) {
                kP -= .01;
                pid.setConstants(kP, kI, kD);
                constants[0].ChangeLabelFloat(kP);
                Sleep(.1);
            }
        } else if (decrease[1].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y)) {
                kI -= .005;
                pid.setConstants(kP, kI, kD);
                constants[1].ChangeLabelFloat(kI);
                Sleep(.1);
            }
        } else if (decrease[2].Pressed(x, y, 0)) {
            while (LCD.Touch(&x, &y)) {
                kD -= .005;
                pid.setConstants(kP, kI, kD);
                constants[2].ChangeLabelFloat(kD);
                Sleep(.1);
            }
        }
    }
    LCD.Clear(WHITE);
}

void Robot::PT1() {
    coin.resetRamp();
    ham.raise();
    LCD.WriteLine("Start");
    drive.driveFor(4, .5); //NICK changed from 10 inches to 4 inches

//    drive.rotateFor(45, -.4);
    Sleep(.5);
    drive.check_heading(0);

    drive.dashAndSmash(.5);
    LCD.WriteLine("Turn to ramp");

//    drive.driveFor(1, .3);
//    drive.bankFor(-92, -.5);
    Sleep(.5);
    drive.check_x_plus(29);
    drive.check_heading(95); //NICK changed  from 100 to 95

    LCD.WriteLine("Ascend");
    drive.independent(.6, .7); //NICK changed from 0.6 to 0.7 and 0.6 to 0.7
    Sleep(3.);
    drive.rotateFor(-20, .3);
    drive.dashAndSmash(.5);
    LCD.WriteLine("SMASH");
    drive.driveFor(8, -.3); //NICK changed from 13 to 8
    LCD.WriteLine("Go for it");
    drive.steer(.4, .35); //NICK changed from 0.65 to 0.35
    Sleep(1.);
    drive.steer(.4, .9);
    LCD.WriteLine("Line 129");
    Sleep(2.);
    LCD.WriteLine("Realigning");
    drive.dashAndSmash(-.3);
    drive.driveFor(16, .5);
    drive.bankFor(80, .5);
    drive.driveFor(3, .5);
    LCD.WriteLine("\"You want me to put down the hammer??\"");
    ham.smite();


    drive.steer(.4, .8);
    Sleep(1.8);
    drive.forback(.4);
    Sleep(4.);
    drive.stop();
}

void Robot::nickAndNatalieAreBetterThanDeetzAtCoding() {
    ham.lowerFoos();
    drive.driveFor(9, 0.25);
    ham.raise();
}

void Robot::nickTest() {
    drive.rotateFor(45, .3);
    manualAlignment();
}

void Robot::PT2() {
    coin.resetRamp();
    ham.raise();
    LCD.WriteLine("Start");
    drive.driveFor(1, .5);
    drive.rotateFor(50, -.4);
    drive.resetEncoders();
    drive.forback(.2);
    bool red = true;
    while (cds.Value() > .3 ) {
        if (drive.getEncoders()/40.48901752 > 12.5) {
            red = false;
            break;
        }
    }
    drive.stop();
    Sleep(.5);
    if (red) {
        LCD.Clear(RED);
//        drive.driveFor(.5, .2);
        drive.bankFor(-40, .5);
        Sleep(5.);
        drive.bankFor(-80, -.5);
        drive.driveFor(9.0,0.5);
        drive.bankFor(-50, 0.4);
    } else {
        LCD.Clear(BLUE);
        drive.driveFor(4, .3);
        drive.bankFor(-40, .5);

        Sleep(5.);
        drive.driveFor(5, -.5);
        drive.bankFor(-80, -.5);
        drive.driveFor(7.0, 0.5);
        drive.bankFor(-40, 0.4);

    }
    drive.dashAndSmash(.4);
    drive.driveFor(1, .3);

    drive.bankFor(-92, -.5);
    LCD.WriteLine("Ascend");
    drive.independent(.6, .8);
    Sleep(3.);
    drive.rotateFor(20, .3);
    drive.dashAndSmash(.5);
    LCD.WriteLine("SMASH");
    for (int i = 0; i < 10; i++) {
        drive.driveFor(8, -.3);
        drive.rotateFor(20, .2);
        drive.dashAndSmash(.3);
    }
}

void Robot::PT3() {
    coin.resetRamp();
    ham.raise();
    LCD.WriteLine("Start");
    drive.driveFor(7, .5); //NICK changed from 10 inches to 4 inches

//    drive.rotateFor(45, -.4);
    Sleep(.5);
    drive.rotateTo(0);

    drive.independent(0.48, 0.55);
    Sleep(1.);
    drive.dashAndSmash(.3);
    LCD.WriteLine("Turn to ramp");

//    drive.driveFor(1, .3);
//    drive.bankFor(-92, -.5);
    Sleep(.5);
    drive.check_x_plus(28);
    drive.rotateTo(90);

    LCD.WriteLine("Ascend");
    drive.independent(0.65, 0.72);
    Sleep(1.);
    drive.independent(.65, .8); //NICK changed from 0.6 to 0.7 and 0.6 to 0.7
    Sleep(1.5);
    drive.stop();
    Sleep(1.0);
    //at top of ramp
    drive.check_heading(105);
    drive.driveFor(2.0, 0.3);
    drive.check_heading(115);
    drive.driveFor(2.5, 0.3);
    drive.check_heading(90);

    //leaving top of ramp
    //drive.independent(0.45, 0.55);
    //Sleep(2.0);
    //drive.dashAndSmash(.3);
    //LCD.WriteLine("SMASH");
    //drive.driveFor(14, -.3); //NICK changed from 13 to 8
    drive.check_y_plus(52.0);
    drive.rotateTo(180);
    drive.driveFor(1.5, 0.2);
    LCD.WriteLine("turning");
    drive.rotateTo(215);

    drive.forback(.5);
    Sleep(1.25);
    drive.check_y_minus(41);
    drive.bankFor(-35, .3);
    drive.rotateTo(180);
    drive.check_x_minus(10.099); //insert y coordinate for location of coin deposit
    coin.lowerRamp();
    Sleep(2.);
    coin.resetRamp();
}

void Robot::PT4() {
    coin.resetRamp();
    ham.raise();
    LCD.WriteLine("Start");

    drive.check_y_plus(13.9); //CHANGE COORDINATES

    drive.rotateTo(0);
    drive.resetEncoders();

    //New DDR
    drive.forback(.6);
    Sleep(0.3);
    drive.check_heading(0);
    drive.forback(.6);
    Sleep(0.4);
    drive.check_heading(0);
    drive.check_x_plus(21.7); //Over light
    bool red = false;
    if (cds.Value() < .3) red = true;
    if (red) {
        drive.driveFor(.5, -.3);
        drive.bankFor(-35, .4);
        Sleep(4.);
    } else {
        drive.driveFor(2, .4);
        drive.check_heading(0);
        drive.driveFor(2, .4);
        drive.check_heading(0);
        drive.check_x_plus(26.5);

        drive.bankFor(-35, .4);
        Sleep(4.);
    }

    //RPS Button
    drive.driveFor(.5, -.3);
    drive.rotateTo(0);
    drive.check_x_plus(28.5);
    ham.lowerRPS();
    Sleep(4.);
    ham.raise();
    Sleep(1.);
//    drive.driveFor(3, -.4);
//    drive.check_heading(358);
    drive.independent(-0.6, -0.66);
    Sleep(0.4);
    drive.driveFor(2, -.5);
    drive.check_heading(0);
    drive.driveFor(7, -.4);
    drive.rotateTo(45);
    drive.driveFor(8, .5);
    drive.rotateTo(0);
    //drive.dashAndSmash(.4);
    //drive.driveFor(1.5, .3);

    drive.driveFor(7, 0.5);
    drive.check_x_plus(29);
    drive.rotateTo(90);

    LCD.WriteLine("Ascend");
    drive.independent(0.65, 0.72);
//    Sleep(1.);
//    drive.independent(.65, .8); //NICK changed from 0.6 to 0.7 and 0.6 to 0.7
    Sleep(3.);
    drive.independent(.8, .83);
    Sleep(0.4);

    //by dodecahedron
//    drive.rotateTo(110);
//    drive.driveFor(5.5, 0.6);
//    drive.rotateTo(90);
//    drive.check_y_plus(59.0);

//    //gets to start of foosball
//    drive.rotateTo(135);
//    drive.driveFor(7.8, 0.7);
//    drive.check_y_plus(63);
//    drive.rotateTo(180);
//      drive.check_x_minus(27);

    drive.rotateTo(95);
    drive.check_y_plus(61);
    drive.bankFor(60, 0.4);
    Sleep(1.0);
    drive.check_heading(180);
    drive.driveFor(1.0, -0.4);
    drive.check_x_minus(26);
    drive.check_heading(180);

    //start discs
//    int count = 0;
//    do {
//        if (count <=5 ) {
//            drive.check_heading(180);
//        } else {
//            drive.check_heading(190);
//        }
//        ham.lowerFoos();
//        Sleep(.7);
//        //Pulse
//        drive.independent(.2, .37);
//        Sleep(.8);
//        drive.stop();

//        ham.raise();
//        Sleep(.2);
//        drive.driveFor(1., -.4);
//        count++;
//    } while (RPS.WifiTimeLeft() > 0 && RPS.X() > 20);


    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.2, .33);
    Sleep(1.2);
    drive.stop();

    ham.raise();
    Sleep(.2);
    drive.rotateTo(180);
    drive.driveFor(1.5, -.6);
    drive.check_x_minus(26.7);

    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.6, 0.83);
    Sleep(0.4);
    drive.independent(.3, 0.43);
    Sleep(.2);
    drive.stop();
    ham.raise();
    Sleep(.2);

//    drive.check_x_minus(19);

    //get back
//    drive.check_heading(175);
//    drive.driveFor(4, -.8);
//    drive.rotateTo(150);
//    drive.driveFor(4, -.8);
    drive.bankFor(45, -0.4);
    drive.driveFor(10, -0.4);
    drive.check_x_minus(29);
    drive.rotateTo(90);
    drive.driveFor(10, -0.8);
    drive.check_heading(90);
    drive.driveFor(15, -0.8);
    //if (RPS.Heading() != -1) {
       // drive.check_y_plus(38);
       // drive.check_heading(85);
    //}
    drive.independent(-.4, -.5);
    Sleep(1.0);
    drive.check_y_plus(17);
    drive.bankFor(90, -0.3);
    drive.driveFor(9, -0.8);
    drive.check_x_plus(12);
    drive.rotateTo(50);
    drive.forback(-0.6);
}

void Robot::PT4v2() {
    coin.resetRamp();
    ham.raise();
    LCD.WriteLine("Start");

    drive.check_y_plus(12.9);

    drive.rotateTo(0);

    //New DDR
    drive.independent(0.6, 0.66);
    Sleep(0.3);
    drive.rotateTo(0);
    drive.independent(0.4, 0.4);
    Sleep(0.6);
//    drive.rotateTo(0);
//    drive.check_x_plus(21);
//    bool red = false;
//    if (cds.Value() < .3) red = true;
//    if (red) {
//        drive.bankFor(-35, .4);
//        Sleep(4.);
//    } else {
//        drive.driveFor(2, .6);
//        drive.check_heading(0);
//        drive.driveFor(2, .6);
//        drive.check_heading(0);
//        drive.check_x_plus(25.9);

//        drive.bankFor(-35, .4);
//        Sleep(4.);
//    }

    //RPS Button
    drive.rotateTo(0);
    drive.driveFor(2, 0.2);
    drive.check_x_plus(28.5);
    ham.lowerRPS();
    Sleep(4.);
    ham.raise();
    Sleep(1.);
    drive.independent(-0.6, -0.66);
    Sleep(0.4);
    drive.driveFor(2, -.5);
    drive.check_heading(0);
    drive.driveFor(7, -.4);
    drive.rotateTo(45);
    drive.driveFor(8, .5);
    drive.rotateTo(0);

    drive.driveFor(7, 0.5);
    drive.check_x_plus(29);
    drive.rotateTo(90);

    //GET UP RAMP
    LCD.WriteLine("Ascend");
    drive.independent(0.65, 0.72);
    Sleep(1.);
    drive.independent(.65, .8);
    Sleep(1.8);
    drive.independent(.45, .48);
    Sleep(1.0);
    drive.check_y_plus(51.0);

    //by dodecahedron
    drive.rotateTo(110);
    drive.driveFor(5.5, 0.3);
    drive.rotateTo(90);
    drive.check_y_plus(59.0);

    //gets to start of foosball
    drive.rotateTo(135);
    drive.driveFor(7.8, 0.4);
    drive.check_y_plus(64);
    drive.rotateTo(180);
    drive.independent(-0.3, -0.37);
    Sleep(.75);
    drive.check_heading(180);
    drive.check_x_minus(27);

    //FOOSBALL
//    do {
//        drive.check_heading(180);
//        ham.lowerFoos();
//        Sleep(.7);
//        //Pulse
//        drive.independent(.2, .37);
//        Sleep(.8);
//        drive.stop();

//        ham.raise();
//        Sleep(.2);
//        drive.driveFor(1., -.4);
//    } while (RPS.WifiTimeLeft() > 0 && RPS.X() > 20);

//    drive.check_x_minus(19);

    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.2, .37);
    Sleep(1.2);
    drive.stop();

    ham.raise();
    Sleep(.2);
    drive.driveFor(1.5, -.6);
    drive.check_x_minus(26.7);

    ham.lowerFoos();
    Sleep(.7);
    //Pulse
    drive.independent(.6, 0.83);
    Sleep(0.4);
    drive.independent(.3, 0.43);
    Sleep(.2);
    drive.stop();
    ham.raise();
    Sleep(.2);

    drive.check_x_minus(19);

    //get back
    drive.check_heading(175);
    drive.driveFor(4, -.8);
    drive.rotateTo(150);
    drive.driveFor(4, -.8);
    drive.check_x_minus(29);
    drive.rotateTo(90);
    drive.driveFor(10, -0.8);
    drive.check_heading(90);
    drive.driveFor(15, -0.8);
    drive.independent(-.4, -.5);
    Sleep(1.0);
    drive.check_y_plus(17);
    drive.forback(-0.2);
    Sleep(3.0);
    drive.check_y_plus(17);
    drive.bankFor(90, -0.3);
    drive.driveFor(9, -0.8);
    drive.check_x_plus(12);
    drive.rotateTo(50);
    drive.forback(-0.6);
}



void Robot::coinDeposit() {
    FEHMotor coinMotor(FEHMotor::Motor0, 4.5);
    LCD.WriteLine("About to run...");
    Sleep(2.);
    float time = TimeNow();
    float x, y;
    coinMotor.SetPercent(-50.);
    while (!LCD.Touch(&x, &y));
    coinMotor.Stop();
    LCD.WriteLine(TimeNow() - time);
    Sleep(5.);
}

void Robot::testAngleToAlign() {
    LCD.WriteLine(drive.angleToAlign());
    Sleep(5.);
}

void Robot::testFoosball() {
    drive.rotateTo(180);
    drive.check_x_minus(27);

    //start discs
    do {
        ham.lowerFoos();
        Sleep(.7);
        //Pulse
        drive.independent(.2, .4);
        Sleep(.8);
        drive.stop();

        ham.raise();
        Sleep(.2);
        drive.driveFor(1., -.4);
    } while (RPS.WifiTimeLeft() > 0 && RPS.X() > 20);
    LCD.WriteLine(RPS.WifiTimeLeft());
}

void Robot::straightForward() {
    LCD.WriteLine("Tap screen to stop.");
    drive.resetEncoders();
    drive.forback(.5);
    float x, y ,xTemp, yTemp;
    while (!LCD.Touch(&x, &y));
    drive.stop();
    while (LCD.Touch(&x, &y));
    drive.printEncoders();
    Sleep(5.);
}

void Robot::calibrateTurnConstant() {
    LCD.WriteLine("Tap screen to stop.");
    drive.resetEncoders();
    drive.rotate(.5);
    float x, y ,xTemp, yTemp;
    while (!LCD.Touch(&x, &y));
    drive.stop();
    while (LCD.Touch(&x, &y));
    drive.printEncoders();
    Sleep(5.);
}

void Robot::calibrateServo() {
    LCD.Clear(WHITE);
    LCD.WriteLine("Make sure servo is plugged in 0 and unobstructed.");
    Sleep(2.);
    LCD.WriteLine("Touch to launch calibration.");
    float x, y;
    while (!LCD.Touch(&x, &y));
    while (LCD.Touch(&x, &y));
    FEHServo servo(FEHServo::Servo0);
    servo.TouchCalibrate();
}

void Robot::readCdS() {
    float x, y;
    while (!LCD.Touch(&x, &y)) {
        int time = (int)(TimeNow()*100);
        if (time % 5 == 0) {
            LCD.SetFontColor(BLACK);
            LCD.WriteAt(cds.Value(), 0, 3);
            do {
                time = (int)(TimeNow()*100);
            } while (time % 6 == 0);
        }
    }
}

void Robot::testDriveForPID() {
    drive.driveTo(-1, 25);
}

void Robot::testRPSDrive() {
    drive.check_heading(90);
    drive.check_y_plus(20);
    drive.check_heading(0);
    drive.check_x_plus(15);
    drive.check_heading(270);
    drive.check_y_minus(15);
    drive.check_heading(180);
    drive.check_x_minus(10);
}

void Robot::testDrivetrain() {
    LCD.WriteLine("Testing forback motions...");
    Sleep(1.);
    drive.forback(.5);
    Sleep(1.);
    drive.stop();
    Sleep(1.);
    drive.forback(-.5);
    Sleep(1.);
    drive.stop();
    LCD.WriteLine("Testing steering motions...");
    Sleep(1.);
    drive.steer(.5, .5);
    Sleep(1.);
    drive.stop();
    Sleep(1.);
    drive.steer(-.5, .5);
    Sleep(1.);
    drive.stop();
    Sleep(1.);
    drive.steer(.5, -.5);
    Sleep(1.);
    drive.stop();
    Sleep(1.);
    drive.steer(-.5, -.5);
    Sleep(1.);
    drive.stop();
    LCD.WriteLine("Testing rotating motions...");
    Sleep(1.);
    drive.rotate(.4);
    Sleep(1.);
    drive.stop();
    Sleep(1.);
    drive.rotate(-.4);
    Sleep(1.);
    drive.stop();
    LCD.WriteLine("Test complete.");
    Sleep(1.);
}

void Robot::testHammerarm() {
    LCD.WriteLine("Hit the claw...");
    ham.lowerClaw();
    Sleep(1.5);
    LCD.WriteLine("Up...");
    ham.raise();
    Sleep(1.5);
    LCD.WriteLine("Hit the foos...");
    ham.lowerFoos();
    Sleep(1.5);
    LCD.WriteLine("Up...");
    ham.raise();
    Sleep(1.5);
    LCD.WriteLine("Test complete.");
    Sleep(1.);
}

void Robot::calibrateRPSOffset() {
    if (!checkRegion()) return;
    off_x = RPS.X() - 15.4;
    off_y = RPS.Y() - 6.8;
    LCD.Write("X Offset: ");
    LCD.WriteLine(off_x);
    LCD.Write("Y Offset: ");
    LCD.WriteLine(off_y);
    Sleep(3.);
    LCD.Clear(WHITE);
}
