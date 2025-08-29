#include <iostream>
#include <random>
#include <string>
#include <limits>

class NumberGuessGame {
private:
    int secretNumber;
    int attempts;
    int maxAttempts;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    NumberGuessGame(int min = 1, int max = 100, int maxTries = 10) 
        : gen(rd()), dis(min, max), maxAttempts(maxTries), attempts(0) {
        secretNumber = dis(gen);
    }

    void displayWelcome() {
        std::cout << "========================================\n";
        std::cout << "    Welcome to GUESS THE NUMBER!       \n";
        std::cout << "========================================\n";
        std::cout << "I'm thinking of a number between 1-100\n";
        std::cout << "You have " << maxAttempts << " attempts to guess it!\n";
        std::cout << "========================================\n\n";
    }

    void displayStats() {
        std::cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n";
        std::cout << "Enter your guess: ";
    }

    int getPlayerGuess() {
        int guess;
        while (true) {
            if (std::cin >> guess) {
                if (guess >= 1 && guess <= 100) {
                    return guess;
                } else {
                    std::cout << "Please enter a number between 1 and 100: ";
                }
            } else {
                std::cout << "Invalid input! Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    bool processGuess(int guess) {
        attempts++;
        
        if (guess == secretNumber) {
            std::cout << "\n🎉 CONGRATULATIONS! 🎉\n";
            std::cout << "You guessed it in " << attempts << " attempts!\n";
            return true;
        } else if (guess < secretNumber) {
            std::cout << "📈 Too low! Try a higher number.\n\n";
        } else {
            std::cout << "📉 Too high! Try a lower number.\n\n";
        }
        
        return false;
    }

    bool isGameOver() {
        return attempts >= maxAttempts;
    }

    void displayGameOver() {
        std::cout << "\n💀 GAME OVER! 💀\n";
        std::cout << "The number was: " << secretNumber << "\n";
        std::cout << "Better luck next time!\n";
    }

    void resetGame() {
        secretNumber = dis(gen);
        attempts = 0;
    }
};

class GameManager {
public:
    void run() {
        NumberGuessGame game;
        bool playAgain = true;

        while (playAgain) {
            game.displayWelcome();
            
            // Main game loop
            while (true) {
                game.displayStats();
                int guess = game.getPlayerGuess();
                
                if (game.processGuess(guess)) {
                    break; // Player won
                }
                
                if (game.isGameOver()) {
                    game.displayGameOver();
                    break; // Game over
                }
            }
            
            // Ask to play again
            playAgain = askPlayAgain();
            if (playAgain) {
                game.resetGame();
                clearScreen();
            }
        }
        
        std::cout << "\nThanks for playing! Goodbye! 👋\n";
    }

private:
    bool askPlayAgain() {
        std::string response;
        std::cout << "\nWould you like to play again? (y/n): ";
        std::cin >> response;
        
        return (response == "y" || response == "Y" || response == "yes" || response == "Yes");
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};

int main() {
    GameManager gameManager;
    gameManager.run();
    return 0;
}
