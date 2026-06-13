#include "Global.h"

#include "mc/server/commands/CommandRegistry.h"
#include "mc/server/commands/CommandOutput.h"

#include "ll/api/command/CommandHandle.h"
#include "ll/api/service/Bedrock.h"

#include "gmlib/mc/world/actor/Actor.h"

void RegisterCommand() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "inventorycheck",
        tr("command.inventorycheck.desc"),
        CommandPermissionLevel::GameDirectors
    );
    ll::service::getCommandRegistry()->registerAlias("inventorycheck", "ic");
    cmd.overload().execute<[&](CommandOrigin const& origin, CommandOutput& output) {
        auto entity = (GMLIB_Actor*)origin.getEntity();
        if (entity && entity->isPlayer()) {
            auto pl = (Player*)entity;
            return mainForm(*pl);
        }
        return output.error(tr("command.error.console"));
    }>();
}