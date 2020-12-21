#include "game_window.h"
#include "ui_game_window.h"



/**
 * Constructor.
 */
GameWindow::GameWindow(QWidget *parent,QString path) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);

    //Default data;
    int current_gold;
    //Verify if we will use the save data
    bool save_correct_read = false;
    QString line[2];

    //Have saved data
    if(path != nullptr){
        QFile file(path);
        save_correct_read = true;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox *dialog = new QMessageBox;
            dialog->setWindowTitle("Error#0");
            dialog->setText("Error to read your save");
            dialog->show();
            save_correct_read = false;
        }
        else{
            //Read the data

           QTextStream in(&file);
           //First read the gold value
           current_gold = in.readLine().toInt();
           while(!in.atEnd()){
               line[0] = in.readLine();
               line[1] = in.readLine();
               //Se alguma das duas for NULL algo está errado no arquivo de save
               if(line[0].isEmpty() || line[1].isEmpty()){
                   QMessageBox *dialog = new QMessageBox;
                   dialog->setWindowTitle("Error#1");
                   dialog->setText("Error to read your save");
                   dialog->show();
                   save_correct_read = false;
                   break;
               }
               else{
                   //Inicializa o tier lido
                    this->buildings_tier[line[0]] = line[1].toInt();
               }
           }
        }

        file.close();
    }


    // initialize current_tier to 0 and initialize current_gold
    if(!save_correct_read){
        current_gold = 1500;
        // initializing buildings
        this->buildings_tier["Blacksmith"] = 0;
        this->buildings_tier["Castle"] = 0;
        this->buildings_tier["Tavern"] = 0;
        this->buildings_tier["Clothes Shop"] = 0;
        this->buildings_tier["Apple Orchard"] = 0;
        this->buildings_tier["Inn"] = 0;
        this->buildings_tier["Farm"] = 0;
        this->buildings_tier["Mine"] = 0;
        this->buildings_tier["Hunter Hut"] = 0;
        this->buildings_tier["Food Shop"] = 0;
        this->buildings_tier["Lumberjack"] = 0;
    }

    // initializing gold purse
    this->purse = new GoldPurse(ui->gold_label);
    purse->addGold(current_gold);  // initial gold

    // initializing buildings
    this->buildings["blacksmith"] = new Building("Blacksmith",
                                                 ui->blacksmith_unbuilt, ui->blacksmith,
                                                 this->purse,
                                                 500, 1200, 5000,this->buildings_tier["Blacksmith"]);
    this->buildings["castle"] = new Building("Castle",
                                             ui->castle_unbuilt, ui->castle,
                                             this->purse,
                                             10000, 2000, 1000000,this->buildings_tier["Castle"]);
    this->buildings["tavern"] = new Building("Tavern",
                                             nullptr, ui->tavern,
                                             this->purse,
                                             30, 1000, 500,this->buildings_tier["Tavern"]);
    this->buildings["clothes"] = new Building("Clothes Shop",
                                              ui->clothes_shop_unbuilt, ui->clothes_shop,
                                              this->purse,
                                              10,700,300,this->buildings_tier["Clothes Shop"]);
    this->buildings["apple"] = new Building("Apple Orchard",
                                            ui->apple_unbuilt, ui->apple,
                                            this->purse,
                                            5, 500, 100,this->buildings_tier["Apple Orchard"]);
    this->buildings["inn"] = new Building("Inn",
                                          ui->inn_unbuilt, ui->inn,
                                          this->purse,
                                          60, 1000, 1000,this->buildings_tier["Inn"]);
    this->buildings["farm"] = new Building("Farm",
                                          ui->farm_unbuilt, ui->farm,
                                          this->purse,
                                          20, 700, 500,this->buildings_tier["Farm"]);
    this->buildings["mine"] = new Building("Mine",
                                           ui->mine_unbuilt, ui->mine,
                                           this->purse,
                                           80, 1100, 1200,this->buildings_tier["Mine"]);
    this->buildings["hunter"] = new Building("Hunter Hut",
                                             ui->hunter_hut_unbuilt,ui->hunter_hut,
                                             this->purse,
                                             100,1200,1500,this->buildings_tier["Hunter Hut"]);
    this->buildings["food"] = new Building("Food Shop",
                                           ui->food_shop_unbuilt,ui->food_shop,
                                           this->purse,
                                           20,700,500,this->buildings_tier["Food Shop"]);
    this->buildings["lumberjack"] = new Building("Lumberjack",
                                                 ui->lumberjack_unbuilt,ui->lumberjack,
                                                 this->purse,
                                                 40,1000,700,this->buildings_tier["Lumberjack"]);
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
            this->buildings_tier[b->getName()] = b->getTier();
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
        this->buildings_tier[b->getName()] = b->getTier();
    }
}

// Save
void GameWindow::on_save_clicked(){

    QFile file("dados.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QString money = QString::number(this->purse->getBalance());

    QTextStream stream( &file );
    stream << money << endl;

    for(QMap<QString, int>::iterator it = this->buildings_tier.begin(); it != this->buildings_tier.end(); ++it){
        stream << it.key() << endl;
        QString value = QString::number(it.value());
        stream << value << endl;
    }


    file.close();

    QMessageBox *dialog = new QMessageBox;
    dialog->setWindowTitle("Save");
    dialog->setText("Game Saved");
    dialog->show();
}

//FUNÇÃO PARA O BOTAO DE SAIR
/*


  QFile file("dados.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QString money = QString::number(this->purse->getBalance());

    QTextStream stream( &file );
    stream << money << endl;

    for(QMap<QString, int>::iterator it = this->buildings_tier.begin(); it != this->buildings_tier.end(); ++it){
        stream << it.key() << endl;
        QString value = QString::number(it.value());
        stream << value << endl;
    }


    file.close();

    QMessageBox *dialog = new QMessageBox;
    dialog->setWindowTitle("Save");
    dialog->setText("Game Saved");
    dialog->show();
    delete ui;
    QCoreApplication::exit();


*/

// Tavern
void GameWindow::on_tavern_clicked() {

    QFile file("dados.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QString money = QString::number(this->purse->getBalance());

    QTextStream stream( &file );
    stream << money << endl;

    for(QMap<QString, int>::iterator it = this->buildings_tier.begin(); it != this->buildings_tier.end(); ++it){
        stream << it.key() << endl;
        QString value = QString::number(it.value());
        stream << value << endl;
    }


    file.close();

    QMessageBox *dialog = new QMessageBox;
    dialog->setWindowTitle("Save");
    dialog->setText("Game Saved");
    dialog->show();

    this->buildingClicked("tavern");}

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
