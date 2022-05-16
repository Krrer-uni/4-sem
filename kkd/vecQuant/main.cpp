#include <iostream>
#include "tga/tga.h"

#define imageVec std::vector<std::vector<RGB>>

struct RGB{
    int red;
    int green;
    int blue;

    RGB& operator =(const RGB& a)= default;
};


//calc taxi dist
double dist(RGB a, RGB b){
    double sum = 0;
    sum += abs(a.red - b.red);
    sum += abs(a.green -  b.green);
    sum += abs(a.blue - b.blue);
    return sum;
}

double distortion(imageVec  image_a, imageVec  image_b) {
    if (image_a.size() != image_b.size()) {
        std::cerr << "Trying to compare " + std::to_string(image_a.size()) + " size vector and " +
                     std::to_string(image_b.size()) + " size vector" << std::endl;
        return -1;
    }
    double sum = 0;
    for(int i = 0; i < image_a.size(); i++){
        for(int j = 0; j < image_a[0].size(); j++){
            sum += dist(image_a[i][j], image_b[i][j]);
        }
    }
    sum /= 3 * image_a.size() * image_b.size();
    return sum;
}

RGB best_fit(RGB, std::vector<RGB> dict){
    
}

imageVec quantize(imageVec input, std::vector<RGB> dict){
    imageVec output(input.size(),std::vector<RGB>(input[0].size()));

}



int main() {
    std::string in_fn = "../test/example0.tga";
    FILE *f = std::fopen(in_fn.c_str(), "rb");
    tga::StdioFileInterface file(f);
    tga::Decoder decoder(&file);

    std::string out_fn = "../output.tga";
    FILE *out_f = std::fopen(out_fn.c_str(), "wb");
//    if(!out_f) std::cout <<"nope ";
    tga::StdioFileInterface out_file(out_f);
    tga::Encoder encoder(&out_file);


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


    imageVec input(header.width, std::vector<RGB>(header.height));
    for(int i = 0; i < header.width * header.height; i++){
        input[i % header.width][i / header.width].red = image.pixels[i * 4];
        input[i % header.width][i / header.width].green = image.pixels[i * 4 + 1];
        input[i % header.width][i / header.width].blue = image.pixels[i * 4 + 2];
    }

    imageVec output(header.width, std::vector<RGB>(header.height));
    for(int  i = 0; i < input.size(); i ++){
        for(int j = 0; j < input[0].size(); j++){
            output[i][j] = input[i][j];
//            output[i][j].blue = 125;
//            output[i][j].green = 125;
//            output[i][j].red = 125;
        }
    }
//    std::cout << distortion(input, output) << std::endl;
    std::vector<RGB> quant(128);

    for(int i = 0; i < header.width * header.height; i++){
        image.pixels[i * 4] = output[i % header.width][i / header.width].red;
        image.pixels[i * 4 + 1] = output[i % header.width][i / header.width].green;
        image.pixels[i * 4 + 2] = output[i % header.width][i / header.width].blue;
    }
    encoder.writeHeader(header);
    encoder.writeImage(header, image);
    encoder.writeFooter();
}
