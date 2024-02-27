#include "Forms.h"

void mainForm(Player& pl) {
    auto fm = ll::form::SimpleForm(tr("form.main.title"), tr("form.main.content"));
    fm.appendButton(tr("form.main.checkOnline"), [](Player& pl) { return checkOnlineForm(pl); });
    fm.appendButton(tr("form.main.checkAll"), [](Player& pl) { return checkAllForm(pl); });
    fm.appendButton(tr("form.main.searchPlayer"), [](Player& pl) { return searchPlayerForm(pl); });
    fm.appendButton(tr("form.main.resumeInventory"), [](Player& pl) { return; });
    fm.sendTo(pl);
}

void checkOnlineForm(Player& pl) {
    auto fm = ll::form::SimpleForm(tr("form.checkList.title"), tr("form.checkList.content"));
    std::unordered_map<mce::UUID, std::string> onlineList;
    GMLIB_Level::getLevel()->forEachPlayer([&onlineList](Player& pl) -> bool {
        if (!pl.isSimulated()) {
            onlineList[pl.getUuid()] = pl.getRealName();
        }
        return true;
    });
    for (auto& [uuid, name] : onlineList) {
        fm.appendButton(name, [uuid](Player& pl) { return checkPlayerForm(pl, uuid); });
    }
    fm.sendTo(pl, [](Player& pl, int index) {
        if (index == -1) {
            return mainForm(pl);
        }
    });
}

std::string getNameFormUuid(mce::UUID& uuid) {
    auto        player = GMLIB_Level::getLevel()->getPlayer(uuid);
    std::string name;
    if (player) {
        name = player->getRealName();
    } else {
        auto strUuid   = uuid.asString();
        auto cachename = GMLIB::Server::UserCache::getNameByUuid(strUuid);
        if (cachename.has_value()) {
            name = cachename.value();
        } else {
            name = strUuid;
        }
    }
    return name;
}

std::unordered_map<mce::UUID, std::string> generateUuidMap() {
    auto                                       allUuids = GMLIB_Player::getAllUuids();
    std::unordered_map<mce::UUID, std::string> allList;
    for (auto& strUuid : allUuids) {
        auto uuid     = mce::UUID::fromString(strUuid);
        auto name     = getNameFormUuid(uuid);
        allList[uuid] = name;
    }
    return std::move(allList);
}

void checkAllForm(Player& pl) {
    auto fm      = ll::form::SimpleForm(tr("form.checkList.title"), tr("form.checkList.content"));
    auto allList = generateUuidMap();
    for (auto& [uuid, name] : allList) {
        fm.appendButton(name, [uuid](Player& pl) { return checkPlayerForm(pl, uuid); });
    }
    fm.sendTo(pl, [](Player& pl, int index) {
        if (index == -1) {
            return mainForm(pl);
        }
    });
}

void searchPlayerForm(Player& pl) {
    auto fm = ll::form::CustomForm(tr("form.searchPlayer.title"));
    fm.appendLabel(tr("form.searchPlayer.description"));
    fm.appendInput("name", tr("form.searchPlayer.input"), tr("form.searchPlayer.inputName"));
    fm.appendDropdown(
        "mode",
        tr("form.searchForm.searchMode"),
        {tr("form.searchPlayer.fuzzySearch"), tr("form.searchPlayer.preciseSearch")},
        0
    );
    fm.sendTo(pl, [](Player& pl, const ll::form::CustomFormResult& result) {
        if (result.empty()) {
            return mainForm(pl);
        }
        std::string inputName;
        if (std::holds_alternative<std::string>(result.at("name"))) {
            inputName = std::get<std::string>(result.at("name"));
        }
        auto searchMode = std::get<std::string>(result.at("mode"));
        if (inputName.empty()) {
            return invalidInputForm(pl);
        }
        auto allList = generateUuidMap();
        if (searchMode == tr("form.searchPlayer.preciseSearch")) {
            for (auto& [uuid, name] : allList) {
                if (name == inputName) {
                    return checkPlayerForm(pl, uuid);
                }
            }
        } else {
            std::unordered_map<mce::UUID, std::string> resultList;
            for (auto& [uuid, name] : allList) {
                if (name.find(inputName) != std::string::npos) {
                    resultList[uuid] = name;
                }
            }
            if (!resultList.empty()) {
                return searchResultForm(pl, resultList);
            }
        }
        return searchNotFoundForm(pl, inputName);
    });
}

void searchResultForm(Player& pl, std::unordered_map<mce::UUID, std::string> resultList) {
    auto fm = ll::form::SimpleForm(tr("form.checkList.title"), tr("form.checkList.content"));
    for (auto& [uuid, name] : resultList) {
        fm.appendButton(name, [&uuid](Player& pl) { checkPlayerForm(pl, uuid); });
    }
    fm.sendTo(pl, [](Player& pl, int index) {
        if (index == -1) {
            return searchPlayerForm(pl);
        }
    });
}

void searchNotFoundForm(Player& pl, std::string& name) {
    auto fm = ll::form::ModalForm(
        tr("form.notFound.title"),
        tr("form.notFound.content", {name}),
        tr("form.notFound.returnSearch"),
        tr("form.returnMainForm")
    );
    fm.sendTo(pl, [](Player& pl, ll::form::ModalForm::SelectedButton result) {
        if (result == ll::form::ModalForm::SelectedButton::Upper) {
            return searchPlayerForm(pl);
        }
        return mainForm(pl);
    });
}

void checkPlayerForm(Player& pl, mce::UUID uuid) {
    std::string name = getNameFormUuid(uuid);
    auto        fm   = ll::form::SimpleForm(tr("form.checkPlayer.title"), tr("form.checkPlayer.content", {name}));
    fm.appendButton(tr("form.checkPlayer.copyInventory"), [uuid](Player& pl) {
        auto nbt  = GMLIB_Player::getPlayerNbt(uuid);
        auto self = (GMLIB_Player*)(&pl);
        self->setPlayerNbtTags(pl.getUuid(), *nbt, {"Offhand", "Inventory", "Armor", "EnderChestInventory"});
    });
    fm.appendButton(tr("form.checkPlayer.writeInventory"), [uuid](Player& pl) {
        //
    });
    fm.appendButton(tr("form.checkPlayer.deleteData"), [uuid](Player& pl) {
        //
    });
    fm.sendTo(pl, [](Player& pl, int index) {
        if (index == -1) {
            return mainForm(pl);
        }
    });
}

void invalidInputForm(Player& pl) {
    auto fm = ll::form::ModalForm(
        tr("form.invalidInput.title"),
        tr("form.invalidInput.content"),
        tr("form.invalidInput.returnSearch"),
        tr("form.returnMainForm")
    );
    fm.sendTo(pl, [](Player& pl, ll::form::ModalForm::SelectedButton result) {
        if (result == ll::form::ModalForm::SelectedButton::Upper) {
            return searchPlayerForm(pl);
        }
        return mainForm(pl);
    });
}