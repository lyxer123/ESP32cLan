# ESP32cLan
PicoC 是一款非常小的 C 脚本解释器。它最初是作为无人机机载飞行系统的脚本语言。它也非常适用于其他机器人、嵌入式和非嵌入式应用。
核心 C 源代码大约有 3500 行。它不打算ISO C 的完整实现，但已包含所有基本功能。
编译后只需要几k的代码空间，而且非常节省数据空间。这意味着它可以在小型嵌入式设备中很好地工作。它也是一个有趣的例子，说明如何创建一个非常小的语言实现仍然保持代码的可读性。


## 参考内容 
* 1.picoc的官方原版地址：https://gitlab.com/zsaleeba/picoc
* 2.介绍picoc的地方：https://www.9bis.net/c/#!index.md
* 3.esp8266版本的basic解释器：https://github.com/esp8266/Basic
* 4.esp32的c语言：https://www.codeproject.com/Articles/5061494/Run-a-C-Language-Interpreter-on-Your-ESP32
* 5.picoc的arduino版本：https://github.com/rhelmus/picoc-arduino

编译通过

## 原版picoc-arduino与本项目代码差异
如下文件基本保持一致
platform.h 是您选择平台类型并指定包含的内容的地方等等，适用于您的平台。 
platform_XXX.c 包含支持函数，以便编译器可以您的平台，例如如何将字符写入控制台等。 
platform_library.c 包含您想要创建的函数库可供用户程序使用。 
还有一个 clibrary.c，其中包含用户库函数，例如printf() 与平台无关。 

移植系统将涉及设置适当的包含和定义 
在 platform.h 中，在 platform_XXX.c 中编写一些 I/O 例程，将在 platform_library.c 中你想要的任何用户功能然后更改picoc.c 中的主程序，用于获取程序所需的任何操作进入系统。 

platform.h 默认设置为 UNIX_HOST，因此可以轻松运行测试UNIX 系统。您需要根据以下条件指定自己的主机设置您的目标平台。 

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
