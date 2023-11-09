#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "kbhit.h"
#include <termios.h>
#include "PomodoroTimer.h"

using namespace std;

void PomodoroTimer::playSound()
{
    cout << "\a";
}

void PomodoroTimer::startSession()
{

    unsigned char c;

    totalWorkDuration = totalWorkDuration + workDuration;
    totalBreakDuration = totalBreakDuration + breakDuration;
    totalPomodoroCompleted++;
    if (!running)
    {
        do
        {
            running = true;
            while (workDuration.count() > 0)
            {

                std::this_thread::sleep_for(std::chrono::seconds(1));
                workDuration = workDuration - std::chrono::seconds(1);

                displayTimeRemaining(workDuration);
            }
            cout << endl;
            cout << "Work session completed. Take a break!" << endl;
            while (breakDuration.count() > 0)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                breakDuration = breakDuration - std::chrono::seconds(1);
                displayTimeRemaining(breakDuration);
            }
            cout << endl
                 << "Break time is over. Choose your next action from the menu!" << endl;
            running = false;
            playSound();
        } while (c != 'p');
        running = false;
    }
}

void PomodoroTimer::unpause()
{
    unsigned char c;
    do
    {
        c = getchar();
        printf("%d ", c);
    } while (c != 'p');
    // std::this_thread::sleep_for(std::chrono::microseconds(1));
}

void PomodoroTimer::pauseSession()
{
    if (checkPause())
    {
        std::this_thread::sleep_for(std::chrono::hours(1000));
    }
}

void PomodoroTimer::reset()
{
    workDuration = std::chrono::seconds(25 * 60);
    breakDuration = std::chrono::seconds(5 * 60);
    running = false;
}

void PomodoroTimer::displayMenu()
{
    system("clear");
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
    int localWorkDuration, localBreakDuration;
    do
    {
        cout << "Enter work time in minutes: " << endl;
        cin >> localWorkDuration;
    } while (localWorkDuration <= 0);

    do
    {
        cout << "Enter break time in minutes: " << endl;
        cin >> localBreakDuration;
    } while (localBreakDuration <= 0);
    workDuration = std::chrono::seconds(localWorkDuration * 60);
    breakDuration = std::chrono::seconds(localBreakDuration * 60);
    cout << "Work time in minutes: " << localWorkDuration << "/ Break time in minutes: " << localBreakDuration << endl;
}

void PomodoroTimer::displayTimeRemaining(std::chrono::seconds time)
{
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count();
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count() % 60;
    cout << '\r' << "Time Remaining: " << minutes << " minutes and " << seconds << " seconds" << flush;
}

void PomodoroTimer::displayStatistics()
{
    system("clear");
    cout << "Pomodoros completed: " << totalPomodoroCompleted << endl;
    int minutesWork = std::chrono::duration_cast<std::chrono::minutes>(totalWorkDuration).count();
    int minutesBreak = std::chrono::duration_cast<std::chrono::minutes>(totalBreakDuration).count();
    cout << "total work time in minutes is: " << minutesWork + minutesBreak << endl;
}

// check if user pressed p or P
bool PomodoroTimer::checkPause()
{
    if (_kbhit())
    {
        char c = getchar();
        if (c == 'p' || c == 'P')
        {
            return true;
        }
    }
    return false;
}

void PomodoroTimer::waitUserInput()
{
    cout << "Press any key..." << endl;
    while (!_kbhit())
    {
        // do nothing
    }
}

bool PomodoroTimer::check_number(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
int PomodoroTimer::validateUserInput(string input)
{

    while (check_number(input) == false)
    {
        displayMenu();
        cout << "Invalid input. Please try again." << endl;
        cin >> input;
    }
    return stoi(input);
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
