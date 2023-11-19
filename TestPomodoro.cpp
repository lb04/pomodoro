#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cstdint>
#include "PomodoroTimer.h"

TEST_CASE( "Check Pomodoro start session", "[pomodoro]" ) {
    PomodoroTimer timer;
    timer.reset();
    timer.startSession();
    REQUIRE( timer.getTotalWorkDuration() == 1 );
    REQUIRE( timer.getTotalBreakDuration() == 1 );
    
}