#include <iostream>
#include <string>

// Random
#include <ctime>
#include <cstdlib>

// Utf-8
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// FONCTION : Compter les bombes autour des cases
int ObtenirNbrBombe(int x, int y, string** Grille, int NbrLignes, int NbrColonnes) {
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) {// décalage de ligne
        for (int dy = -1; dy <= 1; dy++) {// décalage de colone
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < NbrLignes && ny >= 0 && ny < NbrColonnes) {// Vérifier que la case voisine est dans la grille
                if (Grille[nx][ny] == "💣")
                    count++;
            }
        }
    }
    // Retourner le nombre total de bombes voisines
    return count;
}

// FONCTION : afficher les grille durant la partie
void AfficherGrille(string** Grille, bool** Drapeaux,int NbrLignes, int NbrColonnes) {
    cout << endl;

    for (int i = 0; i < NbrLignes; i++) {
        for (int j = 0; j < NbrColonnes; j++) {
            if (Drapeaux[i][j]) {
                cout << "🚩 ";
            }
            else if (Grille[i][j] == "💣") {
                cout << "[ ] ";
            }
            else {
                cout << Grille[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// FONCTION : AFFICHER LA GRILLE FINALE
void AfficherGrilleFinale(string** Grille, bool** Drapeaux,int NbrLignes, int NbrColonnes) {//pointeur tableau Grille et Tableau Drapeau
    cout << endl;

    for (int i = 0; i < NbrLignes; i++) {
        for (int j = 0; j < NbrColonnes; j++) {
            if (Grille[i][j] == "💣") {
                cout << "💣 ";
            }
            else if (Drapeaux[i][j]) {
                cout << "🚩 ";
            }
            else {
                cout << Grille[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// FONCTION : RRévéler les case vides voisines
void FloodFill(int x, int y, string** Grille, bool** Drapeaux,int NbrLignes, int NbrColonnes) {
    if (x < 0 || x >= NbrLignes || y < 0 || y >= NbrColonnes)
        return;

    if (Grille[x][y] != "[ ]")
        return;

    if (Drapeaux[x][y])
        return;

    int NumBombs = ObtenirNbrBombe(x, y, Grille, NbrLignes, NbrColonnes);

    if (NumBombs > 0) {
        Grille[x][y] = "[ " + to_string(NumBombs) + " ]";
        return;
    }

    Grille[x][y] = "[.]";

    FloodFill(x + 1, y, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x, y + 1, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x, y - 1, Grille, Drapeaux, NbrLignes, NbrColonnes);

    FloodFill(x + 1, y + 1, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y + 1, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x + 1, y - 1, Grille, Drapeaux, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y - 1, Grille, Drapeaux, NbrLignes, NbrColonnes);
}


// PROGRAMME PRINCIPAL
int main() {
    srand(static_cast<unsigned int>(time(NULL)));

#ifdef _WIN32 //utf-8
    SetConsoleOutputCP(65001);
#endif

    char Rejouer = 'o';

    // BOUCLE PRINCIPALE
    while (Rejouer == 'o' || Rejouer == 'O') {
        int Choix;
        int SizeX;
        int SizeY;
        int mine;

        // CHOISIR LA TAILLE DE LA GRILLE ET LE NOMBRE DE BOMBES
        cout << "Choisis une taille de tableau :" << endl;
        cout << "1) 9/9" << endl;
        cout << "2) 16/16" << endl;
        cout << "3) 30/30" << endl;
        cin >> Choix;

        //Celon le choix j'ai une taille de tableau differente et un nombre de mine
        if (Choix == 1) {
            SizeX = 9;
            SizeY = 9;
            mine = 10;
        }
        else if (Choix == 2) {
            SizeX = 16;
            SizeY = 16;
            mine = 40;
        }
        else if (Choix == 3) {
            SizeX = 30;
            SizeY = 30;
            mine = 99;
        }
        else {
            cout << "Mauvais choix." << endl;
            break;
        }

        //Le NbrLignes/Colonnes devient le choix que j'ai demandé
        int NbrLignes = SizeX;
        int NbrColonnes = SizeY;

        //Initialisation de la grille
        string** Grille = new string*[NbrLignes];

        for (int i = 0; i < NbrLignes; i++)
            Grille[i] = new string[NbrColonnes];

        for (int i = 0; i < NbrLignes; i++) {
            for (int j = 0; j < NbrColonnes; j++)
                Grille[i][j] = "[ ]";
        }

        // Creation Tableau Drapeaux
        bool** Drapeaux = new bool*[NbrLignes];

        for (int i = 0; i < NbrLignes; i++)
            Drapeaux[i] = new bool[NbrColonnes];

        for (int i = 0; i < NbrLignes; i++) {
            for (int j = 0; j < NbrColonnes; j++)
                Drapeaux[i][j] = false;
        }

        // Placement Bombe aléatoire
        int place = 0;

        while (place < mine) {
            int x = rand() % NbrLignes;
            int y = rand() % NbrColonnes;

            if (Grille[x][y] != "💣") {
                Grille[x][y] = "💣";
                place++;
            }
        }

        // État de la partie
        bool PartieTerminee = false;
        bool PremierCoup = true;

        // BOUCLE DE JEU : DEMANDER LES ACTIONS DU JOUEUR
        while (!PartieTerminee) {
            int x, y;
            char flag;

            cout << "Souhaites-tu placer ou retirer un drapeau ? (o/n) ";
            cin >> flag;

            cout << "Choisis une ligne (0 a "
                 << NbrLignes - 1 << ") : ";
            cin >> x;

            cout << "Choisis une colonne (0 a "
                 << NbrColonnes - 1 << ") : ";
            cin >> y;

            // VÉRIFIER LES COORDONNÉES
            if (x < 0 || x >= NbrLignes ||
                y < 0 || y >= NbrColonnes) {
                cout << "Coordonnees invalides !" << endl;
                continue;
            }

            // EMPÊCHER LA MODIFICATION D'UNE CASE DÉJÀ RÉVÉLÉE
            if (Grille[x][y] != "[ ]" &&
                Grille[x][y] != "💣") {
                cout << "Cette case est deja revelee !" << endl;
                continue;
            }

            // POSER OU RETIRER UN DRAPEAU
            if (flag == 'o' || flag == 'O') {
                Drapeaux[x][y] = !Drapeaux[x][y];

                if (Drapeaux[x][y])
                    cout << "Drapeau pose !" << endl;
                else
                    cout << "Drapeau retire !" << endl;

                AfficherGrille(Grille, Drapeaux, NbrLignes, NbrColonnes);
                continue;
            }

            // EMPÊCHER DE RÉVÉLER UNE CASE AVEC UN DRAPEAU
            if (Drapeaux[x][y]) {
                cout << "Retire le drapeau avant de reveler cette case !"
                     << endl;
                continue;
            }


            // GARANTIR QUE LE PREMIER COUP NE TOUCHE PAS DE BOMBE
            if (PremierCoup) {
                PremierCoup = false;

                if (Grille[x][y] == "💣") {
                    Grille[x][y] = "[ ]";

                    int bx, by;

                    do {
                        bx = rand() % NbrLignes;
                        by = rand() % NbrColonnes;
                    } while (Grille[bx][by] == "💣" ||
                             (bx == x && by == y));
                    Grille[bx][by] = "💣";
                }
            }


            // VÉRIFIER SI LE JOUEUR A TOUCHÉ UNE BOMBE
            if (Grille[x][y] == "💣") {
                cout << "BOUM ! Tu as perdu !" << endl;
                cout << "Voici la grille finale :" << endl;

                AfficherGrilleFinale(Grille, Drapeaux, NbrLignes, NbrColonnes);
                PartieTerminee = true;
            }else {
                // RÉVÉLER LA CASE CHOISIE ET LES CASES VIDES VOISINES
                FloodFill(x, y, Grille, Drapeaux, NbrLignes, NbrColonnes);

                // VÉRIFIER S'IL RESTE DES CASES CACHÉES
                int CasesCachees = 0;

                for (int i = 0; i < NbrLignes; i++) {
                    for (int j = 0; j < NbrColonnes; j++) {
                        if (Grille[i][j] == "[ ]")
                            CasesCachees++;
                    }
                }

                // VÉRIFIER LA VICTOIRE ET AFFICHER LA GRILLE
                if (CasesCachees == 0) {
                    cout << "Bravo, tu as gagne !" << endl;

                    AfficherGrilleFinale(Grille, Drapeaux, NbrLignes, NbrColonnes);
                    PartieTerminee = true;
                }
                else {
                    AfficherGrille(
                        Grille, Drapeaux, NbrLignes, NbrColonnes
                    );
                }
            }
        }

        // LIBÉRER LA MÉMOIRE UTILISÉE PAR LA GRILLE ET LES DRAPEAUX
        for (int i = 0; i < NbrLignes; i++)
            delete[] Grille[i];
        delete[] Grille;

        for (int i = 0; i < NbrLignes; i++)
            delete[] Drapeaux[i];
        delete[] Drapeaux;

        // DEMANDER AU JOUEUR S'IL VEUT REJOUER
        cout << "Veux-tu rejouer ? (o/n) : ";
        cin >> Rejouer;
        cout << endl;
    }
    // FIN DU PROGRAMME
    cout << "Merci d'avoir joue !" << endl;
    return 0;
}
