#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "PomodoroTimer.h"

using namespace std;

int main()
{
    PomodoroTimer timer; // I create an object of the class PomodoroTimer by the name timer.
    system("cls"); // Those two are to start the program with a clear screen and non random numbers.
    timer.reset();
    timer.displayMenu(); // And here i display the menu.

    string input;
    while (true)
    {
        cin >> input;
        int number = timer.validateUserInput(input);

        if (number == 1)
        {
            timer.displayMenu();
            timer.startSession();
            timer.reset();
        }
        else if (number == 2)
        {
            timer.displayStatistics();
            timer.waitUserInput();
            timer.displayMenu();
        }
        else if (number == 3)
        {
            timer.setValues();
            timer.waitUserInput();
            timer.displayMenu();
        }
        else if (number == 4)
        {
            break;
        }
        
    }
    return 0;
}