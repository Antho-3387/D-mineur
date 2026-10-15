#include <iostream>
#include <string>
using namespace std;

int main() {
    int NbrRaw;
    int NbrCol;

    int* Grid = new int[NbrRaw * NbrCol];

    for (int x = 0; x < NbrRaw; x++) {
        for (int y = 0; y < NbrCol; y++) {
            int index = x * NbrCol + y;
            Grid[index] = 0;
        }
    }


    delete[] Grid;
    return 0;
}

