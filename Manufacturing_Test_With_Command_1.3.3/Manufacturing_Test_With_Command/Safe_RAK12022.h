// Safe_RAK12022.h - 用于解决 SPIClock 枚举冲突的包装头文件
#ifndef SAFE_RAK12022_H
#define SAFE_RAK12022_H

// 警告：此头文件必须在任何包含 DW1000Ng.hpp 的代码之前被包含！
// 第一步：在包含原库之前，将冲突的枚举名 SPIClock “重定向”为我们独有的名字
#define SPIClock RAK12022_INTERNAL_SPIClock // 将原库中的SPIClock替换掉
// 第二步：包含原库的头文件。此时，原库内部所有 SPIClock 都会变成 RAK12022_INTERNAL_SPIClock
#include "RAK12022_MAX31865.h"
// 第三步：立即取消宏定义，防止污染后续其他代码
#undef SPIClock

// 包装完成，RAK12022库现在使用 RAK12022_INTERNAL_SPIClock 枚举，
// 而 DW1000Ng 库继续使用它自己的 SPIClock 枚举，冲突解除。
#endif