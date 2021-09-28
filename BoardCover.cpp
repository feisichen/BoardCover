#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void BoardCover(int** board, int x0, int x1, int y0, int y1, int size) {
    if (x0 == x1)
    {
        return;
    }
    int tempx = (x0 + x1) / 2;
    int tempy = (y0 + y1) / 2;
    int x, y;
    int t = ++board[size][0];
    for (int i = x0; i <= x1; ++i) {
        for (int j = y0; j <= y1; ++j) {
            if (board[i][j] != -1) {
                x = (i - x0) < (x1 - i) ? tempx : tempx + 1;
                y = (j - y0) < (y1 - j) ? tempy : tempy + 1;
            }
        }
    }
    if (tempx != x || tempy != y)
    {
        board[tempx][tempy] = t;
    }
    if (tempx + 1 != x || tempy != y)
    {
        board[tempx + 1][tempy] = t;
    }
    if (tempx != x || tempy + 1 != y)
    {
        board[tempx][tempy + 1] = t;
    }
    if (tempx + 1 != x || tempy + 1 != y)
    {
        board[tempx + 1][tempy + 1] = t;
    }
    BoardCover(board, x0, tempx, y0, tempy, size);
    BoardCover(board, x0, tempx, tempy + 1, y1, size);
    BoardCover(board, tempx + 1, x1, y0, tempy, size);
    BoardCover(board, tempx + 1, x1, tempy + 1, y1, size);
}
int main(int argc, char* argv[])
{
    int k0, k, x, y;
    while (1) {
        cin >> k0 >> x >> y;
        k = 2 << (k0 - 1);
        int** board;
        board = new int* [k + 1];
        for (int i = 0; i < k; i++) {
            board[i] = new int[k];
        }
        board[k] = new int[1];
        board[k][0] = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                board[i][j] = -1;
            }
        }
        board[x - 1][y - 1] = 0;
        BoardCover(board, 0, k - 1, 0, k - 1, k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (board[i][j] != 0)
                    cout << board[i][j] << '\t';
                else
                    cout << '#' << '\t';
            }
            cout << endl;
        }
        delete[] board;
        cout << endl;
    }
    return 0;
}