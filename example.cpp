/*

Example.

Copyright (C) 2016 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 7068 $ $Date:: 2017-06-13 #$ $Author: serge $

#include <iostream>         // cout
#include <thread>                   // std::thread
#include <functional>               // std::bind


#include "periodic_call_gen.h"      // PeriodicCallGen
#include "default_periodic.h"       // DefaultPeriodic

#include "utils/mutex_helper.h"     // THIS_THREAD_SLEEP_SEC
#include "scheduler/scheduler.h"    // Scheduler

class Periodic: public periodic_call_gen::DefaultPeriodic
{
public:

    virtual void once_per_second()
    {
        std::cout << "once_per_second: " << std::endl;
    }

    virtual void once_per_minute()
    {
        std::cout << "once_per_minute: " << std::endl;
    }

    virtual void once_per_hour()
    {
        std::cout << "once_per_hour: " << std::endl;
    }

    virtual void once_per_day()
    {
        std::cout << "once_per_day: " << std::endl;
    }
};


int main( int argc, const char* argv[] )
{
    std::cout << "Hello World" << std::endl;

    Periodic dummy;

    scheduler::Scheduler sched( scheduler::Duration( std::chrono::milliseconds( 1 ) ) );

    periodic_call_gen::PeriodicCallGen call_gen;

    call_gen.init( & sched );

    call_gen.register_callee( & dummy );

    sched.run();

    THIS_THREAD_SLEEP_SEC( 120 );

    sched.shutdown();

    return 0;
}
