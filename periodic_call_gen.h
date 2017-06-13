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

// $Revision: 7068 $ $Date:: 2017-06-13 #$ $Author: serge $

#include <set>
#include <cstdint>          // uint32_t
#include <mutex>            // std::mutex

#include "i_periodic.h"             // IPeriodic
#include "scheduler/job_id_t.h"     // job_id_t

namespace scheduler
{
class IScheduler;
}

namespace periodic_call_gen
{

class PeriodicCallGen
{
public:
    PeriodicCallGen();
    ~PeriodicCallGen();

    void init(
            scheduler::IScheduler           * scheduler );

    void shutdown();

    void register_callee( IPeriodic * p );
    void unregister_callee( IPeriodic * p );

private:

    void once_per_second();
    void once_per_minute();
    void once_per_hour();
    void once_per_day();

private:

    mutable std::mutex          mutex_;

    std::set<IPeriodic*>        callees_;

    bool                        is_done_;

    uint32_t                    sec_;
    uint32_t                    min_;
    uint32_t                    hour_;

    scheduler::job_id_t         job_id_;

    scheduler::IScheduler       * sched_;
};

} // namespace periodic_call_gen
