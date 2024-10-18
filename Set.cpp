#include "Set.h"

Set::operator BitField() {
    return BitField(this->_bitfield);
}

Set::Set(const BitField& tmp) : _maxPower(tmp.GetLenght()), _bitfield(tmp) {}

Set::Set(const Set& tmp):_maxPower(tmp.GetMaxPow()), _bitfield(tmp._bitfield) {}

Set::Set(const size_t maxPower) :_bitfield(maxPower) { _maxPower = maxPower; }

void Set::InsElem(uint64_t elem) {
    if (elem < _maxPower)
        _bitfield.SetBit(elem);
    else {
        throw "Elem out of range";
    }
}

void Set::DelElem(uint64_t elem) {
    _bitfield.ClrBit(elem);
}

size_t Set::GetMaxPow() const {
    return _maxPower;
}

bool Set::IsMember(uint64_t elem) {
    return _bitfield.GetBit(elem);
}

bool Set::operator==(const Set& tmp){
    if (_bitfield == tmp._bitfield)
        return true;
    return false;
}

Set& Set::operator= (const Set& tmp) {
    _maxPower = tmp._maxPower;
    _bitfield = tmp._bitfield;
}

Set Set::operator+(const Set& tmp) {
    Set result(max(tmp._maxPower, _maxPower));
    result._bitfield = _bitfield | tmp._bitfield;
    return result;
}


void Set::operator+(uint64_t elem) {
    InsElem(elem);
}

void Set::operator-(uint64_t elem) {
    DelElem(elem);
}

Set Set::operator*(const Set& elem) {

}

Set Set::operator~() {
    Set result(_maxPower);
    result._bitfield = ~_bitfield;
}


ostream& operator<<(ostream& os, const Set& tmp) {
    os << tmp._bitfield;
    return os << endl;
};

istream& operator>>(istream& is, Set& tmp) {
    is >> tmp._maxPower;
    is >> tmp._bitfield;
    return is;
}

