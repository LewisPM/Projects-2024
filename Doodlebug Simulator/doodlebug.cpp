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
        Organism* address;

    public:
        //To figure out, ask Professors or TAs - in setting up virtuals all parameters needed to match in pointer transition, is there another way?
        //How would you solve this problem? Where would you simplify?

        //REQUIRED BIG 3
        virtual ~Organism() { delete address; }
        virtual Organism& operator=(const Organism& rhs) { return *address = *rhs.address; }

        virtual void move(world& arr, int x, int y, vector <Organism*> antLog){};
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
        virtual void starve(world& arr, int x, int y){};

};

class Ant : public Organism {
    public:
        void move(world& arr, int x, int y, vector <Organism*> antLog);
        void breed(world& arr, int x, int y);
};

class Doodlebug : public Organism {
    private:
        int daysSinceLastMeal = 0;
    public:
        void move(world& arr, int x, int y, vector <Organism*> antLog);
        void breed(world& arr, int x, int y);
        void starve(world& arr, int x, int y);
        int getDaysSinceLastMeal() const {return daysSinceLastMeal;}
        void incrementDaysSinceLastMeal() { daysSinceLastMeal++; };
        void resetDaysSinceLastMeal() { daysSinceLastMeal = 0; };
};

world generateWorld(vector <Organism*>& doodleLog, vector <Organism*>& antLog);
void printWorld(world& arr);
void simulate(world& arr, vector <Organism*>& doodleLog, vector <Organism*>& antLog);

int main(){    
    srand(time(0));

    vector <Organism*> doodlebugLog;
    vector <Organism*> antLog;
    vector <Organism*> deadBugLog;

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

   /*
    for (auto i: antLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }
    */
   for (auto i: antLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }
    int iter = 0;
    for (auto i: antLog){
        if ((i->getLocation().x == 0)) {
            cout<<"Deleting..."<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
            Organism* temper = i;
            antLog.erase(antLog.begin()+iter);
            //delete i;
            cout<<temper<<endl;
            deadBugLog.push_back(temper);
        }
        iter++;
    }
    /*
    for (auto i: antLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }*/
   cout<<"DEAD BUGS: "<<endl;
    for (auto i: deadBugLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }
    deadBugLog.clear();
    cout<<"DEAD BUGS AFTER FLUSH: "<<endl;
    for (auto i: deadBugLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
    }

    //printWorld(world);
    string runAgain;
    getline(cin, runAgain);
    while (runAgain == ""){
        /*
        for (auto i: antLog){
        cout<<i<<": ";
        cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
        }
        */
        //simulate(world, doodlebugLog, antLog);
        //printWorld(world);
        getline(cin, runAgain);
    }

    return 0;
}

void Ant::move(world& arr, int r, int c, vector <Organism*> antLog){
    int moveChoice = rand() % 3;
    if (moveChoice == UP) {
        if (((r - 1) >= 0) && (arr.grid[r - 1][c] == SPACE)){
            this->setLocation(r-1, c);
            arr.grid[r-1][c] = ANT;
            arr.grid[r][c] = SPACE;            
        }
    } else if (moveChoice == LEFT) {
        if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
            this->setLocation(r, c-1);
            arr.grid[r][c-1] = ANT;
            arr.grid[r][c] = SPACE; 
        }
    } else if (moveChoice == DOWN) {
        if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r + 1][c] == SPACE)){
            this->setLocation(r+1, c);
            arr.grid[r+1][c] = ANT;
            arr.grid[r][c] = SPACE; 
        }
    } else if (moveChoice == RIGHT) {
        if (((c + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
            this->setLocation(r, c+1);
            arr.grid[r][c+1] = ANT;
            arr.grid[r][c] = SPACE; 
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

void Doodlebug::move(world& arr, int r, int c, vector <Organism*> antLog){
    //Priority One - Eat Ant
    if (arr.grid[r - 1][c] == ANT){
        //move up and eat ant
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == r) && (antY == c)){
                //"I am the ant you seek"
                delete i;
                i = nullptr;
                antLog.erase(antLog.begin()+iter);
            }
            iter++;
        }
        this->setLocation(r-1, c);
        arr.grid[r-1][c] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
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
                this->setLocation(r-1, c);
                arr.grid[r-1][c] = DOODLEBUG;
                arr.grid[r][c] = SPACE;
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == LEFT) {
            if (((c - 1) >= 0) && (arr.grid[r][c - 1] == SPACE)){
                this->setLocation(r, c-1);
                arr.grid[r][c-1] = DOODLEBUG;
                arr.grid[r][c] = SPACE;
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == DOWN) {
            if (((r + 1) < MAX_GRID_SIZE) && (arr.grid[r][c + 1] == SPACE)){
                this->setLocation(r+1, c);
                arr.grid[r+1][c] = DOODLEBUG;
                arr.grid[r][c] = SPACE; 
                this->incrementDaysSinceLastMeal();
            }
        } else if (moveChoice == RIGHT) {
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
            
            /*Consider second version of implementation where
            Organism call generates organism on the heap
            then has the big 3 set-up for Organism* address;
            1. Organism (): address (new Organism())
            2. ~Organism() { delete address; }
            3. Organism (const Organism& rhs) { *address = *rhs.address } (copy constructor)
            4. Organism& operator=(const Organism& rhs) { *address = *rhs.address } (To make it possible for Organisms to equal other organisms)*/
            /*
            Doodlebug tempDoodle = Doodle(randoNumX, randoNumY);
            Organism* tempDoodlePtr = tempDoodle.getAddress();
            doodleLog.push_back(tempDoodlePtr);
            */
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

void simulate(world& arr, vector <Organism*>& doodleLog, vector <Organism*>& antLog){
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            if (arr.grid[r][c] == ANT){
                for (auto i: antLog){
                    int antX = i->getLocation().x;
                    int antY = i->getLocation().y;
                    if ((antX == r) && (antY == c)){
                        //"I am the ant you seek"
                        i->move(arr, antX, antY, antLog);
                        i->breed(arr, antX, antY);
                    }
                }
            }
            if (arr.grid[r][c] == DOODLEBUG){
                for (auto i: doodleLog){
                    int doodleX = i->getLocation().x;
                    int doodleY = i->getLocation().y;
                    if ((doodleX == r) && (doodleY == c)){
                        //"I am the doodle you seek"
                        i->move(arr, doodleX, doodleY, antLog);
                        i->breed(arr, doodleX, doodleY);
                        i->starve(arr, doodleX, doodleY);
                    }
                }
            }
        }
    }
    arr.days++;
}