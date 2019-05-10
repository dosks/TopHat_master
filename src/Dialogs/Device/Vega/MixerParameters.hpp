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

#ifndef XCSOAR_VEGA_MIXER_PARAMETERS_HPP
#define XCSOAR_VEGA_MIXER_PARAMETERS_HPP

#include "VegaParametersWidget.hpp"
#include "Language/Language.hpp"

static constexpr
VegaParametersWidget::StaticParameter mixer_parameters[] = {
  { DataField::Type::BOOLEAN, "MuteVarioOnPlay", N_("Mute vario on voice") },
  { DataField::Type::BOOLEAN, "MuteVarioOnCom", N_("Mute vario on radio") },
  { DataField::Type::INTEGER, "VarioRelativeMuteVol", N_("Vario muting"),
    NULL, NULL, 0, 254, 1, _T("%d/255") },
  { DataField::Type::INTEGER, "VoiceRelativeMuteVol", N_("Voice muting"),
    NULL, NULL, 0, 254, 1, _T("%d/255") },
  { DataField::Type::INTEGER, "MuteComSpkThreshold", N_("Speaker threshold"),
    NULL, NULL, 0, 254, 1, _T("%d/255") },
  { DataField::Type::INTEGER, "MuteComPhnThreshold", N_("Headset threshold"),
    NULL, NULL, 0, 254, 1, _T("%d/255") },
  { DataField::Type::INTEGER, "MinUrgentVolume", N_("Urgent min. volume"),
    NULL, NULL, 0, 254, 1, _T("%d/255") },

  /* sentinel */
  { DataField::Type::BOOLEAN }
};

#endif