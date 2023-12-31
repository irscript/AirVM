#ifndef __AIRVM_RUNTIME_INC__
#define __AIRVM_RUNTIME_INC__

#include <Precompiled.h>

typedef struct airvm_actuator *airvm_actor_t; // 虚拟机执行器上下文
typedef struct airvm_function *airvm_func_t;  // 虚拟机执行的函数

typedef struct
{
    int8_t isMemfile;     // 是否是内存文件
    uintptr_t memfile;    // 可执行文件的地址指针
    uintptr_t memsize;   // 内存文件大小
    const char *filename; // 可执行文件的名称
} airvm_config;

// 虚拟机环境初始化
uintptr_t airvm_init(const airvm_config *config);
// 虚拟机环境终结化
void airvm_terminal();
// 加载文件
uintptr_t airvm_load_file(const char *path);
// 释放文件
void airvm_unload_file(uintptr_t *handle);
// 分析文件
int32_t airvm_parse_file(uintptr_t handle);

// 从句柄中获取入口函数
airvm_func_t airvm_get_entry(uintptr_t handle);

// 获取一个执行器上下文
airvm_actor_t airvm_alloc_actor();
// 释放执行器上下文
void airvm_free_actor(airvm_actor_t *actor);
// 设置运行函数函数栈
int32_t airvm_set_func(airvm_actor_t actor, airvm_func_t func, uint32_t argc, uint32_t *argv);

// 运行函数
void airvm_run(airvm_actor_t actor);

#endif // __AIRVM_RUNTIME_INC__