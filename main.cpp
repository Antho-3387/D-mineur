#include <iostream>
#include <string>
#include <vector>
using namespace std;


void Grid (int *tab, int nbrlignes, int nbrcolonnes) {
    for (int x=0; x < nbrlignes; x++) {
        for (int y=0; y < nbrcolonnes; y++) {
            int index= x * nbrcolonnes + y;
            cout << tab[index] << " ";
        }
        cout << endl;
    }
}


int main() {

    int nbrlignes;
    int nbrcolonnes;

    cout << "Combien de lignes ? ";
    cin >> nbrlignes;

    cout << "Combien de colonnes ? ";
    cin >> nbrcolonnes;

    int* tab = new int[nbrlignes * nbrcolonnes]();
    Grid(tab, nbrlignes, nbrcolonnes);

    delete[] tab;

    return 0;
}
