#include "BitField.h"


BitField::BitField(size_t sizeBit) {
    _sizeBit = sizeBit;
    _sizeMem = (_sizeBit / (16 * (sizeof(uint16_t)))) + (sizeBit % (16 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_sizeMem];
    for (size_t i = 0; i < _sizeMem; ++i)
        _mem[i] = 0;
}

BitField::~BitField() {
    _sizeMem = 0;
    _sizeBit = 0;
    delete[] _mem;
    _mem = nullptr;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _sizeMem = tmp._sizeMem;
    // delete [] _mem;
    // _mem = nullptr;
    _mem = new uint16_t[tmp._sizeMem];
    for (int i = 0; i < _sizeMem; i++)
        _mem[i] = tmp._mem[i];
}

size_t BitField::GetMemIndex(size_t n) const{
    if (n < _sizeBit) return n / 16;
    throw "Bit out of range";
}

uint16_t BitField::GetMask(size_t n) {
    uint16_t mask = 1;
    return (mask << (n & 15));
}

void BitField::SetBit(size_t n) {
    if (n < _sizeBit)
        _mem[GetMemIndex(n)] |= GetMask(n);
}

void BitField::ClrBit(size_t n) {
    _mem[GetMemIndex(n)] ^= GetMask(n);
}

uint8_t BitField::GetBit(size_t n) {
    if ((n > _sizeBit) || (n < 0)) throw "Negative n";
    uint16_t tmp = _mem[GetMemIndex(n)];
    tmp &= GetMask(n);
    return (tmp != 0 ? 1 : 0);
}

size_t BitField::GetLenght() const {
    return _sizeBit;
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_sizeMem != tmp._sizeMem) {
        // *this = BitField(1);
        _sizeMem = tmp._sizeMem;
        _sizeMem = tmp._sizeMem;
        delete[] _mem;
        _mem = nullptr;
        _mem = new uint16_t[_sizeMem];
    }
    for (size_t i = 0; i < _sizeMem; ++i)
        _mem[i] = tmp._mem[i];

}

bool BitField::operator==(const BitField& tmp) const {
    for (int i = 0; i < _sizeMem; i++)
        if (_mem[i] != tmp._mem[i])
            return false;
    return true;
}

BitField BitField::operator~() {
    BitField a(*this);
    for (int i = 0; i < (a._sizeMem - 1); i++) a._mem[i] = ~(a._mem[i]);
	for (int i = ((a._sizeMem - 1) * (sizeof(uint16_t) * 8)); i < (a._sizeBit); i++) {
		if (a.GetBit(i) == 1) a.ClrBit(i);
		else a.SetBit(i);
	}
	return a;
}

BitField& BitField::operator&(const BitField& tmp) const {
    BitField result(max(_sizeBit, tmp._sizeBit));
    for (int i = 0; i < min(_sizeBit, tmp._sizeBit); i++)
        result._mem[i] = _mem[i] & tmp._mem[i];
    return result;
}


BitField& BitField::operator|(const BitField& tmp) const {
    BitField result(max(_sizeBit,tmp._sizeBit));
    int i = 0; 
    while (i < min(_sizeBit, tmp._sizeBit)) {
        result._mem[i] = _mem[i] | tmp._mem[i];
        i++;
    }
    if (_sizeBit > tmp._sizeBit) {
        while (i < _sizeBit) {
            result._mem[i] = _mem[i];
            i++;
        }
    }
    else if (_sizeBit > tmp._sizeBit) {
        while (i < tmp._sizeBit) {
            result._mem[i] = _mem[i];
            i++;
        }
    }
    return result;
}

BitField& BitField::operator^(const BitField& tmp) const {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = _mem[i] ^ tmp._mem[i];
    return result;
}

BitField& BitField::Universe() {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeMem; i++)
        result._mem[i] = 65535;
    return result;

}

istream& operator>>(istream& in, BitField& x) {
    size_t sizeBit;
    in >> sizeBit;
    x._sizeBit = sizeBit;
    x._sizeMem = (sizeBit / (16 * (sizeof(uint16_t)))) + (sizeBit % (16 * sizeof(uint16_t)) != 0);
    x._mem = new uint16_t[x._sizeMem];
    uint64_t tmp;
    while (true) {
        in >> tmp;
        x.SetBit(tmp);
    }
    return in;
}

ostream& operator<<(ostream& os, const BitField& x) {
    int flag = 0;
    BitField tmp(x);
    os << "{";
    for (int j = 0; j < tmp._sizeMem; j++)
        for (int i = 0; i < 16; i++) {
            if ((tmp._mem[j] & 1) && (j == tmp._sizeMem - 1) && (i == 15)) {
                os << flag;
            }
            else if (tmp._mem[j] & 1) {
                os << flag << " ,";
            }
            flag++;
            tmp._mem[j] >> 1;
        }
    return os << "}";
}