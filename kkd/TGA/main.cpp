#include <iostream>

struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

#include "tga_parser/tga/tga.h"
#include <cstdio>
#include <vector>
#include <cmath>


std::vector<std::vector<RGB>> pack(std::vector<std::vector<RGB>> pixels, int width, int height) {
    RGB black;
    black.red = 0;
    black.green = 0;
    black.blue = 0;
    std::vector<RGB> black_row(width + 2);
    for (int i = 0; i < width + 2; i++) black_row[i] = black;
    for (int i = 0; i < width; i++) {
        pixels[i].insert(pixels[i].begin(), black);
        pixels[i].push_back(black);
    }
    pixels.insert(pixels.begin(), black_row);
    pixels.push_back(black_row);
    return pixels;
}

std::vector<std::vector<RGB>> unpack(std::vector<std::vector<RGB>> pixels, int width, int height) {

    pixels.pop_back();
    pixels.erase(pixels.begin());
    for (int i = 0; i < width; i++) {
        pixels[i].pop_back();
        pixels[i].erase(pixels[i].begin());
    }

    return pixels;
}

void entropy(std::vector<std::vector<RGB>> pixels, int width, int height, std::vector<std::vector<double>> &scores) {
    int char_counters_red[256]{0};
    int char_counters_green[256]{0};
    int char_counters_blue[256]{0};
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            char_counters_red[pixels[i][j].red]++;
            char_counters_green[pixels[i][j].green]++;
            char_counters_blue[pixels[i][j].blue]++;
        }
    }
    double log_count = log2((double) (width * height));
    double log_count_all = log2((double) (width * height * 3));
    std::vector<double> result(4);
    for (int i = 0; i < 256; i++) {
        if (char_counters_red[i] > 0)
            result[0] += (double) char_counters_red[i] * (log2((double) char_counters_red[i]) - log_count);
        if (char_counters_green[i] > 0)
            result[1] += (double) char_counters_green[i] * (log2((double) char_counters_green[i]) - log_count);
        if (char_counters_blue[i] > 0)
            result[2] += (double) char_counters_blue[i] * (log2((double) char_counters_blue[i]) - log_count);
        if (char_counters_blue[i] > 0 || char_counters_green[i] > 0 || char_counters_red[i] > 0)
            result[3] += (double) (char_counters_blue[i] + char_counters_red[i] + char_counters_green[i]) *
                         (log2((double) (char_counters_blue[i] + char_counters_red[i] + char_counters_green[i])) -
                          log_count_all);
    }
    for (int i = 0; i < 3; i++) {
        result[i] /= -(double) (width * height);
//        std::cout << result[i] << std::endl;
    }
    result[3] /= -(double) (width * height * 3);
    std::cout << "whole file entropy " << result[3] << std::endl;
    std::cout << "red color entropy " << result[0] << std::endl;
    std::cout << "green color entropy " << result[1] << std::endl;
    std::cout << "blue color entropy " << result[2] << std::endl;
    std::vector<double> local_scores;
    for(int i = 0; i < 4; i++){
        local_scores.push_back(result[i]);
    }
    scores.push_back(local_scores);
}

int main() {
    //read header
    const char *filename = "example0.tga";
    FILE *f = std::fopen("../test/example1.tga", "rb");
    tga::StdioFileInterface file(f);
    tga::Decoder decoder(&file);
    tga::Header header;

    if (!decoder.readHeader(header))
        return 2;

    tga::Image image;
    image.bytesPerPixel = header.bytesPerPixel();
    image.rowstride = header.width * header.bytesPerPixel();

    std::vector<uint8_t> buffer(image.rowstride * header.height);
    image.pixels = &buffer[0];

    if (!decoder.readImage(header, image, nullptr))
        return 3;
//    for(auto pixel : buffer){
//        std::cout << (int)pixel << std::endl;
//    }
    std::cout << (int) header.colormapType << std::endl;
    std::cout << (int) header.imageType << std::endl;
    std::cout << header.width << " " << header.height << std::endl;
    std::cout << buffer.size() << std::endl << std::endl;
    decoder.postProcessImage(header, image);
//    std::cout << image.pixels << std::endl;
//    for(auto pixel : buffer){
//        std::cout << (int)pixel << std::endl;
//    }
    std::vector<std::vector<double>> scores;
    std::vector<std::vector<RGB>> pixels(header.width, std::vector<RGB>(header.height));
    for (int i = 0; i < header.width * header.height; i++) {
        (pixels[i % header.width][i / header.width]).red = image.pixels[i * 4];
        pixels[i % header.width][i / header.width].green = image.pixels[i * 4 + 1];
        pixels[i % header.width][i / header.width].blue = image.pixels[i * 4 + 2];
    }
    std::cout << "unmodified file" << std::endl;
    entropy(pixels, header.width, header.height, scores);
    auto packed = pack(pixels, header.width, header.height);
    std::vector<std::vector<RGB>> pred_1(header.width, std::vector<RGB>(header.height));

    std::cout << "pred_1" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red = packed[i][j].red - packed[i - 1][j].red;
            pred_1[i - 1][j - 1].green = packed[i][j].green - packed[i - 1][j].green;
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - packed[i - 1][j].blue;
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_2" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red = packed[i][j].red - packed[i][j - 1].red;
            pred_1[i - 1][j - 1].green = packed[i][j].green - packed[i][j - 1].green;
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - packed[i][j - 1].blue;
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_3" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red = packed[i][j].red - packed[i - 1][j - 1].red;
            pred_1[i - 1][j - 1].green = packed[i][j].green - packed[i - 1][j - 1].green;
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - packed[i - 1][j - 1].blue;
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_4" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red =
                    packed[i][j].red - (packed[i][j - 1].red + packed[i - 1][j].red - packed[i - 1][j - 1].red);
            pred_1[i - 1][j - 1].green =
                    packed[i][j].green - (packed[i][j - 1].green + packed[i - 1][j].green - packed[i - 1][j - 1].green);
            pred_1[i - 1][j - 1].blue =
                    packed[i][j].blue - (packed[i][j - 1].blue + packed[i - 1][j].blue - packed[i - 1][j - 1].blue);
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_5" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red =
                    packed[i][j].red - (packed[i][j - 1].red + (packed[i - 1][j].red - packed[i - 1][j - 1].red) / 2);
            pred_1[i - 1][j - 1].green = packed[i][j].green - (packed[i][j - 1].green +
                                                               (packed[i - 1][j].green - packed[i - 1][j - 1].green) /
                                                               2);
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - (packed[i][j - 1].blue +
                                                             (packed[i - 1][j].blue - packed[i - 1][j - 1].blue) / 2);
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_6" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red =
                    packed[i][j].red - (packed[i - 1][j].red + (packed[i][j - 1].red - packed[i - 1][j - 1].red) / 2);
            pred_1[i - 1][j - 1].green = packed[i][j].green - (packed[i - 1][j].green +
                                                               (packed[i][j - 1].green - packed[i - 1][j - 1].green) /
                                                               2);
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - (packed[i - 1][j].blue +
                                                             (packed[i][j - 1].blue - packed[i - 1][j - 1].blue) / 2);
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "pred_7" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {
            pred_1[i - 1][j - 1].red = packed[i][j].red - (packed[i][j - 1].red + packed[i - 1][j].red) / 2;
            pred_1[i - 1][j - 1].green = packed[i][j].green - (packed[i][j - 1].green + packed[i - 1][j].green) / 2;
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - (packed[i][j - 1].blue + packed[i - 1][j].blue) / 2;
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    std::cout << "new standard" << std::endl;
    for (int i = 1; i < header.width + 1; i++) {
        for (int j = 1; j < header.height + 1; j++) {

            uint8_t x_hat;
            if (packed[i - 1][j - 1].red >=
                std::max(packed[i][j - 1].red, packed[i - 1][j].red)) {
                x_hat = std::max(packed[i][j - 1].red, packed[i - 1][j].red);
            } else if (packed[i - 1][j - 1].red >=
                       std::min(packed[i][j - 1].red, packed[i - 1][j].red)) {
                x_hat = std::min(packed[i][j - 1].red, packed[i - 1][j].red);
            } else {
                x_hat = packed[i][j - 1].red + packed[i - 1][j].red - packed[i - 1][j - 1].red;
            }
            pred_1[i - 1][j - 1].red = packed[i][j].red - x_hat;

            if (packed[i - 1][j - 1].green >=
                std::max(packed[i][j - 1].green, packed[i - 1][j].green)) {
                x_hat = std::max(packed[i][j - 1].green, packed[i - 1][j].green);
            } else if (packed[i - 1][j - 1].green >=
                       std::min(packed[i][j - 1].green, packed[i - 1][j].green)) {
                x_hat = std::min(packed[i][j - 1].green, packed[i - 1][j].green);
            } else {
                x_hat = packed[i][j - 1].green + packed[i - 1][j].green - packed[i - 1][j - 1].green;
            }
            pred_1[i - 1][j - 1].green = packed[i][j].green - x_hat;

            if (packed[i - 1][j - 1].blue >=
                std::max(packed[i][j - 1].blue, packed[i - 1][j].blue)) {
                x_hat = std::max(packed[i][j - 1].blue, packed[i - 1][j].blue);
            } else if (packed[i - 1][j - 1].blue >=
                       std::min(packed[i][j - 1].blue, packed[i - 1][j].blue)) {
                x_hat = std::min(packed[i][j - 1].blue, packed[i - 1][j].blue);
            } else {
                x_hat = packed[i][j - 1].blue + packed[i - 1][j].blue - packed[i - 1][j - 1].blue;
            }
            pred_1[i - 1][j - 1].blue = packed[i][j].blue - x_hat;
        }
    }
    entropy(pred_1, header.width, header.height, scores);

    int best_scores[4]{10,10,10,10};
    for(int i = 0; i < 4; i++){
        double min = 10.0;
        for(int j = 0; j < 8; j++){
            if(scores[j][i] < min){
                best_scores[i] = j;
                min =  scores[j][i];
            }
        }
    }

    for(int i = 0; i < 4; i++){
        std::cout << best_scores[i] << std::endl;
    }
}
