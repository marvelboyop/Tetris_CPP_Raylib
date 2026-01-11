#include <iostream>
#include <raylib.h>

using namespace std;

// Grid configuration
const int cellSize = 52;
const int gridCols = 10;
const int gridRows = 16;

const int screen_width = 882;
const int screen_height = cellSize * gridRows; // 832

int board[gridRows][gridCols] = {0};

// class shape
// {
// public:
//     // Position on the GRID (not pixels)
//     int posX;
//     int posY;

//     float fallTimer = 0.0f;
//     float fallDelay = 0.5f; // seconds per cell

//     int gridByGrid;
//     bool isLocked = false;

//     int twoByTwoMatrix[2][2];

//     int threeByThreeMatrix[3][3];

//     int fourByFourMatrix[4][4];

//     void Draw()
//     {
//         for (int row = 0; row < gridByGrid; row++)
//         {
//             for (int col = 0; col < gridByGrid; col++)
//             {
//                 if (gridByGrid == 2)
//                 {
//                     if (twoByTwoMatrix[row][col] == 1)
//                     {
//                         DrawRectangle(
//                             (posX + col) * cellSize,
//                             (posY + row) * cellSize,
//                             cellSize,
//                             cellSize,
//                             RED);
//                     }
//                 }
//                 else if (gridByGrid == 3)
//                 {
//                     if (threeByThreeMatrix[row][col] == 1)
//                     {
//                         DrawRectangle(
//                             (posX + col) * cellSize,
//                             (posY + row) * cellSize,
//                             cellSize,
//                             cellSize,
//                             RED);
//                     }
//                 }
//                 else if (gridByGrid == 4)
//                 {
//                     if (fourByFourMatrix[row][col] == 1)
//                     {
//                         DrawRectangle(
//                             (posX + col) * cellSize,
//                             (posY + row) * cellSize,
//                             cellSize,
//                             cellSize,
//                             RED);
//                     }
//                 }
//             }
//         }
//     }

//     void Update()
//     {
//         // ---------- Gravity ----------
//         if (!isLocked)
//         {
//             fallTimer += GetFrameTime();
//             if (fallTimer >= fallDelay)
//             {
//                 if (posY < gridRows - gridByGrid)
//                 {
//                     posY++;
//                 }
//                 else
//                 {
//                     isLocked = true; // LANDING
//                 }
//                 fallTimer = 0.0f;
//             }

//             // ---------- Horizontal movement ----------
//             if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
//                 posX--;

//             if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
//                 posX++;
//         }
//     }

//     void LimitMovement()
//     {
//         // Left wall
//         if (posX < 0)
//             posX = 0;

//         // Right wall (square is 2 cells wide)
//         if (posX > gridCols - gridByGrid)
//             posX = gridCols - gridByGrid;
//     }
// };

class Shape
{
public:
    int matrix[4][4]; // ONE matrix (max size)
    int size;         // 2, 3, or 4

    int posX, posY;
    float fallTimer = 0.0f;
    float fallDelay = 0.5f;
    bool isLocked = false;

    Shape(int s) : size(s)
    {
        posX = gridCols / 2 - 1;
        posY = 0;

        // Clear matrix
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix[i][j] = 0;
    }

    void Draw()
    {
        for (int r = 0; r < size; r++)
        {
            for (int c = 0; c < size; c++)
            {
                if (matrix[r][c] == 1)
                {
                    DrawRectangle(
                        (posX + c) * cellSize,
                        (posY + r) * cellSize,
                        cellSize,
                        cellSize,
                        RED);
                }
            }
        }
    }
};

//======================================= Square ==========================================
class Square : public Shape
{
public:
    Square() : Shape(2)
    {
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
    }
};

//======================================== Plus =================================
class Plus : public Shape
{
public:
    Plus() : Shape(3)
    {
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][1] = 1;
    }
};

// ====================================== Z shape =============================

class ZShape : public Shape
{
public:
    ZShape() : Shape(3)
    {
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
    }
};

// =============================== L shape ===================================
class LShape : public Shape
{
public:
    LShape() : Shape(4)
    {
        matrix[0][0] = 1;
        matrix[1][0] = 1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
    }
};

// =========================== line ============================================
class Line : public Shape
{
public:
    Line() : Shape(4)
    {
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[1][3] = 1;
    }
};

int main()
{
    InitWindow(screen_width, screen_height, "Tetris made by marvelboyop & Dwip");
    SetTargetFPS(60);
    Square square;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Update
        square.Update();

        // Draw grid
        square.Draw();
        for (int row = 0; row < gridRows; row++)
        {
            for (int col = 0; col < gridCols; col++)
            {
                DrawRectangleLines(
                    col * cellSize,
                    row * cellSize,
                    cellSize,
                    cellSize,
                    WHITE);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}