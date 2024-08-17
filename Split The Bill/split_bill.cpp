//for student pml298

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//1. Calculate how much each person would owe if even.
//2. Compare what they owe to the calculated
//3. Store said info in a linked-list class

//'Diner' node
class Diner {
    private:
        double contribution = 0;
        string name;
        Diner* next = nullptr;
    public:
        Diner(string person, double amt = 0) { name = person; contribution = amt; };
        string getName() { return name; }
        void setName(string person) { name = person; }
        double getContribution() { return contribution; }
        void setContribution(double amt) { contribution = amt; }
        Diner* getNextPerson();
        void setNextPerson(Diner* newPerson) { this->next = newPerson; }
        //copy constructor
        Diner(const Diner& rhs) { this->contribution = rhs.contribution; this->name = rhs.name; }
        //operator= overload
        Diner& operator=(const Diner& rhs);
};

class LinkedList {
    private:
        Diner* head;
    public:
        LinkedList(): head(nullptr) {};

        //Big 3
        ~LinkedList() { clear(); };
        LinkedList(const LinkedList& rhs);
        LinkedList& operator=(const LinkedList& rhs);

        void clear();

        void setHead(Diner* person){ head = person; }
        Diner* getHead() { return head; }

};

//Functions

void extractFile(string fileName, LinkedList& list) {
    ifstream inFile(fileName);
    double amt;
    string name;
    int count = 0;
    Diner* currPtr = list.getHead();
    while (inFile >> amt) {
        count++;
        inFile.ignore();
        getline(inFile, name);
        if (!currPtr){
            Diner* head = new Diner(name, amt);
            head->setNextPerson(nullptr);
            list.setHead(head);
            cout << head->getName() << " has been added to the head of the table." << endl;
            currPtr = list.getHead();
        } else {
            Diner* next = new Diner(name, amt);
            currPtr->setNextPerson(next);
            cout << next->getName() << " has been added to the table." << endl;
            currPtr = next;
        }
        currPtr->setNextPerson(nullptr);
    }
    inFile.close();
}

int main() {
    /*
    //Test for Diner Node Class
    Diner Linda = Diner("Linda", 50.1);
    cout << Linda.getName() << ": " << Linda.getContribution() << endl;
    */

    /*
    //Test for Linked List and Access
    Diner Linda = Diner("Linda", 50.1);
    LinkedList Table = LinkedList();
    Table.setHead(&Linda);
    cout << Table.getHead()->getName() << endl;
    */

    /*
    //Test for file name format
    LinkedList Table = LinkedList();
    extractFile("C:/Users/PBody/Code/Projects 2024/Split The Bill/bill_contributions.txt", Table);
    cout << Table.getHead()->getName() << endl;
    */


    return 0;
}


Diner* Diner::getNextPerson() {
    if (this->next == nullptr) {
        //cout << "No next person." <<endl;
        return nullptr;
    } else {
        return this->next;
    }
}

Diner& Diner::operator=(const Diner& rhs) { 
    if (this == &rhs) {
        return *this;
    } else {
        this->contribution = rhs.contribution; 
        this->name = rhs.name; 
        return *this;
    }
}

void LinkedList::clear() {
    while (head) {
        Diner* temp = head;
        head = head->getNextPerson();
        //cout << temp->getName() << " is deleted..." << endl;
        delete temp;
    }
}

LinkedList::LinkedList(const LinkedList& rhs) : head(nullptr) {
    if (rhs.head) /*checking for empty*/{
        head = new Diner(*rhs.head);
        Diner* currPtr = head;
        Diner* rhsNext = rhs.head->getNextPerson();
        while (rhsNext) {
            currPtr->setNextPerson(new Diner(*rhsNext));
            currPtr = currPtr->getNextPerson();
            rhsNext = rhsNext->getNextPerson();
        }
    }
}

LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    if (this == &rhs) {
        return *this;
    } else if (rhs.head) {
        head = new Diner(*rhs.head);
        Diner* currPtr = head;
        Diner* rhsNext = rhs.head->getNextPerson();
        while (rhsNext) {
            currPtr->setNextPerson(new Diner(*rhsNext));
            currPtr = currPtr->getNextPerson();
            rhsNext = rhsNext->getNextPerson();
        }
    }
    return *this;
}
