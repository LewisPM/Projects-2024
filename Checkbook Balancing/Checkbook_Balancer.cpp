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
    private:
        int checkNum;
        Money amt;
        bool cashed;
    public:
        Check(int checkNum, int amount, bool cashed);
        Money getAmt() const { return amt; }
};

//Main
int main() {
    //Check zero = Check(0, 1, 0); 
    //cout<<"Check zero: "<<zero.getAmt().getValue()<<endl;
    Check one = Check(1, 1, 0);
    cout<<"Check one: "<<one.getAmt().getValue()<<endl;
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

Check::Check(int checkNum, int amount, bool cashed){
    if (checkNum < 1) {
        cout<<"Check number should be greater than 0."<<endl;
        exit(1);
    }
    checkNum = checkNum;
    amt = Money(amount);
    cashed = cashed;
}