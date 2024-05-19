#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include <QDialog>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); // Конструктор класса
    ~MainWindow(); // Деструктор класса


protected:
    virtual void keyPressEvent(QKeyEvent * event); // Обработчик нажатия клавиш

private slots:
    void Init(); // Инициализация окна

private:

    void showDialog(); // Показать окно меню
    void Generate(); // Генерация элементов игры
    void up(); // Движение вверх
    void down();
    void left();
    void right();
    void rotate(); // Поворот
    void changeColor(int x, int y); // Изменение цвета
    bool checkGameOver(); // Проверка на окончание игры
    int score; // Переменная для хранения счета

    QWidget *centralWidget; // Центральный виджет
    QPushButton *newGame; // Кнопка "Новая игра"
    QLabel *title, *title2; // Заголовки
    QLabel *scoreLabel; // Метка для отображения счета
    QGridLayout *grid; // Сетка для размещения элементов игры
    QLabel* labels[4][4]; // Двумерный массив меток для отображения игрового поля
};

#endif // MAINWINDOW_H


