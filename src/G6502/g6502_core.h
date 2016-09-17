/*
 * G6502 - 6502 Emulator
 * Copyright (C) 2016  Ignacio Sanchez Gines

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#ifndef G6502_CORE_H_
#define	G6502_CORE_H_

#include "g6502_definitions.h"
#include "g6502_eight_bit_register.h"
#include "g6502_sixteen_bit_register.h"
#include "g6502_memory_interface.h"

namespace g6502
{
   
class G6502
{
public:
    G6502();
    ~G6502();
    void Init(MemoryInterface* memory_impl);
    void Reset();
    unsigned int RunFor(unsigned int t_states);
    unsigned int Tick();
    void RequestIRQ(bool assert);
    void RequestNMI();
    void SetMemoryImpl();

private:
    typedef void (G6502::*OPCptr) (void);
    OPCptr opcodes_[256];
    SixteenBitRegister PC_;
    EightBitRegister A_;
    EightBitRegister X_;
    EightBitRegister Y_;
    EightBitRegister S_;
    EightBitRegister P_;
    MemoryInterface* memory_impl_;
    unsigned int t_states_;
    bool interrupt_asserted_;
    bool nmi_interrupt_requested_;
    bool page_crossed_;
    bool branch_taken_;

private:
    u8 Fetch8();
    u16 Fetch16();
    u16 MakeAddress16(u8 high, u8 low);
    bool PageCrossed(u16 old_address, u16 new_address);
    void ClearAllFlags();
    void SetZeroFlagFromResult(u8 result);
    void SetOverflowFlagFromResult(u8 result);
    void SetNegativeFlagFromResult(u8 result);
    void SetFlag(u8 flag);
    void FlipFlag(u8 flag);
    void ClearFlag(u8 flag);
    bool IsSetFlag(u8 flag);
    void StackPush16(u16 value);
    void StackPush8(u8 value);
    u16 StackPop16();
    u8 StackPop8();
    u8 Read(u16 address);
    void Write(u16 address, u8 value);
    u8 ImmediateAddressing();
    u16 ZeroPageAddressing();
    u16 ZeroPageXAddressing();
    u16 ZeroPageYddressing();
    s8 RelativeAddressing();
    u16 AbsoluteAddressing();
    u16 AbsoluteXAddressing();
    u16 AbsoluteYAddressing();
    u16 IndirectAddressing();
    u16 IndexedIndirectAddressing();
    u16 IndirectIndexedAddressing();
    void UnofficialOPCode();
    void OPCodes_ADC(u8 value);
    void OPCodes_AND(u8 value);
    void OPCodes_ASL_Accumulator();
    void OPCodes_ASL_Memory(u16 address);
    void OPcodes_Branch(bool condition);
    void OPCodes_BIT(u16 address);
    void OPCodes_BRK();
    void OPCodes_ClearFlag(u8 flag);
    void OPCodes_SetFlag(u8 flag);
    void OPCodes_CMP(EightBitRegister* reg, u8 value);
    void OPCodes_DEC_Mem(u16 address);
    void OPCodes_DEC_Reg(EightBitRegister* reg);
    void OPCodes_EOR(u8 value);
    void OPCodes_INC_Mem(u16 address);
    void OPCodes_INC_Reg(EightBitRegister* reg);
    void OPCodes_LD(EightBitRegister* reg, u8 value);

    void InitOPCodeFunctors();

    void OPCode0x00(); void OPCode0x01(); void OPCode0x02(); void OPCode0x03();
    void OPCode0x04(); void OPCode0x05(); void OPCode0x06(); void OPCode0x07();
    void OPCode0x08(); void OPCode0x09(); void OPCode0x0A(); void OPCode0x0B();
    void OPCode0x0C(); void OPCode0x0D(); void OPCode0x0E(); void OPCode0x0F();
    void OPCode0x10(); void OPCode0x11(); void OPCode0x12(); void OPCode0x13();
    void OPCode0x14(); void OPCode0x15(); void OPCode0x16(); void OPCode0x17();
    void OPCode0x18(); void OPCode0x19(); void OPCode0x1A(); void OPCode0x1B();
    void OPCode0x1C(); void OPCode0x1D(); void OPCode0x1E(); void OPCode0x1F();
    void OPCode0x20(); void OPCode0x21(); void OPCode0x22(); void OPCode0x23();
    void OPCode0x24(); void OPCode0x25(); void OPCode0x26(); void OPCode0x27();
    void OPCode0x28(); void OPCode0x29(); void OPCode0x2A(); void OPCode0x2B();
    void OPCode0x2C(); void OPCode0x2D(); void OPCode0x2E(); void OPCode0x2F();
    void OPCode0x30(); void OPCode0x31(); void OPCode0x32(); void OPCode0x33();
    void OPCode0x34(); void OPCode0x35(); void OPCode0x36(); void OPCode0x37();
    void OPCode0x38(); void OPCode0x39(); void OPCode0x3A(); void OPCode0x3B();
    void OPCode0x3C(); void OPCode0x3D(); void OPCode0x3E(); void OPCode0x3F();
    void OPCode0x40(); void OPCode0x41(); void OPCode0x42(); void OPCode0x43();
    void OPCode0x44(); void OPCode0x45(); void OPCode0x46(); void OPCode0x47();
    void OPCode0x48(); void OPCode0x49(); void OPCode0x4A(); void OPCode0x4B();
    void OPCode0x4C(); void OPCode0x4D(); void OPCode0x4E(); void OPCode0x4F();
    void OPCode0x50(); void OPCode0x51(); void OPCode0x52(); void OPCode0x53();
    void OPCode0x54(); void OPCode0x55(); void OPCode0x56(); void OPCode0x57();
    void OPCode0x58(); void OPCode0x59(); void OPCode0x5A(); void OPCode0x5B();
    void OPCode0x5C(); void OPCode0x5D(); void OPCode0x5E(); void OPCode0x5F();
    void OPCode0x60(); void OPCode0x61(); void OPCode0x62(); void OPCode0x63();
    void OPCode0x64(); void OPCode0x65(); void OPCode0x66(); void OPCode0x67();
    void OPCode0x68(); void OPCode0x69(); void OPCode0x6A(); void OPCode0x6B();
    void OPCode0x6C(); void OPCode0x6D(); void OPCode0x6E(); void OPCode0x6F();
    void OPCode0x70(); void OPCode0x71(); void OPCode0x72(); void OPCode0x73();
    void OPCode0x74(); void OPCode0x75(); void OPCode0x76(); void OPCode0x77();
    void OPCode0x78(); void OPCode0x79(); void OPCode0x7A(); void OPCode0x7B();
    void OPCode0x7C(); void OPCode0x7D(); void OPCode0x7E(); void OPCode0x7F();
    void OPCode0x80(); void OPCode0x81(); void OPCode0x82(); void OPCode0x83();
    void OPCode0x84(); void OPCode0x85(); void OPCode0x86(); void OPCode0x87();
    void OPCode0x88(); void OPCode0x89(); void OPCode0x8A(); void OPCode0x8B();
    void OPCode0x8C(); void OPCode0x8D(); void OPCode0x8E(); void OPCode0x8F();
    void OPCode0x90(); void OPCode0x91(); void OPCode0x92(); void OPCode0x93();
    void OPCode0x94(); void OPCode0x95(); void OPCode0x96(); void OPCode0x97();
    void OPCode0x98(); void OPCode0x99(); void OPCode0x9A(); void OPCode0x9B();
    void OPCode0x9C(); void OPCode0x9D(); void OPCode0x9E(); void OPCode0x9F();
    void OPCode0xA0(); void OPCode0xA1(); void OPCode0xA2(); void OPCode0xA3();
    void OPCode0xA4(); void OPCode0xA5(); void OPCode0xA6(); void OPCode0xA7();
    void OPCode0xA8(); void OPCode0xA9(); void OPCode0xAA(); void OPCode0xAB();
    void OPCode0xAC(); void OPCode0xAD(); void OPCode0xAE(); void OPCode0xAF();
    void OPCode0xB0(); void OPCode0xB1(); void OPCode0xB2(); void OPCode0xB3();
    void OPCode0xB4(); void OPCode0xB5(); void OPCode0xB6(); void OPCode0xB7();
    void OPCode0xB8(); void OPCode0xB9(); void OPCode0xBA(); void OPCode0xBB();
    void OPCode0xBC(); void OPCode0xBD(); void OPCode0xBE(); void OPCode0xBF();
    void OPCode0xC0(); void OPCode0xC1(); void OPCode0xC2(); void OPCode0xC3();
    void OPCode0xC4(); void OPCode0xC5(); void OPCode0xC6(); void OPCode0xC7();
    void OPCode0xC8(); void OPCode0xC9(); void OPCode0xCA(); void OPCode0xCB();
    void OPCode0xCC(); void OPCode0xCD(); void OPCode0xCE(); void OPCode0xCF();
    void OPCode0xD0(); void OPCode0xD1(); void OPCode0xD2(); void OPCode0xD3();
    void OPCode0xD4(); void OPCode0xD5(); void OPCode0xD6(); void OPCode0xD7();
    void OPCode0xD8(); void OPCode0xD9(); void OPCode0xDA(); void OPCode0xDB();
    void OPCode0xDC(); void OPCode0xDD(); void OPCode0xDE(); void OPCode0xDF();
    void OPCode0xE0(); void OPCode0xE1(); void OPCode0xE2(); void OPCode0xE3();
    void OPCode0xE4(); void OPCode0xE5(); void OPCode0xE6(); void OPCode0xE7();
    void OPCode0xE8(); void OPCode0xE9(); void OPCode0xEA(); void OPCode0xEB();
    void OPCode0xEC(); void OPCode0xED(); void OPCode0xEE(); void OPCode0xEF();
    void OPCode0xF0(); void OPCode0xF1(); void OPCode0xF2(); void OPCode0xF3();
    void OPCode0xF4(); void OPCode0xF5(); void OPCode0xF6(); void OPCode0xF7();
    void OPCode0xF8(); void OPCode0xF9(); void OPCode0xFA(); void OPCode0xFB();
    void OPCode0xFC(); void OPCode0xFD(); void OPCode0xFE(); void OPCode0xFF();
};

} // namespace g6502

#include "g6502_core_inl.h"

#endif // G6502_CORE_H_

