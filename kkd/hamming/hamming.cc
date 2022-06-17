//
// Created by krrer on 16.06.22.
//

#include "include/hamming.hpp"

void generate_dict(uint8_t *output, int size) {
    Eigen::Matrix<int, 8, 4> G;
    G << 0, 0, 0, 1,
            0, 0, 1, 1,
            0, 1, 1, 0,
            1, 1, 0, 1,
            1, 0, 1, 0,
            0, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 0, 0;

    for (int i = 0; i < size; i++) {
        Eigen::Matrix<int, 8, 1> b = G * ctb(i).tail<4>();
        b(7, 0) = b.sum();
        b = b.unaryExpr([&](const int x) { return x % 2; });
//        std::cout << (int)btc(b) << " " << b.transpose() << "\n\n";
        output[i] = btc(b);

    }
}

uint8_t decode_word(uint8_t n) {
    auto a = ctb(n);
    Eigen::Matrix<int, 4, 8> H;
    H << 0, 0, 1, 0, 1, 1, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0,
            1, 0, 1, 1, 1, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1;
    Eigen::Matrix<int, 4,1> syndrom = (H * a).unaryExpr([&](const int x) {return x%2;});
    if(syndrom.sum() != 0){
        std::cout << ctb(n).transpose() << "\n" << syndrom.transpose() << "\n\n";
        if(syndrom(3,0) == 0){
            return 0;
        }
        int idx = syndrom(2,0) * 4 + syndrom(1,0) * 2 + syndrom(0,0);
        a(idx) = (a(idx) + 1) %2;
    }
    uint8_t f = a(0,0) + ((a(1,0) + a(0,0))%2) * 2 + a(5,0) * 4 + a(6,0) * 8;
    return f;
}
