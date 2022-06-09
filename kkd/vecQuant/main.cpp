#include <iostream>

#include "tga/tga.h"
#include "vecQuantlib.cpp"
#include <cmath>
#define imageVec std::vector<std::vector<RGB>>

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
  RGB avg(0, 0, 0);
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

  RGB RGB_dist(1, 1, 1);
  std::vector<RGB> dic;
  dic.push_back(avg);
  quantize(output, dic, result, 0.0001);
  dic.push_back((avg + RGB_dist) % 256);

  for (int i = 0; i < n; i++) {
    quantize(output, dic, result, 0.0001);
    int size = dic.size();
    for (int j = 0; j < size; j++) {
      dic.push_back((dic[j] + get_dist()) % 256);
    }
    std::cout << "Distortion for " << i + 1 << " bits" << std::endl;
  }
  std::cout << "Distortion: " << distortion(input, result) << std::endl;
  std::cout << "SNR: " << snr(input, result) << std::endl;
  for (int i = 0; i < header.width * header.height; i++) {
    image.pixels[i * 4] = result[i % header.width][i / header.width].red;
    image.pixels[i * 4 + 1] = result[i % header.width][i / header.width].green;
    image.pixels[i * 4 + 2] = result[i % header.width][i / header.width].blue;
  }
  encoder.writeHeader(header);
  encoder.writeImage(header, image);
  encoder.writeFooter();
}
