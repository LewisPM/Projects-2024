//for student pml298

#include <iostream>
#include <random>
#include <time.h>

using namespace std;

const int MAX_GRID_SIZE = 20;
const char DOODLEBUG = 'X';
const int DOODLE_COUNT = 5;
const char ANT = 'o';
const int ANT_COUNT = 100;
const char SPACE = '-';

char* generateWorld(int gridSize, int doodleCount, int antCount);

class Organism {
    private:
        char symbol = SPACE;
        int ageInDays = 0;
    public:
        virtual void step(int& grid);
        virtual void breed(int& grid);
};

class Ant : public Organism {
    private:
        char symbol = ANT;
    public:
        void step(int& grid);
        void breed(int& grid);
};

class Doodlebug : public Organism {
    private:
        char symbol = DOODLEBUG;
        int daysSinceLastMeal = 0;
    public:
        void step(int& grid);
        void breed(int& grid);
        void starve(int& grid);
};

int main(){
    int days = 0;
    return 0;
}

char* generateWorld(int gridSize, int doodleCount, int antCount) {
    char* arr = new char[gridSize];
    char secondDimension[gridSize] = {SPACE};

    srand(time(0));
    int randoNum = rand() % 19;
    int x = doodleCount;
    int y = antCount;

    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; r < gridSize; r++) {
            //cout<<*arr[r][c].getSymbol();
            //cout<<arr[r][c];
        }
        
        cout<<endl;
    }
    return arr;
}