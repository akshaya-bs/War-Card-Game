#pragma once
#ifndef DECK_H
#define DECK_H

#include <iostream>

class Deck {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v) : value(v), next(nullptr) {}
    };
    Node* Front;  // Front of the queue
    Node* Rear;   // Rear of the queue
    int Count;    // Number of cards in the deck

public:
    Deck();
    ~Deck();

    void Add_Card(int card);   // Add card to the back of the deck
    int Draw_Card();           // Draw a card from the front of the deck
    int Cards_Remaining() const { return Count; }
    bool IsEmpty() const { return Count == 0; }
};

#endif // DECK_H
