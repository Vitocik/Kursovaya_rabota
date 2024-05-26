//PlayerField.cpp
#include "PlayerField.h"
#include <iostream>
#include <ctime>
#include <fstream>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Красный */
#define GREEN   "\033[32m"      /* Зеленый */
#define CYAN    "\033[36m"      /* Циан */
// Определение конструктора класса PlayerField
PlayerField::PlayerField(int rows, int cols) : rows(rows), cols(cols), field(rows, std::vector<CellState>(cols, CellState::Empty)) {}

// Метод для размещения корабля
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

// Метод для проверки возможности размещения корабля
bool PlayerField::canPlaceShip(const Ship& ship, int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // Выход за границы
    }

    for (int i = 0; i < ship.size; i++) {
        int cx = x + (ship.isHorizontal ? 0 : i);
        int cy = y + (ship.isHorizontal ? i : 0);

        if (cx < 0 || cx >= rows || cy < 0 || cy >= cols || field[cx][cy] != CellState::Empty) {
            return false; // Корабль перекрывается с другим кораблем или выходит за границы
        }

        // Проверка соседних ячеек на наличие корабля
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && field[nx][ny] == CellState::Ship) {
                    return false; // Корабль соседствует с другим кораблем
                }
            }
        }
    }
    return true;
}

bool PlayerField::takeFileShot(const std::string& filename) {
    std::ifstream file(filename); // Открыть файл для чтения
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удается открыть файл " << filename << std::endl;
        return false;
    }

    int x, y;
    if (!(file >> x >> y)) {
        std::cerr << "Ошибка: Не удается прочитать координаты из файла " << filename << std::endl;
        file.close();
        return false;
    }

    file.close(); // Закрыть файл

    return takeShot(x, y); // Сделать выстрел, используя координаты, считанные из файла
}
// Метод для отображения игрового поля
void PlayerField::displayField(bool showShips) const {
    // Вывод номеров столбцов с одинаковым промежутком
    std::cout << " ";
    for (int col = 0; col < cols; col++) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << row << " ";
        for (int col = 0; col < cols; col++) {
            if (showShips && field[row][col] == CellState::Ship) {
                std::cout << GREEN << "S " << RESET;  // Корабль - зеленый цвет
            }
            else if (field[row][col] == CellState::MissedShot) {
                std::cout << CYAN << "- " << RESET;   // Промах - синий цвет
            }
            else if (field[row][col] == CellState::HitShip) {
                std::cout << RED << "X " << RESET;    // Попадание по кораблю - красный цвет
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

// Метод для ручного размещения кораблей
void PlayerField::manuallyPlaceShips() {
    int oneDeckCount = 0;
    int twoDeckCount = 0;
    int threeDeckCount = 0;
    int fourDeckCount = 0;

    std::cout << "Расставьте корабли на вашем поле вручную:" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        int size, x, y;
        bool isHorizontal;

        std::cout << "Введите размер корабля " << i << ": ";
        std::cin >> size;

        // Проверяем, чтобы не превышалось количество кораблей заданного размера
        switch (size) {
        case 1:
            if (oneDeckCount >= 4) {
                std::cout << "Превышено количество однопалубных кораблей. Попробуйте снова." << std::endl;
                --i;
                continue; // Прерываем текущую итерацию цикла и переходим к следующей
            }
            oneDeckCount++;
            break;
        case 2:
            if (twoDeckCount >= 3) {
                std::cout << "Превышено количество двухпалубных кораблей. Попробуйте снова." << std::endl;
                --i;
                continue;
            }
            twoDeckCount++;
            break;
        case 3:
            if (threeDeckCount >= 2) {
                std::cout << "Превышено количество трехпалубных кораблей. Попробуйте снова." << std::endl;
                --i;
                continue;
            }
            threeDeckCount++;
            break;
        case 4:
            if (fourDeckCount >= 1) {
                std::cout << "Превышено количество четырехпалубных кораблей. Попробуйте снова." << std::endl;
                --i;
                continue;
            }
            fourDeckCount++;
            break;
        default:
            std::cout << "Недопустимый размер корабля. Попробуйте снова." << std::endl;
            --i;
            continue;
        }

        std::cout << "Введите начальные координаты (x, y) для корабля " << i << ": ";
        std::cin >> x >> y;
        std::cout << "Введите ориентацию (0 для вертикальной, 1 для горизонтальной) для корабля " << i << ": ";
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
            std::cout << "Невозможно разместить корабль в указанном месте. Попробуйте снова." << std::endl;
            --i;
        }
    }
}

// Метод для совершения выстрела
bool PlayerField::takeShot(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // Недопустимые координаты
    }

    if (field[x][y] == CellState::Empty) {
        field[x][y] = CellState::MissedShot;
        return false; // Промах
    }
    else if (field[x][y] == CellState::Ship) {
        field[x][y] = CellState::HitShip;
        return true; // Попадание
    }
    return false; // Эта ячейка уже была атакована
}

// Метод для проверки потопления всех кораблей
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

// Метод для совершения хода с вводом координат от пользователя
bool PlayerField::takeQueryShot() {
    int x, y;
    std::cout << "Введите координаты (x, y): ";
    std::cin >> x >> y;

    // Открываем файл для записи, используя конструктор с именем файла
    std::ofstream outputFile("shots.txt", std::ios::app); // ios::app для добавления в конец файла

    // Проверяем, успешно ли открыт файл
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return false; // Если файл не открыт, завершаем функцию
    }

    // Записываем координаты в файл
    outputFile << x << " " << y << std::endl;

    // Закрываем файл
    outputFile.close();

    return takeShot(x, y);
}

// Метод для совершения случайного хода
bool PlayerField::takeRandomShot() {
    int x = rand() % rows;
    int y = rand() % cols;
    return takeShot(x, y);
}