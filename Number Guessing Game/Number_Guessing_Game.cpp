#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    int randoNum = rand() % 100;

    cout<<"I thought of a number between 1 and 100! Try to guess it."<<endl;

    int guess, lower = 1, upper = 100;

    for (int guessesLeft = 5; guessesLeft > 0; guessesLeft--){
        cout<<"Range: ["<<lower<<", "<<upper<<"], Number of guesses left: "<<guessesLeft<<endl;
        cout<<"Your guess: ";
        cin>>guess;

        if (guess < randoNum && guessesLeft > 1){
            cout<<"Wrong! My number is bigger."<<endl;
        } else if (guess > randoNum && guessesLeft > 1){
                cout<<"Wrong! My number is smaller."<<endl;
        } else if (guess == randoNum){
            cout<<"Congrats! You guessed my number in "<<(5 - guessesLeft)<<"guesses.";
            exit(0);
        } else {
            cout<<"Out of guesses! My number is "<<randoNum;
        }
    }
}