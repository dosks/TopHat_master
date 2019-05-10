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

#ifndef XCSOAR_TASK_RENDERER_HPP
#define XCSOAR_TASK_RENDERER_HPP

#include "Geo/GeoBounds.hpp"

class TaskPointRenderer;
class AbortTask;
class OrderedTask;
class GotoTask;
class TaskInterface;

class TaskRenderer
{
  TaskPointRenderer &tpv;
  GeoBounds screen_bounds;
  /**
   * if true, drawing the ordered task shows only OZ outlines
   */
  bool show_only_ordered_outlines;

public:
  TaskRenderer(TaskPointRenderer &_tpv, GeoBounds _screen_bounds);

  /**
   * Draws Goto or Abort or Ordered task.
   * ALso draws the outlines of the Ordered OZ's while in Goto or Abort mode.
   * @param active_task.  The active task
   * @param ordered_task.  The ordered task.  May not be active
   * or have zero turnpoints
   */
  void Draw(const TaskInterface &active_task,
            const OrderedTask &ordered_task);
  void Draw(const AbortTask &task);
  void Draw(const OrderedTask &task);
  void Draw(const GotoTask &task);
};

#endif