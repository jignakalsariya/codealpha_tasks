#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

#define N 9

// Function to check if a number can be placed in a given position
bool is_valid(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }
    
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku using backtracking
bool solve_sudoku(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve_sudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to display Sudoku using SFML GUI
void draw_board(sf::RenderWindow &window, int board[N][N]) {
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);

    sf::RectangleShape cell(sf::Vector2f(50, 50));
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color::Black);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cell.setPosition(j * 50, i * 50);
            window.draw(cell);

            if (board[i][j] != 0) {
                text.setString(to_string(board[i][j]));
                text.setPosition(j * 50 + 15, i * 50 + 5);
                window.draw(text);
            }
        }
    }
}

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    if (solve_sudoku(board)) {
        sf::RenderWindow window(sf::VideoMode(450, 450), "Sudoku Solver");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            draw_board(window, board);
            window.display();
        }
    } else {
        cout << "No solution exists" << endl;
    }
    
    return 0;
}

