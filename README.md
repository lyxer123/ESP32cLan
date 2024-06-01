# ESP32cLan


## 参考内容 
* 1.picoc的官方原版地址：https://gitlab.com/zsaleeba/picoc
* 2.介绍picoc的地方：https://www.9bis.net/c/#!index.md
* 3.esp8266版本的basic解释器：https://github.com/esp8266/Basic
* 4.esp32的c语言：https://www.codeproject.com/Articles/5061494/Run-a-C-Language-Interpreter-on-Your-ESP32
* 5.picoc的arduino版本：https://github.com/rhelmus/picoc-arduino

编译通过

## 原版picoc-arduino与本项目代码差异
如下文件基本保持一致
clibrary.c   （在这个文件中增加自定义函数，方便调用）
debug.c
expression.c
heap.c
include.c
interpreter.h
lex.c
parse.c
picoc.c
picoc.h
platform.c
platform.h
table.c
type.c
variable.c
