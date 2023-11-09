#include <chrono>
#include <string>
#include <thread>
#include <iostream>
using std::string;

class PomodoroTimer{
public:
    void unpause();
    void playSound();
    void startSession();
    void pauseSession();
    void reset();
    void displayMenu();
    void setValues();
    void displayTimeRemaining(std::chrono::seconds time);
    void displayStatistics();
    void waitUserInput();
    bool check_number(string input);
    bool checkPause();
    int validateUserInput(string input);
    int getTotalWorkDuration();
    int getTotalBreakDuration();

private:
    std::chrono::seconds workDuration;
    std::chrono::seconds breakDuration;
    bool running;
    int totalPomodoroCompleted = 0;
    std::chrono::seconds totalWorkDuration = std::chrono::seconds(0);
    std::chrono::seconds totalBreakDuration = std::chrono::seconds(0);

};