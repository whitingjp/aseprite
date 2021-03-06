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

#include "app/commands/command.h"
#include "app/context.h"
#include "app/context_access.h"
#include "app/document.h"
#include "app/launcher.h"

namespace app {

class OpenWithAppCommand : public Command {
public:
  OpenWithAppCommand();
  Command* clone() const override { return new OpenWithAppCommand(*this); }

protected:
  bool onEnabled(Context* context) override;
  void onExecute(Context* context) override;
};

OpenWithAppCommand::OpenWithAppCommand()
  : Command("OpenWithApp",
            "Open With Associated Application",
            CmdUIOnlyFlag)
{
}

bool OpenWithAppCommand::onEnabled(Context* context)
{
  const ContextReader reader(context);
  return
    reader.document() &&
    reader.document()->isAssociatedToFile();
}

void OpenWithAppCommand::onExecute(Context* context)
{
  launcher::open_file(context->activeDocument()->filename());
}

Command* CommandFactory::createOpenWithAppCommand()
{
  return new OpenWithAppCommand;
}

} // namespace app
