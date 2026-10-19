#include <iostream>
#include <string>
#include <ctime>
using namespace std;


int GetNumberOfBombs(int x, int y, int** Grille, int NbrLignes, int NbrColonnes) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < NbrLignes && ny >= 0 && ny < NbrColonnes) {
                if (Grille[nx][ny] == -1) {
                    count++;
                }
            }
        }
    }

    return count;
}


void FloodFill(int x, int y, int** Grille, int NbrLignes, int NbrColonnes) {
    if (x < 0 || x >= NbrLignes || y < 0 || y >= NbrColonnes)
        return;

    if (Grille[x][y] != 0)
        return;

    int NumBombs = GetNumberOfBombs(x, y, Grille, NbrLignes, NbrColonnes);

    if (NumBombs > 0) {
        Grille[x][y] = NumBombs;
        return;
    }

    Grille[x][y] = -2;

    FloodFill(x + 1, y,     Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y,     Grille, NbrLignes, NbrColonnes);
    FloodFill(x,     y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x,     y - 1, Grille, NbrLignes, NbrColonnes);

    FloodFill(x + 1, y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x + 1, y - 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y - 1, Grille, NbrLignes, NbrColonnes);
}

int main () {

    int Choix;
    int SizeX;
    int SizeY;
    int mine;

    cout << "Choisis une taille de tableau :" << endl;
    cout << "1) 9/9" << endl;
    cout << "2) 16/16" << endl;
    cout << "3) 30/30" << endl;
    cin >> Choix;

    if (Choix == 1) {
        SizeX = 9;
        SizeY = 9;
        mine = 10;
    } else if (Choix == 2) {
        SizeX = 16;
        SizeY = 16;
        mine = 40;
    } else if (Choix == 3) {
        SizeX = 30;
        SizeY = 30;
        mine = 99;
    } else {
        cout << "Mauvais choix" << endl;
        return 0;
    }

    int NbrLignes = SizeX;
    int NbrColonnes = SizeY;

    srand(time(NULL));

    int** Grille = new int*[NbrLignes];
    for (int i = 0; i < NbrLignes; i++) {
        Grille[i] = new int[NbrColonnes];
    }

    for (int x = 0; x < NbrLignes; x++) {
        for (int y = 0; y < NbrColonnes; y++) {
            Grille[x][y] = 0;
        }
    }

    int place = 0;

    while (place < mine) {
        int x = rand() % NbrLignes;
        int y = rand() % NbrColonnes;

        if (Grille[x][y] != -1) {
            Grille[x][y] = -1;
            place++;
        }
    }

    for (int i=0; i < NbrLignes; i++) {
        for (int j=0; j < NbrColonnes; j++ ) {
            cout << Grille[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
