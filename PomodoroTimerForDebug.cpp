#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

class PomodoroTimerForDebug
{
public:
    void playSound()
    {
        cout << "\a";
    }

    void startSession()
    {

        totalWorkDuration = totalWorkDuration + workDuration;
        totalBreakDuration = totalBreakDuration + breakDuration;
        totalPomodoroCompleted++;
        if (!running)
        {
            bool paused = false;
            while (!paused == true)
            {
                running = true;
                while (workDuration.count() > 0)
                {

                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    workDuration = workDuration - std::chrono::seconds(1);

                    displayTimeRemaining(workDuration);

                    if (_kbhit())
                    {
                        //cout << "tha me emfaniseis pote" << endl;
                        // int _getch(_kbhit());
                        int flushall(void);
                        // sleep(1);
                        paused = true;
                        while (paused)
                        {
                            cout << _getch();
                            //cout << "unpause outer" << endl;
                            while (_kbhit())
                            {
                                //cout << "unpause inner" << endl;
                                paused = false;
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
                std::this_thread::sleep_for(std::chrono::seconds(1));
                breakDuration = breakDuration - std::chrono::seconds(1);
                displayTimeRemaining(breakDuration);
            }
            cout << endl
                 << "Break time is over. Choose your next action from the menu!" << endl;
            running = false;
            playSound();
        }
    }

    void unpause()
    {
        unsigned char c;
        do
        {
            c = getchar();
            printf("%d ", c);
        } while (c != 'p');
        // std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    void pauseSession()
    {
        if (checkPause())
        {
            std::this_thread::sleep_for(std::chrono::hours(1000));
        }
    }

    void reset()
    {
        workDuration = std::chrono::seconds(25 * 60);
        breakDuration = std::chrono::seconds(5 * 60);
        running = false;
    }

    void displayMenu()
    {
        system("cls");
        cout << "Welcome to pomodoro Timer" << endl;
        cout << "Work time in minutes: " << std::chrono::duration_cast<std::chrono::minutes>(workDuration).count() << " Break time in minutes: " << std::chrono::duration_cast<std::chrono::minutes>(breakDuration).count() << endl;
        cout << "  1. startSession " << endl;
        cout << "  2. getStatistics(pomodoros completed, all worktime) " << endl;
        cout << "  3. setwork-breaktime " << endl;
        cout << "  4. endSession " << endl;
        cout << "Select action:" << endl;
        cout << "To pause during your work time press 'p' or 'P'" << endl;
    }

    void setValues()
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

    void displayTimeRemaining(std::chrono::seconds time)
    {
        int minutes = std::chrono::duration_cast<std::chrono::minutes>(time).count();
        int seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count() % 60;
        cout << '\r' << "Time Remaining: " << minutes << " minutes and " << seconds << " seconds" << flush;
    }

    void displayStatistics()
    {
        system("clear");
        cout << "Pomodoros completed: " << totalPomodoroCompleted << endl;
        int minutesWork = std::chrono::duration_cast<std::chrono::minutes>(totalWorkDuration).count();
        int minutesBreak = std::chrono::duration_cast<std::chrono::minutes>(totalBreakDuration).count();
        cout << "total work time in minutes is: " << minutesWork + minutesBreak << endl;
    }

    // check if user pressed p or P
    bool checkPause()
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

    void waitUserInput()
    {
        cout << "Press any key..." << endl;
        while (!_kbhit())
        {
            // do nothing
        }
    }

    bool check_number(string str)
    {
        for (int i = 0; i < str.length(); i++)
            if (isdigit(str[i]) == false)
                return false;
        return true;
    }
    int validateUserInput(string input)
    {

        while (check_number(input) == false)
        {
            displayMenu();
            cout << "Invalid input. Please try again." << endl;
            cin >> input;
        }
        return stoi(input);
    }

    int getTotalWorkDuration()
    {
        return std::chrono::duration_cast<std::chrono::minutes>(totalWorkDuration).count();
        ;
    }

    int getTotalBreakDuration()
    {
        return std::chrono::duration_cast<std::chrono::minutes>(totalBreakDuration).count();
        ;
    }

private:
    std::chrono::seconds workDuration;
    std::chrono::seconds breakDuration;
    bool running;
    int totalPomodoroCompleted = 0;
    std::chrono::seconds totalWorkDuration = std::chrono::seconds(0);
    std::chrono::seconds totalBreakDuration = std::chrono::seconds(0);
};
int main()
{
    PomodoroTimerForDebug timer;
    system("clear");
    timer.reset();
    timer.displayMenu();

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