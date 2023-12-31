#ifndef __AIRVM_BCFMT_ENUM_INC__
#define __AIRVM_BCFMT_ENUM_INC__

// 字节码文件相关枚举值

enum airvm_bcfmt_enum
{
    // 文件规格版本
    airvm_bcfmt_header_file_formart = 0 << 8 | 1,
    // 指令版本
    airvm_bcfmt_header_instruction_version = 0 << 8 | 1,
    // 文件类别
    airvm_bcfmt_header_file_kind_exe = 'A' << 24 | 'E' << 16 | 'X' << 8 | 'E', // 可执行文件
    airvm_bcfmt_header_file_kind_dll = 'A' << 24 | 'D' << 16 | 'Y' << 8 | 'N', // 动态库文件
    airvm_bcfmt_header_file_kind_lib = 'A' << 24 | 'S' << 16 | 'L' << 8 | 'I', // 静态库文件
    airvm_bcfmt_header_file_kind_obj = 'A' << 24 | 'O' << 16 | 'B' << 8 | 'J', // 对象文件

    // 段表项类别
    airvm_bcfmt_segtab_item_kind_string_table = 1u << 0, // 字符串表
    airvm_bcfmt_segtab_item_kind_string_data = 1u << 1,  // 字符串数据

    airvm_bcfmt_segtab_item_kind_type_table = 1u << 2, // 类型表
    airvm_bcfmt_segtab_item_kind_type_data = 1u << 3,  // 类型数据

    airvm_bcfmt_segtab_item_kind_variable_table = 1u << 4, // 变量表
    airvm_bcfmt_segtab_item_kind_variable_data = 1u << 5,  // 变量数据

    airvm_bcfmt_segtab_item_kind_function_table = 1u << 6, // 函数表
    airvm_bcfmt_segtab_item_kind_function_data = 1u << 7,  // 函数数据

    airvm_bcfmt_segtab_item_kind_host_dll = 1u << 8, // 主机库表
    airvm_bcfmt_segtab_item_kind_plug_in = 1u << 9,  // 插件库表

    // 类型数据标记值
    airvm_bcfmt_type_data_init = 1u << 0,      // 标记该类型数据已经初始化
    airvm_bcfmt_type_builtin = 1u << 1,        // 基本（内建）类型
    airvm_bcfmt_type_enum = 1u << 2,           // 枚举类型
    airvm_bcfmt_type_struct = 1u << 3,         // 结构体类型
    airvm_bcfmt_type_entrust_func = 1u << 4,   // 静态函数委托类型
    airvm_bcfmt_type_entrust_object = 1u << 5, // 成员函数委托类型
    airvm_bcfmt_type_interface = 1u << 6,      // 接口类型
    airvm_bcfmt_type_class = 1u << 7,          // 类类型

    // 函数位标记值
    airvm_bcfmt_func_static = 1u << 0,    // 静态函数
    airvm_bcfmt_func_member = 1u << 1,    // 成员函数
    airvm_bcfmt_func_virtual = 1u << 2,   // 虚函数
    airvm_bcfmt_func_closure = 1u << 3,   // 闭包函数
    airvm_bcfmt_func_public = 1u << 4,    // 公开的函数
    airvm_bcfmt_func_protected = 1u << 5, // 受保护的函数
    airvm_bcfmt_func_private = 1u << 6,   // 私有的函数

    airvm_bcfmt_func_no_data = 1u << 30,   // 函数没有背景数据
    airvm_bcfmt_func_data_init = 1u << 31, // 函数背景数据已加载

};

#endif // __AIRVM_BCFMT_ENUM_INC__