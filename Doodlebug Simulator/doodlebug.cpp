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
struct twoDArray {
    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
};
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

twoDArray generateWorld(int gridSize, int doodleCount, int antCount);
void printWorld(twoDArray& arr);

int main(){
    int days = 0;
    
    twoDArray world = generateWorld(MAX_GRID_SIZE, DOODLE_COUNT, ANT_COUNT);
    printWorld(world);

    return 0;
}

twoDArray generateWorld(int gridSize, int doodleCount, int antCount) {

    twoDArray arr;
    for (int i = 0; i < gridSize; i++){
        for (int i2 = 0; i2 < gridSize; i2++){
            arr.grid[i][i2] = SPACE;
        }
    }

    int spaceCount = gridSize * gridSize;
    int goal = spaceCount - (doodleCount + antCount);
    int x = 0, y = 0;
    srand(time(0));

    while (spaceCount > goal){
        cout<<"spaceCount: "<<spaceCount<<endl;
        cout<<"goal: "<<spaceCount - (doodleCount + antCount)<<endl;
        while (x < doodleCount) {
            int randoNumX = rand() % (gridSize - 1);
            int randoNumY = rand() % (gridSize - 1);
            if (arr.grid[randoNumX][randoNumY] == SPACE) {
                arr.grid[randoNumX][randoNumY] = DOODLEBUG;
                x++;
                spaceCount--;
            }
        }
        while (y < antCount) {
            int randoNumX = rand() % (gridSize - 1);
            int randoNumY = rand() % (gridSize - 1);
            if (arr.grid[randoNumX][randoNumY] == SPACE) {
                arr.grid[randoNumX][randoNumY] = ANT;
                y++;
                spaceCount--;
            }
        }
    }
    return arr;
}

void printWorld(twoDArray& arr){
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            cout<<arr.grid[r][c];
        }
        cout<<endl;
    }
};