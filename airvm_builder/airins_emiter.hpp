#ifndef __AIRINS_EMITER_INC__
#define __AIRINS_EMITER_INC__

#include <airvm_opcode.h>
#include <cstdint>
#include <stdio.h>
#include <vector>

// 小端序列
struct airvm_code_buffer_t
{
    std::vector<uint8_t> buffer;

    // 获取当前大小
    uint32_t getsize() const { return (uint32_t)buffer.size(); }

    inline void emiter(uint8_t byte) { buffer.push_back(byte); }
    inline void emiter2(uint16_t word)
    {
        buffer.push_back(word);
        buffer.push_back(word >> 8);
    }
    inline void emiter4(uint32_t dword)
    {
        buffer.push_back(dword);
        buffer.push_back(dword >> 8);
        buffer.push_back(dword >> 16);
        buffer.push_back(dword >> 24);
    }
    inline void emiter8(uint64_t qword)
    {
        buffer.push_back(qword);
        buffer.push_back(qword >> 8);
        buffer.push_back(qword >> 16);
        buffer.push_back(qword >> 24);
        buffer.push_back(qword >> 32);
        buffer.push_back(qword >> 40);
        buffer.push_back(qword >> 48);
        buffer.push_back(qword >> 56);
    }
};
struct Emiter
{
    Emiter() {}
    airvm_code_buffer_t code;

    void write_to_flie(const char *file)
    {
        FILE *fp = nullptr;
        fopen_s(&fp, file, "wb");
        fwrite(code.buffer.data(), 1, code.buffer.size(), fp);
        fclose(fp);
    }

    inline void nop() { code.emiter2(op_nop); }
    // 4 bit 常量赋值: 8-4-4
    inline void const_r4_imm4(uint8_t op, uint8_t des, uint8_t imm)
    {
        uint16_t ins = op << 8;
        ins |= (des << 4) | (imm & 0xF);
        code.emiter2(ins);
    }
    // 8 bit 常量赋值：8-8-8-8
    inline void const_r8_imm8(uint8_t subop, uint8_t des, uint8_t imm)
    {
        uint16_t ins = (op_const_r8_subop << 8) | subop;
        code.emiter2(ins);
        ins = (des << 8) | imm;
        code.emiter2(ins);
    }
    // 16 bit 常量赋值：8-8-16
    inline void const_r8_imm16(uint8_t op, uint8_t des, uint16_t imm)
    {
        uint16_t ins = (op << 8) | des;
        code.emiter2(ins);
        code.emiter2(imm);
    }
    // 32 bit 常量赋值：8-8-32
    inline void const_r8_imm32(uint8_t op, uint8_t des, uint32_t imm)
    {
        uint16_t ins = (op << 8) | des;
        code.emiter2(ins);
        code.emiter4(imm);
    }
    // 64 bit 常量赋值：8-8-64
    inline void const_r8_imm64(uint8_t op, uint8_t des, uint64_t imm)
    {
        uint16_t ins = (op << 8) | des;
        code.emiter2(ins);
        code.emiter8(imm);
    }
    // 16/32/64 bit 常量赋值：8-8-16-16/8-8-16-32/8-8-16-64
    inline void const_r16_imm16(uint8_t subop, uint16_t des, uint16_t imm)
    {
        uint16_t ins = (op_const_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter2(imm);
    }
    inline void const_r16_imm32(uint8_t subop, uint16_t des, uint32_t imm)
    {
        uint16_t ins = (op_const_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter4(imm);
    }
    inline void const_r16_imm64(uint8_t subop, uint16_t des, uint64_t imm)
    {
        uint16_t ins = (op_const_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter8(imm);
    }

    inline void mov_r4(uint8_t op, uint8_t des, uint8_t src)
    {
        uint16_t ins = (op << 8) | ((des & 0xF) << 4) | (src & 0xF);
        code.emiter2(ins);
    }
    inline void mov_r8(uint8_t subop, uint8_t des, uint8_t src)
    {
        uint16_t ins = (op_mov_r8_subop << 8) | subop;
        code.emiter2(ins);
        ins = (des << 8) | src;
        code.emiter2(ins);
    }
    inline void mov_r16(uint8_t subop, uint16_t des, uint16_t src)
    {
        uint16_t ins = (op_mov_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter2(src);
    }

    inline void math_r8(uint8_t subop, uint8_t des, uint8_t src)
    {
        uint16_t ins = (op_math2_r8_subop << 8) | subop;
        code.emiter2(ins);
        ins = (des << 8) | src;
        code.emiter2(ins);
    }
    inline void math_r16(uint8_t subop, uint16_t des, uint16_t src)
    {
        uint16_t ins = (op_math2_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter2(src);
    }

    inline void math3_r4(uint8_t subop, uint8_t des, uint8_t src, uint8_t src2)
    {
        uint16_t ins = (op_math3_r4_subop << 8) | subop;
        code.emiter2(ins);
        ins = (des << 8) | ((src & 0xF) << 4) | (src2 & 0xF);
        code.emiter2(ins);
    }
    inline void math3_r8(uint8_t subop, uint16_t des, uint8_t src, uint8_t src2)
    {
        uint16_t ins = (op_math3_r8_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        ins = (src << 8) | src2;
        code.emiter2(ins);
    }
    inline void math3_r16(uint8_t subop, uint16_t des, uint16_t src, uint16_t src2)
    {
        uint16_t ins = (op_math3_r16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(des);
        code.emiter2(src);
        code.emiter2(src2);
    }

    inline void goto_i8(uint8_t imm)
    {
        uint16_t ins = (op_goto_i8 << 8) | imm;
        code.emiter2(ins);
    }
    inline void goto_i24(uint32_t imm)
    {
        imm &= 0xFFFFFF;
        uint16_t ins = (op_goto_i24 << 8) | (imm & 0xFF);
        code.emiter2(ins);
        code.emiter2(imm >> 8);
    }
    inline void goto_i32(uint32_t imm)
    {
        uint16_t ins = (op_goto_i32 << 8);
        code.emiter2(ins);
        code.emiter4(imm);
    }

    inline void jbrz_r4_imm12(uint8_t subop, uint8_t src, uint16_t imm)
    {
        uint16_t ins = (op_jbrz_r4_imm12_subop << 8) | subop;
        code.emiter2(ins);
        ins = ((src & 0xF) << 12) | (imm & 0xFFF);
        code.emiter2(ins);
    }
    inline void jbrz_r8_imm8(uint8_t subop, uint8_t src, uint8_t imm)
    {
        uint16_t ins = (op_jbrz_r8_imm8_subop << 8) | subop;
        code.emiter2(ins);
        ins = (src << 8) | imm;
        code.emiter2(ins);
    }
    inline void jbrz_r8_imm24(uint8_t subop, uint8_t src, uint32_t imm)
    {
        uint16_t ins = (op_jbrz_r8_imm24_subop << 8) | subop;
        code.emiter2(ins);
        ins = src << 8 | (imm & 0xFF);
        code.emiter2(ins);
        ins = imm >> 8;
        code.emiter2(ins);
    }
    inline void jbrz_r16_imm16(uint8_t subop, uint16_t src, uint16_t imm)
    {
        uint16_t ins = (op_jbrz_r16_imm16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(src);
        code.emiter2(imm);
    }
    inline void jbrz_r16_imm32(uint8_t subop, uint16_t src, uint32_t imm)
    {
        uint16_t ins = (op_jbrz_r16_imm32_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(src);
        code.emiter2(imm);
        code.emiter2(imm >> 16);
    }
    inline void jbr_r4_imm8(uint8_t subop, uint8_t src, uint8_t src2, uint8_t imm)
    {
        uint16_t ins = (op_jbr_r4_imm8_subop << 8) | subop;
        code.emiter2(ins);
        ins = (imm << 8) | ((src2 & 0xF) << 4) | (src & 0xF);
        code.emiter2(ins);
    }
    inline void jbr_r8_imm16(uint8_t subop, uint8_t src, uint8_t src2, uint16_t imm)
    {
        uint16_t ins = (op_jbr_r8_imm16_subop << 8) | subop;
        code.emiter2(ins);
        ins = (src2 << 8) | src;
        code.emiter2(ins);
        code.emiter2(imm);
    }
    inline void jbr_r8_imm32(uint8_t subop, uint8_t src, uint8_t src2, uint32_t imm)
    {
        uint16_t ins = (op_jbr_r8_imm32_subop << 8) | subop;
        code.emiter2(ins);
        ins = (src2 << 8) | src;
        code.emiter2(ins);
        code.emiter4(imm);
    }
    inline void jbr_r16_imm16(uint8_t subop, uint16_t src, uint16_t src2, uint16_t imm)
    {
        uint16_t ins = (op_jbr_r16_imm16_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(src);
        code.emiter2(src2);
        code.emiter2(imm);
    }
    inline void jbr_r16_imm32(uint8_t subop, uint16_t src, uint16_t src2, uint32_t imm)
    {
        uint16_t ins = (op_jbr_r16_imm32_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(src);
        code.emiter2(src2);
        code.emiter4(imm);
    }
    inline void return_void()
    {
        uint16_t ins = (op_return_subop << 8) | subop_return_void;
        code.emiter2(ins);
    }

    inline void return_imm16(uint8_t subop, uint16_t imm)
    {
        uint16_t ins = (op_return_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(imm);
    }
    inline void return_imm32(uint8_t subop, uint32_t imm)
    {
        uint16_t ins = (op_return_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter4(imm);
    }
    inline void return_imm64(uint8_t subop, uint64_t imm)
    {
        uint16_t ins = (op_return_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter8(imm);
    }
    inline void return_reg(uint8_t subop, uint16_t reg)
    {
        uint16_t ins = (op_return_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(reg);
    }

    inline void getret_reg(uint8_t subop, uint16_t reg)
    {
        uint16_t ins = (op_getret_subop << 8) | subop;
        code.emiter2(ins);
        code.emiter2(reg);
    }
    // 8-8-16-32-4,4-4-4-...-4
    // func subop,dllserial,funcserial,argcnt,arg,arg1,...,argn
    // 参数个数，在 arg 的第一个元素
    inline void call_r4_native_func(uint16_t dllserial, uint32_t funcserial, std::vector<uint8_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r4_native_func;
        code.emiter2(ins);
        code.emiter2(dllserial);
        code.emiter4(funcserial);
        uint32_t count = arg.size();
        uint32_t align = (count + 3) & (~3);
        // 进行补位
        uint32_t mod = align - count;
        for (uint32_t i = 0; i < mod; ++i)
            arg.push_back(0);

        count = arg.size();
        // 进行组装
        for (uint32_t i = 0; i < align; i += 2)
        {
            uint8_t val = (0xF & arg[i]) | ((0xF & arg[i + 1]) << 4);
            code.emiter(val);
        }
    }
    inline void call_r8_native_func(uint16_t dllserial,uint32_t funcserial, std::vector<uint8_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r8_native_func;
        code.emiter2(ins);
        code.emiter2(dllserial);
        code.emiter4(funcserial);
        for (auto &item : arg)
            code.emiter(item);
        // 2字节对齐
        uint32_t len = arg.size();
        if ((len % 2) != 0)
        {
            code.emiter(0);
        }
    }
    inline void call_r16_native_func(uint16_t dllserial,uint32_t funcserial, std::vector<uint16_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r16_native_func;
        code.emiter2(ins);
        code.emiter2(dllserial);
        code.emiter4(funcserial);
        for (auto &item : arg)
            code.emiter2(item);
    }
    // 8-8-32-4,4-4-4-...-4
    // func subop,funcserial,argcnt,arg,arg1,...,argn
    // 参数个数，在 arg 的第一个元素
    inline void call_r4_static_func(uint32_t funcserial, std::vector<uint8_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r4_static_func;
        code.emiter2(ins);
        code.emiter4(funcserial);
        uint32_t count = arg.size();
        uint32_t align = (count + 3) & (~3);
        // 进行补位
        uint32_t mod = align - count;
        for (uint32_t i = 0; i < mod; ++i)
            arg.push_back(0);

        count = arg.size();
        // 进行组装
        for (uint32_t i = 0; i < align; i += 2)
        {
            uint8_t val = (0xF & arg[i]) | ((0xF & arg[i + 1]) << 4);
            code.emiter(val);
        }
    }
    inline void call_r8_static_func(uint32_t funcserial, std::vector<uint8_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r8_static_func;
        code.emiter2(ins);
        code.emiter4(funcserial);
        for (auto &item : arg)
            code.emiter(item);
        // 2字节对齐
        uint32_t len = arg.size();
        if ((len % 2) != 0)
        {
            code.emiter(0);
        }
    }
    inline void call_r16_static_func(uint32_t funcserial, std::vector<uint16_t> arg)
    {
        uint16_t ins = (op_func_subop << 8) | subop_call_r16_static_func;
        code.emiter2(ins);
        code.emiter4(funcserial);
        for (auto &item : arg)
            code.emiter2(item);
    }
};

#endif // __AIRINS_EMITER_INC__