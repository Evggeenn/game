#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Создаем QLabel для отображения "Game Over"
    QLabel *gameOverLabel = new QLabel("Game Over", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet("QLabel { color: red; font: 24pt; font-weight: bold; }");

    // Добавляем QLabel в вертикальный layout для централизации
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(gameOverLabel);

    // Добавляем кнопки под надписью "Game Over"
    layout->addWidget(ui->pushButton_2);
    layout->addWidget(ui->pushButton);


    // Подключаем сигналы от кнопок к соответствующим слотам
    connect(ui->pushButton_2, &QPushButton::released, this, &Dialog::continueButtonReleased);
    connect(ui->pushButton, &QPushButton::released, this, &Dialog::exitButtonReleased);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::continueButtonReleased()
{
    // Излучаем сигнал о продолжении игры
    emit this->continueGame();
    // Скрываем диалоговое окно
    this->hide();
}

void Dialog::exitButtonReleased()
{
    // Излучаем сигнал о завершении игры
    emit this->exitGame();
    // Скрываем диалоговое окно
    this->hide();
}


