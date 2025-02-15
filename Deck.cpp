#include "Deck.h"

// Constructor for Deck class
Deck::Deck() {
    // Initialize Front and Rear pointers to nullptr (empty queue) and set Count to 0
    Front = nullptr;
    Rear = nullptr;
    Count = 0;
}

// Destructor for Deck class
Deck::~Deck() {
    // Continuously draw cards until the deck is empty, effectively clearing all nodes
    while (!IsEmpty()) {
        Draw_Card(); // Clear all nodes in the deck
    }
}

// Adds a card to the deck (implemented as a queue) using linked list
void Deck::Add_Card(int card) {
    // Create a new node with the card value
    Node* newNode = new Node(card);
    if (IsEmpty()) { // If the deck is empty
        // Set both Front and Rear to point to the new node
        Front = Rear = newNode;
    }
    else { // If there are already cards in the deck
        // Link the new node to the end of the queue and update the Rear pointer
        Rear->next = newNode;
        Rear = newNode;
    }
    ++Count; // Increment the count of cards in the deck
}

// Draws a card from the front of the deck (removes it from the queue)
int Deck::Draw_Card() {
    // Check if the deck is empty
    if (IsEmpty()) {
        std::cerr << "Deck is empty.\n";
        return -1; // Return an error code
    }
    // Temporarily store the Front node for deletion
    Node* temp = Front;
    int card = Front->value; // Get the value of the front card
    Front = Front->next; // Move the Front pointer to the next node
    delete temp; // Delete the old front node
    --Count; // Decrement the count of cards in the deck
    return card; // Return the value of the drawn card
}
