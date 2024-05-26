//PlayerField.h
#pragma once
#ifndef PLAYERFIELD_H
#define PLAYERFIELD_H

#include "Ship.h"
#include <vector>
#include <fstream>

class PlayerField {
public:
    std::vector<std::vector<CellState>> field; 
    int rows; 
    int cols; 

    PlayerField(int rows, int cols); 

    void placeShip(const Ship& ship); // ����� ��� ���������� �������
    bool canPlaceShip(const Ship& ship, int x, int y); // ����� ��� �������� ����������� ���������� �������
    void displayField(bool showShips = false) const; // ����� ��� ����������� �������� ����
    void manuallyPlaceShips(); // ����� ��� ������� ���������� ��������
    bool takeFileShot(const std::string& filename); // ������ ��������� �������� �� �����
    bool takeShot(int x, int y); // ����� ��� ���������� ��������
    bool allShipsSunk() const; // ����� ��� �������� ���������� ���� ��������
    bool takeQueryShot(); // ����� ��� ���������� ���� � ������ ��������� �� ������������
    bool takeRandomShot(); // ����� ��� ���������� ���������� ����
};

#endif // PLAYERFIELD_H