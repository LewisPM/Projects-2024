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

        friend Money operator+(const Money& amount1, const Money& amount2);
        friend Money operator-(const Money& amount1, const Money& amount2);
        friend Money operator-(const Money& amount);
        friend bool operator==(const Money& amount1, const Money& amount2);
        friend bool operator<(const Money& amount1, const Money& amount2);
        friend istream& operator >>(istream& ins, Money& amount);
        friend ostream& operator <<(ostream& outs, const Money& amount);
};
class Check {
    private:
        int checkNum;
        Money amount;
        bool cashed;
    public:
        Check(int checkNum, Money amount, bool cashed);

        Money getAmt() const { return amount; }
        int getNum() const { return checkNum; }
        bool getCashedStatus() const { return this->cashed; }

};

//Functions
Check getCheck();

//Main
int main() {
    vector <Check> checks;
    //Check checkOne(9, 5, 0), checkTwo(10, 7, 0);
    //checks.push_back(checkOne);
    //checks.push_back(checkOne);
    
    int addAnotherCheck;
    cout<<"Adding a check? (1 for yes): ";
    cin>>addAnotherCheck;
    if (addAnotherCheck != 1) {
        cout<<"No longer entering checks..."<<endl;
    } else {
        while (addAnotherCheck == 1) {
            Check temp = getCheck();
            if (temp.getNum() >= 1 && temp.getAmt().getValue() > 0.01) {
                checks.push_back(temp);
            }
            cout<<"Adding another check? (1 for yes): ";
            cin>>addAnotherCheck;
        }
    }

    for (Check i : checks) {
        cout<<"Check No. "<<i.getNum()<<": "<<i.getAmt().getValue()<<endl;
    }

    return 0;
}

//MONEY - Constructors
Money::Money(long dollars, int cents){
    try {
        if (dollars < 0 || cents < 0) {
            throw(dollars);
        } else {
            total_in_cents = (dollars * 100) + cents;
        }
    } catch (long dollars) {
        cout<<"Dollars & cents values should be greater than or equal to 0."<<endl;
    }
}

Money::Money(long dollars){
    try {
        if (dollars < 0) {
            throw(dollars);
        } else {
            total_in_cents = dollars * 100;
        }
    } catch (long dollars) {
        cout<<"Dollars value should be greater than or equal to 0."<<endl;
    }
}

Money::Money(){
    total_in_cents = 0;
}

//MONEY - Methods
double Money::getValue() {
    return total_in_cents / 100.0;
}

//MONEY - operator overloads
Money operator+(const Money& amount1, const Money& amount2) {
    Money temp;
    temp.total_in_cents = amount1.total_in_cents + amount2.total_in_cents;
    return temp;
}

Money operator-(const Money& amount1, const Money& amount2){
    Money temp;
    temp.total_in_cents = amount1.total_in_cents - amount2.total_in_cents;
    return temp;
}

Money operator-(const Money& amount){
    Money temp;
    temp.total_in_cents = amount.total_in_cents * -1;
    return temp;
}

bool operator==(const Money& amount1, const Money& amount2){
    if (amount1.total_in_cents == amount2.total_in_cents){
        return true;
    } else {
        return false;
    }
}

bool operator<(const Money& amount1, const Money& amount2){
    if (amount1.total_in_cents < amount2.total_in_cents){
        return true;
    } else {
        return false;
    }
}

istream& operator >>(istream& ins, Money& amount){
    //TO DO! FIGURE OUT AND COMPLETE ISTREAM - MONEY CLASS PG 632 & PG 657
    return ins;
}

ostream& operator <<(ostream& outs, const Money& amount){
    //TO DO! FIGURE OUT AND COMPLETE ISTREAM - MONEY CLASS PG 632 & PG 657
    return outs;
}

//CHECK - Constructors
Check::Check(int checkNum, Money amount, bool cashed){
    try {
        if (checkNum < 1) {
            throw(checkNum);
        } else if (amount.getValue() < 0.01){
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
    catch (Money amount) {
        cout<<"Check amount must be greater than 0."<<endl;
    }
}

//Check - Methods


//Functions
Check getCheck(){
    int checkNumber;
    double checkAmount;
    bool checkCashed;

    cout<<"Check Number: ";
    cin>>checkNumber;

    cout<<"Check Amount: ";
    cin>>checkAmount;
    long dollar = checkAmount/1;
    int cents = checkAmount - dollar;
    Money amount(dollar, cents);
    
    cout<<"Check Cashed? (1 for yes, 0 for no): ";
    cin>>checkCashed;
    cout<<endl;

    Check temp(checkNumber, amount, checkCashed);
    return temp;
}