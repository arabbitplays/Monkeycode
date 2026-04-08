#include "io/ImageWriter.hpp"

#include "util/vectors/IVec2.hpp"
#include "util/vectors/Vec3.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

static unsigned char toByte(float c) {
    c = std::clamp(c, 0.0f, 1.0f);
    return static_cast<unsigned char>(c * 255.0f);
}

void ImageWriter::writePPM(const std::string &filename,
                           const std::vector<Vec3> &pixels,
                           const IVec2 &extent) {

    std::ofstream file(filename, std::ios::binary);

    file << "P6\n" << extent.x << " " << extent.y << "\n255\n";

    for (const auto &p : pixels) {
        unsigned char r = toByte(p.x);
        unsigned char g = toByte(p.y);
        unsigned char b = toByte(p.z);

        file.write(reinterpret_cast<char *>(&r), 1);
        file.write(reinterpret_cast<char *>(&g), 1);
        file.write(reinterpret_cast<char *>(&b), 1);
    }
}