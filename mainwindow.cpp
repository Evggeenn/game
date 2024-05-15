
#include "mainwindow.h" // Включение заголовочного файла класса MainWindow
//#include "ui_mainwindow.h" // Включение сгенерированного файла ui для класса MainWindow

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Конструктор класса MainWindow
    centralWidget = new QWidget(this); // Создание центрального виджета
    this->setCentralWidget(centralWidget); // Установка центрального виджета для главного окна
    grid = new QGridLayout(centralWidget); // Создание сетки размещения виджетов

    newGame = new QPushButton(); // Создание кнопки "New Game"
    newGame->setText("New Game"); // Установка текста кнопки
    QObject::connect(newGame, SIGNAL(clicked()), this, SLOT(Init())); // Подключение сигнала нажатия кнопки к слоту Init()
    grid->addWidget(newGame, 0, 2); // Добавление кнопки в сетку

    title = new QLabel("2048", this); // Создание метки "2048"
    title->setAlignment(Qt::AlignCenter); // Установка выравнивания текста
    title->setStyleSheet("QLabel {color: red; font:20pt; font-weight:300; }"); // Установка стилей CSS для метки
    grid->addWidget(title, 0, 0); // Добавление метки в сетку

    title2 = new QLabel("game", this); // Создание второй метки "game"
    title2->setAlignment(Qt::AlignCenter); // Установка выравнивания текста
    title2->setStyleSheet("QLabel { color: black; font:20pt; font-weight:300; }"); // Установка стилей CSS для метки
    grid->addWidget(title2, 0, 1); // Добавление второй метки в сетку

    score = 0; // Инициализация счета
    scoreLabel = new QLabel("Score: \n 0", this); // Создание метки для отображения счета
    scoreLabel->setAlignment(Qt::AlignCenter); // Установка выравнивания текста
    scoreLabel->setStyleSheet("QLabel { background-color: #bbae9e; color: white; font:15pt; font-weight:200; border-radius: 5px; }"); // Установка стилей CSS для метки счета
    grid->addWidget(scoreLabel, 0, 3); // Добавление метки счета в сетку

    // Создание и расстановка меток для игрового поля
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            labels[i][j] = new QLabel("", this); // Создание метки
            grid->addWidget(labels[i][j], i+1, j); // Добавление метки в сетку
            labels[i][j]->setAlignment(Qt::AlignCenter); // Установка выравнивания текста
            changeColor(i, j); // Вызов функции изменения цвета
        }
    labels[1][0]->setFocus(); // Установка фокуса на определенную метку

    setWindowTitle("2048"); // Установка заголовка главного окна
    setFixedSize(600, 600); // Установка фиксированных размеров главного окна
    Generate(); // Генерация элементов игры
}

MainWindow::~MainWindow() {
    // Деструктор класса MainWindow
    // Удаление динамически выделенной памяти для меток игрового поля
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            delete labels[i][j];
}

void MainWindow::Init() {
    // Слот для инициализации окна
    // Очистка меток игрового поля и генерация новых элементов игры
    score = 0; // Обнуляем счет
    scoreLabel->setText("Score: \n 0"); // Обновляем отображение счет
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            labels[i][j]->setText(""); // Очистка текста метки
            changeColor(i, j); // Вызов функции изменения цвета
        }
    newGame->clearFocus(); // Снятие фокуса с кнопки "New Game"
    Generate(); // Генерация элементов игры
}

// void MainWindow::Generate() {
//     // Генерация новых элементов игры
//     bool hasPlace = false; // Флаг наличия свободного места на игровом поле
//     for (int i = 0; i < 4; ++i)
//         for (int j = 0; j < 4; ++j) {
//             if (labels[i][j]->text() == "" || labels[i][j]->text() == "2") {
//                 hasPlace = true; // Если нашлось свободное место или пустая метка со значением "2", устанавливаем флаг в true
//                 break;
//             }
//         }
//     if (!hasPlace) {
//         // Если свободного места нет
//         QDialog* endDialog = new QDialog(); // Создание диалогового окна
//         endDialog->setMinimumWidth(200); // Установка минимальной ширины окна
//         endDialog->show(); // Отображение окна
//     }
//     int row = 0, column = 0; // Переменные для строки и столбца
//     // Выбор случайной пустой ячейки для добавления нового элемента
//     do {
//         row = rand() % 4; // Генерация случайной строки
//         column = rand() % 4; // Генерация случайного столбца
//     } while (labels[row][column]->text() != "" && labels[row][column]->text() != "2"); // Повторяем, пока выбранная ячейка не будет пустой или содержать "2"
//     labels[row][column]->setText(QString::number(labels[row][column]->text().toInt() + 2)); // Установка значения в выбранную ячейку
//     changeColor(row,column); // Вызов функции изменения цвета
// }

void MainWindow::Generate() {
    // Проверка наличия свободного места на игровом поле
    bool hasPlace = false;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (labels[i][j]->text() == "" || labels[i][j]->text() == "2") {
                hasPlace = true;
                break;
            }
        }
        if (hasPlace) {
            break;
        }
    }

    if (!hasPlace) {
        // Если свободного места нет, проверяем возможность продолжения игры
        bool canContinue = false;
        // Проверяем, можно ли объединить какие-либо пары элементов
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QString current = labels[i][j]->text();
                // Проверяем элементы сверху, снизу, слева и справа
                if ((i > 0 && labels[i - 1][j]->text() == current) ||
                    (i < 3 && labels[i + 1][j]->text() == current) ||
                    (j > 0 && labels[i][j - 1]->text() == current) ||
                    (j < 3 && labels[i][j + 1]->text() == current)) {
                    canContinue = true;
                    break;
                }
            }
            if (canContinue) {
                break;
            }
        }

        if (!canContinue) {
            // Если нельзя продолжить игру, показываем сообщение о завершении игры
            QDialog* gameOverDialog = new QDialog(this);
            QLabel* gameOverLabel = new QLabel("Игра окончена", gameOverDialog);
            gameOverLabel->setAlignment(Qt::AlignCenter);
            QVBoxLayout* layout = new QVBoxLayout(gameOverDialog);
            layout->addWidget(gameOverLabel);
            gameOverDialog->exec();
            return;
        }
    }

    // Генерация нового элемента, если есть свободное место
    int row = 0, column = 0;
    do {
        row = rand() % 4;
        column = rand() % 4;
    } while (labels[row][column]->text() != "" && labels[row][column]->text() != "2");
    labels[row][column]->setText(QString::number(labels[row][column]->text().toInt() + 2));
    changeColor(row, column);
}

void MainWindow::changeColor(int i, int j)

{
    // Функция для изменения цвета метки в зависимости от значения в ней
    switch (labels[i][j]->text().toInt()) {
    case 0:
        labels[i][j]->setStyleSheet("QLabel { background-color: #cdc1b5; color: black; font:20pt; font-weight:400; border-radius: 5px;}");
        break;
    case 2:
        labels[i][j]->setStyleSheet("QLabel { background-color: #eee4da; color: black; font:20pt; font-weight:400; border-radius: 5px;}");
        break;
    case 4:
        labels[i][j]->setStyleSheet("QLabel { background-color: #eddfc4; color: black; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 8:
        labels[i][j]->setStyleSheet("QLabel { background-color: #f4b17a; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 16:
        labels[i][j]->setStyleSheet("QLabel { background-color: #f79663; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 32:
        labels[i][j]->setStyleSheet("QLabel { background-color: #f67d62; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 64:
        labels[i][j]->setStyleSheet("QLabel { background-color: #f65e39; color: white; font:20pt; font-weight:400; border-radius: 5px;}");
        break;
    case 128:
        labels[i][j]->setStyleSheet("QLabel { background-color: #edce73; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 256:
        labels[i][j]->setStyleSheet("QLabel { background-color: #e9cf58; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 512:
        labels[i][j]->setStyleSheet("QLabel { background-color: #edc651; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 1024:
        labels[i][j]->setStyleSheet("QLabel { background-color: #eec744; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    case 2048:
        labels[i][j]->setStyleSheet("QLabel { background-color: #edca64; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;
    }
}

// void MainWindow::keyPressEvent(QKeyEvent * event) {
//     // Обработчик события нажатия клавиш
//     QString* a[4][4]; // Создание массива строк для хранения предыдущего состояния меток
//     for (int i = 0; i < 4; ++i)
//         for (int j = 0; j < 4; ++j)
//             a[i][j] = new QString(labels[i][j]->text()); // Сохранение текущего состояния меток

//     switch (event->key()) {
//     case Qt::Key_Up:
//         up(); // Обработка нажатия клавиши "Вверх"
//         break;
//     case Qt::Key_Down:
//         down(); // Обработка нажатия клавиши "Вниз"
//         break;
//     case Qt::Key_Left:
//         left(); // Обработка нажатия клавиши "Влево"
//         break;
//     case Qt::Key_Right:
//         right(); // Обработка нажатия клавиши "Вправо"
//         break;
//     default:
//         QMainWindow::keyPressEvent(event); // Обработка других клавиш
//     }

//     bool flag = false; // Флаг для определения изменилось ли состояние меток
//     for (int i = 0; i < 4; ++i)
//         for (int j = 0; j < 4; ++j)
//             if (a[i][j] != labels[i][j]->text())
//                 flag = true; // Если хотя бы одна метка изменила значение, устанавливаем флаг в true
//     if (flag)
//         Generate(); // Если состояние меток изменилось, генерируем новый элемент игры
// }



void MainWindow::keyPressEvent(QKeyEvent * event) {
    QString* a[4][4]; // Создание массива строк для хранения предыдущего состояния меток
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = new QString(labels[i][j]->text()); // Сохранение текущего состояния меток

    switch (event->key()) {
    case Qt::Key_Up:
        up(); // Обработка нажатия клавиши "Вверх"
        break;
    case Qt::Key_Down:
        down(); // Обработка нажатия клавиши "Вниз"
        break;
    case Qt::Key_Left:
        left(); // Обработка нажатия клавиши "Влево"
        break;
    case Qt::Key_Right:
        right(); // Обработка нажатия клавиши "Вправо"
        break;
    default:
        QMainWindow::keyPressEvent(event); // Обработка других клавиш
    }

    bool flag = false; // Флаг для определения изменилось ли состояние меток
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (a[i][j] != labels[i][j]->text())
                flag = true; // Если хотя бы одна метка изменила значение, устанавливаем флаг в true
    if (flag)
        Generate(); // Если состояние меток изменилось, генерируем новый элемент игры

    // Проверяем, есть ли возможность продолжить игру
    bool hasPlace = false;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (labels[i][j]->text() == "" || labels[i][j]->text() == "2") {
                hasPlace = true;
                break;
            }
        }
        if (hasPlace) {
            break;
        }
    }

    if (!hasPlace) {
        // Если свободного места нет, проверяем возможность продолжения игры
        bool canContinue = false;
        // Проверяем, можно ли объединить какие-либо пары элементов
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QString current = labels[i][j]->text();
                // Проверяем элементы сверху, снизу, слева и справа
                if ((i > 0 && labels[i - 1][j]->text() == current) ||
                    (i < 3 && labels[i + 1][j]->text() == current) ||
                    (j > 0 && labels[i][j - 1]->text() == current) ||
                    (j < 3 && labels[i][j + 1]->text() == current)) {
                    canContinue = true;
                    break;
                }
            }
            if (canContinue) {
                break;
            }
        }

        if (!canContinue) {
            // Если нельзя продолжить игру, показываем сообщение о завершении игры
            QDialog* gameOverDialog = new QDialog(this);
            QLabel* gameOverLabel = new QLabel("Игра окончена", gameOverDialog);
            gameOverLabel->setAlignment(Qt::AlignCenter);
            QVBoxLayout* layout = new QVBoxLayout(gameOverDialog);
            layout->addWidget(gameOverLabel);
            gameOverDialog->exec();
            return;
        }
    }
}


void MainWindow::down() {
    // Функция для движения элементов игры вниз
    // Цикл для перемещения пустых ячеек вниз
    for (int j = 0; j < 4; ++j)
        for (int i = 3; i >= 0; --i)
            if (labels[i][j]->text() == "") // Если текущая ячейка пуста
                for (int k = i-1; k >= 0; --k)
                    if (labels[k][j]->text() != "") { // Поиск первой непустой ячейки выше текущей
                        labels[i][j]->setText(labels[k][j]->text()); // Перемещение значения из найденной ячейки в текущую
                        changeColor(i,j); // Изменение цвета текущей ячейки
                        labels[k][j]->setText(""); // Очистка найденной ячейки
                        changeColor(k,j); // Изменение цвета найденной ячейки
                        break;
                    }
    int k;
    // Цикл для слияния одинаковых значений внизу
    for (int j = 0; j < 4; ++j) {
        for (int i = 2; i >= 0; i--) {
            if (labels[i][j]->text() == labels[i+1][j]->text() && labels[i][j]->text() != "") { // Если две соседние ячейки имеют одинаковые значения и они не пусты
                labels[i+1][j]->setText(QString::number(labels[i+1][j]->text().toInt() * 2)); // Увеличиваем значение в ячейке в два раза
                score += labels[i+1][j]->text().toInt(); // Увеличиваем счет
                scoreLabel->setText("Score: \n" + QString::number(score)); // Обновляем отображение счета
                    changeColor(i+1, j); // Изменяем цвет ячейки
                k = i;
                while (k > 0) { // Перемещение значений вверх, чтобы заполнить пустые места
                    k--;
                    labels[k+1][j]->setText(labels[k][j]->text()); // Перемещение значения в ячейке выше
                    changeColor(k+1, j); // Изменение цвета ячейки
                }
                if (k == 0) { // Если достигнут верхний край игрового поля
                    labels[0][j]->setText(""); // Очищаем верхнюю ячейку
                    changeColor(0, j); // Изменяем цвет верхней ячейки
                }
            }
        }
    }
}

void MainWindow::up() {
    // Функция для движения элементов игры вверх
    rotate(); // Поворот игрового поля на 180 градусов
    rotate(); // Повторный поворот игрового поля на 180 градусов
    down(); // Вызов функции движения элементов игры вниз
    rotate(); // Поворот игрового поля на 180 градусов
    rotate(); // Повторный поворот игрового поля на 180 градусов
}

void MainWindow::left() {
    // Функция для движения элементов игры влево
    rotate(); // Поворот игрового поля
    down(); // Вызов функции движения элементов игры вниз
    rotate(); // Поворот игрового
    rotate(); // Повторный поворот
    rotate(); // Повторный поворот
}

void MainWindow::right() {
    // Функция для движения элементов игры вправо
    rotate(); // Поворот игрового поля
    rotate(); // Повторный поворот игрового поля
    rotate(); // Повторный поворот игрового поля
    down(); // Вызов функции движения элементов игры вниз
    rotate(); // Поворот игрового поля
}

void MainWindow::rotate() {
    // Функция для поворота элементов игры на 90 градусов
    int a[4][4]; // Создание временного массива для хранения значений меток
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            a[4-j-1][i] = labels[i][j]->text().toInt(); // Поворот значений на 90 градусов
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            if (a[i][j] == 0) { // Если значение в ячейке равно 0
                labels[i][j]->setText(""); // Очищаем метку
            } else {
                labels[i][j]->setText(QString::number(a[i][j])); // Иначе, устанавливаем новое значение в метке
            }
            changeColor(i, j); // Изменяем цвет метки
        }
}











