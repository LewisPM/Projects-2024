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
        void move(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& deadBugLog);
        void breed(world& arr, int x, int y);
};

class Doodlebug : public Organism {
    private:
        int daysSinceLastMeal = 0;
    public:
        void move(world& arr, int x, int y, vector <Organism*>& antLog, vector <Organism*>& deadBugLog);
        void breed(world& arr, int x, int y);
        void starve(world& arr, int x, int y);
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
        
        cout<<"DEAD BUGS: "<<endl;
        for (auto i: deadBugLog){
            cout<<i<<": ";
            cout<<"["<<i->getLocation().x<<", "<<i->getLocation().y<<"]"<<endl;
        }
        
        deadBugLog.clear();
        getline(cin, runAgain);
    }

    return 0;
}

//DONE!
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

//TO DO: Finish Ant breed()
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

//TO DO: Correct Doodlebug move()
void Doodlebug::move(world& arr, int r, int c, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){
    //Priority One - Eat Ant
    cout<<"I am doodle at "<<r<<", "<<c<<endl;
    if (arr.grid[r - 1][c] == ANT){
        cout<<"There is an ant above me."<<endl;
        //move up and eat ant
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == (r - 1)) && (antY == c)){
                //"I am the ant you seek"
                cout<<"I'm ant at iter: "<<iter<<endl;

                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) {
                    antLog.erase(antLog.begin()+iter);
                }
                else {
                    antLog.pop_back();
                }
                deadBugLog.push_back(deadAnt);
                cout<<"I've added ant to deathlog - now I should exit..."<<endl;
                break;
            }
            iter++;
        }
        cout<<"I am doodle at "<<r<<", "<<c<<" and I have eaten, time to move"<<endl;
        this->setLocation(r-1, c);
        arr.grid[r-1][c] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c - 1] == ANT){
        //move left and eat ant
        cout<<"There is an ant left of me."<<endl;
        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == r) && (antY == (c - 1))){
                //"I am the ant you seek"
                                cout<<"I'm ant at iter: "<<iter<<endl;

                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) {
                    antLog.erase(antLog.begin()+iter);
                }
                else {
                    antLog.pop_back();
                }
                deadBugLog.push_back(deadAnt);
                                cout<<"I've added ant to deathlog - now I should exit..."<<endl;

                break;
            }
            iter++;
        }
                cout<<"I am doodle at "<<r<<", "<<c<<" and I have eaten, time to move"<<endl;

        this->setLocation(r, c-1);
        arr.grid[r][c-1] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r + 1][c] == ANT){
        //move down and eat ant
                cout<<"There is an ant below me."<<endl;

        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == (r + 1)) && (antY == c)){
                //"I am the ant you seek"
                                cout<<"I'm ant at iter: "<<iter<<endl;

                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) {
                    antLog.erase(antLog.begin()+iter);
                }
                else {
                    antLog.pop_back();
                }
                deadBugLog.push_back(deadAnt);
                                cout<<"I've added ant to deathlog - now I should exit..."<<endl;

                break;
            }
            iter++;
        }
                cout<<"I am doodle at "<<r<<", "<<c<<" and I have eaten, time to move"<<endl;

        this->setLocation(r+1, c);
        arr.grid[r+1][c] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else if (arr.grid[r][c + 1] == ANT){
        //move right and eat ant
                cout<<"There is an ant right of me."<<endl;

        int iter = 0;
        for (auto i: antLog){
            int antX = i->getLocation().x;
            int antY = i->getLocation().y;
            if ((antX == r) && (antY == (c + 1))){
                //"I am the ant you seek"
                                cout<<"I'm ant at iter: "<<iter<<endl;

                Organism* deadAnt = i;
                if (iter != (antLog.size() - 1)) {
                    antLog.erase(antLog.begin()+iter);
                }
                else {
                    antLog.pop_back();
                }
                deadBugLog.push_back(deadAnt);
                                cout<<"I've added ant to deathlog - now I should exit..."<<endl;

                break;
            }
            iter++;
        }
                cout<<"I am doodle at "<<r<<", "<<c<<" and I have eaten, time to move"<<endl;

        this->setLocation(r, c+1);
        arr.grid[r][c+1] = DOODLEBUG;
        arr.grid[r][c] = SPACE;
        this->resetDaysSinceLastMeal();
    } else {
        //DONE!
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

//TO DO: Complete doodlebug breed()
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

//TO DO: Complete Doodlebug Starve()
void Doodlebug::starve(world& arr, int r, int c){
    if (this->getDaysSinceLastMeal() == 3) {
        //bugs dies
    }
}

//DONE!
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

//DONE!
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

void simulate(world& arr, vector <Organism*>& doodleLog, vector <Organism*>& antLog, vector <Organism*>& deadBugLog){
    for (int r = 0; r < MAX_GRID_SIZE; r++){
        for (int c = 0; c < MAX_GRID_SIZE; c++){
            if (arr.grid[r][c] == ANT){
                for (auto i: antLog){
                    int antX = i->getLocation().x;
                    int antY = i->getLocation().y;
                    if ((antX == r) && (antY == c)){
                        i->move(arr, antX, antY, antLog, deadBugLog);
                        i->breed(arr, antX, antY);
                    }
                }
            }
            if (arr.grid[r][c] == DOODLEBUG){
                for (auto i: doodleLog){
                    int doodleX = i->getLocation().x;
                    int doodleY = i->getLocation().y;
                    if ((doodleX == r) && (doodleY == c)){
                        i->move(arr, doodleX, doodleY, antLog, deadBugLog);
                        i->breed(arr, doodleX, doodleY);
                        i->starve(arr, doodleX, doodleY);
                    }
                }
            }
        }
    }
    arr.days++;
}