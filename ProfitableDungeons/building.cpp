#include "building.h"


/**
 * Base constructor.
 */
Building::Building(QString name,
                   ClickableLabel *ui_unbuilt,
                   ClickableLabel *ui_built,
                   GoldPurse *purse,
                   int gold_per_tick, int tick_interval, int cost)
    : BASE_GPT(gold_per_tick),
      BASE_COST(cost),
      BASE_TICK_INT(tick_interval)
{
    this->name = name;
    this->ui_unbuilt = ui_unbuilt;
    this->ui_built = ui_built;
    this->purse = purse;
    this->reset();
}


/**
 * Destructor. Necessary to stop the production thread.
 */
Building::~Building() {
    this->active = false;
    this->worker->join();
}


QString Building::getName() {
    return this->name;
}


int Building::getTier() {
    return this->tier;
}


QPixmap Building::getBuiltImg() {
    return *this->ui_built->pixmap();
}


int Building::getCost() {
    return this->cost;
}


int Building::getSellCost() {
    if(this->tier == 0)
        return 0;

    return (this->cost / this->COST_UPG_PC) * this->SELL_COST_PC;
}


int Building::getGPT() {
    return this->gold_per_tick;
}


int Building::getTickInterval() {
    return this->tick_interval;
}

/**
 * Handle the production of the building.
 */
void Building::produce() {
    while(this->active) {
        this->purse->addGold(this->gold_per_tick * this->tier * 0.5);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->tick_interval));
    }
}


/**
 * Upgrades the building's tier.
 */
void Building::upgrade(int x) {
    for(int i = 0; i < x; i++) {
        this->tier++;
        this->cost = int(this->BASE_COST * pow(this->COST_UPG_PC, tier));
        this->gold_per_tick = int(this->BASE_GPT * pow(this->GOLD_UPG_PC, tier - 1));
        this->tick_interval = int(this->BASE_TICK_INT * pow(this->TICK_UPG_PC, tier - 1));
    }

    // shows building
    if(this->tier >= 1 && ui_unbuilt != nullptr) {
        this->ui_unbuilt->setVisible(false);
        this->ui_built->setVisible(true);
    }

    // starts production
    if(!this->active) {
        this->active = true;
        this->worker = new std::thread(&Building::produce, this);
    }
}


/**
 * Resets the building to its initial/unbuilt state.
 */
void Building::reset() {
    this->active = false;
    this->tier = 0;
    this->gold_per_tick = this->BASE_GPT;
    this->tick_interval = this->BASE_TICK_INT;
    this->cost = this->BASE_COST;

    if(ui_unbuilt != nullptr) {
        ui_built->setVisible(false);
        ui_unbuilt->setVisible(true);
    }
}
