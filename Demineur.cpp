#include <iostream>
#include <random>
using namespace std;

int main() {
    int Choix;
    int SizeX;
    int SizeY;
    int NbrBombes;

    cout << "Choisis une taille de tableau :" << endl;
    cout << "1) 9/9" << endl;
    cout << "2) 16/16" << endl;
    cout << "3) 30/30" << endl;
    cin >> Choix;

    if (Choix == 1) {
        SizeX = 9;
        SizeY = 9;
        NbrBombes = 10;
    } else if (Choix == 2) {
        SizeX = 16;
        SizeY = 16;
        NbrBombes = 40;
    } else if (Choix == 3) {
        SizeX = 30;
        SizeY = 30;
        NbrBombes = 99;
    } else {
        cout << "Mauvais choix" << endl;
        return 0;
    }

    int NbrLignes = SizeX;
    int NbrColonnes = SizeY;
    int TotalCases = NbrColonnes * NbrLignes;

    int* Grille = new int[TotalCases];

    for (int x = 0; x < NbrLignes; x++) {
        for (int y = 0; y < NbrColonnes; y++) {
            int INDEX = x * NbrColonnes + y;
            Grille[INDEX] = 0;
        }
    }

    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<int> tirage(0, TotalCases - 1);
    //
    // int CountBombe = 0;
    //
    // while (CountBombe < NbrBombes) {
    //     int INDEX = tirage(gen);
    //
    //     if (Grille[INDEX] == 0) {
    //         Grille[INDEX] = 1;
    //         CountBombe++;
    //     }
    // }
    //
    // for (int x = 0; x < NbrLignes; x++) {
    //     for (int y = 0; y < NbrColonnes; y++) {
    //         int INDEX = x * NbrColonnes + y;
    //         cout << Grille[INDEX] << " ";
    //     }
    //     cout << endl;
    // }

    delete[] Grille;
    return 0;
}