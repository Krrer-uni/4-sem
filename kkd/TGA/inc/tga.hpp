//
// Created by krrer on 04.05.22.
//

#ifndef TGA_TGA_HPP
#define TGA_TGA_HPP

#include <cstdint>
#include <string>

struct Header{
    uint8_t  idLength;
    uint8_t  colormapType;
    uint8_t  imageType;
    uint16_t colormapOrigin;
    uint16_t colormapLength;
    uint8_t  colormapDepth;
    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t  bitsPerPixel;
    uint8_t  imageDescriptor;
    std::string imageId;
};

struct Image {
    uint8_t* pixels;
    uint32_t bytesPerPixel;
    uint32_t rowstride;
};

#endif //TGA_TGA_HPP
