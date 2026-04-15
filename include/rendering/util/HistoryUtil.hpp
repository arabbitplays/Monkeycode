#ifndef MONKEYCODE_HISTORYUTIL_HPP
#define MONKEYCODE_HISTORYUTIL_HPP
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>

class HistoryUtil {
  public:
    static inline const std::string HISTORY_FILE_PREFIX = "history_";

    static int32_t extractFileIndex(const std::string &file_name) {
        if (file_name.rfind(HISTORY_FILE_PREFIX, 0) != 0) {
            throw std::invalid_argument("History filename " + file_name +
                                        " is not valid");
        }

        return std::stoi(file_name.substr(HISTORY_FILE_PREFIX.size()));
    }

    static size_t countLines(const std::string &filename) {
        std::ifstream file(filename, std::ios::binary);
        return std::count(std::istreambuf_iterator<char>(file),
                          std::istreambuf_iterator<char>(), '\n');
    }

    static std::ofstream createNewHistoryFile(std::filesystem::path dir,
                                              uint32_t index) {
        std::filesystem::path path =
            dir / (HISTORY_FILE_PREFIX + std::to_string(index) + ".csv");
        if (std::filesystem::exists(path)) {
            throw std::runtime_error("History file " + path.string() +
                                     " does already exist");
        }

        std::ofstream file(path);
        if (!file) {
            throw std::runtime_error("Failed to create new history file");
        }

        return file;
    }
};

#endif // MONKEYCODE_HISTORYUTIL_HPP
