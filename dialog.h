#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel> // Добавляем заголовочный файл для QLabel
#include <QVBoxLayout> // Добавляем заголовочный файл для QVBoxLayout

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr); // Конструктор класса Dialog
    ~Dialog(); // Конструктор класса Dialog
signals:
    void continueGame(); // Отправляет сигнал о продолжении игры
    void exitGame(); // Отправляет сигнал о завершении игры
private slots:
    //void on_pushButton_2_released();
    void continueButtonReleased();// Слот для кнопки продолжения игры
    //void on_pushButton_released();
    void exitButtonReleased();// Слот для кнопки выхода из игры
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
