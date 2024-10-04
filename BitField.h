#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

#ifndef BITFIELD_BITFIELD_H
#define BITFIELD_BITFIELD_H


class BitField {
private:
    size_t _sizeMem;
    size_t _sizeBit;
    uint16_t *_mem;

    size_t GetMemIndex(size_t n);

    uint16_t GetMask(size_t n);

public:
    BitField(size_t sizeBit);

    ~BitField();

    BitField(const BitField &tmp);

    BitField &Universe();

    void SetBit(size_t n);

    uint16_t GetBit(size_t n);

    void ClrBit(size_t n);

    size_t GetLenght() const;

    BitField &operator=(const BitField &tmp);

    bool operator==(const BitField &tmp) const;

    BitField &operator^(const BitField &tmp) const;

    BitField &operator&(const BitField &tmp) const;

    BitField &operator|(const BitField &tmp) const;

    friend istream &operator>>(istream &in, BitField &x) {
        size_t sizeBit;
        in >> sizeBit;
        x._sizeBit = sizeBit;
        x._sizeMem = (x._sizeBit / 16) + 1;
        x._mem = new uint16_t[x._sizeMem];
        string tmp;
        string close_one = " ", close_two = "\t";
        while (1) {
            in >> tmp;
            if (tmp == close_one || tmp == close_two) {
                break;
            }
            x.SetBit(stoi(tmp));
        }
        return in;
    }



    friend ostream &operator<<(ostream &os, const BitField &x) {
        int flag = 0;
        BitField tmp(x);
        os << "{";
        for (int j = 0; j < tmp._sizeMem; j++)
            for (int i = 0; i < 16; i++) {
                if ((tmp._mem[j] & 1) && (j == tmp._sizeMem - 1) && (i == 15)) {
                    os << flag;
                } else if (tmp._mem[j] & 1) {
                    os << flag << " ,";
                }
                flag++;
                tmp._mem[j] >> 1;
            }
        return os << "}";
    };

    void operator~();

};


#endif //BITFIELD_BITFIELD_H
