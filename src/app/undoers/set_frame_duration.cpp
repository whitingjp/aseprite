/* Aseprite
 * Copyright (C) 2001-2013  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/undoers/set_frame_duration.h"

#include "doc/sprite.h"
#include "undo/objects_container.h"
#include "undo/undoers_collector.h"

namespace app {
namespace undoers {

using namespace undo;

SetFrameDuration::SetFrameDuration(ObjectsContainer* objects, Sprite* sprite, frame_t frame)
  : m_spriteId(objects->addObject(sprite))
  , m_frame(frame)
{
  ASSERT(frame >= 0 && frame < sprite->totalFrames());

  m_duration = sprite->frameDuration(frame);
}

void SetFrameDuration::dispose()
{
  delete this;
}

void SetFrameDuration::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  Sprite* sprite = objects->getObjectT<Sprite>(m_spriteId);

  // Push another SetFrameDuration as redoer
  redoers->pushUndoer(new SetFrameDuration(objects, sprite, m_frame));

  sprite->setFrameDuration(m_frame, m_duration);
}

} // namespace undoers
} // namespace app
