#ifndef MONKEYCODE_IMAGEWRITE_HPP
#define MONKEYCODE_IMAGEWRITE_HPP
#include "util/vectors/Vec3.hpp"
#include "util/vectors/IVec2.hpp"

class ImageWriter {
  public:
    ImageWriter();

    static void writePPM(const std::string &filename,
                         const std::vector<Vec3> &pixels, const IVec2 &extent);
};

#endif // MONKEYCODE_IMAGEWRITE_HPP
