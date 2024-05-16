#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    int x1 = rand() % 100;
    cout<<x1;
}