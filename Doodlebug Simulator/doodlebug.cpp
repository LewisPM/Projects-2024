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

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;


struct world {
    int days = 0;
    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
};

struct worldLocation {
    int x = 0;
    int y = 0;
};

class Organism {
    private:
        int breedDays = 0;
        worldLocation location;
        Organism* address = nullptr;

    public:
        virtual void move(world& arr, int x, int y){};
        virtual void breed(world& arr, int x, int y){};
        virtual int getBreedDays() const { return breedDays; }
        virtual void incrementBreedDays() { breedDays++; }
        virtual void resetBreedDays() { breedDays = 0; }
        virtual worldLocation getLocation() { return location; }
        virtual void setLocation(int x, int y) {
            location.x = x;
            location.y = y;
        }
        virtual Organism* getAddress() { return address; }
        virtual void setAddress(Organism* newAddress) { address = newAddress; }
};

class Ant : public Organism {
    public:
        void move(world& arr, int x, int y);
        void breed(world& arr, int x, int y);
};

class Doodlebug : public Organism {
    private:
        int daysSinceLastMeal = 0;
    public:
        void move(world& arr, int x, int y);
        void breed(world& arr, int x, int y);
        void starve(world& arr, int x, int y);
        int getDaysSinceLastMeal() const {return daysSinceLastMeal;}
        void incrementDaysSinceLastMeal() { daysSinceLastMeal++; };
        void resetDaysSinceLastMeal() { daysSinceLastMeal = 0; };
};

world generateWorld(vector <Organism*>& doodleLog, vector <Organism*>& antLog);
void printWorld(world& arr);
void simulate(world& arr);

int main(){    
    srand(time(0));

    vector <Organism*> doodlebugLog;
    vector <Organism*> antLog;

    //WORKS
    /*
    Organism*  antPtr = new Ant();
    cout<<"Address of Ptr: "<<&antPtr<<endl;
    cout<<"Ptr "<<antPtr<<endl;

    Organism*  antPtr = new Ant();
    antLog.push_back(antPtr);
    cout<<antLog[0]<<endl;
    */

    world world = generateWorld(doodlebugLog, antLog);

    //WORKS
    /*
    for (auto i: doodlebugLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }
    */

    printWorld(world);
    string runAgain;
    getline(cin, runAgain);
    while (runAgain == ""){
        simulate(world);
        printWorld(world);
        
        //WORKS
        //antPtr->move(world, 0, 0);

        getline(cin, runAgain);
    }

    return 0;
}

void Ant::move(world& arr, int r, int c){
    cout<<"Moving!"<<endl;
    int moveChoice = rand() % 3;
    if (moveChoice == UP) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            //move ant up
        }
    } else if (moveChoice == LEFT) {
        if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            //move ant left
        }
    } else if (moveChoice == DOWN) {
        if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //move ant down
        }
    } else if (moveChoice == RIGHT) {
        if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //move ant right
        }
    }
    this->incrementBreedDays();
}

void Ant::breed(world& arr, int r, int c){
    if (this->getBreedDays() >= 3) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            //baby ant up
            this->resetBreedDays();
        } else if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            //baby ant left
            this->resetBreedDays();
        } else if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby ant down
            this->resetBreedDays();
        } else if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby ant right
            this->resetBreedDays();
        } else {
            this->incrementBreedDays();
        }
    }
}

void Doodlebug::move(world& arr, int r, int c){
    //Priority One - Eat Ant
    if (arr.grid[r - 1][c] == ANT){
        //move up and eat ant
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c - 1] == ANT){
        //move left and eat ant
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c + 1] == ANT){
        //move down and eat ant
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c + 1] == ANT){
        //move right and eat ant
        this->resetDaysSinceLastMeal();
    } else {
        int moveChoice = rand() % 3;
        if (moveChoice == UP) {
            if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
                //move bug up
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == LEFT) {
            if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
                //move bug left
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == DOWN) {
            if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
                //move bug down
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == RIGHT) {
            if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
                //move bug right
                this->incrementDaysSinceLastMeal();
            }
        }
    }
    this->incrementBreedDays();
}

void Doodlebug::breed(world& arr, int r, int c){
    if (this->getBreedDays() >= 8) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            //baby bug up
            this->resetBreedDays();
        } else if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            //baby bug left
            this->resetBreedDays();
        } else if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby bug down
            this->resetBreedDays();
        } else if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby bug right
            this->resetBreedDays();
        } else {
            this->incrementBreedDays();
        }
    }
}

void Doodlebug::starve(world& arr, int r, int c){
    if (this->getDaysSinceLastMeal() == 3) {
        //bugs dies
    }
}

world generateWorld(vector <Organism*>& doodleLog, vector <Organism*>& antLog) {
    world arr;
    for (int i = 0; i < MAX_GRID_SIZE; i++){
        for (int i2 = 0; i2 < MAX_GRID_SIZE; i2++){
            arr.grid[i][i2] = SPACE;
        }
    }

    int x = 0, y = 0;

    while (x < DOODLE_COUNT) {
        int randoNumX = rand() % (MAX_GRID_SIZE - 1);
        int randoNumY = rand() % (MAX_GRID_SIZE - 1);
        if (arr.grid[randoNumX][randoNumY] == SPACE) {
            arr.grid[randoNumX][randoNumY] = DOODLEBUG;
            Organism* tempDoodlePtr = new Doodlebug();
            tempDoodlePtr->setLocation(randoNumX, randoNumY);
            tempDoodlePtr->setAddress(tempDoodlePtr);
            doodleLog.push_back(tempDoodlePtr);
            x++;
        }
    }
    while (y < ANT_COUNT) {
        int randoNumX = rand() % (MAX_GRID_SIZE - 1);
        int randoNumY = rand() % (MAX_GRID_SIZE - 1);
        if (arr.grid[randoNumX][randoNumY] == SPACE) {
            arr.grid[randoNumX][randoNumY] = ANT;
            Organism* tempAntPtr = new Ant();
            tempAntPtr->setLocation(randoNumX, randoNumY);
            tempAntPtr->setAddress(tempAntPtr);
            antLog.push_back(tempAntPtr);
            y++;
        }
    }
    return arr;
}

void printWorld(world& arr){
    cout<<endl<<"World Days: "<<arr.days<<endl<<endl;
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            cout<<arr.grid[r][c];
        }
        cout<<endl;
    }
    cout<<endl<<"Press ENTER to continue simulation...";
};

void simulate(world& arr){
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            if (arr.grid[r][c] == ANT){
                //do ant things
            }
            if (arr.grid[r][c] == DOODLEBUG){
                //do doodlebug things
            }
        }
    }
}