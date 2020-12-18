#include "gold_purse.h"


void GoldPurse::updateLabel(){
    this->gold_label->setText(QString(
        "<html><head/><body><p><span style=' font-size:12pt; color:#edd400;'>"
        "Gold: %1</span></p></body></html>").arg(this->balance));
}


/**
 * Adds or subtracts gold to/from the purse.
 */
void GoldPurse::addGold(int value) {
    this->semaphore->wait();    // acquiring lock

    this->balance += value;
    this->updateLabel();

    this->semaphore->signal();  // releasing lock
}


int GoldPurse::getBalance() {
    return this->balance;
}
