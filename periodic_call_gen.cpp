/*

PeriodicCallGen.

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

// $Revision: 10610 $ $Date:: 2019-03-10 #$ $Author: serge $

#include "periodic_call_gen.h"          // self

#include <functional>                   // std::bind

#include "utils/utils_assert.h"               // ASSERT
#include "utils/mutex_helper.h"         // MUTEX_SCOPE_LOCK
#include "scheduler/i_scheduler.h"      // scheduler::IScheduler
#include "scheduler/periodic_job_aux.h" // create_and_insert_periodic_job

namespace periodic_call_gen
{

PeriodicCallGen::PeriodicCallGen():
        is_done_( false ),
        sec_( 0 ),
        min_( 0 ),
        hour_( 0 ),
        job_id_( 0 ),
        sched_( nullptr )
{
}

PeriodicCallGen::~PeriodicCallGen()
{
    MUTEX_SCOPE_LOCK( mutex_ );

    callees_.clear();

    if( is_done_ == false )
    {
        std::string error_str;

        if( sched_ )
            sched_->delete_job( & error_str, job_id_ );
    }
}

void PeriodicCallGen::init(
        scheduler::IScheduler           * scheduler )
{
    ASSERT( scheduler );

    sched_  = scheduler;

    auto now = scheduler::get_now();

    scheduler::Time     exec_time   = now + std::chrono::seconds( 1 );
    scheduler::Duration period      = std::chrono::seconds( 1 );

    scheduler::job_id_t job_id;
    std::string         error_msg;


    auto res = scheduler::create_and_insert_periodic_job(
            & job_id, & error_msg, * sched_, "once_per_second", exec_time, period,
            std::bind( &PeriodicCallGen::once_per_second, this ) );

    ASSERT( res );
}

void PeriodicCallGen::shutdown()
{
    MUTEX_SCOPE_LOCK( mutex_ );

    is_done_    = true;

    std::string error_str;

    sched_->delete_job( & error_str, job_id_ );
}

void PeriodicCallGen::register_callee( IPeriodic * p )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto b = callees_.insert( p ).second;

    if( b == false )
        throw std::runtime_error( "callee is already registered" );
}

void PeriodicCallGen::unregister_callee( IPeriodic * p )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto it = callees_.find( p );

    if( it == callees_.end() )
        throw std::runtime_error( "callee not found" );

    callees_.erase( it );
}

void PeriodicCallGen::once_per_second()
{
    MUTEX_SCOPE_LOCK( mutex_ );

    if( is_done_ )
        return;

    for( auto c : callees_ )
        c->once_per_second();

    if( ++sec_ == 60 )
    {
        once_per_minute();
        sec_ = 0;
    }
}

void PeriodicCallGen::once_per_minute()
{
    // called from the locked area

    for( auto c : callees_ )
        c->once_per_minute();

    if( ++min_ == 60 )
    {
        once_per_hour();
        min_ = 0;
    }
}

void PeriodicCallGen::once_per_hour()
{
    // called from the locked area

    for( auto c : callees_ )
        c->once_per_hour();

    if( ++hour_ == 24 )
    {
        once_per_day();
        hour_ = 0;
    }
}

void PeriodicCallGen::once_per_day()
{
    // called from the locked area

    for( auto c : callees_ )
        c->once_per_day();
}

} // namespace periodic_call_gen
