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

#ifndef SCREEN_LABELBLOCK_HPP
#define SCREEN_LABELBLOCK_HPP

#include "Screen/Point.hpp"
#include "Util/StaticArray.hpp"
#include "Compiler.h"

/**
 * Simple code to prevent text writing over map city names.
 */
class LabelBlock {
#if defined(_WIN32_WCE) && _WIN32_WCE < 0x400
  /* PPC2000 (ancient hardware, expect small screens) */
  static constexpr unsigned SCREEN_HEIGHT = 1024;
  static constexpr unsigned BUCKET_SIZE = 32;
#elif defined(_WIN32_WCE) || defined(HAVE_GLES)
  /* embedded (Android or Windows CE) */
  static constexpr unsigned SCREEN_HEIGHT = 2048;
  static constexpr unsigned BUCKET_SIZE = 64;
#else
  /* desktop, screen may be huge, lots of memory */
  static constexpr unsigned SCREEN_HEIGHT = 4096;
  static constexpr unsigned BUCKET_SIZE = 64;
#endif
  static constexpr unsigned BUCKET_SHIFT = 7;
  static constexpr unsigned BUCKET_HEIGHT = 1 << BUCKET_SHIFT;
  static constexpr unsigned BUCKET_COUNT = SCREEN_HEIGHT / BUCKET_HEIGHT;

  /**
   * A bucket is responsible for hit tests in one horizontal section
   * of the screen.
   */
  class Bucket {
    typedef StaticArray<PixelRect, BUCKET_SIZE> BlockArray;
    BlockArray blocks;

  public:
    void Clear();

    gcc_pure
    bool Check(const PixelRect rc) const;

    void Add(const PixelRect rc) {
      if (!blocks.full())
        blocks.append(rc);
    }
  };

  Bucket buckets[BUCKET_COUNT];

public:
  /**
   * @param add_no_check.  adds the label regardless of overlap
   */
  bool check(const PixelRect rc, bool add_no_check = false);
  void reset();
};

#endif