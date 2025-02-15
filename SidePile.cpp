#include "SidePile.h" 

// Constructor for SidePile, initializing Top to -1 (indicating an empty pile)
SidePile::SidePile() : Top(-1) {}

// Pushing a card onto the side pile
// Checks if the pile is full before adding a card
bool SidePile::Push(int card) {
    if (IsFull()) {  // If the pile is full, print an error and don't add the card
        std::cout << "Side pile is full.\n";
        return false;
    }
    Pile[++Top] = card;  // Add the card to the top of the pile
    return true;
}

// Removing (popping) the top card from the side pile for the player to play
int SidePile::Pop() {
    if (IsEmpty()) {  // If the pile is empty, print an error and return -1
        std::cout << "Side pile is empty.\n";
        return -1;
    }
    return Pile[Top--];  // Remove and return the top card, decreasing the Top index
}

// Returns the number of cards remaining in the side pile
int SidePile::Cards_Remaining() const {
    return Top + 1;  // Top is zero-based, so add 1 to get the count
}

// Checks if the side pile is full
// Returns true if Top index has reached the maximum capacity
bool SidePile::IsFull() const {
    return Top >= MAX_PILE_SIZE - 1;  // Maximum capacity is defined by MAX_PILE_SIZE
}

// Checks if the side pile is empty
// Returns true if no cards are in the pile (Top is at the initial value -1)
bool SidePile::IsEmpty() const {
    return Top == -1;
}
