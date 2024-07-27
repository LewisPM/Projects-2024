//for student pml298

#include <iostream>
#include <random>
#include <time.h>

using namespace std;

const int MAX_GRID_SIZE = 20;

const char DOODLEBUG = 'X';
const char ANT = 'o';
const char SPACE = '-';

const int DOODLE_COUNT = 5;
const int ANT_COUNT = 100;

const int DOODLE_BREED_DAYS = 8;
const int ANT_BREED_DAYS = 3;

const int DOODLE_STARVE_DAYS = 3;

struct world {
    int days = 0;
    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
};

class Organism {
    private:
        char symbol = SPACE;
        int ageInDays = 0;
    public:
        virtual void move(world& grid);
        virtual void breed(world& grid);
        virtual int getSymbol() const {return symbol;}
        virtual int getAge() const {return ageInDays;}
};

class Ant : public Organism {
    private:
        char symbol = ANT;
    public:
        void move(world& grid);
        void breed(world& grid);
};

class Doodlebug : public Organism {
    private:
        char symbol = DOODLEBUG;
        int daysSinceLastMeal = 0;
    public:
        void move(world& grid);
        void breed(world& grid);
        void starve(world& grid);
};

world generateWorld(int gridSize, int doodleCount, int antCount);
void printWorld(world& arr);
void simulate(world& arr);

int main(){    
    srand(time(0));
    world world = generateWorld(MAX_GRID_SIZE, DOODLE_COUNT, ANT_COUNT);
    printWorld(world);
    string runAgain;
    getline(cin, runAgain);
    while (runAgain == ""){
        simulate(world);
        printWorld(world);
        getline(cin, runAgain);
    }
    return 0;
}

world generateWorld(int gridSize, int doodleCount, int antCount) {
    world arr;
    for (int i = 0; i < gridSize; i++){
        for (int i2 = 0; i2 < gridSize; i2++){
            arr.grid[i][i2] = SPACE;
        }
    }

    int x = 0, y = 0;

    while (x < doodleCount) {
        int randoNumX = rand() % (gridSize - 1);
        int randoNumY = rand() % (gridSize - 1);
        if (arr.grid[randoNumX][randoNumY] == SPACE) {
            arr.grid[randoNumX][randoNumY] = DOODLEBUG;
            x++;
        }
    }
    while (y < antCount) {
        int randoNumX = rand() % (gridSize - 1);
        int randoNumY = rand() % (gridSize - 1);
        if (arr.grid[randoNumX][randoNumY] == SPACE) {
            arr.grid[randoNumX][randoNumY] = ANT;
            y++;
        }
    }
    return arr;
}

void printWorld(world& arr){
    cout<<endl<<"World Days: "<<arr.days<<endl;
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            cout<<arr.grid[r][c];
        }
        cout<<endl;
    }
    cout<<"Press ENTER to continue simulation...";
};

void simulate(world& arr){
    for (int x = 0; x < MAX_GRID_SIZE; x++){
        for (int y = 0; y < MAX_GRID_SIZE; y++){
            if (arr.grid[x][y] == ANT){
                //do ant things
            }
            if (arr.grid[x][y] == DOODLEBUG){
                //do doodlebug things
            }
        }
    }
}