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

void entropy(std::vector<std::vector<RGB>> pixels, int width, int height) {
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
    for(int i = 0; i < 3; i++){
        result[i] /= -(double)(width * height);
        std::cout << result[i] << std::endl;
    }
    result[3] /= -(double)(width * height * 3);
    std::cout << result[3];
}

int main() {
    //read header
    const char *filename = "example0.tga";
    FILE *f = std::fopen("../test/example0.tga", "rb");
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
    std::vector<std::vector<RGB>> pixels(header.width, std::vector<RGB>(header.height));
    for (int i = 0; i < header.width * header.height; i++) {
        (pixels[i % header.width][i / header.width]).red = image.pixels[i * 4];
        pixels[i % header.width][i / header.width].green = image.pixels[i * 4 + 1];
        pixels[i % header.width][i / header.width].blue = image.pixels[i * 4 + 2];
    }
    entropy(pixels, header.width, header.height);
}
