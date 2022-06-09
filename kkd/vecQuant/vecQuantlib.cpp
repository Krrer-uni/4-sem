//
// Created by krrer on 6/6/22.
//
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


double euc_dist(RGB a, RGB b) {
  double sum;
  double x = abs(a.red - b.red);
  double y = abs(a.green - b.green);
  double z = abs(a.blue - b.blue);
  sum = x*x + y*y + z+z;

  return sqrt(sum);
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
      double a = euc_dist(image_a[i][j], image_b[i][j]);
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
  double best_fit_dist = euc_dist(x, best_fit);
  for (RGB cand: dict) {
    if (euc_dist(x, cand) < best_fit_dist) {
      best_fit_dist = euc_dist(x, cand);
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

RGB get_dist(){
  int i =((rand()%2) * 2) -1;
  int j = ((rand()%2) * 2) -1;
  int k = ((rand()%2) * 2) -1;
  return RGB(i,j,k);
}
