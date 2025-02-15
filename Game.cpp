#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <set>

// Constructor for the Game class
Game::Game() {
    // Initialize win counters, game mode, and max rounds to default values
    Player_Wins = 0;
    Computer_Wins = 0;
    Game_Mode = 0;
    Max_Rounds = 0;
}

// Displays a welcome message and prompts the user to select a game mode
void Game::Welcome_Message() const {
    std::cout << "Welcome to the Game of War!\n";
    std::cout << "Prepare for battle, soldier! Your strategy and luck will determine the victor!\n";
    std::cout << "Choose the style you'd like to play:\n";
    std::cout << "1. Play until one participant runs out of cards\n";
    std::cout << "2. Play for a fixed number of rounds, with the player who wins the most rounds declared the winner\n";
    std::cout << "Enter your choice (1 or 2): ";
}

// Sets up the game by distributing unique cards to the player and computer decks
void Game::Setup_Game() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    std::set<int> playerCards;  // Set to store unique cards for player
    std::set<int> computerCards;  // Set to store unique cards for computer

    // Add 10 unique cards to the player's deck
    while (playerCards.size() < 10) {
        int card = rand() % 10 + 1;  // Random card value between 1 and 10
        if (playerCards.insert(card).second) {  // Insert if unique
            Player_Deck.Add_Card(card);
        }
    }

    // Add 10 unique cards to the computer's deck
    while (computerCards.size() < 10) {
        int card = rand() % 10 + 1;  // Random card value between 1 and 10
        if (computerCards.insert(card).second) {  // Insert if unique
            Computer_Deck.Add_Card(card);
        }
    }

    std::cout << "Unique cards shuffled and distributed to each deck!\n\n";
}

// Displays options after each round and processes user input for various actions
void Game::View_Options() {
    char Choice;
    while (true) {
        std::cout << "\nDo you want to:\n";
        std::cout << "1. See number of cards in your side pile\n";
        std::cout << "2. See number of cards in your deck\n";
        std::cout << "3. See number of cards in the computer's deck\n";
        std::cout << "4. Proceed to the next round\n";
        std::cout << "5. Exit game\n";
        std::cout << "Enter your choice: ";
        std::cin >> Choice;

        if (Choice == '1') {
            std::cout << "Your side pile has " << Player_Pile.Cards_Remaining() << " cards.\n";
        }
        else if (Choice == '2') {
            std::cout << "Your deck has " << Player_Deck.Cards_Remaining() << " cards.\n";
        }
        else if (Choice == '3') {
            std::cout << "The computer's deck has " << Computer_Deck.Cards_Remaining() << " cards.\n";
        }
        else if (Choice == '4') {
            return;  // Proceed to the next round
        }
        else if (Choice == '5') {
            std::cout << "Exiting the game early.\n";
            Display_Game_Result();  // Show final game results
            exit(0);  // Exit the game
        }
        else {
            std::cout << "Invalid option. Try again.\n";
        }
    }
}

// Plays a single round of the game with actions for both player and computer
void Game::Play_Round() {
    int Player_Card;  // Holds the player's card for this round
    char Action;  // Player action choice

    // Player's turn to draw a card
    if (!Player_Deck.IsEmpty()) {
        Player_Card = Player_Deck.Draw_Card();
        std::cout << "Your current card is " << Player_Card << ".\n";
    }
    else if (!Player_Pile.IsEmpty()) {
        Player_Card = Player_Pile.Pop();  // Draw from side pile if main deck is empty
        std::cout << "Your deck is empty. Drawing from your side pile. Your card is " << Player_Card << ".\n";
    }
    else {
        std::cout << "You have no cards left! Computer wins this round by default.\n";
        Computer_Wins++;  // Computer wins if player has no cards
        return;
    }

    // Array to store player's played cards for this round and a counter to track them
    int playerPlayedCards[2] = { Player_Card, -1 };
    int playerCardCount = 1;

    // Loop for player action selection
    while (true) {
        std::cout << "\nChoose an action:\n";
        std::cout << "P - Push: Place this card onto your side pile and draw a new card.\n";
        std::cout << "L - Pull: Pull a card from your side pile and play both.\n";
        std::cout << "Enter your choice (P or L): ";
        std::cin >> Action;

        if (Action == 'P' || Action == 'p') {
            // Push action - add current card to side pile and draw a new card if possible
            if (Player_Pile.IsFull()) {
                std::cout << "You can't have more than 5 cards in your side pile. Playing your current card.\n";
            }
            else {
                Player_Pile.Push(Player_Card);
                std::cout << "You pushed " << Player_Card << " to your side pile.\n";
                if (!Player_Deck.IsEmpty()) {
                    Player_Card = Player_Deck.Draw_Card();
                    playerPlayedCards[0] = Player_Card;
                    std::cout << "Your new card is " << Player_Card << ".\n";
                }
                else if (!Player_Pile.IsEmpty()) {
                    Player_Card = Player_Pile.Pop();
                    playerPlayedCards[0] = Player_Card;
                    std::cout << "No cards in deck. Using a card from your side pile: " << Player_Card << ".\n";
                }
                else {
                    std::cout << "No cards left to draw. Exiting round.\n";
                    break;
                }
            }
            break;
        }
        else if (Action == 'L' || Action == 'l') {
            // Pull action - pull a card from side pile and add its value to current card
            int additionalCard = Player_Pile.Pop();
            if (additionalCard != -1) {
                std::cout << "You pulled " << additionalCard << " from your side pile.\n";
                playerPlayedCards[1] = additionalCard;
                playerCardCount = 2;
                Player_Card += additionalCard;  // Sum cards for final value
                std::cout << "Your combined card value is " << Player_Card << ".\n";
            }
            else {
                std::cout << "No cards in side pile. Playing only your current card.\n";
            }
            break;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    // Computer draws a card
    int computerCard = Computer_Deck.Draw_Card();
    std::cout << "Computer plays a card with value " << computerCard << ".\n";

    // Compare player and computer cards to determine the round winner
    if (Player_Card > computerCard) {
        std::cout << "You win this round!\n";
        for (int i = 0; i < playerCardCount; i++) {
            Player_Deck.Add_Card(playerPlayedCards[i]);
        }
        Player_Deck.Add_Card(computerCard);
        Player_Wins++;
    }
    else {
        std::cout << "Computer wins this round!\n";
        for (int i = 0; i < playerCardCount; i++) {
            Computer_Deck.Add_Card(playerPlayedCards[i]);
        }
        Computer_Deck.Add_Card(computerCard);
        Computer_Wins++;
    }
}

// Displays the result of the game based on the game mode chosen by the player
void Game::Display_Game_Result() const {
    std::cout << "\nGame Over.\n";

    // Mode 1: Game ends when one player runs out of cards
    if (Game_Mode == 1) {
        if (Player_Deck.IsEmpty() && Player_Pile.IsEmpty()) {
            // Player has no cards left, so the computer wins
            std::cout << "You ran out of cards. Computer wins the game!\n";
        }
        else if (Computer_Deck.IsEmpty() && Computer_Pile.IsEmpty()) {
            // Computer has no cards left, so the player wins
            std::cout << "Computer ran out of cards. You win the game!\n";
        }
    }
    // Mode 2: Game ends after a fixed number of rounds
    else if (Game_Mode == 2) {  // Mode 2: Play for a fixed number of rounds
        // Show the number of rounds each player won
        std::cout << "You won " << Player_Wins << " rounds, Computer won " << Computer_Wins << " rounds.\n";

        // Determine the overall winner based on round wins
        if (Player_Wins > Computer_Wins) {
            std::cout << "You are the overall winner!\n";  // Player wins more rounds
        }
        else if (Player_Wins < Computer_Wins) {
            std::cout << "Computer is the overall winner!\n";  // Computer wins more rounds
        }
        else {
            std::cout << "It's a tie game!\n";  // Equal number of rounds won by both
        }
    }
}

// Set the game mode to the user's choice (either 1 or 2)
// 1: Game continues until a player runs out of cards
// 2: Game continues for a fixed number of rounds
void Game::Set_Game_Mode(int mode) {
    Game_Mode = mode;
}

// Set the maximum number of rounds if the user chose mode 2 (fixed number of rounds)
void Game::Set_Max_Rounds(int rounds) {
    Max_Rounds = rounds;
}

// The main function that starts the game loop and manages the progression until completion
void Game::Start() {
    // Set up the game by distributing unique cards to both the player and the computer
    Setup_Game();

    // If Game_Mode is 2, prompt the user to enter the number of rounds to play
    if (Game_Mode == 2) {
        std::cout << "Enter the number of rounds you wish to play: ";
        std::cin >> Max_Rounds;
    }

    // Initialize variables to track the number of rounds played and whether the game should continue
    int Rounds_Played = 0;
    bool Game_Ongoing = true;

    // Loop to play rounds until the game ends based on the selected game mode
    while (Game_Ongoing) {
        // For mode 2: end the game when the set number of rounds has been played
        if (Game_Mode == 2 && Rounds_Played >= Max_Rounds) {
            Game_Ongoing = false;  // Stop the game loop
            break;
        }

        // For mode 1: stop if either player has run out of cards in both their deck and side pile
        if ((Player_Deck.IsEmpty() && Player_Pile.IsEmpty()) ||
            (Computer_Deck.IsEmpty() && Computer_Pile.IsEmpty())) {
            Game_Ongoing = false;  // Stop the game loop
            break;
        }

        // Play a single round and update the round count
        Play_Round();
        Rounds_Played++;

        // After each round, provide options for the player to view information or proceed
        View_Options();
    }

    // Display the final results and declare the winner after the game concludes
    Display_Game_Result();
}
