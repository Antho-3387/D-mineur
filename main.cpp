#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    int NbrRaws = 10;
    int NbrColumns = 10;
    int* Grid = new int[NbrRaws * NbrColumns];

    for (int X = 0; X < NbrRaws; X++) {
        for (int Y = 0; Y < NbrColumns; Y++) {
            int INDEX = X * NbrColumns + Y;
            Grid[INDEX] = 0;
        }
    }
    Grid[54] = 1;
    Grid[55] = 1;
    Grid[56] = 1;
    auto TimePoint = std::chrono::steady_clock::now();
    bool IsSimulating = true;
    int NbrIteration = 0;

    while (IsSimulating) {
        auto SecondTimePoint = std::chrono::steady_clock::now();
        auto Duration = SecondTimePoint - TimePoint;
        auto Time = std::chrono::duration_cast<std::chrono::seconds>(Duration);
        if (Time.count() >= 2) {
            TimePoint = std::chrono::steady_clock::now();
            int* TempGrid = new int[NbrRaws * NbrColumns];
            for (int X = 0; X < NbrRaws; X++) {
                for (int Y = 0; Y < NbrColumns; Y++) {
                    int NeighborsAliveCount = 0;
                    for (int NeighborX = X - 1; NeighborX <= X + 1; NeighborX++) {
                        for (int NeighborY = Y - 1; NeighborY <= Y + 1; NeighborY++) {

                            bool IsOutside =
                                NeighborX < 0 ||
                                NeighborX >= NbrRaws ||
                                NeighborY < 0 ||
                                NeighborY >= NbrColumns;

                            bool IsSelf = NeighborX == X && NeighborY == Y;

                            if (!IsOutside && !IsSelf) {
                                int NeighborIndex = NeighborX * NbrColumns + NeighborY;

                                if (Grid[NeighborIndex] == 1) {
                                    NeighborsAliveCount++;
                                }
                            }
                        }
                    }

                    int CellIndex = X * NbrColumns + Y;

                    if (Grid[CellIndex] == 1) {
                        if (NeighborsAliveCount < 2 || NeighborsAliveCount > 3) {
                            TempGrid[CellIndex] = 0;
                        }
                        else {
                            TempGrid[CellIndex] = 1;
                        }
                    }
                    else {
                        if (NeighborsAliveCount == 3) {
                            TempGrid[CellIndex] = 1;
                        }
                        else {
                            TempGrid[CellIndex] = 0;
                        }
                    }
                }
            }
            for (int X = 0; X < NbrRaws; X++) {
                for (int Y = 0; Y < NbrColumns; Y++) {
                    int CellIndex = X * NbrColumns + Y;
                    Grid[CellIndex] = TempGrid[CellIndex];
                }
            }

            delete[] TempGrid;

            std::cout << "\033[2J\033[H";

            for (int X = 0; X < NbrRaws; X++) {
                for (int Y = 0; Y < NbrColumns; Y++) {
                    int CellIndex = X * NbrColumns + Y;

                    if (Grid[CellIndex] == 1) {
                        std::cout << "[]";
                    }
                    else {
                        std::cout << "--";
                    }
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
            NbrIteration++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    delete[] Grid;

    return 0;
}
