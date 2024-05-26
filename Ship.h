//Ship.h
#pragma once
#ifndef SHIP_H
#define SHIP_H

#include <vector>

enum class CellState { Empty, MissedShot, Ship, HitShip };

class Ship {
public:
    int size; // Размер корабля
    bool isHorizontal; // Ориентация корабля (вертикальная или горизонтальная)
    std::vector<CellState> cells; // Вектор состояний ячеек, из которых состоит корабль

    Ship(int size, bool isHorizontal); // Конструктор класса Ship

    void displayShipDetails() const; // Метод для отображения деталей корабля
};
#endif // SHIP_H
