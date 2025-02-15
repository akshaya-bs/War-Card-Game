#pragma once
#ifndef SIDEPILE_H
#define SIDEPILE_H

#include <iostream>
#define MAX_PILE_SIZE 5

class SidePile {
private:
    int Pile[MAX_PILE_SIZE];
    int Top;  // Index of the top element

public:
    SidePile();
    bool Push(int card);
    int Pop();
    int Cards_Remaining() const;
    bool IsFull() const;
    bool IsEmpty() const;
};

#endif // SIDEPILE_H
