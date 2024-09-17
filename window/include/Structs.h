#pragma once

#include "common.h"

namespace LAB
{
    //-------------
    struct WindowInfo {
        int32_t pos_x;
        int32_t pos_y;
        int32_t width;
        int32_t height;
    };
    //-------------
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    //-------------
    struct Circle {
        int32_t pos_x;
        int32_t pos_y;
        int32_t radius;
        Color color;
    };
    //-------------
    struct Square {
        int32_t pos_x;
        int32_t pos_y;
        int32_t length;
        Color color;
    };
    //-------------
    struct SharedData {
        WindowInfo win_info;
        Circle circle1;
        Circle circle2;
        Square square1;
        Square square2;
    };
    //-------------
}