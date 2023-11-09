#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING 
#include <catch2/catch.hpp>
#include <cstdint>
#include "PomodoroTimer.h"

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    PomodoroTimer timer;
    //timer.reset();
    //timer.startSession();
    REQUIRE( timer.getTotalWorkDuration() == 1 );
    REQUIRE( timer.getTotalBreakDuration() == 1 );
    REQUIRE(timer.check_number("1") == true);
    REQUIRE(timer.validateUserInput("1") == 1);
    
}