
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Grid(int *tab, int nbrlignes, int nbrcolonnes) {
    for (int x = 0; x < nbrlignes; x++) {
        for (int y = 0; y < nbrcolonnes; y++) {
            int index = x * nbrcolonnes + y;
            cout << tab[index] << " ";
        }
        cout << endl;
    }
}

void printgrid(int nbrlignes, int nbrcolonnes, int* grid) {
    for (int i = 0; i < nbrlignes; i++) {
        for (int j = 0; j < nbrcolonnes; j++) {
            int tab = i * nbrcolonnes + j;
            if (grid[tab] == 1)
                cout << "[#]";
            else
                cout << "[_]";
        }
        cout << endl;
    }
}

int vstatus(int cellx, int celly, int* grid, int nbrcolonnes, int nbrlignes) {
    int nbrlivev = 0;

    for (int voisinx = cellx - 1; voisinx <= cellx + 1; voisinx++) {
        for (int voisiny = celly - 1; voisiny <= celly + 1; voisiny++) {

            if (voisinx < 0 || voisiny < 0 ||
                voisinx >= nbrlignes || voisiny >= nbrcolonnes)
                continue;

            if (voisinx == cellx && voisiny == celly)
                continue;

            if (grid[voisinx * nbrcolonnes + voisiny] == 1) {
                nbrlivev++;
            }
        }
    }

    return nbrlivev;
}

int main() {
    int nbrlignes;
    int nbrcolonnes;

    cout << "Combien de lignes ?" << endl;
    cin >> nbrlignes;

    cout << "Combien de colonnes ?" << endl;
    cin >> nbrcolonnes;

    if (nbrlignes <= 0 || nbrcolonnes <= 0) {
        cout << "Dimensions invalides" << endl;
        return 1;
    }

    int* tab = new int[nbrlignes * nbrcolonnes]();
    int* newtab = new int[nbrlignes * nbrcolonnes]();

    int cellulesvivantes;

    cout << "Combien il y a de cellules vivantes ?" << endl;
    cin >> cellulesvivantes;

    if (cellulesvivantes >= 0 &&
        cellulesvivantes <= nbrlignes * nbrcolonnes) {
//ici
        for (int i = 0; i < cellulesvivantes; i++) {
            int ligne;
            int colonne;

            cout << "Choisis le numero de la ligne (0 a " << nbrlignes - 1 << ")" << endl;
            cin >> ligne;

            cout << "Choisis le numero de la colonne (0 a " << nbrcolonnes - 1 << ")" << endl;
            cin >> colonne;

            if (ligne < 0 || ligne >= nbrlignes ||
                colonne < 0 || colonne >= nbrcolonnes) {
                cout << "Coordonnees invalides" << endl;
                i--;
                continue;
                }

            int index = ligne * nbrcolonnes + colonne;
            tab[index] = 1;
        }
    } else {
        cout << "Nombre de cellules invalide" << endl;
    }

    printgrid(nbrlignes, nbrcolonnes, tab);

    delete[] tab;
    delete[] newtab;

    return 0;
}
