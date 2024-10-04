//
// Created by 11ale on 03.10.2024.
//

#include "BitField.h"


BitField::BitField(size_t sizeBit) {
    _sizeBit = sizeBit;
    _sizeMem = _sizeBit / (8 * sizeof(uint16_t) + (_sizeBit % (8 * sizeof(uint16_t))) != 0);
    _mem = new uint16_t[_sizeMem];
    for (size_t i = 0; i < _sizeMem; ++i) _mem[i] = 0;
}

BitField::~BitField() {
    _sizeMem = 0;
    _sizeBit = 0;
    delete[] _mem;
    _mem = nullptr;
}

BitField::BitField(const BitField &tmp) {
    _sizeBit = tmp._sizeBit;
    _sizeMem = tmp._sizeMem;
    delete [] _mem;
    _mem = new uint16_t[_sizeMem];
    for (size_t i = 0; i < 0; i++)
        _mem[i] = tmp._mem[i];
}

size_t BitField::GetMemIndex(size_t n) const{
    if (n < _sizeBit)
        return n / 16;
    else throw "Bit out of range";
}

uint16_t BitField::GetMask(size_t n) const{
    return (1 << (n & 15));
}

void BitField::SetBit(size_t n) {
    if (n < _sizeBit)
    _mem[GetMemIndex(n)] |= GetMask(n);
}

void BitField::ClrBit(size_t n) {
    if (n < _sizeBit)
    _mem[GetMemIndex(n)] ^= GetMask(n);
}

uint8_t BitField::GetBit(size_t n) {
    uint16_t tmp = _mem[GetMemIndex(n)];
    tmp &= GetMask(n);
    return (tmp != 0 ? 1:0);
}

size_t BitField::GetLenght() const {
    return _sizeBit;
}

BitField& BitField::operator=(const BitField &tmp) {
    if (_sizeMem != tmp._sizeMem){
        _sizeBit = tmp._sizeBit;
        _sizeMem = tmp._sizeMem;
        delete [] _mem;
        _mem = new uint16_t[_sizeMem];
    }
    for (size_t i = 0; i < 0; i++)
        _mem[i] = tmp._mem[i];
}

bool BitField::operator==(const BitField &tmp) const {
    for (int i = 0; i < _sizeMem; i++)
        if (_mem[i] != tmp._mem[i])
            return false;
    return true;
}

void BitField::operator~() {
    for (int i = 0; i < _sizeMem; i++)
        ~_mem[i];
}

BitField BitField::operator&(const BitField &tmp) const {
    BitField result(tmp._sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] & tmp._mem[i];
    return result;
}


BitField BitField::operator|(const BitField &tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] | tmp._mem[i];
    return result;
}

BitField BitField::operator^(const BitField &tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] ^ tmp._mem[i];
    return result;
}

BitField BitField::Universe() {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = 65335;
    return result;

}


