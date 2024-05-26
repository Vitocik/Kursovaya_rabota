//Ship.cpp
#include "Ship.h"
#include <iostream>

// ����������� ������������ ������ Ship
Ship::Ship(int size, bool isHorizontal) : size(size), isHorizontal(isHorizontal) {
    cells.resize(size, CellState::Ship); // ������������� ������� cells
}

// ����� ��� ����������� ������� �������
void Ship::displayShipDetails() const {
    // ����� ������� � ����������� �� ��� ����������
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
