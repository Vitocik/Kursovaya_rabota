//main.cpp
#include "PlayerField.h"
#include <iostream>
#include <ctime>
using namespace std;

void displayMapLegend() {
    cout << "Легенда карты:" << endl;
    cout << "S - Корабль" << endl;
    cout << "- - Промах" << endl;
    cout << "X - Попадание по кораблю" << endl;
    cout << ". - Пустая ячейка" << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0)); // Инициализация генератора случайных чисел

    int rows = 10, cols = 10;
    PlayerField myField(rows, cols);
    PlayerField enemyField(rows, cols);
    // Меню выбора метода размещения кораблей
    cout << "Выберите метод размещения кораблей:" << endl;
    cout << "1. Разместить корабли вручную" << endl;
    cout << "2. Автоматическое размещение кораблей" << endl;
    int placementMethod;
    cin >> placementMethod;

    if (placementMethod == 1) {
        myField.manuallyPlaceShips();
    }
    else if (placementMethod == 2) {
        // Автоматическое размещение кораблей на обоих полях
        myField.placeShip(Ship(4, true));
        myField.placeShip(Ship(3, false));
        myField.placeShip(Ship(3, true));
        myField.placeShip(Ship(2, false));
        myField.placeShip(Ship(2, true));
        myField.placeShip(Ship(2, false));
        myField.placeShip(Ship(1, true));
        myField.placeShip(Ship(1, false));
        myField.placeShip(Ship(1, true));
        myField.placeShip(Ship(1, false));
    }

    // Автоматическое размещение кораблей на поле противника
    enemyField.placeShip(Ship(4, true));
    enemyField.placeShip(Ship(3, false));
    enemyField.placeShip(Ship(3, true));
    enemyField.placeShip(Ship(2, false));
    enemyField.placeShip(Ship(2, true));
    enemyField.placeShip(Ship(2, false));
    enemyField.placeShip(Ship(1, true));
    enemyField.placeShip(Ship(1, false));
    enemyField.placeShip(Ship(1, true));
    enemyField.placeShip(Ship(1, false));

    bool extraTurn = false; // Флажок, указывающий, получает ли игрок дополнительный ход
    int turn = 1;
    while (true) {
        cout << "Поле противника:" << endl;
        myField.displayField();

        cout << "Ваше поле:" << endl;
        enemyField.displayField(true); // Не показывать корабли противника
        displayMapLegend();
        if (turn % 2 == 1) { // Ваш ход
            cout << "Ваш ход!" << endl;
            cout << "Хотите сделать ход сами? (1) или сгенерировать его? (2) или взять координаты из файла? (3): ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                if (!myField.takeQueryShot()) {
                    cout << "Мимо!" << endl;
                }
                else {
                    cout << "Попадание!" << endl;
                    extraTurn = true; // Установите флажок для дополнительного хода
                }
            }
            else if (choice == 2) {
                if (!myField.takeRandomShot()) {
                    cout << "Мимо!" << endl;
                }
                else {
                    cout << "Попадание!" << endl;
                    extraTurn = true; // Установите флажок для дополнительного хода
                }
            }
            else if (choice == 3) {
                // Взять координаты выстрела из файла
                string filename;
                cout << "Введите имя файла, из которого нужно сделать выстрел: ";
                cin >> filename;
                if (!myField.takeFileShot(filename)) {
                    cout << "Ошибка: Не удалось сделать выстрел из файла." << endl;
                }
                else {
                    extraTurn = true; // Установите флажок для дополнительного хода, если выстрел попадет в цель
                }
            }
            else {
                cout << "Неверный выбор. По умолчанию совершается ваш ход." << endl;
                if (!myField.takeQueryShot()) {
                    cout << "Мимо!" << endl;
                }
                else {
                    cout << "Попадание!" << endl;
                    extraTurn = true; // Установите флажок для дополнительного хода
                }
            }
        }
        else if (turn % 2 == 0) { // Ход противника
            cout << "Ход противника!" << endl;
            if (!enemyField.takeRandomShot()) {
                cout << "Противник промахнулся." << endl;
            }
            else {
                cout << "Противник попал в ваш корабль!" << endl;
                extraTurn = true; // Установите флажок для дополнительного хода
            }
        }

        // Проверьте, получает ли игрок дополнительный ход
        if (!extraTurn) {
            turn++; // Если дополнительного хода нет, ход переходит к следующему игроку

        }
        extraTurn = false; // Сбросьте флажок для следующего хода

        if (enemyField.allShipsSunk()) {
            cout << "Вы проиграли!" << endl;
            break;
        }
        else if (myField.allShipsSunk()) {
            cout << "Вы выиграли!" << endl;
            break;
        }
    }

    return 0;
}
