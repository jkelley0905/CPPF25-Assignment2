#include <iostream>
#include <deque>
#include <cstdint>
#include <algorithm>
#include "bmp.hpp"

using namespace std;

bool visited[1600][1600];

bool sameColor(const color& c1, const color& c2, int tolerance = 12) {
    return (abs(c1.r - c2.r) <= tolerance &&
        abs(c1.g - c2.g) <= tolerance &&
        abs(c1.b - c2.b) <= tolerance);
}

//-------------------------------------------------------------------
//Flood fill function

void floodFill(BMP& image, int startX, int startY, color fillColor) {
    int width = image.get_width();
    int height = image.get_height();

    if (startX < 0 || startX >= width || startY < 0 || startY >= height)
        return;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            visited[i][j] = false;

    uint8_t sr, sg, sb;
    image.get_pixel(startX, startY, sr, sg, sb);
    color startColor(sr, sg, sb);

    if (sameColor(startColor, fillColor))
        return;

    deque<pair<int, int>> q;
    q.push_back({ startX, startY });
    visited[startY][startX] = true;


    int dx[8] = { 0, 0, -1, 1, -1, -1, 1, 1 };
    int dy[8] = { -1, 1, 0, 0, 1, -1, 1, -1 };

    while (!q.empty()) {
        auto p = q.front();
        int x = p.first;
        int y = p.second;
        q.pop_front();

        uint8_t r, g, b;
        image.get_pixel(x, y, r, g, b);
        color current(r, g, b);

        if (sameColor(current, startColor)) {
            image.set_pixel(x, y, fillColor.r, fillColor.g, fillColor.b);
        }

        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push_back({ nx, ny });
            }
        }
    }
}

//--------------------------------------------------------------------------------
//Blurred Image Function


void applySquareBlur(const BMP& image, BMP& blurredImage, int blurSize) {
    int width = image.get_width();
    int height = image.get_height();

    int half = blurSize / 2;

    for (int y = 0; y < height; y++) {

        long totalR = 0, totalG = 0, totalB = 0;
        int count = 0;

        for (int x = 0; x < width; x++) {

            long firstColR = 0, firstColG = 0, firstColB = 0;
            long lastColR = 0, lastColG = 0, lastColB = 0;

            if (x == 0) {

                for (int dx = -half; dx <= half; dx++) {
                    for (int dy = -half; dy <= half; dy++) {

                        int ny = y + dy;
                        int nx = x + dx;

                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            uint8_t r, g, b;
                            image.get_pixel(nx, ny, r, g, b);
                            color neighborColor(r, g, b);
                            totalR += neighborColor.r;
                            totalG += neighborColor.g;
                            totalB += neighborColor.b;
                            count++;
                        }
                    }
                }

            }

            else {

                for (int dy = -half; dy <= half; dy++) {
                    int ny = y + dy;
                    int nx = x - 1 - half;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        uint8_t r, g, b;
                        image.get_pixel(nx, ny, r, g, b);
                        color neighborColor(r, g, b);
                        firstColR += neighborColor.r;
                        firstColG += neighborColor.g;
                        firstColB += neighborColor.b;
                        count--;
                    }
                }

                for (int dy = -half; dy <= half; dy++) {
                    int ny = y + dy;
                    int nx = x + half;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        uint8_t r, g, b;
                        image.get_pixel(nx, ny, r, g, b);
                        color neighborColor(r, g, b);
                        lastColR += neighborColor.r;
                        lastColG += neighborColor.g;
                        lastColB += neighborColor.b;
                        count++;
                    }
                }

                totalR += -(firstColR)+lastColR;
                totalG += -(firstColG)+lastColG;
                totalB += -(firstColB)+lastColB;

            }

            color averageColor(totalR / count, totalG / count, totalB / count);

            blurredImage.set_pixel(x, y, averageColor.r, averageColor.g, averageColor.b);
        }
    }
}

int main() {

    try {

        BMP image("sample.bmp");

        cout << "Image loaded: " << image.get_width() << "x" << image.get_height() << endl;

// -------------------------------------------------------------------------

// Flood fill
        color fillColor(0, 255, 0);

        floodFill(image, 50, 50, fillColor);

        image.write("flood_filled.bmp");

        cout << "Flood fill completed -> flood_filled.bmp\n";

// -------------------------------------------------------------------------

// Blur

        BMP original("sample.bmp");

        BMP blurredImage(original.get_width(), original.get_height());

        applySquareBlur(original, blurredImage, 5);

        blurredImage.write("blurredImage.bmp");

        cout << "Blur completed -> blurredImage.bmp\n";

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
