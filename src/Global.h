#pragma once
#include <include_all.h>

#define PLUGIN_NAME "InventoryCheck"

extern ll::Logger logger;

extern std::string tr(std::string key, std::vector<std::string> data = {});

extern void initPlugin();
extern void RegisterCommand();