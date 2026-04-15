#include "../../include/io/TestHistoryLoader.hpp"

#include "rendering/util/HistoryUtil.hpp"

#include <algorithm>
#include <fstream>

TestHistoryLoader::TestHistoryLoader(const std::filesystem::path &history_dir)
    : history_dir(history_dir) {}

std::shared_ptr<TestHistory> TestHistoryLoader::load() const {
    auto test_history = std::make_shared<TestHistory>();

    std::vector<std::filesystem::path> files{};

    for (const auto &history_file :
         std::filesystem::directory_iterator(history_dir)) {
        files.push_back(history_file.path());
    }

    std::sort(files.begin(), files.end(), [](const std::filesystem::path &a, const std::filesystem::path &b) {
        return HistoryUtil::extractFileIndex(a.stem()) < HistoryUtil::extractFileIndex(b.stem());
    });

    for (const auto &file_path : files) {
        std::ifstream file(file_path);

        if (!file.is_open())
            throw std::runtime_error("Failed to open history file " + file_path.string());

        std::string line;

        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string field;

            ReportDto dto;

            std::getline(ss, dto.timestamp, ',');
            std::getline(ss, field, ',');
            dto.cpm = std::stof(field);
            std::getline(ss, field, ',');
            dto.accuracy = std::stof(field);
            std::getline(ss, field, ',');
            dto.extra_char_count = static_cast<uint32_t>(std::stoul(field));
            std::getline(ss, field, ',');
            dto.missing_char_count = static_cast<uint32_t>(std::stoul(field));

            test_history->reports.push_back(dto);
        }
    }

    return test_history;
}