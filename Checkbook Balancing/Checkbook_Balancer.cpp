//Submission for HW12 Student: pml298

/*Read in via iostream: 
    1. Number of each check
    2. Amount of the check
    3. Cashed? Bool 1/0

    4. the deposits
    5. Old and new account balance
*/

/*Use a "Check" class array*/

/*The class CHECK contains: 
    1. the 3 read-in info items, check no., amt and cashed?Y/N
        ~the check amount is of type, class Money (See Display 11.9)
    2. should have setters and getters, constructors and functions for i/o of a check
        */

/* Should output: 
    1. the total of the checks cashed
    2. the total deposits
    3. what the new balance should be
    4. how much the figure differes from what the bank says
    5. two lists of checks:
        a. the ones cashed since the last balance
        b. the ones not cashed 
        *. display the checks sorted from low-high*/

#include <iostream>
#include <vector>
using namespace std;

//Classes
class Money {
    private:
        long total_in_cents;
    public:
        Money(long dollars, int cents);
        Money(long dollars);
        Money();
        double getValue();
};
class Check {
    public:
        int checkNum;
        double amount;
        bool cashed;
        Check(int checkNum, double amount, bool cashed);
        double getAmt() const { return amount; }
        int getNum() const { return checkNum; }
};

//Functions
Check getCheck();

//Main
int main() {
    vector <Check> checks;
    //Check checkOne(9, 5, 0), checkTwo(10, 7, 0);
    //checks.push_back(checkOne);
    //checks.push_back(checkOne);
    
    bool addAnotherCheck;
    cout<<"Adding a check? (1 for yes, 0 for no): ";
    cin>>addAnotherCheck;
    while (addAnotherCheck == true) {
        Check temp = getCheck();
        if (temp.getNum() >= 1) {
            checks.push_back(temp);
        }
        cout<<"Adding another check? (1 for yes, 0 for no): ";
        cin>>addAnotherCheck;
    }

    for (Check i : checks) {
        cout<<"Check No. "<<i.getNum()<<": "<<i.getAmt()<<endl;
    }
    
    
    return 0;
}

//Methods
double Money::getValue() {
    return total_in_cents / 100.0;
}

Money::Money(long dollars, int cents){
    if (dollars < 0 || cents < 0) {
        cout<<"Dollars & cents values should be greater than or equal to 0."<<endl;
        exit(1);
    }
    total_in_cents = (dollars * 100) + cents;
}

Money::Money(long dollars){
    if (dollars < 0) {
        cout<<"Dollars value should be greater than or equal to 0."<<endl;
        exit(1);
    }
    total_in_cents = (dollars * 100);
}

Money::Money(){
    total_in_cents = 0;
}

Check::Check(int checkNum, double amount, bool cashed){
    try {
        if (checkNum < 1) {
            throw(checkNum);
        } else if (amount < 1){
            throw(amount);
        } else {
            this->checkNum = checkNum;
            this->amount = amount;
            this->cashed = cashed;
        }
    }
    catch (int checkNum) {
        cout<<"Check number must be greater than 0."<<endl;
    }
    catch (double amount) {
        cout<<"Check amount must be greater than 0."<<endl;
    }
}

Check getCheck(){
    int checkNumber;
    double checkAmount;
    bool checkCashed;

    cout<<"Check Number: ";
    cin>>checkNumber;
    cout<<"Check Amount: ";
    cin>>checkAmount;
    cout<<"Check Cashed? (1 for yes, 0 for no): ";
    cin>>checkCashed;
    cout<<endl;

    Check temp(checkNumber, checkAmount, checkCashed);
    return temp;
}