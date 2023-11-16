#include "airins_emiter.h"

int main(int argc, const char *argv[])
{
    airvm_code_file_t code;
    Emiter emiter(code);

    // 预设值
    emiter.nop(); // 寄存器计数
    emiter.nop(); // 参数计数
    emiter.nop(); // 指令条数
    emiter.nop();

    float f32 = 3.14159;
    double f64 = 9.45679235;

    // 开始填充指令
   // /*
    // 4 bit 常量赋值: 8-4-4
      emiter.const_r4_imm4(op_const_w32_r4_i4, 0, -2);
      emiter.const_r4_imm4(op_const_w32_r4_u4, 1, 15);
      emiter.const_r4_imm4(op_const_w64_r4_i4, 2, -1);
      emiter.const_r4_imm4(op_const_w64_r4_u4, 3, 15);

     // 8 bit 常量赋值：8-8-8-8
     emiter.const_r8_imm8(subop_const_w32_r8_b0, 0, 0x10);
     emiter.const_r8_imm8(subop_const_w32_r8_b1, 1, 0x11);
     emiter.const_r8_imm8(subop_const_w32_r8_b2, 2, 0x12);
     emiter.const_r8_imm8(subop_const_w32_r8_b3, 3, 0x13);

     emiter.const_r8_imm8(subop_const_w32_r8_i8, 5, -1);
     emiter.const_r8_imm8(subop_const_w32_r8_u8, 6, -1);

     emiter.const_r8_imm8(subop_const_w32_r8_h16_i8, 0, -1);
     emiter.const_r8_imm8(subop_const_w32_r8_h16_u8, 1, -1);
     emiter.const_r8_imm8(subop_const_w32_r8_l16_i8, 2, -1);
     emiter.const_r8_imm8(subop_const_w32_r8_l16_u8, 3, -1);

     emiter.const_r8_imm8(subop_const_w64_r8_i8, 5, -1);
     emiter.const_r8_imm8(subop_const_w64_r8_u8, 6, -1);

    // 16 bit 常量赋值：8-8-16
    emiter.const_r8_imm16(op_const_w32_r8_i16, 0, -1);
    emiter.const_r8_imm16(op_const_w32_r8_u16, 1, -1);
    emiter.const_r8_imm16(op_const_w64_r8_i16, 2, -1);
    emiter.const_r8_imm16(op_const_w64_r8_u16, 3, -1);

    emiter.const_r8_imm16(op_const_w32_r8_h16, 4, -1);
    emiter.const_r8_imm16(op_const_w32_r8_l16, 5, -1);

    // 32/64 bit 常量赋值：8-8-32/8-8-64

    emiter.const_r8_imm32(op_const_w32_r8_i32, 0, -1);
    emiter.const_r8_imm32(op_const_w32_r8_u32, 1, -1);
    emiter.const_r8_imm32(op_const_w32_r8_f32, 2, *(uint32_t *)&f32);

    emiter.const_r8_imm64(op_const_w64_r8_i64, 0, -256);
    emiter.const_r8_imm64(op_const_w64_r8_u64, 1, 256);
    emiter.const_r8_imm64(op_const_w64_r8_f64, 2, *(uint64_t *)&f64);

    // 16/32/64 bit 常量赋值：8-8-16-16/8-8-16-32/8-8-16-64
    emiter.const_r16_imm16(subop_const_w32_r16_i16, 0, -456);
    emiter.const_r16_imm16(subop_const_w32_r16_u16, 1, -1);
    emiter.const_r16_imm32(subop_const_w32_r16_i32, 2, -456);
    emiter.const_r16_imm32(subop_const_w32_r16_u32, 3, -1);
    emiter.const_r16_imm32(subop_const_w32_r16_f32, 4, *(uint32_t *)&f32);

    emiter.const_r16_imm16(subop_const_w64_r16_i16, 0, -456);
    emiter.const_r16_imm16(subop_const_w64_r16_u16, 1, -1);
    emiter.const_r16_imm32(subop_const_w64_r16_i32, 2, -456);
    emiter.const_r16_imm32(subop_const_w64_r16_u32, 3, -1);
    emiter.const_r16_imm64(subop_const_w64_r16_i64, 2, -456);
    emiter.const_r16_imm64(subop_const_w64_r16_u64, 3, -1);
    emiter.const_r16_imm64(subop_const_w64_r16_f64, 4, *(uint64_t *)&f64);
    // 寄存器间赋值：8-4-4
    emiter.const_r16_imm32(subop_const_w32_r16_u32, 0, -1);
    emiter.mov_r4(op_mov_w32_r4_i32, 1, 0);
    emiter.mov_r4(op_mov_w32_r4_u32, 2, 0);

    emiter.const_r16_imm32(subop_const_w32_r16_f32, 3, *(uint32_t *)&f32);
    emiter.mov_r4(op_mov_w32_r4_f32, 4, 3);

    emiter.const_r16_imm64(subop_const_w64_r16_u64, 5, -1);
    emiter.mov_r4(op_mov_w64_r4_i64, 7, 5);
    emiter.mov_r4(op_mov_w64_r4_u64, 9, 5);

    emiter.const_r16_imm64(subop_const_w64_r16_f64, 11, *(uint64_t *)&f64);
    emiter.mov_r4(op_mov_w64_r4_f64, 13, 11);
//*/
    // 寄存器间赋值: op subop,des,src  : src => des :8-8-8-8
    emiter.const_r16_imm32(subop_const_w32_r16_u32, 0, -1);
    emiter.const_r16_imm32(subop_const_w32_r16_f32, 1, *(uint32_t *)&f32);
    emiter.const_r16_imm64(subop_const_w64_r16_u64, 2, -1);
    emiter.const_r16_imm64(subop_const_w64_r16_f64, 4, *(uint64_t *)&f64);

   // /*
    emiter.mov_r8(subop_mov_w32_sb0, 6, 0);
    emiter.mov_r8(subop_mov_w32_ub0, 6, 0);
    emiter.mov_r8(subop_mov_w32_sb1, 6, 0);
    emiter.mov_r8(subop_mov_w32_ub1, 6, 0);
    emiter.mov_r8(subop_mov_w32_sb2, 6, 0);
    emiter.mov_r8(subop_mov_w32_ub2, 6, 0);
    emiter.mov_r8(subop_mov_w32_sb3, 6, 0);
    emiter.mov_r8(subop_mov_w32_ub3, 6, 0);

    emiter.mov_r8(subop_mov_w32_sh16, 6, 0);
    emiter.mov_r8(subop_mov_w32_uh16, 6, 0);
    emiter.mov_r8(subop_mov_w32_sl16, 6, 0);
    emiter.mov_r8(subop_mov_w32_ul16, 6, 0);

    emiter.mov_r8(subop_mov_w32_i32, 6, 0);
    emiter.mov_r8(subop_mov_w32_u32, 6, 0);
    emiter.mov_r8(subop_mov_w32_f32, 6, 1);
    emiter.mov_r8(subop_bitcast_w32, 6, 1);

    emiter.mov_r8(subop_mov_w64_sb0, 6, 0);
    emiter.mov_r8(subop_mov_w64_ub0, 6, 0);
    emiter.mov_r8(subop_mov_w64_sb1, 6, 0);
    emiter.mov_r8(subop_mov_w64_ub1, 6, 0);
    emiter.mov_r8(subop_mov_w64_sb2, 6, 0);
    emiter.mov_r8(subop_mov_w64_ub2, 6, 0);
    emiter.mov_r8(subop_mov_w64_sb3, 6, 0);
    emiter.mov_r8(subop_mov_w64_ub3, 6, 0);

    emiter.mov_r8(subop_mov_w64_sh16, 6, 0);
    emiter.mov_r8(subop_mov_w64_uh16, 6, 0);
    emiter.mov_r8(subop_mov_w64_sl16, 6, 0);
    emiter.mov_r8(subop_mov_w64_ul16, 6, 0);

    emiter.mov_r8(subop_mov_w64_i64, 6, 2);
    emiter.mov_r8(subop_mov_w64_u64, 6, 2);
    emiter.mov_r8(subop_mov_w64_f64, 6, 4);
    emiter.mov_r8(subop_bitcast_w64, 6, 4);
    

    emiter.mov_r8(subop_cast_i32_to_i64, 6, 0);
    emiter.mov_r8(subop_cast_u32_to_u64, 8, 0);
    emiter.mov_r8(subop_cast_i64_to_i32, 10, 6);
    emiter.mov_r8(subop_cast_u64_to_u32, 10, 8);

    emiter.mov_r8(subop_cast_f32_to_f64, 6, 1);
    emiter.mov_r8(subop_cast_f64_to_f32, 8, 6);
    //*/

    emiter.mov_r8(subop_cast_i32_to_f32, 6, 0);
    emiter.mov_r8(subop_cast_u32_to_f32, 8, 0);
    emiter.mov_r8(subop_cast_i32_to_f64, 6, 0);
    emiter.mov_r8(subop_cast_u32_to_f64, 6, 0);

    emiter.mov_r8(subop_cast_i64_to_f32, 6, 2);
    emiter.mov_r8(subop_cast_u64_to_f32, 8, 2);
    emiter.mov_r8(subop_cast_i64_to_f64, 6, 2);
    emiter.mov_r8(subop_cast_u64_to_f64, 6, 2);

    emiter.mov_r8(subop_cast_f32_to_i32, 6, 1);
    emiter.mov_r8(subop_cast_f32_to_u32, 8, 1);
    emiter.mov_r8(subop_cast_f32_to_i64, 6, 1);
    emiter.mov_r8(subop_cast_f32_to_u64, 6, 1);

    emiter.mov_r8(subop_cast_f64_to_i32, 6, 4);
    emiter.mov_r8(subop_cast_f64_to_u32, 8, 4);
    emiter.mov_r8(subop_cast_f64_to_i64, 6, 4);
    emiter.mov_r8(subop_cast_f64_to_u64, 6, 4);

    // 更新值
    auto data = emiter.code.buffer.data();
    *(uint16_t *)data = 24;
    *(uint16_t *)&data[2] = 0;
    *(uint32_t *)&data[4] = ((uint32_t)emiter.code.buffer.size() - 8) / 2;

    emiter.write_to_flie("test.bc");
    return 0;
}