#include "Set.h"

int main() {
    uint64_t n;
    cin >> n;
    Set sett(n + 1);
    for (size_t i = 0; i < n + 1; i++) sett.InsElem(i);
    vector<uint64_t> vec = sett.GetPriority();
    for (size_t i = 0; i < vec.size(); i++) cout << vec[i] << endl;
    return 0;
}
