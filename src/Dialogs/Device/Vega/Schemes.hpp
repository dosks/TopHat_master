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

#ifndef XCSOAR_VEGA_SCHEMES_HPP
#define XCSOAR_VEGA_SCHEMES_HPP

#include "Types.hpp"

struct VEGA_SCHEME
{
  int ToneClimbComparisonType;
  int ToneLiftComparisonType;

  struct Audio {
    int beep_type, pitch_scheme, pitch_scale, period_scheme, period_scale;
  } audio[6];
};

static constexpr VEGA_SCHEME VegaSchemes[4]= {
  // Vega
  {X_NONE, Y_RELATIVE_MACCREADY_HALF,
   {
     { BEEPTYPE_LONG, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_INTERMITTENT, SCALE_LINEAR, },
     { BEEPTYPE_SHORTDOUBLE, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_INTERMITTENT, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_RELATIVE, SCALE_LINEAR, PERIOD_VARIO_RELATIVE, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_MEDIUM, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_CONTINUOUS, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_HI, SCALE_LINEAR},
   },
  },

  // Borgelt
  {X_AVERAGE, Y_RELATIVE_MACCREADY,
   {
     { BEEPTYPE_LONG, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_INTERMITTENT, SCALE_LINEAR, },
     { BEEPTYPE_SHORTDOUBLE, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_INTERMITTENT, SCALE_LINEAR, },
     { BEEPTYPE_MEDIUM, PITCH_VARIO_RELATIVE, SCALE_LINEAR, PERIOD_VARIO_RELATIVE, SCALE_LINEAR, },
     { BEEPTYPE_MEDIUM, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_LONG, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_CONTINUOUS, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_HI, SCALE_LINEAR},
   },
  },

  // Cambridge
  {X_NONE, Y_RELATIVE_ZERO, // should be net>zero
   {
     { BEEPTYPE_CONTINUOUS, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_HI, SCALE_LINEAR, },
     { BEEPTYPE_SHORTDOUBLE, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_LO, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_RELATIVE, SCALE_LINEAR, PERIOD_VARIO_RELATIVE, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_VARIO_GROSS, SCALE_LINEAR, },
     { BEEPTYPE_CONTINUOUS, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_HI, SCALE_LINEAR},
   },
  },

  // Zander
  {X_NONE, Y_RELATIVE_ZERO, // should be net>zero
   {
     { BEEPTYPE_CONTINUOUS, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_HI, SCALE_LINEAR, },
     { BEEPTYPE_SHORTDOUBLE, PITCH_SPEED_ERROR, SCALE_LINEAR, PERIOD_CONST_LO, SCALE_LINEAR, },
     { BEEPTYPE_CONTINUOUS, PITCH_VARIO_RELATIVE, SCALE_LINEAR, PERIOD_CONST_LO, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_LO, SCALE_LINEAR, },
     { BEEPTYPE_SHORT, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_LO, SCALE_LINEAR, },
     { BEEPTYPE_LONG, PITCH_VARIO_GROSS, SCALE_LINEAR, PERIOD_CONST_MEDIUM, SCALE_LINEAR},
   },
  },
};

#endif