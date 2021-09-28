#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <math.h>

using namespace std;

void setPixel(cv::Mat& background, int x0, int y0, int x1, int y1, int x, int y, int z) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            background.ptr<uchar>(j, i)[0] = x;
            background.ptr<uchar>(j, i)[1] = y;
            background.ptr<uchar>(j, i)[2] = z;
        }
    }
}

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
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::namedWindow("Image1");
    int height = 721;
    int width = 721;
    cv::Mat image1(height, width, CV_8UC3, (0, 0, 0));
    int k0, k, x, y;
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
    int row = 721 / k;
    int col = 721 / k;
    int color = 255 / board[k][0];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (board[i][j] != 0)
                cout << board[i][j] << '\t';
            else
                cout << '#' << '\t';
        }
        cout << endl;
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            setPixel(image1, j * col, i * row, (j + 1) * col, (i + 1) * row, color * board[i][j], color * (abs((board[k][0] / 2 - board[i][j]))), color * (board[k][0] - board[i][j]));
        }
    }
    cv::imshow("Image1", image1);
    cv::waitKey(0);
    delete[] board;
    cout << endl;
    return 0;
}