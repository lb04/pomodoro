#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include "PomodoroTimer.h"

using namespace std;

void PomodoroTimer::playSound()
{
    cout << "\a"; // \a is a special character that makes a sound only if runned in a terminal.
}

void PomodoroTimer::startSession()
{

    totalWorkDuration = totalWorkDuration + workDuration; // Here i add the workDuration to the totalWorkDuration because totalWorkduration was set to 0, so i give it the value of workDuration
    totalBreakDuration = totalBreakDuration + breakDuration; // Here i add the breakDuration to the totalBreakDuration because totalBreakduration was set to 0, so i give it the value of breakDuration
    totalPomodoroCompleted++; // This is for the statistics. Every time i start a session i add 1 to the totalPomodoroCompleted
    // Those three above are all used for the statistics.
    if (!running) // This is a check to see if a session has ended.
    {
        
            running = true; // Here i set it as true because i start a session.
            
            while (workDuration.count() > 0)
            {

                std::this_thread::sleep_for(std::chrono::seconds(1)); // This line just makes the program wait for 1 second before going into action.
                workDuration = workDuration - std::chrono::seconds(1); // Here i subtract 1 second from the workDuration in very while

                displayTimeRemaining(workDuration); // and here i diplay the time remaining in every while loop.

                    if (_kbhit()) // kbhit() is a function that checks if a key is pressed. Both _kbhit() and getch() are functions from conio.h library
                    {
                        // p in ascii is 112
                        // P in ascii is 80
                        // an paththike to p kanw to pause
                        if(_getch() == 112 || _getch() == 80){ // with _getch() i get the ascii value of the key that i press
                            bool paused = true;
                            while(paused == true){
                                displayTimeRemaining(workDuration); // Here i make the pause when worktime is on. I display the same time in a while loop
                                if(getch() == 112 || getch() == 80){ // and it leaves the while only when i press p or P again. To make that happen i
                                    paused = false;                  // used a bool variable that i set as false when i press p or P again.
                                    break;
                                    
                                }
                            }
                            
                            
                        }
                        
                        
                    }
            
            }
            cout << endl;
            cout << "Work session completed. Take a break!" << endl;
            while (breakDuration.count() > 0)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1)); // This line just makes the program wait for 1 second before going into action.
                breakDuration = breakDuration - std::chrono::seconds(1);
                displayTimeRemaining(breakDuration);
            }
            cout << endl
                 << "Break time is over. Choose your next action from the menu!" << endl;
            running = false;
            playSound(); // At the end of the break time i make a sound.
        
        running = false; // And here is were the session ended so i set it as false.
    }
}



void PomodoroTimer::reset()
{
    workDuration = std::chrono::seconds(25 * 60); // Here i set the workDuration and breakDuration to the default values.
    breakDuration = std::chrono::seconds(5 * 60); 
    running = false;
}

void PomodoroTimer::displayMenu()
{
    system("cls"); // I use system("cls") to clear the screen every time befor i display the menu.
    cout << "Welcome to pomodoro Timer" << endl;
    cout << "Work time in minutes: " << std::chrono::duration_cast<std::chrono::minutes>(workDuration).count() << " Break time in minutes: " << std::chrono::duration_cast<std::chrono::minutes>(breakDuration).count() << endl;
    cout << "  1. startSession " << endl;
    cout << "  2. getStatistics(pomodoros completed, all worktime) " << endl;
    cout << "  3. setwork-breaktime " << endl;
    cout << "  4. endSession " << endl;
    cout << "Select action:" << endl;
    cout << "To pause during your work time press 'p' or 'P'" << endl;
}

void PomodoroTimer::setValues()
{
    int localWorkDuration, localBreakDuration; // Here i make two local variables that i will use to set the workDuration and breakDuration
    do
    {
        cout << "Enter work time in minutes: " << endl;
        cin >> localWorkDuration;
    } while (localWorkDuration <= 0);
// The two do whiles i use is to make sure that the user will enter a number bigger than 0.
    do
    {
        cout << "Enter break time in minutes: " << endl;
        cin >> localBreakDuration;
    } while (localBreakDuration <= 0);
    workDuration = std::chrono::seconds(localWorkDuration * 60); // Here i set the workDuration and breakDuration to seconds beacause i will have to use them
    breakDuration = std::chrono::seconds(localBreakDuration * 60); // in seconds in the startSession function. But the local variables i use i set them  in minutes to display them.
    cout << "Work time in minutes: " << localWorkDuration << "/ Break time in minutes: " << localBreakDuration << endl;
}

void PomodoroTimer::displayTimeRemaining(std::chrono::seconds time)
{
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count(); // Here i use the chrono library to convert the seconds to minutes. 
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count() % 60; // And here i use the modulo to get the seconds that are left.
    cout << '\r' << "Time Remaining: " << minutes << " minutes and " << seconds << " seconds" << flush; // And here i display the time remaining by refreshing the line with the '\r' and flush at the end.
}

void PomodoroTimer::displayStatistics()
{
    system("cls");
    cout << "Pomodoros completed: " << totalPomodoroCompleted << endl; // Here i use a private variable of the class because im in a public function of it.
    int minutesWork = std::chrono::duration_cast<std::chrono::minutes>(totalWorkDuration).count();
    int minutesBreak = std::chrono::duration_cast<std::chrono::minutes>(totalBreakDuration).count();
    cout << "total work time in minutes is: " << minutesWork + minutesBreak << endl; // For the total work time i add the total work time and the total break time.
}



void PomodoroTimer::waitUserInput()
{
    cout << "Press any key..." << endl;
    while (!_kbhit())
    {
        // do nothing
    }
}

bool PomodoroTimer::check_number(string str) // The check number function is used to check if the input is a number. It gets a string as an input
{                                            // and checks every character of it. If it finds a character that is not a number it returns false.
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
int PomodoroTimer::validateUserInput(string input) // In this function i use the check_number function to check if the input is a number. While it 
{                                                  // is not a number i display the menu again and ask for a new input.

    while (check_number(input) == false)
    {
        displayMenu();
        cout << "Invalid input. Please try again." << endl;
        cin >> input;
    }
    return stoi(input); // Here i use the stoi function to convert the string input to an integer.
}

int PomodoroTimer::getTotalWorkDuration()
{
    return std::chrono::duration_cast<std::chrono::minutes>(totalWorkDuration).count();
    ;
}

int PomodoroTimer::getTotalBreakDuration()
{
    return std::chrono::duration_cast<std::chrono::minutes>(totalBreakDuration).count();
    ;
}
