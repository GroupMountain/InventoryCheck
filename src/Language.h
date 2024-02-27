#pragma once
#include "Global.h"

std::string defaultLanguage_en_US = R"(
    
)";

std::string defaultLanguage_zh_CN = R"(
    form.main.title=查询玩家背包
    form.main.content=请选择查询模式
    form.main.checkOnline=查询在线玩家
    form.main.checkAll=查询全部玩家
    form.main.searchPlayer=搜索玩家
    form.main.resumeInventory=恢复查包前背包
    form.checkList.title=玩家列表
    form.checkList.content=请选择你要查询的玩家
    form.searchPlayer.title=搜索玩家
    form.searchPlayer.description=请输入玩家名进行搜索
    form.searchPlayer.input=玩家名
    form.searchPlayer.inputName=请输入玩家名称信息
    form.searchForm.searchMode=搜索模式
    form.searchPlayer.fuzzySearch=模糊搜索
    form.searchPlayer.preciseSearch=精确搜索
    form.notFound.title=未找到匹配结果
    form.notFound.content=没有找到和 %s 匹配的玩家数据
    form.notFound.returnSearch=返回搜索菜单
    form.returnMainForm=返回主菜单
    form.checkPlayer.title=查询玩家背包
    form.checkPlayer.content=你正在查询玩家 %s 的背包\n请选择操作模式
    form.checkPlayer.copyInventory=将玩家背包复制到自身背包
    form.checkPlayer.writeInventory=用自身背包覆盖玩家背包
    form.checkPlayer.deleteData=删除玩家全部数据（不仅仅是背包）
    form.invalidInput.title=非法的输入
    form.invalidInput.content=输入的玩家名不能为空！
    form.invalidInput.returnSearch=重新搜索
    command.error.console=该命令只能由玩家执行
    command.inventorycheck.desc=查询玩家背包
    checkPlayer.copyInventory.success=已成功将玩家 %s 的背包复制到你的背包！
    checkPlayer.copyInventory.failed=无法将玩家 %s 的背包复制到你的背包！\n玩家 %s 没有任何数据！
    form.confirmWrite.title=确认覆盖背包
    form.confirmWrite.content=你确定要用你的背包覆盖玩家 %s 的背包吗？\n\n注意！\n此操作不可逆！
    form.confirmAction=确认操作
    form.cancelAction=我再想想
    checkPlayer.writeInventory.success=已成功覆盖玩家 %s 的背包！
    checkPlayer.writeInventory.failed=无法覆盖玩家 %s 的背包！\n玩家 %s 没有任何数据！
    form.confirmDelete.title=确认删除数据
    form.confirmDelete.content=你确定要删除玩家 %s 的全部数据吗？\n这包含玩家在存档的全部数据！\n不仅仅是背包！\n\n注意！\n此操作不可逆！\n请谨慎操作
    checkPlayer.deleteNbt.success=已成功删除玩家 %s 的全部数据！
    form.deleteFailed.title=删除失败
    form.deleteFailed.content=玩家 %s 在线！无法删除玩家全部数据！\n\n如需删除全部玩家数据，请先将该玩家踢出游戏再操作！
    form.deleteFailed.returnCheck=返回操作界面
    checkOnline.empty=全服就你一个人在线，还在这查在线玩家呢？\n还不快去招人？
    checkAll.empty=整个存档就你一个人玩过，还在这玩查包呢？\n还不快去招人？
)";
