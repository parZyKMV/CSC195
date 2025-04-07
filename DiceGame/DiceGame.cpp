#include <iostream>
#include <string>
using namespace std;

int main()
{
    int totalPlayer1 = 0;
    int totalPlayer2 = 0;

    cout << "Welcome to Dice Game!\n";
    cout << "Each player gonna throw two dice during 3 turns.\n";

    for (int turn = 1; turn <= 3; turn++ )
    {
        cout << "Press ENTER to player 1 throw dices\n";
        cin.get();
        
        int dice1P1 = rand() % 6 + 1;
        int dice2P1 = rand() % 6 + 1;
        int totalP1 = dice1P1 + dice2P1;

        cout << "Player 1 get: " << dice1P1 << " and " << dice2P1 << " a total of: " << totalP1 << "\n";
        totalPlayer1 += totalP1;

        cout << "Press ENTER to player 2 throw dices\n";
        cin.get();

        int dice1P2 = rand() % 6 + 1;
        int dice2P2 = rand() % 6 + 1;
        int totalP2 = dice1P2 + dice2P2;

        cout << "Player 2 get: " << dice1P2 << " and " << dice2P2 << " a total of: " << totalP2 << "\n";
        totalPlayer2 += totalP2;

        cout << "--------------------------------------------------------------------------\n";
    }
    cout << "Final score:\n" << "Player 1: " << totalPlayer1 << "\n" << "Player 2: " << totalPlayer2 << "\n";
    if (totalPlayer1 > totalPlayer2)
    {
        cout << "Player 1 WIN";
    }
    else if (totalPlayer2 > totalPlayer1) {
        cout << "Player 2 WIN";
    }
    else
    {
        cout << "DRAW";
    }
}

