#include <iostream>
#include <array>
#include <cmath>
using namespace std;

int row, col;
array<array<int, 2>, 4> chckin{};
array<int, 4> dist{};

void init(int row, int col);
void dcopy(array<array<int, 8>, 8> &clake, array<array<int, 8>, 8> &lake);
bool valid(int x, int y, int stage, int step);
int countPath(array<array<int, 8>, 8> lake, int stage, int step, int x, int y);
int countEmpt(array<array<int, 8>, 8> &lake, int x, int y);

int main() {
    int caseno = 0;

    while(++caseno && cin >> row >> col){
        if (!row && !col)
            break;

        array<array<int, 8>, 8> lake{};
        init(row, col);

        int stage = 0;
        int step = 1;

        cout << "Case " << caseno << ": " << countPath(lake, stage, step, 0, 0) << endl;
    }

    return 0;
}

void init(int row, int col){
    cin >> chckin[0][0] >> chckin[0][1];
    cin >> chckin[1][0] >> chckin[1][1];
    cin >> chckin[2][0] >> chckin[2][1];
    chckin[3][0] = 0; chckin[3][1] = 1;

    int len = row * col;
    dist[0] = len / 4;
    dist[1] = len / 2;
    dist[2] = 3 * len / 4;
    dist[3] = len;

}

bool valid(int x, int y, int stage, int step){
    if ((x == chckin[0][0] && y == chckin[0][1]) || (x == chckin[1][0] && y == chckin[1][1])
            || (x == chckin[2][0] && y == chckin[2][1]) || (x == chckin[3][0] && y == chckin[3][1]))
        return false;

    if (dist[stage] - step < abs(chckin[stage][0] - x) + abs(chckin[stage][1] - y))
        return false;

    return true;
}

int countEmpt(array<array<int, 8>, 8> &lake, int x, int y){
    int count = 1;

    lake[x][y] = 1;

    if (x-1 >= 0 && x-1 < row && lake[x-1][y] == 0)
        count += countEmpt(lake, x-1, y);

    if (x+1 >= 0 && x+1 < row && lake[x+1][y] == 0)
        count += countEmpt(lake, x+1, y);

    if (y-1 >= 0 && y-1 < col && lake[x][y-1] == 0)
        count += countEmpt(lake, x, y-1);

    if (y+1 >= 0 && y+1 < col && lake[x][y+1] == 0)
        count += countEmpt(lake, x, y+1);

    return count;
}

void dcopy(array<array<int, 8>, 8> &clake, array<array<int, 8>, 8> &lake){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            clake[i][j] = lake[i][j];
        }
    }
}

int countPath(array<array<int, 8>, 8> lake, int stage, int step, int x, int y){
    int count = 0;

    if (stage == 3 && step == row*col && x == 0 && y == 1)
        return (++count);

    if (step == dist[stage]) {
        if (x != chckin[stage][0] || y != chckin[stage][1])
            return count;
        else
            stage++;
    }
    else if (!valid(x, y, stage, step))
        return count;

    lake[x][y] = step++;
    int en = row * col - step + 1;

    array<array<int, 8>, 8> clake{};
    dcopy(clake, lake);
    if (x-1 >= 0 && x-1 < row && lake[x-1][y] == 0 && countEmpt(clake, x-1, y) == en)
        count += countPath(lake, stage, step, x-1, y);

    dcopy(clake, lake);
    if (x+1 >= 0 && x+1 < row && lake[x+1][y] == 0 && countEmpt(clake, x+1, y) == en)
        count += countPath(lake, stage, step, x+1, y);

    dcopy(clake, lake);
    if (y-1 >= 0 && y-1 < col && lake[x][y-1] == 0 && countEmpt(clake, x, y-1) == en)
        count += countPath(lake, stage, step, x, y-1);

    dcopy(clake, lake);
    if (y+1 >= 0 && y+1 < col && lake[x][y+1] == 0 && countEmpt(clake, x, y+1) == en)
        count += countPath(lake, stage, step, x, y+1);

    return count;
}