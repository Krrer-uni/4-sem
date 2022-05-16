#include <iostream>

#include "tga/tga.h"
#include <cmath>
#define imageVec std::vector<std::vector<RGB>>

struct RGB {
    int red{};
    int green{};
    int blue{};

    RGB() = default;

    ~RGB() = default;

    RGB(int r, int g, int b) : red(r), green(g), blue(b) {}

    RGB &operator=(const RGB &a) = default;

    RGB operator+(const RGB &a) const {
        return {red + a.red, green + a.green, blue + a.blue};
    }

    RGB operator/(const int &a) const {
        return {red / a, green / a, blue / a};
    }

    RGB operator%(const int &a) const{
        return {red%a, green %a, blue%a};
    }

    bool operator==(const RGB &a) const {
        return (red == a.red && green == a.green && blue == a.blue);
    }
};


//calc taxi dist
double dist(RGB a, RGB b) {
    double sum = 0;
    sum += abs(a.red - b.red);
    sum += abs(a.green - b.green);
    sum += abs(a.blue - b.blue);
    return sum;
}

double distortion(imageVec image_a, imageVec image_b) {
    if (image_a.size() != image_b.size()) {
        std::cerr << "Trying to compare " + std::to_string(image_a.size()) + " size vector and " +
                     std::to_string(image_b.size()) + " size vector" << std::endl;
        return -1;
    }
    double sum = 0;
    for (int i = 0; i < image_a.size(); i++) {
        for (int j = 0; j < image_a[0].size(); j++) {
            double a = dist(image_a[i][j], image_b[i][j]);
            sum += a*a;
        }
    }
    sum /= 3 * image_a.size() * image_b.size();
    return sum;
}

double snr(imageVec image_a, imageVec image_b){
    double a = distortion(image_a, image_b);
    for(auto& rgb_vec : image_b){
        for(auto& rgb : rgb_vec){
            RGB tmp(0,0,0);
            rgb = tmp;
        }
    }
    double b = distortion(image_a, image_b);
    return 10 * log10((b*b)/(a*a));
}

RGB best_fit(RGB x, std::vector<RGB> dict) {
    RGB best_fit = dict[0];
    double best_fit_dist = dist(x, best_fit);
    for (RGB cand: dict) {
        if (dist(x, cand) < best_fit_dist) {
            best_fit_dist = dist(x, cand);
            best_fit = cand;
        }
    }
    return best_fit;
}

void quantize(imageVec input, std::vector<RGB> &dict, imageVec &output, double eps) {
//    imageVec output(input.size(),std::vector<RGB>(input[0].size()));
    double distor = 0;
    double last_distor = 0;
    double cond;
    do {
        std::vector<std::vector<RGB>> dict_vec(dict.size(), std::vector<RGB>());
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[0].size(); j++) {
                output[i][j] = best_fit(input[i][j], dict);
            }
        }
        for (auto& region: dict) {
            RGB sum(0, 0, 0);
            int c = 0;
            for (int i = 0; i < input.size(); i++) {
                for (int j = 0; j < input[0].size(); j++) {
                    if (region == output[i][j]) {
                        c++;
                        sum = sum + input[i][j];
                    }
                }
            }
            if (c != 0)
                region = sum / c;
        }
        last_distor = distor;
        distor = distortion(input, output);
//        std::cout << distor << std::endl;
        cond = std::abs((distor - last_distor) / distor);
        if(last_distor != 0 && distor > last_distor) break;
    }while (cond > eps);
}


int main(int argc, char *argv[]) {
    int n = 10;
    auto fn_in = argv[1];
    auto fn_out = argv[2];
    n = std::stoi(argv[3]);
    std::string in_fn = "../test/example0.tga";
    FILE *f = std::fopen(fn_in, "rb");
    tga::StdioFileInterface file(f);
    tga::Decoder decoder(&file);

    std::string out_fn = "../output.tga";
    FILE *out_f = std::fopen(fn_out, "wb");
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
    for (int i = 0; i < header.width * header.height; i++) {
        input[i % header.width][i / header.width].red = image.pixels[i * 4];
        input[i % header.width][i / header.width].green = image.pixels[i * 4 + 1];
        input[i % header.width][i / header.width].blue = image.pixels[i * 4 + 2];
    }
    RGB avg(0,0,0);
    imageVec output(header.width, std::vector<RGB>(header.height));
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            output[i][j] = input[i][j];
            avg = avg + input[i][j];
        }
    }
    avg = avg / (header.width * header.height);
    imageVec result(header.width, std::vector<RGB>(header.height));
//    int dic_size = 1024;
//    std::vector<RGB> quant(dic_size);
//    for (int i = 0; i < dic_size; i++) {
//
//        RGB np(rand() % 256, rand() % 256, rand() % 256);
//        quant[i] = np;
//    }


//    quantize(output, quant, result, 0.001);
//    std::cout << distortion(input, result) << std::endl;

    RGB RGB_dist(10,10,10);
    std::vector<RGB> dic;
    dic.push_back(avg);
    dic.push_back((avg+RGB_dist)%256);
    for(int i =0; i < n ; i++){
        quantize(output,dic, result,0.0001);
        int size = dic.size();
        for(int j = 0; j < size; j++){
            dic.push_back((dic[j] + RGB_dist)%256);
        }
        std::cout << "Distortion for " << i + 1 << " bits" << std::endl;
    }
    std::cout << "Distortion: " << distortion(input,result) << std::endl;
    std::cout << "SNR: " << snr(input,result) << std::endl;
    for (int i = 0; i < header.width * header.height; i++) {
        image.pixels[i * 4] = result[i % header.width][i / header.width].red;
        image.pixels[i * 4 + 1] = result[i % header.width][i / header.width].green;
        image.pixels[i * 4 + 2] = result[i % header.width][i / header.width].blue;
    }
    encoder.writeHeader(header);
    encoder.writeImage(header, image);
    encoder.writeFooter();
}
