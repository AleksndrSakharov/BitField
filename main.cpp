#include "Set.h"

int main() {
    const size_t size = 38;
    BitField bf(size), negBf(size), expNegBf(size);

    std::vector<uint64_t> bits;
    bits.push_back(0);
    bits.push_back(1);
    bits.push_back(14);
    bits.push_back(16);
    bits.push_back(33);
    bits.push_back(37);

    for (size_t i = 0; i < bits.size(); i++)
      bf.SetBit(bits[i]);
    cout << bf << "\n";
    negBf = ~bf;
    
    for(size_t i = 0; i < size; i++)
      expNegBf.SetBit(i);
    for (size_t i = 0; i < bits.size(); i++)
      expNegBf.ClrBit(bits[i]);
    cout << expNegBf << "\n" << negBf;
    return 0;
}
 