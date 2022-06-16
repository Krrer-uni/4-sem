//
// Created by krrer on 16.06.22.
//

#ifndef HAMMING_BIT_OPERATIONS_HPP
#define HAMMING_BIT_OPERATIONS_HPP

#include <eigen3/Eigen/Dense>

Eigen::Matrix<int , 8, 1> ctb(uint8_t n);
uint8_t btc(Eigen::Matrix<int , 8, 1> n);

#endif //HAMMING_BIT_OPERATIONS_HPP
