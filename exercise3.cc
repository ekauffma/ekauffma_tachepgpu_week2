#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

string playRockPaperScissors(string *input1, string *input2){

    if ( !( (*input1=="rock") || (*input1=="scissors") || (*input1=="paper") ) ) {
        throw std::invalid_argument("Player 1's input must be either rock, paper, or scissors");
    }
    if ( !( (*input2=="rock") || (*input2=="scissors") || (*input2=="paper") ) ) {
        throw std::invalid_argument("Player 2's input must be either rock, paper, or scissors");
    }

    if (*input1==*input2) return "Draw";
    if (*input1=="rock") {
        if (*input2=="paper") return "Player 2 Wins";
        if (*input2=="scissors") return "Player 1 Wins";
    }
    if (*input1=="scissors") {
        if (*input2=="paper") return "Player 1 Wins";
        if (*input2=="rock") return "Player 2 Wins";
    }
    if (*input1=="paper") {
        if (*input2=="scissors") return "Player 2 Wins";
        if (*input2=="rock") return "Player 1 Wins";
    }

    return "";
}


int main() {

    string player1Input;
    cout<< "Player 1 Input (rock, paper, scissors): ";
    cin >> player1Input;
    string player2Input;
    cout<< "Player 2 Input (rock, paper, scissors): ";
    cin >> player2Input;

    try {
        string result = playRockPaperScissors(&player1Input, &player2Input);
        cout<<"Game Result: "<<result<<endl;
    }
    catch (std::invalid_argument& e) {
        cerr<<e.what()<<endl;
        return -1;
    }

    return 0;
}
