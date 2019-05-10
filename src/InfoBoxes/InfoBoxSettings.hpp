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

#ifndef XCSOAR_INFO_BOX_SETTINGS_HPP
#define XCSOAR_INFO_BOX_SETTINGS_HPP

#include "Util/StaticString.hxx"
#include "Compiler.h"
#include "InfoBoxes/Content/Type.hpp"

#include <stdint.h>

struct InfoBoxSettings {
  enum PanelIndex {
    PANEL_CIRCLING,
    PANEL_CRUISE,
    PANEL_FINAL_GLIDE,
    PANEL_AUXILIARY,
  };

  struct Panel {
    static constexpr unsigned MAX_CONTENTS = 24;

    StaticString<32u> name;
    InfoBoxFactory::Type contents[MAX_CONTENTS];

    void Clear();

    gcc_pure
    bool IsEmpty() const;
  };

  static constexpr unsigned MAX_PANELS = 8;
  static constexpr unsigned PREASSIGNED_PANELS = 3;

  /**
   * Auto-switch to the "final glide" panel if above final glide?
   * This setting affects the #DisplayMode, and is checked by
   * GetNewDisplayMode().
   */
  bool use_final_glide;

  enum class Geometry : uint8_t {
    /** 8 infoboxes split bottom/top or left/right */
    SPLIT_8,

    /** 8 infoboxes along bottom or right */
    BOTTOM_RIGHT_8 = 1,

    /** 8 infoboxes along top or left */
    TOP_LEFT_8 = 2,

    /** @see #SPLIT_8 */
    OBSOLETE_SPLIT_8 = 3,

    /** @see #TOP_LEFT_8 */
    OBSOLETE_TOP_LEFT_8 = 4,

    /** @see #BOTTOM_RIGHT_8 */
    OBSOLETE_BOTTOM_RIGHT_8 = 5,

    /** infoboxes GNAV (9 right + vario) */
    RIGHT_9_VARIO = 6,

    /** infoboxes (5) along right side (square screen) */
    RIGHT_5 = 7,

    /** 12 infoboxes along bottom or right side */
    BOTTOM_RIGHT_12 = 8,

    /** 24 infoboxes along right side (3x8) */
    RIGHT_24 = 9,

    /** @see BOTTOM_RIGHT_12 */
    OBSOLETE_BOTTOM_RIGHT_12 = 10,

    /** 12 infoboxes along top or left */
    TOP_LEFT_12 = 11,

    /** 6 left, 3 right + vario */
    LEFT_6_RIGHT_3_VARIO = 12,

    /** 8 bottom + vario */
    BOTTOM_8_VARIO = 13,
    TOP_LEFT_4 = 14,
    BOTTOM_RIGHT_4 = 15,

    OBSOLETE_BOTTOM_RIGHT_4 = 16,
    OBSOLETE_TOP_LEFT_4 = 17,

    /** 8 top + vario */
    TOP_8_VARIO = 18,

    /** 16 infoboxes along right side (2x8) */
    RIGHT_16 = 19,

    /** infoboxes (7) along top or right side  */
    TOP_RIGHT_7 = 20,

    /** 10 infoboxes right or bottom (2*5) */
    BOTTOM_RIGHT_10 = 21,

  } geometry;

  bool inverse, use_colors;

  enum class BorderStyle : uint8_t {
    BOX,
    TAB,
    SHADED,
    GLASS,
  } border_style;

  Panel panels[MAX_PANELS];

  /**
   * should the altitude info boxes display an alternate unit
   * in the comment field
   **/
  bool show_alternative_altitude_units;

  void SetDefaults();
};

#endif