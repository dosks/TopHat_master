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

#include "TaskPointRenderer.hpp"
#include "Screen/Canvas.hpp"
#include "Screen/Layout.hpp"
#include "Projection/WindowProjection.hpp"
#include "Engine/Task/Ordered/Points/AATPoint.hpp"
#include "Engine/Task/Ordered/AATIsolineSegment.hpp"
#include "Look/TaskLook.hpp"
#include "Math/Screen.hpp"
#include "OZRenderer.hpp"

TaskPointRenderer::TaskPointRenderer(Canvas &_canvas,
                                     const WindowProjection &_projection,
                                     const TaskLook &_task_look,
                                     const FlatProjection &_flat_projection,
                                     OZRenderer &_ozv,
                                     bool _draw_bearing,
                                     TargetVisibility _target_visibility,
                                     const GeoPoint &_location)
  :canvas(_canvas), m_proj(_projection),
   map_canvas(_canvas, _projection,
              _projection.GetScreenBounds().Scale(fixed(1.1))),
   task_look(_task_look),
   flat_projection(_flat_projection),
   draw_bearing(_draw_bearing),
   target_visibility(_target_visibility),
   index(0),
   ozv(_ozv),
   active_index(0),
   location(_location),
   task_finished(false),
   mode_optional_start(false)
{
}

void
TaskPointRenderer::DrawOrdered(const OrderedTaskPoint &tp, Layer layer)
{
  int offset = index - active_index;

  if (offset == 0 && task_finished && tp.GetType() == TaskPointType::FINISH)
    /* if the task is finished, pretend the active_index is past the
       current index; we need this because XCSoar never moves
       active_index to one after the finish point, because that would
       point to an invalid task point index */
    offset = -1;

  switch (layer) {
  case LAYER_OZ_SHADE:
    if (tp.BoundingBoxOverlaps(bb_screen))
      // draw shaded part of observation zone
      DrawOZBackground(canvas, tp, offset);

    break;

  case LAYER_LEG:
    if (index > 0)
      DrawTaskLine(last_point, tp.GetLocationRemaining());

    last_point = tp.GetLocationRemaining();

    break;

  case LAYER_OZ_OUTLINE:
    if (tp.BoundingBoxOverlaps(bb_screen)) {
      if (mode_optional_start && offset == 0)
        /* render optional starts as deactivated */
        offset = -1;

      DrawOZForeground(tp, offset);
    }

    break;

  case LAYER_SYMBOLS:
    return;
  }
}

bool
TaskPointRenderer::IsTargetVisible(const TaskPoint &tp) const
{
  if (!tp.HasTarget() || target_visibility == NONE)
    return false;

  if (target_visibility == ALL)
    return true;

  return PointCurrent();
}

void
TaskPointRenderer::DrawBearing(const TaskPoint &tp)
{
  if (!location.IsValid() || !draw_bearing || !PointCurrent())
    return;

  canvas.Select(task_look.bearing_pen);
  map_canvas.DrawLineWithOffset(location, tp.GetLocationRemaining());
}

void
TaskPointRenderer::DrawTarget(const TaskPoint &tp)
{
  if (!IsTargetVisible(tp))
    return;

  RasterPoint sc;
  if (m_proj.GeoToScreenIfVisible(tp.GetLocationRemaining(), sc))
    task_look.target_icon.Draw(canvas, sc.x, sc.y);
}

void
TaskPointRenderer::DrawTaskLine(const GeoPoint &start, const GeoPoint &end)
{
  canvas.Select(LegActive() ? task_look.leg_active_pen :
                              task_look.leg_inactive_pen);
  canvas.SetBackgroundTransparent();
  map_canvas.DrawLine(start, end);
  canvas.SetBackgroundOpaque();

  // draw small arrow along task direction
  RasterPoint p_p;
  RasterPoint Arrow[3] = { {6,6}, {-6,6}, {0,0} };

  const RasterPoint p_start = m_proj.GeoToScreen(start);
  const RasterPoint p_end = m_proj.GeoToScreen(end);

  const Angle ang = Angle::FromXY(fixed(p_start.y - p_end.y),
                                  fixed(p_end.x - p_start.x)).AsBearing();

  ScreenClosestPoint(p_start, p_end, m_proj.GetScreenOrigin(), &p_p, Layout::Scale(25));
  PolygonRotateShift(Arrow, 2, p_p, ang);
  Arrow[2] = Arrow[1];
  Arrow[1] = p_p;

  canvas.Select(task_look.arrow_pen);
  canvas.DrawPolyline(Arrow, 3);
}

inline void
TaskPointRenderer::DrawIsoline(const AATPoint &tp)
{
  if (!tp.valid() || !IsTargetVisible(tp))
    return;

  AATIsolineSegment seg(tp, flat_projection);
  if (!seg.IsValid())
    return;

  #define fixed_twentieth fixed(1.0 / 20.0)

  GeoPoint start = seg.Parametric(fixed(0));
  GeoPoint end = seg.Parametric(fixed(1));

  if (m_proj.GeoToScreenDistance(start.DistanceS(end)) <= 2)
    return;

  RasterPoint screen[21];
  screen[0] = m_proj.GeoToScreen(start);
  screen[20] = m_proj.GeoToScreen(end);

  for (unsigned i = 1; i < 20; ++i) {
    fixed t = i * fixed_twentieth;
    GeoPoint ga = seg.Parametric(t);
    screen[i] = m_proj.GeoToScreen(ga);
  }

  canvas.Select(task_look.isoline_pen);
  canvas.SetBackgroundTransparent();
  canvas.DrawPolyline(screen, 21);
  canvas.SetBackgroundOpaque();
}

inline void
TaskPointRenderer::DrawOZBackground(Canvas &canvas, const OrderedTaskPoint &tp,
                                    int offset)
{
  ozv.Draw(canvas, OZRenderer::LAYER_SHADE, m_proj, tp.GetObservationZone(),
           offset);
}

inline void
TaskPointRenderer::DrawOZForeground(const OrderedTaskPoint &tp, int offset)
{
  ozv.Draw(canvas, OZRenderer::LAYER_INACTIVE, m_proj, tp.GetObservationZone(),
           offset);
  ozv.Draw(canvas, OZRenderer::LAYER_ACTIVE, m_proj, tp.GetObservationZone(),
           offset);
}

void
TaskPointRenderer::Draw(const TaskPoint &tp, Layer layer)
{
  const OrderedTaskPoint &otp = (const OrderedTaskPoint &)tp;
  const AATPoint &atp = (const AATPoint &)tp;

  switch (tp.GetType()) {
  case TaskPointType::UNORDERED:
    if (layer == LAYER_LEG && location.IsValid())
      DrawTaskLine(location, tp.GetLocationRemaining());

    if (layer == LAYER_SYMBOLS)
      DrawBearing(tp);

    index++;
    break;

  case TaskPointType::START:
    index = 0;

    DrawOrdered(otp, layer);
    if (layer == LAYER_SYMBOLS) {
      DrawBearing(tp);
      DrawTarget(tp);
    }

    break;

  case TaskPointType::AST:
    index++;

    DrawOrdered(otp, layer);
    if (layer == LAYER_SYMBOLS) {
      DrawBearing(tp);
      DrawTarget(tp);
    }
    break;

  case TaskPointType::AAT:
    index++;

    DrawOrdered(otp, layer);
    if (layer == LAYER_SYMBOLS) {
      if (otp.GetNext() != nullptr &&
          !(otp.GetNext()->GetWaypoint() == otp.GetWaypoint()) &&
          otp.GetPrevious() != nullptr &&
          !(otp.GetPrevious()->GetWaypoint() == otp.GetWaypoint()))
        DrawIsoline(atp);
      DrawBearing(tp);
      DrawTarget(tp);
    }
    break;

  case TaskPointType::FINISH:
    index++;

    DrawOrdered(otp, layer);
    if (layer == LAYER_SYMBOLS) {
      DrawBearing(tp);
      DrawTarget(tp);
    }
    break;
  }
}