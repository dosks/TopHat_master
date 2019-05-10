/*
Copyright_License {

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

#ifndef XCSOAR_FLARM_DATA_HPP
#define XCSOAR_FLARM_DATA_HPP

#include "FLARM/Error.hpp"
#include "FLARM/Version.hpp"
#include "FLARM/Status.hpp"
#include "FLARM/List.hpp"

#include <type_traits>

/**
 * A container for all data received by a FLARM.
 */
struct FlarmData {
  FlarmError error;

  FlarmVersion version;

  FlarmStatus status;

  TrafficList traffic;

  bool IsDetected() const {
    return status.available || !traffic.IsEmpty();
  }

  void Clear() {
    error.Clear();
    version.Clear();
    status.Clear();
    traffic.Clear();
  }

  void Complement(const FlarmData &add) {
    error.Complement(add.error);
    version.Complement(add.version);
    status.Complement(add.status);
    traffic.Complement(add.traffic);
  }

  void Expire(fixed clock) {
    error.Expire(clock);
    version.Expire(clock);
    status.Expire(clock);
    traffic.Expire(clock);
  }
};

static_assert(std::is_trivial<FlarmData>::value, "type is not trivial");

#endif