/*

Default IPeriodic implementation.

Copyright (C) 2017 Sergey Kolevatov

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

// $Revision: 5449 $ $Date:: 2017-01-03 #$ $Author: serge $

#include "i_periodic.h"     // IPeriodic

#ifndef PERIODIC_CALL_GEN_DEFAULT_PERIODIC_H
#define PERIODIC_CALL_GEN_DEFAULT_PERIODIC_H

namespace periodic_call_gen
{

class DefaultPeriodic: public IPeriodic
{
public:
    virtual void once_per_second()
    {
    }

    virtual void once_per_minute()
    {
    }

    virtual void once_per_hour()
    {
    }

    virtual void once_per_day()
    {
    }
};

} // namespace periodic_call_gen

#endif // PERIODIC_CALL_GEN_DEFAULT_PERIODIC_H
