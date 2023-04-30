// Copyright 2023 Musin Alexandr

#include <gtest/gtest.h>
#include <omp.h>

#include <vector>

struct image {
    int leftColorLimit;
    int rightColorLimit;
    int width;
    int height;
    std::vector<std::vector<int>> data;
    explicit image(const std::vector<std::vector<int>>& vec) {
        int size = vec.size();
        if (!size) {
            width = 0;
            height = 0;
            leftColorLimit = 0;
            rightColorLimit = 0;
            return;
        }
        width = size;
        height = vec.at(0).size();
        data = vec;
        leftColorLimit = 255;
        rightColorLimit = 0;
        for (auto i : data) {
            for (auto j : i) {
                if (j > rightColorLimit) rightColorLimit = j;
                if (j < leftColorLimit) leftColorLimit = j;
            }
        }
    }
    friend bool operator==(const image& lhs, const image& rhs) {
        if (lhs.width != rhs.width || lhs.height != rhs.height) return false;
        for (int i = 0; i < lhs.width; i++) {
            for (int j = 0; j < lhs.height; j++) {
                if (lhs.data.at(i).at(j) != rhs.data.at(i).at(j)) return false;
            }
        }
        return true;
    }
};

image linearContrastSeq(const image& img) {
    image res(img);

#pragma omp parallel for
    for (int i = 0; i < res.width; i++) {
        for (int j = 0; j < res.height; j++) {
            res.data.at(i).at(j) = (res.data.at(i).at(j) - res.leftColorLimit) *
                                   255 /
                                   (res.rightColorLimit - res.leftColorLimit);
        }
    }
    return res;
}

TEST(OMP, Test_5x5) {
    std::vector<std::vector<int>> img{
        std::vector<int>{183, 186, 177, 115, 193},
        std::vector<int>{135, 186, 192, 149, 121},
        std::vector<int>{162, 127, 190, 159, 163},
        std::vector<int>{126, 140, 126, 172, 136},
        std::vector<int>{111, 168, 167, 129, 182}};

    std::vector<std::vector<int>> resImg{
        std::vector<int>{223, 233, 205, 12, 255},
        std::vector<int>{74, 233, 251, 118, 31},
        std::vector<int>{158, 49, 245, 149, 161},
        std::vector<int>{46, 90, 46, 189, 77},
        std::vector<int>{0, 177, 174, 55, 220}};

    image fnRes = linearContrastSeq(image(img));
    ASSERT_EQ(image(resImg), fnRes);
}

TEST(OMP, Test_7x7) {
    std::vector<std::vector<int>> img{
        std::vector<int>{183, 186, 177, 115, 193, 135, 186},
        std::vector<int>{192, 149, 121, 162, 127, 190, 159},
        std::vector<int>{163, 126, 140, 126, 172, 136, 111},
        std::vector<int>{168, 167, 129, 182, 130, 162, 123},
        std::vector<int>{167, 135, 129, 102, 122, 158, 169},
        std::vector<int>{167, 193, 156, 111, 142, 129, 173},
        std::vector<int>{121, 119, 184, 137, 198, 124, 115}};

    std::vector<std::vector<int>> resImg{
        std::vector<int>{215, 223, 199, 34, 241, 87, 223},
        std::vector<int>{239, 124, 50, 159, 66, 233, 151},
        std::vector<int>{162, 63, 100, 63, 185, 90, 23},
        std::vector<int>{175, 172, 71, 212, 74, 159, 55},
        std::vector<int>{172, 87, 71, 0, 53, 148, 177},
        std::vector<int>{172, 241, 143, 23, 106, 71, 188},
        std::vector<int>{50, 45, 217, 92, 255, 58, 34}};

    image fnRes = linearContrastSeq(image(img));
    ASSERT_EQ(image(resImg), fnRes);
}

TEST(OMP, Test_10x10) {
    std::vector<std::vector<int>> img{
        std::vector<int>{183, 186, 177, 115, 193, 135, 186, 192, 149, 121},
        std::vector<int>{162, 127, 190, 159, 163, 126, 140, 126, 172, 136},
        std::vector<int>{111, 168, 167, 129, 182, 130, 162, 123, 167, 135},
        std::vector<int>{129, 102, 122, 158, 169, 167, 193, 156, 111, 142},
        std::vector<int>{129, 173, 121, 119, 184, 137, 198, 124, 115, 170},
        std::vector<int>{113, 126, 191, 180, 156, 173, 162, 170, 196, 181},
        std::vector<int>{105, 125, 184, 127, 136, 105, 146, 129, 113, 157},
        std::vector<int>{124, 195, 182, 145, 114, 167, 134, 164, 143, 150},
        std::vector<int>{187, 108, 176, 178, 188, 184, 103, 151, 154, 199},
        std::vector<int>{132, 160, 176, 168, 139, 112, 126, 186, 194, 139}};

    std::vector<std::vector<int>> resImg{
        std::vector<int>{212, 220, 197, 34, 239, 86, 220, 236, 123, 49},
        std::vector<int>{157, 65, 231, 149, 160, 63, 99, 63, 184, 89},
        std::vector<int>{23, 173, 170, 70, 210, 73, 157, 55, 170, 86},
        std::vector<int>{70, 0, 52, 147, 176, 170, 239, 141, 23, 105},
        std::vector<int>{70, 186, 49, 44, 215, 92, 252, 57, 34, 178},
        std::vector<int>{28, 63, 233, 205, 141, 186, 157, 178, 247, 207},
        std::vector<int>{7, 60, 215, 65, 89, 7, 115, 70, 28, 144},
        std::vector<int>{57, 244, 210, 113, 31, 170, 84, 162, 107, 126},
        std::vector<int>{223, 15, 194, 199, 226, 215, 2, 128, 136, 255},
        std::vector<int>{78, 152, 194, 173, 97, 26, 63, 220, 241, 97}};

    image fnRes = linearContrastSeq(image(img));
    ASSERT_EQ(image(resImg), fnRes);
}

TEST(OMP, Test_13x13) {
    std::vector<std::vector<int>> img{
        std::vector<int>{183, 186, 177, 115, 193, 135, 186, 192, 149, 121, 162,
                         127, 190},
        std::vector<int>{159, 163, 126, 140, 126, 172, 136, 111, 168, 167, 129,
                         182, 130},
        std::vector<int>{162, 123, 167, 135, 129, 102, 122, 158, 169, 167, 193,
                         156, 111},
        std::vector<int>{142, 129, 173, 121, 119, 184, 137, 198, 124, 115, 170,
                         113, 126},
        std::vector<int>{191, 180, 156, 173, 162, 170, 196, 181, 105, 125, 184,
                         127, 136},
        std::vector<int>{105, 146, 129, 113, 157, 124, 195, 182, 145, 114, 167,
                         134, 164},
        std::vector<int>{143, 150, 187, 108, 176, 178, 188, 184, 103, 151, 154,
                         199, 132},
        std::vector<int>{160, 176, 168, 139, 112, 126, 186, 194, 139, 195, 170,
                         134, 178},
        std::vector<int>{167, 101, 197, 102, 117, 192, 152, 156, 101, 180, 186,
                         141, 165},
        std::vector<int>{189, 144, 119, 140, 129, 131, 117, 197, 171, 181, 175,
                         109, 127},
        std::vector<int>{167, 156, 197, 153, 186, 165, 106, 183, 119, 124, 128,
                         171, 132},
        std::vector<int>{129, 103, 119, 170, 168, 108, 115, 140, 149, 196, 123,
                         118, 145},
        std::vector<int>{146, 151, 121, 155, 179, 188, 164, 128, 141, 150, 193,
                         100, 134}};

    std::vector<std::vector<int>> resImg{
        std::vector<int>{213, 221, 198, 38, 239, 90, 221, 236, 126, 54, 159, 69,
                         231},
        std::vector<int>{151, 162, 66, 103, 66, 185, 92, 28, 175, 172, 74, 211,
                         77},
        std::vector<int>{159, 59, 172, 90, 74, 5, 56, 149, 177, 172, 239, 144,
                         28},
        std::vector<int>{108, 74, 188, 54, 48, 216, 95, 252, 61, 38, 180, 33,
                         66},
        std::vector<int>{234, 206, 144, 188, 159, 180, 247, 208, 12, 64, 216,
                         69, 92},
        std::vector<int>{12, 118, 74, 33, 146, 61, 244, 211, 115, 36, 172, 87,
                         164},
        std::vector<int>{110, 128, 224, 20, 195, 200, 226, 216, 7, 131, 139,
                         255, 82},
        std::vector<int>{154, 195, 175, 100, 30, 66, 221, 242, 100, 244, 180,
                         87, 200},
        std::vector<int>{172, 2, 249, 5, 43, 236, 133, 144, 2, 206, 221, 105,
                         167},
        std::vector<int>{229, 113, 48, 103, 74, 79, 43, 249, 182, 208, 193, 23,
                         69},
        std::vector<int>{172, 144, 249, 136, 221, 167, 15, 213, 48, 61, 72, 182,
                         82},
        std::vector<int>{74, 7, 48, 180, 175, 20, 38, 103, 126, 247, 59, 46,
                         115},
        std::vector<int>{118, 131, 54, 141, 203, 226, 164, 72, 105, 128, 239, 0,
                         87}};

    image fnRes = linearContrastSeq(image(img));
    ASSERT_EQ(image(resImg), fnRes);
}

TEST(OMP, Test_15x15) {
    std::vector<std::vector<int>> img{
        std::vector<int>{183, 186, 177, 115, 193, 135, 186, 192, 149, 121, 162,
                         127, 190, 159, 163},
        std::vector<int>{126, 140, 126, 172, 136, 111, 168, 167, 129, 182, 130,
                         162, 123, 167, 135},
        std::vector<int>{129, 102, 122, 158, 169, 167, 193, 156, 111, 142, 129,
                         173, 121, 119, 184},
        std::vector<int>{137, 198, 124, 115, 170, 113, 126, 191, 180, 156, 173,
                         162, 170, 196, 181},
        std::vector<int>{105, 125, 184, 127, 136, 105, 146, 129, 113, 157, 124,
                         195, 182, 145, 114},
        std::vector<int>{167, 134, 164, 143, 150, 187, 108, 176, 178, 188, 184,
                         103, 151, 154, 199},
        std::vector<int>{132, 160, 176, 168, 139, 112, 126, 186, 194, 139, 195,
                         170, 134, 178, 167},
        std::vector<int>{101, 197, 102, 117, 192, 152, 156, 101, 180, 186, 141,
                         165, 189, 144, 119},
        std::vector<int>{140, 129, 131, 117, 197, 171, 181, 175, 109, 127, 167,
                         156, 197, 153, 186},
        std::vector<int>{165, 106, 183, 119, 124, 128, 171, 132, 129, 103, 119,
                         170, 168, 108, 115},
        std::vector<int>{140, 149, 196, 123, 118, 145, 146, 151, 121, 155, 179,
                         188, 164, 128, 141},
        std::vector<int>{150, 193, 100, 134, 164, 124, 114, 187, 156, 143, 191,
                         127, 165, 159, 136},
        std::vector<int>{132, 151, 137, 128, 175, 107, 174, 121, 158, 195, 129,
                         137, 135, 193, 118},
        std::vector<int>{128, 143, 111, 128, 129, 176, 104, 143, 163, 113, 138,
                         106, 140, 104, 118},
        std::vector<int>{128, 188, 169, 117, 117, 196, 124, 143, 170, 183, 190,
                         199, 172, 125, 144}};

    std::vector<std::vector<int>> resImg{
        std::vector<int>{213, 221, 198, 38, 239, 90, 221, 236, 126, 54, 159, 69,
                         231, 151, 162},
        std::vector<int>{66, 103, 66, 185, 92, 28, 175, 172, 74, 211, 77, 159,
                         59, 172, 90},
        std::vector<int>{74, 5, 56, 149, 177, 172, 239, 144, 28, 108, 74, 188,
                         54, 48, 216},
        std::vector<int>{95, 252, 61, 38, 180, 33, 66, 234, 206, 144, 188, 159,
                         180, 247, 208},
        std::vector<int>{12, 64, 216, 69, 92, 12, 118, 74, 33, 146, 61, 244,
                         211, 115, 36},
        std::vector<int>{172, 87, 164, 110, 128, 224, 20, 195, 200, 226, 216, 7,
                         131, 139, 255},
        std::vector<int>{82, 154, 195, 175, 100, 30, 66, 221, 242, 100, 244,
                         180, 87, 200, 172},
        std::vector<int>{2, 249, 5, 43, 236, 133, 144, 2, 206, 221, 105, 167,
                         229, 113, 48},
        std::vector<int>{103, 74, 79, 43, 249, 182, 208, 193, 23, 69, 172, 144,
                         249, 136, 221},
        std::vector<int>{167, 15, 213, 48, 61, 72, 182, 82, 74, 7, 48, 180, 175,
                         20, 38},
        std::vector<int>{103, 126, 247, 59, 46, 115, 118, 131, 54, 141, 203,
                         226, 164, 72, 105},
        std::vector<int>{128, 239, 0, 87, 164, 61, 36, 224, 144, 110, 234, 69,
                         167, 151, 92},
        std::vector<int>{82, 131, 95, 72, 193, 18, 190, 54, 149, 244, 74, 95,
                         90, 239, 46},
        std::vector<int>{72, 110, 28, 72, 74, 195, 10, 110, 162, 33, 97, 15,
                         103, 10, 46},
        std::vector<int>{72, 226, 177, 43, 43, 247, 61, 110, 180, 213, 231, 255,
                         185, 64, 113}};

    image fnRes = linearContrastSeq(image(img));
    ASSERT_EQ(image(resImg), fnRes);
}
