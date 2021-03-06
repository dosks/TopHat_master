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

#include "WaypointFileType.hpp"

#include "WaypointReaderFS.hpp"
#include "WaypointReaderOzi.hpp"
#include "WaypointReaderCompeGPS.hpp"

#include "OS/PathName.hpp"
#include "IO/TextFile.hpp"
#include "IO/LineReader.hpp"

template<class R>
gcc_pure
static bool
VerifyFormat(const TCHAR *path)
{
  auto reader = OpenTextFile(path);
  if (reader == nullptr)
    return false;

  bool result = R::VerifyFormat(*reader);
  delete reader;
  return result;
}

WaypointFileType
DetermineWaypointFileType(const TCHAR *path)
{
  // If WinPilot waypoint file -> save type and return true
  if (MatchesExtension(path, _T(".dat")) ||
      MatchesExtension(path, _T(".xcw")))
    return WaypointFileType::WINPILOT;

  // If SeeYou waypoint file -> save type and return true
  if (MatchesExtension(path, _T(".cup")))
    return WaypointFileType::SEEYOU;

  // If Zander waypoint file -> save type and return true
  if (MatchesExtension(path, _T(".wpz")))
    return WaypointFileType::ZANDER;

  // If FS waypoint file -> save type and return true
  if (MatchesExtension(path, _T(".wpt"))) {
    if (VerifyFormat<WaypointReaderFS>(path))
      return WaypointFileType::FS;

    if (VerifyFormat<WaypointReaderOzi>(path))
      return WaypointFileType::OZI_EXPLORER;

    if (VerifyFormat<WaypointReaderCompeGPS>(path))
      return WaypointFileType::COMPE_GPS;
  }

  return WaypointFileType::UNKNOWN;
}
