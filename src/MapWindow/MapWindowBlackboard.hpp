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

#ifndef MAP_WINDOW_BLACKBOARD_H
#define MAP_WINDOW_BLACKBOARD_H

#include "Blackboard/BaseBlackboard.hpp"
#include "Blackboard/ComputerSettingsBlackboard.hpp"
#include "Blackboard/MapSettingsBlackboard.hpp"
#include "Thread/Debug.hpp"
#include "UIState.hpp"

/**
 * Blackboard used by map window: provides read-only access to local
 * copies of data required by map window
 * 
 */
class MapWindowBlackboard:
  public BaseBlackboard,
  public ComputerSettingsBlackboard,
  public MapSettingsBlackboard
{
  UIState ui_state;

protected:
  gcc_const
  const MoreData &Basic() const {
    assert(InDrawThread());

    return BaseBlackboard::Basic();
  }

  gcc_const
  const DerivedInfo &Calculated() const {
    assert(InDrawThread());

    return BaseBlackboard::Calculated();
  }

  gcc_const
  const ComputerSettings &GetComputerSettings() const {
    assert(InDrawThread());

    return ComputerSettingsBlackboard::GetComputerSettings();
  }

  gcc_const
  const MapSettings &GetMapSettings() const {
    assert(InDrawThread());

    return settings_map;
  }

  gcc_const
  const UIState &GetUIState() const {
    assert(InDrawThread());

    return ui_state;
  }

  void ReadBlackboard(const MoreData &nmea_info,
                      const DerivedInfo &derived_info);
  void ReadComputerSettings(const ComputerSettings &settings);
  void ReadMapSettings(const MapSettings &settings);

  void ReadUIState(const UIState &new_value) {
    ui_state = new_value;
  }
};

#endif