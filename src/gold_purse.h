#ifndef GOLDPURSE_H
#define GOLDPURSE_H

#include "semaphore.h"
#include <QLabel>

class GoldPurse
{
public:
    GoldPurse(QLabel *gold_label) : gold_label(gold_label) {}

    void addGold(int value);
    int getBalance();

private:
    int balance = 0;  // amount of gold currently available
    Semaphore *semaphore = new Semaphore(1);
    QLabel *gold_label;
    void updateLabel();
};

#endif // GOLDPURSE_H
