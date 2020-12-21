#include "game_window.h"
#include "ui_game_window.h"
#include <QDesktopServices>
#include <QUrl>


/**
 * Constructor.
 */
GameWindow::GameWindow(QWidget *parent, QString saved_path) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);

    // initializing gold purse
    this->purse = new GoldPurse(ui->gold_label);

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
                                              10, 700, 300);
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
                                             100, 1200, 1500);
    this->buildings["food"] = new Building("Food Shop",
                                           ui->food_shop_unbuilt,ui->food_shop,
                                           this->purse,
                                           20, 700, 500);
    this->buildings["lumberjack"] = new Building("Lumberjack",
                                                 ui->lumberjack_unbuilt,ui->lumberjack,
                                                 this->purse,
                                                 40, 1000, 700);

    // loading data
    bool load_successful = false;
    if(saved_path != nullptr)
        load_successful = this->load_game(saved_path);

    if(!load_successful) {
        this->purse->addGold(500);  // initial gold

        if(saved_path != nullptr) {
            QMessageBox *dialog = new QMessageBox;
            dialog->setWindowTitle("Error");
            dialog->setText("Unknown error while loading the saved game. Starting new game instead...");
            dialog->exec();
        }
    }
}


/**
 * Destructor.
 */
GameWindow::~GameWindow() {
    delete ui;
}


/**
 * @brief GameWindow::saveGame
 */
void GameWindow::saveGame() {
    // creating dir
    QString path("./saved_games/");
    QDir dir;

    if(!dir.exists(path))
        dir.mkpath(path);

    // getting current date and time
    time_t now = time(0);
    struct tm  tstruct = *localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer),
             "game_%Y-%m-%d-%H-%M-%S.pd", &tstruct);
    path = QString("%1%2").arg(path, buffer);

    // ask for a path to the user
    path = QFileDialog::getSaveFileName(
                this, tr("Saved Game File"), path,
                tr("Profitable Dungeons Saved Game (*.pd)"));

    // creating file
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    // gold
    QTextStream stream( &file );
    stream << QString::number(this->purse->getBalance()) << endl;

    // buildings
    for(auto key: this->buildings.keys()) {
        stream << key << endl;
        stream << this->buildings[key]->getTier() << endl;
    }

    // finishing
    file.close();

    QMessageBox *dialog = new QMessageBox;
    dialog->setWindowTitle("Game saved");
    dialog->setText(QString("Game saved to \"%1\"").arg(path));
    dialog->exec();
}


/**
 * @brief GameWindow::load_game
 * @param path
 * @return
 */
bool GameWindow::load_game(QString path) {
    QFile file(path);

    // checking if file was openned correctly
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;


    // reading data
    QTextStream in(&file);
    int gold = in.readLine().toInt();

    QString line[2];
    QMap <QString, int> tiers;

    while(!in.atEnd()){
        line[0] = in.readLine(); // building
        line[1] = in.readLine(); // tier

        if(line[0].isEmpty() || line[1].isEmpty()){
            file.close();
            return false;
        }

        tiers[line[0]] = line[1].toInt();
    }

    file.close();

    // updating tiers and gold
    for(auto key: tiers.keys())
        this->buildings[key]->upgrade(tiers[key]);

    this->purse->addGold(gold);
    return true;
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


/**
 * @brief GameWindow::on_save_clicked
 */
void GameWindow::on_save_clicked() { this->saveGame();}

// Help
void GameWindow::on_help_clicked(){ QDesktopServices::openUrl(QUrl("Manual_Profit_Dungeon.pdf",QUrl::TolerantMode));}

// Tavern
void GameWindow::on_tavern_clicked() {this->buildingClicked("tavern");}

// Castle
void GameWindow::on_castle_unbuilt_clicked() { this->buildingClicked("castle");}
void GameWindow::on_castle_clicked() { this->buildingClicked("castle");}

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
