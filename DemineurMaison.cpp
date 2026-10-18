#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main () {

    int tab[10][10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab[i][j] = 0;
        }
    }

    int mine = 10;
    int place = 0;

    while (place < mine) {
        int x = rand() % 10;
        int y = rand() % 10;

        if (tab[x][y] != -1) {
            tab[x][y] = -1;
            place++;
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j =0; j <10; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}