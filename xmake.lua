add_rules("mode.debug", "mode.release", "mode.releasedbg")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires("levilaminalibrary")
add_requires("gmlib")
add_requires("levibuildscript")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("target_type")
    set_default("server")
    set_showmenu(true)
    set_values("server", "client")
option_end()

target("InventoryCheck") -- Change this to your mod name.
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    add_cxflags( "/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE")
    add_packages("levilaminalibrary","gmlib")
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")
    add_files("src/**.cpp")
    add_includedirs("src")
    -- if is_config("target_type", "server") then
    --     add_includedirs("src-server")
    --     add_files("src-server/**.cpp")
    -- else
    --     add_includedirs("src-client")
    --     add_files("src-client/**.cpp")
    -- end
