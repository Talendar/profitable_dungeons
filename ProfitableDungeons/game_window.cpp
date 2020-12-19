#include "game_window.h"
#include "ui_game_window.h"


/**
 * Constructor.
 */
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);

    // initializing gold purse
    this->purse = new GoldPurse(ui->gold_label);
    purse->addGold(1500);  // initial gold

    // initializing buildings
    this->buildings["blacksmith"] = new Building("Blacksmith",
                                                 ui->blacksmith_unbuilt, ui->blacksmith,
                                                 this->purse,
                                                 500, 1200, 5000);
    this->buildings["castle"] = new Building("Castle",
                                             ui->castle_unbuilt, ui->castle,
                                             this->purse,
                                             10000, 2000, 1000000);
    this->buildings["tavern"] = new Building("Tavern",
                                             nullptr, ui->tavern,
                                             this->purse,
                                             30, 1000, 500);
    this->buildings["clothes"] = new Building("Clothes Shop",
                                              ui->clothes_shop_unbuilt, ui->clothes_shop,
                                              this->purse,
                                              10,700,300);
    this->buildings["apple"] = new Building("Apple Orchard",
                                            ui->apple_unbuilt, ui->apple,
                                            this->purse,
                                            5, 500, 100);
    this->buildings["inn"] = new Building("Inn",
                                          ui->inn_unbuilt, ui->inn,
                                          this->purse,
                                          60, 1000, 1000);
    this->buildings["farm"] = new Building("Farm",
                                          ui->farm_unbuilt, ui->farm,
                                          this->purse,
                                          20, 700, 500);
    this->buildings["mine"] = new Building("Mine",
                                           ui->mine_unbuilt, ui->mine,
                                           this->purse,
                                           80, 1100, 1200);
    this->buildings["hunter"] = new Building("Hunter Hut",
                                             ui->hunter_hut_unbuilt,ui->hunter_hut,
                                             this->purse,
                                             100,1200,1500);
    this->buildings["food"] = new Building("Food Shop",
                                           ui->food_shop_unbuilt,ui->food_shop,
                                           this->purse,
                                           20,700,500);
    this->buildings["lumberjack"] = new Building("Lumberjack",
                                                 ui->lumberjack_unbuilt,ui->lumberjack,
                                                 this->purse,
                                                 40,1000,700);
}


/**
 * Destructor.
 */
GameWindow::~GameWindow() {
    delete ui;
}


/**
 * Handles what happens when the user clicks on a building.
 * @param key
 */
void GameWindow::buildingClicked(QString key) {
    Building *b = this->buildings[key];
    BuildingDialog *dialog = new BuildingDialog(nullptr, b);
    dialog->exec();

    switch(dialog->getState()) {
        case BuildingDialog::State::UPGRADE:
            this->handleUpgrade(b);  break;
        case BuildingDialog::State::SELL:
            this->handleSelling(b);  break;
        case BuildingDialog::State::NO_ACTION: ;
    }
}


/**
 * Handles the upgrade of a building.
 * @param b
 */
void GameWindow::handleUpgrade(Building *b) {
    BuyDialog *dialog = new BuyDialog(nullptr, b, false);
    dialog->exec();

    if(dialog->accepted_buying) {
        if(purse->getBalance() >= b->getCost()) {
            this->purse->addGold(-b->getCost());
            b->upgrade();
        }
        else {
            QMessageBox *dialog = new QMessageBox();
            dialog->setWindowTitle("Not enough gold!");
            dialog->setText(
                QString("You don't have enough gold (%1 gold missing).")
                    .arg(b->getCost() - this->purse->getBalance()));
            dialog->show();
        }
    }
}


/**
 * Handles selling a building.
 * @param b
 */
void GameWindow::handleSelling(Building *b) {
    BuyDialog *dialog = new BuyDialog(nullptr, b, true);
    dialog->exec();

    if(dialog->accepted_buying) {
        this->purse->addGold(b->getSellCost());
        b->reset();
    }
}


// Tavern
void GameWindow::on_tavern_clicked() {this->buildingClicked("tavern");}

// Castle
void GameWindow::on_castle_unbuilt_clicked() {this->buildingClicked("castle");}
void GameWindow::on_castle_clicked() {this->buildingClicked("castle");}

// Apple Orchard
void GameWindow::on_apple_unbuilt_clicked() {this->buildingClicked("apple");}
void GameWindow::on_apple_built_clicked() {this->buildingClicked("apple");}
void GameWindow::on_apple_clicked() {this->buildingClicked("apple");}

// Inn
void GameWindow::on_inn_unbuilt_clicked() {this->buildingClicked("inn");}
void GameWindow::on_inn_clicked() {this->buildingClicked("inn");}

// Farm
void GameWindow::on_farm_unbuilt_clicked() {this->buildingClicked("farm");}
void GameWindow::on_farm_clicked() {this->buildingClicked("farm");}

// Blacksmith
void GameWindow::on_blacksmith_unbuilt_clicked() { this->buildingClicked("blacksmith");}
void GameWindow::on_blacksmith_clicked() {this->buildingClicked("blacksmith");}

// Clothes Shop
void GameWindow::on_clothes_shop_unbuilt_clicked() { this->buildingClicked("clothes");}
void GameWindow::on_clothes_shop_clicked() {this->buildingClicked("clothes");}

// Mine
void GameWindow::on_mine_unbuilt_clicked() {this->buildingClicked("mine");}
void GameWindow::on_mine_clicked() {this->buildingClicked("mine");}

// Hunter Hunt
void GameWindow::on_hunter_hut_unbuilt_clicked() {this->buildingClicked("hunter");}
void GameWindow::on_hunter_hut_clicked() {this->buildingClicked("hunter");}

// Food Shop
void GameWindow::on_food_shop_unbuilt_clicked() {this->buildingClicked("food");}
void GameWindow::on_food_shop_clicked() {this->buildingClicked("food");}

// Lumberjack
void GameWindow::on_lumberjack_unbuilt_clicked() {this->buildingClicked("lumberjack");}
void GameWindow::on_lumberjack_clicked() {this->buildingClicked("lumberjack");}
