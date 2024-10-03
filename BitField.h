#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
using namespace std;

#ifndef BITFIELD_BITFIELD_H
#define BITFIELD_BITFIELD_H


class BitField {
private:
    size_t _sizeMem;
    size_t _sizeBit;
    uint8_t* _mem;
    size_t GetMemIndex(size_t n);
    uint8_t GetMask(size_t n);
public:
    BitField(size_t sizeBit);
    ~BitField();
    BitField(const BitField& tmp);
    BitField& Universe();
    void SetBit(size_t n);
    uint8_t GetBit(size_t n);
    void ClrBit(size_t n);
    size_t GetLenght() const;
    BitField& operator=(const BitField& tmp);
    bool operator==(const BitField& tmp) const;
    BitField& operator^(const BitField& tmp) const;
    BitField& operator&(const BitField& tmp) const;
    BitField& operator|(const BitField& tmp) const;
    void operator~();
};




#endif //BITFIELD_BITFIELD_H
