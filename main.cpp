#include <stdio.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHBattery.h>
#include <robot.h>
#include <robotmap.h>
#include <math.h>

Map m;
Robot botiana(m);

void launchArchive();
void launchMenu();
void printBattery();
void updateBattery();
void transition();
void current();
void testing();
void final();

void current() {
    //Put code here:
    //Sleep(6.0);
    //botiana.testNewClaw();


    if (!botiana.checkRegion()) return;
    if (!botiana.waitTilStart()) return;
    botiana.bigBoiTime();
}

void testing() {
    //Put code here:
//    botiana.testAngleToAlign();
    botiana.calibrateRPSOffset();
    //botiana.testFoosball();
    //botiana.maxKross();
}

void final() {
    //Setup
    botiana.calibrateRPS();
//    Sleep(2.);
//    LCD.WriteLine("Click to launch offset calibration.");
//    float x, y;
//    while (!LCD.Touch(&x, &y));
//    LCD.Clear(WHITE);
//    while (LCD.Touch(&x, &y));
//    LCD.WriteLine("Launching offset calibration...");
//    Sleep(1.);
//    LCD.Clear(WHITE);
    botiana.calibrateRPSOffset();
    Sleep(3.);
    LCD.WriteLine("Ready.");

    if (!botiana.waitTilStart()) return;
    LCD.Clear(WHITE);
    botiana.bigBoiTime();
}

void launchArchive() {
    const int numButtons = 6;
    FEHIcon::Icon buttons[numButtons];
    char labels[numButtons][20] = {"RPS Readings", "CdS Readings", "Foosball Slider", "Test Drivetrain", "Test Hammerarm", "Back to Main Menu"};
    FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
    printBattery();

    bool done = false;
    float x,y,xTemp,yTemp;
    while(!done) {
        while (!LCD.Touch(&x, &y)) {
            updateBattery();
        }
        if (buttons[0].Pressed(x, y, 0)) { //RPS Readings
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.manualAlignment();
            transition();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[1].Pressed(x, y, 0)) { //CdS Readings
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.readCdS();
            transition();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[2].Pressed(x, y, 0)) { //Foosball Slider
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.nickAndNatalieAreBetterThanDeetzAtCoding();
            transition();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[3].Pressed(x, y, 0)) { //Test Drivetrain
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.testDrivetrain();
            transition();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[4].Pressed(x, y, 0)) { //Test Hammerarm
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.testHammerarm();
            transition();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[numButtons-1].Pressed(x, y, 0)) { //Back to main menu
            while (LCD.Touch(&xTemp, &yTemp));
            done = true;
            LCD.Clear(WHITE);
        }
    }
}

//      |---------------------------------------|
//      | FINAL - DONT EDIT ANYTHING BELOW HERE |
//      |---------------------------------------|

void transition() {
    LCD.Clear(WHITE);
    LCD.SetFontColor(BLACK);
    Sleep(1);
    LCD.WriteLine("Click screen to return to menu.");
    float x,y,xTemp,yTemp;
    while (!LCD.Touch(&xTemp, &yTemp));
    while (LCD.Touch(&xTemp, &yTemp));
    LCD.Clear(WHITE);
}

void updateBattery() {
    int time = (int)(TimeNow()*100);
    if (time % 5 == 0) {
        LCD.SetFontColor(BLACK);
        float battery = ((int)(Battery.Voltage()*100))/100.;
        LCD.WriteAt(battery, 100, 3);
        do {
            time = (int)(TimeNow()*100);
        } while (time % 6 == 0);
    }
}

void printBattery() {
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Battery: ", 0, 3);
    LCD.SetFontColor(BLACK);
    float battery = ((int)(Battery.Voltage()*100))/100.;
    LCD.WriteAt(battery, 100, 3);
}

void launchMenu() {
    const int numButtons = 5;
    FEHIcon::Icon buttons[numButtons];
    char labels[numButtons][20] = {"Current", "Testing", "Connect to Region", "Archived", "Final Destination"};
    FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
    printBattery();

    float x,y,xTemp,yTemp;
    bool done = false;
    while(!done) {
        while (!LCD.Touch(&x, &y)) {
            updateBattery();
        }
        if (buttons[0].Pressed(x, y, 0)) { //Current program
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            current();

            transition();
            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[1].Pressed(x, y, 0)) { //Testing program
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            testing();

            transition();
            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[2].Pressed(x, y, 0)) { //Connect to region
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            botiana.calibrateRPS();

            transition();
            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[3].Pressed(x, y, 0)) { //Archived programs
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            launchArchive();

            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
        } else if (buttons[numButtons-1].Pressed(x, y, 0)) { //Final Destination
            while (LCD.Touch(&xTemp, &yTemp));
            LCD.Clear(WHITE);

            final();

            transition();
            printBattery();
            FEHIcon::DrawIconArray(buttons, numButtons, 1, 20, 20, 0, 0, labels, BLACK, RED);
            }
    }

}

int main(void) {
//    try {
//        SD.OpenLog();
//    } catch (...) {

//    }
    LCD.Clear(WHITE);
    launchMenu();
//    LCD.Clear();
//    SD.CloseLog();
    return 0;
}
