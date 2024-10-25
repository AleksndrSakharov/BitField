#include "BitField.h"


BitField::BitField(size_t sizeBit) {
    _sizeBit = sizeBit;
    _memSize = (_sizeBit / (16 * (sizeof(uint16_t)))) + (_sizeBit % (16 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::~BitField() { 
    _memSize = 0;
    _sizeBit = 0;
    delete[] _mem;
    _mem = nullptr;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    // delete [] _mem;
    // _mem = nullptr;
    _mem = new uint16_t[tmp._memSize];
    for (int i = 0; i < _memSize; i++)
        _mem[i] = tmp._mem[i];
}

size_t BitField::GetMemIndex(size_t n) const{
    if (n < _sizeBit) return n / (8 * sizeof(uint16_t));
    throw "Bit out of range";
}

uint16_t BitField::GetMask(size_t n) {
    uint16_t mask = 1;
    return (mask << (n & 15));
}

void BitField::SetBit(size_t n) {
    if (n <= _sizeBit){
        uint16_t getmem = GetMemIndex(n);
        uint16_t getmask = GetMask(n);
        size_t s = _memSize;
        _mem[GetMemIndex(n)] |= GetMask(n);
    }

}

void BitField::ClrBit(size_t n) {
    _mem[GetMemIndex(n)] &= GetMask(n);
}

uint8_t BitField::GetBit(size_t n) {
    if ((n > _sizeBit) || (n < 0)) throw "Negative n";
    uint16_t tmp = _mem[GetMemIndex(n)];
    tmp &= GetMask(n);
    return (tmp != 0 ? 1 : 0);
}

size_t BitField::GetLength() const {
    return _sizeBit;
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_memSize != tmp._memSize) {
        // *this = BitField(1);
        _memSize = tmp._memSize;
        _memSize = tmp._memSize;
        delete[] _mem;
        _mem = nullptr;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}

bool BitField::operator==(const BitField& tmp) const {
    for (int i = 0; i < _memSize; i++)
        if (_mem[i] != tmp._mem[i])
            return false;
    return true;
}

BitField BitField::operator~() {
    BitField result(_sizeBit);
    for (int i = 0; i < _sizeBit; i++) {
        if (this->GetBit(i) == 0)
            result.SetBit(i);
        else
            result.ClrBit(i);
    }

    return result;
}

BitField BitField::operator&(const BitField& tmp)  {
    BitField result(max(_sizeBit, tmp._sizeBit));
    for (int i = 0; i < min(_sizeBit, tmp._sizeBit); i++)
        result._mem[i] = _mem[i] & tmp._mem[i];
    return result;
}


BitField BitField::operator|(const BitField& tmp)  {
    BitField result(max(_sizeBit,tmp._sizeBit));
    int i = 0;
    while (i < min(_memSize, tmp._memSize)) {
        result._mem[i] = _mem[i] | tmp._mem[i];
        i++;
    }
    if (_sizeBit > tmp._sizeBit) {
        while (i < _memSize) {
            result._mem[i] = _mem[i];
            i++;
        }
    }
    else if (_sizeBit > tmp._sizeBit) {
        while (i < tmp._memSize) {
            result._mem[i] = _mem[i];
            i++;
        }
    }
    return result;
}

BitField BitField::operator^(const BitField& tmp)  {
    BitField result(_sizeBit);
    for (int i = 0; i < _memSize; i++)
        result._mem[i] = _mem[i] ^ tmp._mem[i];
    return result;
}

BitField BitField::Universe() {
    BitField result(_sizeBit);
    for (int i = 0; i < _memSize; i++)
        result._mem[i] = 65535;
    return result;

}

istream& operator>>(istream& in, BitField& x) {
    size_t sizeBit;
    in >> sizeBit;
    x._sizeBit = sizeBit;
    x._memSize = (sizeBit / (16 * (sizeof(uint16_t)))) + (sizeBit % (16 * sizeof(uint16_t)) != 0);
    x._mem = new uint16_t[x._memSize];
    uint64_t tmp;
    while (true) {
        in >> tmp;
        x.SetBit(tmp);
    }
    return in;
}

ostream& operator<<(ostream& os, const BitField& x) {
    BitField tmp(x);
    for (int i = 0; i < x._sizeBit; i++)
		if (tmp.GetBit(i) == 0) os << 0 << " ";
		else os << 1 << " ";
	os << endl;
	return os;
}