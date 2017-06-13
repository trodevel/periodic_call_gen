/*

Interface IPeriodic.

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

// $Revision: 5448 $ $Date:: 2017-01-03 #$ $Author: serge $

#ifndef PERIODIC_CALL_GEN_I_PERIODIC_H
#define PERIODIC_CALL_GEN_I_PERIODIC_H

namespace periodic_call_gen
{

class IPeriodic
{
public:
    virtual ~IPeriodic() {}

    virtual void once_per_second()  = 0;
    virtual void once_per_minute()  = 0;
    virtual void once_per_hour()    = 0;
    virtual void once_per_day()     = 0;
};

} // namespace periodic_call_gen

#endif // PERIODIC_CALL_GEN_I_PERIODIC_H
