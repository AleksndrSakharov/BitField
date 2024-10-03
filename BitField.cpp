//
// Created by 11ale on 03.10.2024.
//

#include "BitField.h"


BitField::BitField(size_t sizeBit) {
    _sizeBit = sizeBit;
    _sizeMem = (_sizeBit / 8) + 1;
    _mem = new uint8_t[_sizeMem];
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
    _mem = tmp._mem;
}

size_t BitField::GetMemIndex(size_t n) {
    return n / 8 + 1;
}

uint8_t BitField::GetMask(size_t n) {
    return n & 7;
}

void BitField::SetBit(size_t n) {
    _mem[GetMemIndex(n)] += GetMask(n);
}

void BitField::ClrBit(size_t n) {
    _mem[GetMemIndex(n)] ^= GetMask(n);
}

uint8_t BitField::GetBit(size_t n) {
    uint8_t tmp = _mem[GetMemIndex(n)];
    tmp &= GetMask(n);
    tmp >> n & 7;
    return tmp;
}

size_t BitField::GetLenght() const {
    return _sizeMem * 8; //SPROSIT
}

BitField& BitField::operator=(const BitField &tmp) {
    _sizeBit = tmp._sizeBit;
    _sizeMem = tmp._sizeMem;
    _mem = tmp._mem;
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

BitField& BitField::operator&(const BitField &tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] & tmp._mem[i];
    return result;
}


BitField& BitField::operator|(const BitField &tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] | tmp._mem[i];
    return result;
}

BitField& BitField::operator^(const BitField &tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] ^ tmp._mem[i];
    return result;
}

BitField& BitField::Universe() {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = 255;
    return result;

}