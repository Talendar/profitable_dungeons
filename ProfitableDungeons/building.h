#ifndef BUILDING_H
#define BUILDING_H

#include <atomic>
#include <chrono>
#include <thread>
#include <QString>
#include "clickable_label.h"
#include "gold_purse.h"


class Building {
public:
    Building(QString name,
             ClickableLabel *ui_unbuilt,
             ClickableLabel *ui_built,
             GoldPurse *purse,
             int gold_per_tick, int tick_interval, int cost);
    ~Building();

    QString getName();
    int getCost();
    void upgrade();

private:
    QString name;
    std::atomic_bool active;
    std::thread *worker = nullptr;

    int cost;
    int tier = 0;
    GoldPurse *purse;

    ClickableLabel *ui_unbuilt;
    ClickableLabel *ui_built;

    std::atomic_int gold_per_tick;
    std::atomic_int tick_interval;  // in ms

    void produce();
};

#endif // BUILDING_H
