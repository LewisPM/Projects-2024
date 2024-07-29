//for student pml298

#include <iostream>
#include <random>
#include <stdlib.h>
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

struct worldLocation {
    int x = 0;
    int y = 0;
};

class Organism {
    private:
        int breedDays = 0;
        worldLocation location;
        Organism* address;

    public:
        //To figure out, ask Professors or TAs - in setting up virtuals all parameters needed to match in pointer transition, is there another way?
        //How would you solve this problem? Where would you simplify?

        //REQUIRED BIG 3
        virtual ~Organism() { delete address; }
        virtual Organism& operator=(const Organism& rhs) { return *address = *rhs.address; }

        virtual void move(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){};
        virtual void breed(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& doodleBugLog){};
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
        virtual void starve(world& arr, int x, int y, vector <Organism*>& doodleBugLog, vector <Organism*>& deadBugLog){};

};

class Ant : public Organism {
    public:
        void move(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& deadBugLog);
        void breed(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& doodleBugLog);
};

class Doodlebug : public Organism {
    private:
        int daysSinceLastMeal = 0;
    public:
        void move(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& deadBugLog);
        void breed(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& doodleBugLog);
        void starve(world& arr, int x, int y, vector <Organism*>& doodleBugLog, vector <Organism*>& deadBugLog);
        int getDaysSinceLastMeal() const {return daysSinceLastMeal;}
        void incrementDaysSinceLastMeal() { daysSinceLastMeal++; };
        void resetDaysSinceLastMeal() { daysSinceLastMeal = 0; };
};

world generateWorld(vector <Organism*>& doodleLog, vector <Organism*>& antLog);
void printWorld(world& arr);
void simulate(world& arr, vector <Organism*>& doodleLog, vector <Organism*>& antLog, vector <Organism*>& deadBugLog);

int main(){    
    srand(time(0));

    vector <Organism*> doodlebugLog;
    vector <Organism*> antLog;
    vector <Organism*> deadBugLog;

    world world = generateWorld(doodlebugLog, antLog);
    printWorld(world);

    string runAgain;
    getline(cin, runAgain);
    while (runAgain == ""){
        simulate(world, doodlebugLog, antLog, deadBugLog);
        printWorld(world);
        deadBugLog.clear();
        getline(cin, runAgain);
    }
    return 0;
}

void Ant::move(world& arr, int r, int c, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){
    int moveChoice = rand() % 4;
    if (moveChoice == 0) {
        //Ant moves up
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            this->setLocation(r-1, c);
            arr.grid[r-1][c] = ANT;
            arr.grid[r][c] = SPACE;            
        }
    } else if (moveChoice == 1) {
        //Ant moves left
        if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            this->setLocation(r, c-1);
            arr.grid[r][c-1] = ANT;
            arr.grid[r][c] = SPACE; 
        }
    } else if (moveChoice == 2) {
        //Ant moves Down
        if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r + 1][c] == SPACE)){
            this->setLocation(r+1, c);
            arr.grid[r+1][c] = ANT;
            arr.grid[r][c] = SPACE; 
        }
    } else if (moveChoice == 3) {
        //Ant moves right
        if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            this->setLocation(r, c+1);
            arr.grid[r][c+1] = ANT;
            arr.grid[r][c] = SPACE; 
        }
    }
    this->incrementBreedDays();
}

void Ant::breed(world& arr, int r, int c, vector <Organism*>& antLog, vector <Organism*>& doodleBugLog){
    if (this->getBreedDays() >= ANT_BREED_DAYS) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            //baby ant up
            Organism* babyAntPtr = new Ant();
            babyAntPtr->setLocation(r - 1, c);
            babyAntPtr->setAddress(babyAntPtr);
            antLog.push_back(babyAntPtr);
            arr.grid[r-1][c] = ANT;
            this->resetBreedDays();
        } else if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            //baby ant left
            Organism* babyAntPtr = new Ant();
            babyAntPtr->setLocation(r, c - 1);
            babyAntPtr->setAddress(babyAntPtr);
            antLog.push_back(babyAntPtr);
            arr.grid[r][c-1] = ANT;
            this->resetBreedDays();
        } else if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby ant down
            Organism* babyAntPtr = new Ant();
            babyAntPtr->setLocation(r + 1, c);
            babyAntPtr->setAddress(babyAntPtr);
            antLog.push_back(babyAntPtr);
            arr.grid[r+1][c] = ANT;
            this->resetBreedDays();
        } else if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby ant right
            Organism* babyAntPtr = new Ant();
            babyAntPtr->setLocation(r, c + 1);
            babyAntPtr->setAddress(babyAntPtr);
            antLog.push_back(babyAntPtr);
            arr.grid[r][c+1] = ANT;
            this->resetBreedDays();
        } else {
            this->incrementBreedDays();
        }
    }
}

void Doodlebug::move(world& arr, int r, int c, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){
    //Priority One - Eat Ant
    if (arr.grid[r - 1][c] == ANT){
        //move up and eat ant
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == (r - 1)) && (antY == c)){
                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) 
                    antLog.erase(antLog.begin()+iter);
                else 
                    antLog.pop_back();
                deadBugLog.push_back(deadAnt);
                break;
            }
            iter++;
        }
        this->setLocation(r-1, c);
        arr.grid[r-1][c] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c - 1] == ANT){
        //move left and eat ant
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == r) && (antY == (c - 1))){
                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) 
                    antLog.erase(antLog.begin()+iter);
                else 
                    antLog.pop_back();
                deadBugLog.push_back(deadAnt);
                break;
            }
            iter++;
        }
        this->setLocation(r, c-1);
        arr.grid[r][c-1] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r + 1][c] == ANT){
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == (r + 1)) && (antY == c)){
                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) 
                    antLog.erase(antLog.begin()+iter);
                else 
                    antLog.pop_back();
                deadBugLog.push_back(deadAnt);
                break;
            }
            iter++;
        }
        this->setLocation(r+1, c);
        arr.grid[r+1][c] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c + 1] == ANT){
        //move right and eat ant
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == r) && (antY == (c + 1))){
                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) 
                    antLog.erase(antLog.begin()+iter);
                else 
                    antLog.pop_back();
                deadBugLog.push_back(deadAnt);
                break;
            }
            iter++;
        }
        this->setLocation(r, c+1);
        arr.grid[r][c+1] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else {
        int moveChoice = rand() % 4;
        if (moveChoice == 0) {
            //move doodle up
            if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
                this->setLocation(r-1, c);
                arr.grid[r-1][c] = DOODLEBUG;
                arr.grid[r][c] = SPACE;
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == 1) {
            //move doodle left
            if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
                this->setLocation(r, c-1);
                arr.grid[r][c-1] = DOODLEBUG;
                arr.grid[r][c] = SPACE;
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == 2) {
            //move doodle down
            if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r+1][c] == SPACE)){
                this->setLocation(r+1, c);
                arr.grid[r+1][c] = DOODLEBUG;
                arr.grid[r][c] = SPACE; 
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == 3) {
            //move doodle right
            if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
                this->setLocation(r, c+1);
                arr.grid[r][c+1] = DOODLEBUG;
                arr.grid[r][c] = SPACE; 
                this->incrementDaysSinceLastMeal();
            }
        }
    }
    this->incrementBreedDays();
}

//TO DO: Investigate getLocation x an y values and why some are showing up negative - ortherwise done!
void Doodlebug::breed(world& arr, int r, int c, vector <Organism*>& antLog, vector <Organism*>& doodleBugLog){
    if (this->getBreedDays() >= DOODLE_BREED_DAYS) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            //baby doodle up
            Organism* babyDoodlePtr = new Doodlebug();
            babyDoodlePtr->setLocation(r - 1, c);
            babyDoodlePtr->setAddress(babyDoodlePtr);
            doodleBugLog.push_back(babyDoodlePtr);
            arr.grid[r-1][c] = DOODLEBUG;
            this->resetBreedDays();
        } else if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            //baby doodle left
            Organism* babyDoodlePtr = new Doodlebug();
            babyDoodlePtr->setLocation(r, c - 1);
            babyDoodlePtr->setAddress(babyDoodlePtr);
            doodleBugLog.push_back(babyDoodlePtr);
            arr.grid[r][c-1] = DOODLEBUG;
            this->resetBreedDays();
        } else if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r + 1][c] == SPACE)){
            //baby doodle down
            Organism* babyDoodlePtr = new Doodlebug();
            babyDoodlePtr->setLocation(r + 1, c);
            babyDoodlePtr->setAddress(babyDoodlePtr);
            doodleBugLog.push_back(babyDoodlePtr);
            arr.grid[r+1][c] = DOODLEBUG;
            this->resetBreedDays();
        } else if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            //baby doodle right
            Organism* babyDoodlePtr = new Doodlebug();
            babyDoodlePtr->setLocation(r, c + 1);
            babyDoodlePtr->setAddress(babyDoodlePtr);
            doodleBugLog.push_back(babyDoodlePtr);
            arr.grid[r][c+1] = DOODLEBUG;
            this->resetBreedDays();
        } else {
            this->incrementBreedDays();
        }
    }
}

void Doodlebug::starve(world& arr, int r, int c, vector <Organism*>& doodleBugLog, vector <Organism*>& deadBugLog){
    if (this->getDaysSinceLastMeal() == DOODLE_STARVE_DAYS) {
        //cout<<"Doodle at ["<<this->getLocation().x<<", "<<this->getLocation().y<<"] will die of starvation. ("<<this->getDaysSinceLastMeal()<<")"<<endl;
        arr.grid[r][c] = SPACE;
        for (int i = 0; i < doodleBugLog.size(); i++){
            Organism* deadDoodle = doodleBugLog[i];
            if ((doodleBugLog[i]->getAddress() == this->getAddress()) && (doodleBugLog[i] != doodleBugLog[doodleBugLog.size() - 1])){
                doodleBugLog.erase(doodleBugLog.begin()+i);
            } else {
                doodleBugLog.pop_back();
            }
            deadBugLog.push_back(deadDoodle);
            break;
        }
    }
}

world generateWorld(vector <Organism*>& doodleLog, vector <Organism*>& antLog) {
    world arr;
    for (int i = 0; i < MAX_GRID_SIZE; i++){
        for (int i2 = 0; i2 < MAX_GRID_SIZE; i2++)
            arr.grid[i][i2] = SPACE;
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
        for (int c = 0; c < MAX_GRID_SIZE; c++)
            cout<<arr.grid[r][c];
        cout<<endl;
    }
    cout<<endl<<"Press ENTER to continue simulation...";
};

void simulate(world& arr, vector <Organism*>& doodleLog, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){
    //Doodles go first
    for (int i = 0; i < doodleLog.size(); i++) {
        int doodleX = doodleLog[i]->getLocation().x;
        int doodleY = doodleLog[i]->getLocation().y;
        doodleLog[i]->move(arr, doodleX, doodleY, antLog, deadBugLog);
        doodleLog[i]->breed(arr, doodleX, doodleY, antLog, doodleLog);
        doodleLog[i]->starve(arr, doodleX, doodleY, doodleLog, deadBugLog);
    }
    for (int i = 0; i < antLog.size(); i++) {
        int antX = antLog[i]->getLocation().x;
        int antY = antLog[i]->getLocation().y;
        antLog[i]->move(arr, antX, antY, antLog, doodleLog);
        antLog[i]->breed(arr, antX, antY, antLog, doodleLog);
    }
    arr.days++;
}