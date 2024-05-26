//PlayerField.cpp
#include "PlayerField.h"
#include <iostream>
#include <ctime>
#include <fstream>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* ������� */
#define GREEN   "\033[32m"      /* ������� */
#define CYAN    "\033[36m"      /* ���� */
// ����������� ������������ ������ PlayerField
PlayerField::PlayerField(int rows, int cols) : rows(rows), cols(cols), field(rows, std::vector<CellState>(cols, CellState::Empty)) {}

// ����� ��� ���������� �������
void PlayerField::placeShip(const Ship& ship) {
    int x, y;
    do {
        x = rand() % rows;
        y = rand() % cols;
    } while (!canPlaceShip(ship, x, y));

    for (int i = 0; i < ship.size; i++) {
        field[x + (ship.isHorizontal ? 0 : i)][y + (ship.isHorizontal ? i : 0)] = CellState::Ship;
    }
}

// ����� ��� �������� ����������� ���������� �������
bool PlayerField::canPlaceShip(const Ship& ship, int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // ����� �� �������
    }

    for (int i = 0; i < ship.size; i++) {
        int cx = x + (ship.isHorizontal ? 0 : i);
        int cy = y + (ship.isHorizontal ? i : 0);

        if (cx < 0 || cx >= rows || cy < 0 || cy >= cols || field[cx][cy] != CellState::Empty) {
            return false; // ������� ������������� � ������ �������� ��� ������� �� �������
        }

        // �������� �������� ����� �� ������� �������
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && field[nx][ny] == CellState::Ship) {
                    return false; // ������� ����������� � ������ ��������
                }
            }
        }
    }
    return true;
}

bool PlayerField::takeFileShot(const std::string& filename) {
    std::ifstream file(filename); // ������� ���� ��� ������
    if (!file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� " << filename << std::endl;
        return false;
    }

    int x, y;
    if (!(file >> x >> y)) {
        std::cerr << "������: �� ������� ��������� ���������� �� ����� " << filename << std::endl;
        file.close();
        return false;
    }

    file.close(); // ������� ����

    return takeShot(x, y); // ������� �������, ��������� ����������, ��������� �� �����
}
// ����� ��� ����������� �������� ����
void PlayerField::displayField(bool showShips) const {
    // ����� ������� �������� � ���������� �����������
    std::cout << " ";
    for (int col = 0; col < cols; col++) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << row << " ";
        for (int col = 0; col < cols; col++) {
            if (showShips && field[row][col] == CellState::Ship) {
                std::cout << GREEN << "S " << RESET;  // ������� - ������� ����
            }
            else if (field[row][col] == CellState::MissedShot) {
                std::cout << CYAN << "- " << RESET;   // ������ - ����� ����
            }
            else if (field[row][col] == CellState::HitShip) {
                std::cout << RED << "X " << RESET;    // ��������� �� ������� - ������� ����
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

// ����� ��� ������� ���������� ��������
void PlayerField::manuallyPlaceShips() {
    int oneDeckCount = 0;
    int twoDeckCount = 0;
    int threeDeckCount = 0;
    int fourDeckCount = 0;

    std::cout << "���������� ������� �� ����� ���� �������:" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        int size, x, y;
        bool isHorizontal;

        std::cout << "������� ������ ������� " << i << ": ";
        std::cin >> size;

        // ���������, ����� �� ����������� ���������� �������� ��������� �������
        switch (size) {
        case 1:
            if (oneDeckCount >= 4) {
                std::cout << "��������� ���������� ������������ ��������. ���������� �����." << std::endl;
                --i;
                continue; // ��������� ������� �������� ����� � ��������� � ���������
            }
            oneDeckCount++;
            break;
        case 2:
            if (twoDeckCount >= 3) {
                std::cout << "��������� ���������� ������������ ��������. ���������� �����." << std::endl;
                --i;
                continue;
            }
            twoDeckCount++;
            break;
        case 3:
            if (threeDeckCount >= 2) {
                std::cout << "��������� ���������� ������������ ��������. ���������� �����." << std::endl;
                --i;
                continue;
            }
            threeDeckCount++;
            break;
        case 4:
            if (fourDeckCount >= 1) {
                std::cout << "��������� ���������� ��������������� ��������. ���������� �����." << std::endl;
                --i;
                continue;
            }
            fourDeckCount++;
            break;
        default:
            std::cout << "������������ ������ �������. ���������� �����." << std::endl;
            --i;
            continue;
        }

        std::cout << "������� ��������� ���������� (x, y) ��� ������� " << i << ": ";
        std::cin >> x >> y;
        std::cout << "������� ���������� (0 ��� ������������, 1 ��� ��������������) ��� ������� " << i << ": ";
        std::cin >> isHorizontal;

        Ship ship(size, isHorizontal);
        if (canPlaceShip(ship, x, y)) {
            for (int j = 0; j < ship.size; ++j) {
                int cx = x + (ship.isHorizontal ? 0 : j);
                int cy = y + (ship.isHorizontal ? j : 0);
                field[cx][cy] = CellState::Ship;
            }
        }
        else {
            std::cout << "���������� ���������� ������� � ��������� �����. ���������� �����." << std::endl;
            --i;
        }
    }
}

// ����� ��� ���������� ��������
bool PlayerField::takeShot(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // ������������ ����������
    }

    if (field[x][y] == CellState::Empty) {
        field[x][y] = CellState::MissedShot;
        return false; // ������
    }
    else if (field[x][y] == CellState::Ship) {
        field[x][y] = CellState::HitShip;
        return true; // ���������
    }
    return false; // ��� ������ ��� ���� ���������
}

// ����� ��� �������� ���������� ���� ��������
bool PlayerField::allShipsSunk() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == CellState::Ship) {
                return false;
            }
        }
    }
    return true;
}

// ����� ��� ���������� ���� � ������ ��������� �� ������������
bool PlayerField::takeQueryShot() {
    int x, y;
    std::cout << "������� ���������� (x, y): ";
    std::cin >> x >> y;

    // ��������� ���� ��� ������, ��������� ����������� � ������ �����
    std::ofstream outputFile("shots.txt", std::ios::app); // ios::app ��� ���������� � ����� �����

    // ���������, ������� �� ������ ����
    if (!outputFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������!" << std::endl;
        return false; // ���� ���� �� ������, ��������� �������
    }

    // ���������� ���������� � ����
    outputFile << x << " " << y << std::endl;

    // ��������� ����
    outputFile.close();

    return takeShot(x, y);
}

// ����� ��� ���������� ���������� ����
bool PlayerField::takeRandomShot() {
    int x = rand() % rows;
    int y = rand() % cols;
    return takeShot(x, y);
}