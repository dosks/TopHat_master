/* Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
 */

#include "Waypoint.hpp"
#include "Geo/Flat/FlatProjection.hpp"

Waypoint::Waypoint(const GeoPoint &_location)
  :location(_location),
   runway(Runway::Null()), radio_frequency(RadioFrequency::Null()),
   type(Type::NORMAL), flags(Flags::Defaults()),
   origin(WaypointOrigin::NONE)
{
}

bool
Waypoint::IsCloseTo(const GeoPoint &_location, const fixed range) const
{
  return location.Distance(_location) <= range;
}

void
Waypoint::Project(const FlatProjection &projection)
{
  flat_location = projection.ProjectInteger(location);

#ifndef NDEBUG
  flat_location_initialised = true;
#endif
}