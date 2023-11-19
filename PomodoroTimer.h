// In this h file i make the constuction of my PomodoroTimer class. In the public area i have all the functions that will be used in other two cpp files. 
// and on the private area i have the variables that i will use in the functions of the class.

#include <chrono>
#include <string>
#include <thread>
#include <iostream>
using std::string;

class PomodoroTimer{
public:
    
    void playSound();
    void startSession();
    
    void reset();
    void displayMenu();
    void setValues();
    void displayTimeRemaining(std::chrono::seconds time);
    void displayStatistics();
    void waitUserInput();
    bool check_number(string input);
    
    int validateUserInput(string input);
    int getTotalWorkDuration();
    int getTotalBreakDuration();

private:
    std::chrono::seconds workDuration; // this chrono is a library that i use to make the variable workDuration and breakDuration to be in seconds
    std::chrono::seconds breakDuration;
    bool running;
    int totalPomodoroCompleted = 0;
    std::chrono::seconds totalWorkDuration = std::chrono::seconds(0); // Here i do the same thing as above but i set the value of the variable to 0
    std::chrono::seconds totalBreakDuration = std::chrono::seconds(0);

};