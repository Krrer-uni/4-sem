//
// Created by krrer on 09.04.2022.
//

#include "inc/IntDecoding.hpp"

int IntDecoding::nextInt() {
    switch (mode) {
        case 0:
            return reader->getInt();
    }

}

IntDecoding::IntDecoding(std::string filename, int mode) {
    reader = new BitReader(filename);
    this->mode = mode;
}
