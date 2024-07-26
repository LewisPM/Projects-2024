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
    4. how much the figure differs from what the bank says
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
        //Cashed here is understood as: 
        //Cashed = True when Checks the user has written out to others have been deducted from their account balance
        //Cashed = False when Checks the user has written have not yet been deducted from their account balance
        bool cashed;
    public:
        Check(int checkNum, Money amount, bool cashed);

        Money getAmt() const { return amount; }
        int getNum() const { return checkNum; }
        bool cashedStatus() const { return cashed; }

        //TO DO! If needed add mutators

};

//Functions
Check _getCheck();
void addChecks(vector <Check>& checks);
void getDeposits(vector <Money>& deposits);
Money _doubleToMoney(double value);

//Main
int main() {
    vector <Check> checks, cashed, notCashed;
    vector <Money> deposits;
    double cashedSum = 0, depositSum = 0;

    //TO DO! Change the entry for checks such that you are not asked each time if you would like to add, just enter -1 for the check number to finish.
    addChecks(checks);
    getDeposits(deposits);

    cout<<"Please enter the old balance: ";
    double oldBalance;
    cin>>oldBalance;

    cout<<"Please enter the new balance: ";
    double estNewBalance;
    cin>>estNewBalance;

    cout<<"Balancing checks..."<<endl<<endl;

    for (Check i : checks) {
        if (i.cashedStatus() == true) {
            cashed.push_back(i);
            cashedSum += i.getAmt().getValue();
        } else {
            notCashed.push_back(i);
        }
        //cout<<"Check No. "<<i.getNum()<<": "<<i.getAmt().getValue()<<endl;
    }
    cout<<"Old balance: $"<<oldBalance<<endl;
    cout<<"Total of checks cashed: $"<<cashedSum<<endl;

    for (Money j : deposits) {
        depositSum += j.getValue();
    }
    cout<<"Total deposits: $"<<depositSum<<endl;

    double newBalance = depositSum + oldBalance - cashedSum;
    cout<<"New Balance: $"<<newBalance<<endl<<endl;
    cout<<"Difference from provided new balance and calculated: $"<<abs(estNewBalance - newBalance)<<endl<<endl;

    cout<<"Cashed checks: "<<endl;
    for (Check c : cashed) {
        cout<<"Check No. "<<c.getNum()<<": $"<<c.getAmt().getValue()<<endl;
    }

    cout<<endl;

    cout<<"Uncashed checks: "<<endl;
    for (Check nc : notCashed) {
        cout<<"Check No. "<<nc.getNum()<<": $"<<nc.getAmt().getValue()<<endl;
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
    return total_in_cents * 0.01;
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

/*
istream& operator >>(istream& ins, Money& amount){
    //TO DO! FIGURE OUT AND COMPLETE ISTREAM - MONEY CLASS PG 632 & PG 657
    return ins;
}

ostream& operator <<(ostream& outs, const Money& amount){
    //TO DO! FIGURE OUT AND COMPLETE ISTREAM - MONEY CLASS PG 632 & PG 657
    return outs;
}
*/

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
Check _getCheck(){
    int checkNumber;
    double checkAmount;
    bool checkCashed;

    cout<<"Check Number: ";
    cin>>checkNumber;
    cout<<"Check Amount: ";
    cin>>checkAmount;
    Money amount = _doubleToMoney(checkAmount);
    cout<<"Check Cashed? (1 for yes, 0 for no): ";
    cin>>checkCashed;
    cout<<endl;

    Check temp(checkNumber, amount, checkCashed);
    return temp;
}

void addChecks(vector <Check>& checks){   
    int addAnotherCheck;
    cout<<"Adding a check? (1 for yes): ";
    cin>>addAnotherCheck;
    while (addAnotherCheck == 1) {
        Check temp = _getCheck();
        if (temp.getNum() >= 1 && temp.getAmt().getValue() > 0.01) {
            checks.push_back(temp);
        }
        cout<<"Adding another check? (1 for yes): ";
        cin>>addAnotherCheck;
    }
    cout<<"No longer entering checks..."<<endl;
    cout<<endl;
}

void getDeposits(vector <Money>& deposits){
    double deposit;
    cout<<"Please enter your deposits (enter -1 to finish): "<<endl;
    cin>>deposit;
    while (deposit != -1) {
        Money temp (deposit);
        deposits.push_back(temp);
        cin>>deposit;
    }
}

Money _doubleToMoney(double value){
    int all_cents = value * 100;
    long dollar = all_cents/100;
    int cents = all_cents - (dollar * 100);

    Money amount(dollar, cents);
    return amount;
}
