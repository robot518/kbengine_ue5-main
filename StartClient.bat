;此处设置虚幻4引擎编辑器的EXE文件所在的目录
SET EDITOR_EXE_DIR=D:\Program Files\Epic Games\UE_5.1\Engine\Binaries\Win64
@echo off
SET UE_EXE=%EDITOR_EXE_DIR%\UnrealEditor.exe

set var=0
rem ************循环开始
:continue
set /a var+=1
echo 第%var%次循环
start /B "Client" "%UE_EXE%" "%CD%\KBEDemo.uproject" -game
if %var% lss 4 goto continue
rem ************循环结束
echo 循环执行完毕

