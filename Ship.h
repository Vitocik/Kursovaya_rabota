//Ship.h
#pragma once
#ifndef SHIP_H
#define SHIP_H

#include <vector>

enum class CellState { Empty, MissedShot, Ship, HitShip };

class Ship {
public:
    int size; // ������ �������
    bool isHorizontal; // ���������� ������� (������������ ��� ��������������)
    std::vector<CellState> cells; // ������ ��������� �����, �� ������� ������� �������

    Ship(int size, bool isHorizontal); // ����������� ������ Ship

    void displayShipDetails() const; // ����� ��� ����������� ������� �������
};
#endif // SHIP_H
