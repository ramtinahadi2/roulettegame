#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int spinWheel() {
    return rand() % 37; // 0-36
}

bool isEven(int number) {
    return (number % 2 == 0 && number != 0);
}

bool isRed(int number) {
    // 0 is neither red nor black
    return (number != 0 && ((number <= 10 && number % 2 != 0) || (number >= 19 && number <= 28 && number % 2 == 0) || (number >= 11 && number <= 18 && number % 2 == 0)));
}

void displayOptions() {
    cout << "Betting options:" << endl;
    cout << "1. Individual number (0-36 or 37 for 00)" << endl;
    cout << "2. Red or Black (R/r for Red, B/b for Black)" << endl;
    cout << "3. Even or Odd (E/e for Even, O/o for Odd)" << endl;
    cout << "4. Dozen (1-12, 13-24, 25-36)" << endl;
    cout << "Enter your choice: ";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int wallet = 1000;
    int bet, choice;
    char input;
    int number;
    char color;
    char parity;
    int dozen;

    cout << "Welcome to the Roulette Game!" << endl;

    while (wallet > 0) {
        displayOptions();
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please choose between 1 and 4." << endl;
            continue;
        }

        cout << "Place your bet (Enter 0 to exit): $";
        cin >> bet;

        if (bet == 0) {
            cout << "Exiting the game. Your final balance is $" << wallet << endl;
            break;
        }

        if (bet > wallet) {
            cout << "You can't bet more than you have in your wallet!" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Choose a number between 0 and 37 to bet on: ";
                cin >> number;
                if (number < 0 || number > 37) {
                    cout << "Invalid number entered!" << endl;
                    continue;
                }
                break;
            case 2:
                cout << "Choose color (R/r for Red, B/b for Black): ";
                cin >> input;
                color = toupper(input);
                if (color != 'R' && color != 'B') {
                    cout << "Invalid input!" << endl;
                    continue;
                }
                break;
            case 3:
                cout << "Choose parity (E/e for Even, O/o for Odd): ";
                cin >> input;
                parity = toupper(input);
                if (parity != 'E' && parity != 'O') {
                    cout << "Invalid input!" << endl;
                    continue;
                }
                break;
            case 4:
                cout << "Choose dozen (1-12, 13-24, 25-36): ";
                cin >> dozen;
                if (dozen < 1 || dozen > 3) {
                    cout << "Invalid input!" << endl;
                    continue;
                }
                break;
        }

        int result = spinWheel();
        cout << "The wheel spins... The result is " << result << "!" << endl;

        switch (choice) {
            case 1:
                if (number == result) {
                    cout << "Congratulations! You win!" << endl;
                    wallet += bet * 35; // Payout for correctly guessing the number
                } else if (number == 37 && result == 0) { // Handling bet on 00
                    cout << "Congratulations! You win!" << endl;
                    wallet += bet * 35; // Payout for correctly guessing the number 00
                } else {
                    cout << "Sorry, you lose!" << endl;
                    wallet -= bet;
                }
                break;
            case 2:
                if ((color == 'R' && isRed(result)) || (color == 'B' && !isRed(result))) {
                    cout << "Congratulations! You win!" << endl;
                    wallet += bet; // Payout for correctly guessing the color
                } else {
                    cout << "Sorry, you lose!" << endl;
                    wallet -= bet;
                }
                break;
            case 3:
                if ((parity == 'E' && isEven(result)) || (parity == 'O' && !isEven(result))) {
                    cout << "Congratulations! You win!" << endl;
                    wallet += bet; // Payout for correctly guessing the parity
                } else {
                    cout << "Sorry, you lose!" << endl;
                    wallet -= bet;
                }
                break;
            case 4:
                int startOfDozen = (dozen - 1) * 12;
                if (result > startOfDozen && result <= startOfDozen + 12) {
                    cout << "Congratulations! You win!" << endl;
                    wallet += bet * 2; // Payout for correctly guessing the dozen
                } else {
                    cout << "Sorry, you lose!" << endl;
                    wallet -= bet;
                }
                break;
        }

        if (wallet <= 0) {
            cout << "You've run out of money! Game over." << endl;
            break;
        }
    }

    cout << "Thank you for playing!" << endl;

    return 0;
}
