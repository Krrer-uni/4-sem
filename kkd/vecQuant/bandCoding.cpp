//
// Created by krrer on 6/6/22.
//
#include "vecQuantlib.cpp"

inline int quantize(int input, std::vector<int> dict) {
  float dist = 100000;
  int idx = 0;
  for (int i = 0; i < dict.size(); i++) {
    if (std::abs(input - dict[i]) < dist) {
      dist = (std::abs(input - dict[i]));
      idx = i;
    }
  }
  return dict[idx];
}

void lower_band(std::vector<int> input, std::vector<int> &output) {
  output[0] = input[0];
  for (int i = 1; i < input.size(); i += 2) {
    output[(i - 1) / 2] = ((input[i] + input[i - 1])) / 2;
  }
}

void higher_band(std::vector<int> input, std::vector<int> &output) {
  output[0] = 0;
  for (int i = 1; i < input.size(); i += 2) {
    output[(i - 1) / 2] = ((input[i] - input[i - 1])) / 2;
  }
}

void diff_coding(std::vector<int> &input, const std::vector<int> &dict) {
  int curr = quantize(input[0], dict);
  for (int i = 1; i < input.size(); i++) {
    input[i] = input[i] - curr;
    curr += quantize(input[i], dict);
  }
}

void quantize_vect(std::vector<int> &input, const std::vector<int> &dict) {
  for (int &i: input) {
    i = quantize(i, dict);
  }
}

template<class T>
std::vector<T> gen_uniform_dict(T low_bound, T high_bound, int n) {
  n = (int) std::pow(2, n);
  std::vector<T> dict;
  T step = (high_bound - low_bound) / n;
  T last_word = low_bound + step / 2;
  dict.push_back(last_word);
  for (int i = 1; i < n; i++) {
    last_word += step;
    dict.push_back(last_word);
  }
  return dict;
}

double distortion(std::vector<int> a, std::vector<int> b) {
  if (a.size() != b.size()) {
    std::cerr << "Trying to compare " + std::to_string(a.size()) + " size vector and " +
        std::to_string(b.size()) + " size vector" << std::endl;
    return -1;
  }
  double sum = 0;
  for (int i = 0; i < a.size(); i++) {
      double d = a[i] - b[i];
      sum += d*d;
  }
  sum /= a.size() * b.size();
  return sum;
}

std::vector<int> get_optimised_dict(const std::vector<int> &input, int n) {
  double eps = 0.001;
  std::vector<int> dict;
  std::vector<int> output(input.size());
  long avg = 0;
  for (auto i: input) {
    avg += i;
  }
  int s = input.size();
  avg = avg / s;
  dict.push_back(avg);
  for (int k = 0; k < n; k++) {
    int size = dict.size();
    for(int i = 0; i < size; i++){
      dict.push_back(dict[i] + ((rand()%2) * 2) -1);
    }
    double distor = 0;
    double last_distor = 0;
    double cond;
    do {
      std::vector<std::vector<int>> dict_vec(dict.size(), std::vector<int>());
      for (int i = 0; i < input.size(); i++) {
          output[i] = quantize(input[i], dict);
      }
      for (auto &region: dict) {
        int sum =0;
        int c = 0;
        for (int i = 0; i < input.size(); i++) {
            if (region == output[i]) {
              c++;
              sum = sum + input[i];
            }
        }
        if (c != 0)
          region = sum / c;
      }
      last_distor = distor;
      distor = distortion(input, output);
        std::cout << distor << std::endl;
      cond = std::abs((distor - last_distor) / distor);
      if (last_distor != 0 && distor > last_distor) break;
    } while (cond > eps);
  }

  return dict;
}

std::vector<int> get_optimised_diff_dict(const std::vector<int> &input, int n) {
    std::vector<int> diff_coding(input.size());
    for (int i = 1; i < input.size(); i++) {
      diff_coding[i] = input[i] - input[i-1];
    }
    diff_coding = get_optimised_dict(diff_coding,n) ;

    return diff_coding;
}
void decode_color(std::vector<int> low_bound,
                  const std::vector<int> &high_bound,
                  std::vector<int> &output) {

  for (int i = 1; i < low_bound.size(); i++) {
    low_bound[i] = low_bound[i] + low_bound[i - 1];
  }

  for (int i = 0; i < low_bound.size(); i++) {
    int y2n = low_bound[i];
    int z2n = high_bound[i];
    int x = y2n + z2n;
    if (x < 0) x = 0;
    if (x > 255) x = 255;
    output[2 * i + 1] = x;
    x = y2n + z2n;
    if (x < 0) x = 0;
    if (x > 255) x = 255;
    output[2 * i] = x;
  }
}

int main(int argc, char *argv[]) {
  int n = 10;
  auto fn_in = argv[1];
  auto fn_out = argv[2];
  n = std::stoi(argv[3]);
//  std::string in_fn = "../test/example0.tga";
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
  std::vector<int> red(header.width * header.height);
  std::vector<int> green(header.width * header.height);
  std::vector<int> blue(header.width * header.height);

  for (int i = 0; i < header.width * header.height; i++) {
    red[i] = image.pixels[i * 4];
    green[i] = image.pixels[i * 4 + 1];
    blue[i] = image.pixels[i * 4 + 2];
  }

  std::vector<int> dict = gen_uniform_dict(-256, 256, n);
  std::vector<int> high_dict;
  std::vector<int> low_dict;


  std::vector<int> red_high((header.width * header.height) / 2);
  std::vector<int> red_low(header.width * header.height / 2);
  higher_band(red, red_high);
  lower_band(red, red_low);
  high_dict = get_optimised_dict(red_high,n);
  quantize_vect(red_high, high_dict);
  low_dict = get_optimised_diff_dict(red_low,n);
  diff_coding(red_low, low_dict);
  quantize_vect(red_low, low_dict);
  decode_color(red_low, red_high, red);

  std::vector<int> green_high((header.width * header.height) / 2);
  std::vector<int> green_low(header.width * header.height / 2);
  higher_band(green, green_high);
  lower_band(green, green_low);
  high_dict = get_optimised_dict(green_high,n);
  quantize_vect(green_high, high_dict);
  low_dict = get_optimised_diff_dict(green_low,n);
  diff_coding(green_low, low_dict);
  quantize_vect(green_low, low_dict);
  decode_color(green_low, green_high, green);

  std::vector<int> blue_high((header.width * header.height) / 2);
  std::vector<int> blue_low(header.width * header.height / 2);
  higher_band(blue, blue_high);
  lower_band(blue, blue_low);
  high_dict = get_optimised_dict(blue_high,n);
  quantize_vect(blue_high, high_dict);
  low_dict = get_optimised_diff_dict(blue_low,n);
  diff_coding(blue_low, low_dict);
  quantize_vect(blue_low, low_dict);
  decode_color(blue_low, blue_high, blue);

  for (int i = 0; i < header.width * header.height; i++) {
    image.pixels[i * 4] = red[i];
    image.pixels[i * 4 + 1] = green[i];
    image.pixels[i * 4 + 2] = blue[i];
  }
  encoder.writeHeader(header);
  encoder.writeImage(header, image);
  encoder.writeFooter();
}