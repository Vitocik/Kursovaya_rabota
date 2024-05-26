//Ship.cpp
#include "Ship.h"
#include <iostream>

// Определение конструктора класса Ship
Ship::Ship(int size, bool isHorizontal) : size(size), isHorizontal(isHorizontal) {
    cells.resize(size, CellState::Ship); // Инициализация вектора cells
}

// Метод для отображения деталей корабля
void Ship::displayShipDetails() const {
    // Вывод корабля в зависимости от его ориентации
    if (isHorizontal) {
        for (int i = 0; i < size; i++) {
            std::cout << (cells[i] == CellState::Ship ? "S " : ". ");
        }
        std::cout << std::endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            std::cout << (cells[i] == CellState::Ship ? "S\n" : ".") << std::endl;
        }
    }
}
