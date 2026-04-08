#include "../../include/io/TestHistoryLoader.hpp"

#include <fstream>

TestHistoryLoader::TestHistoryLoader(
    const std::filesystem::path &history_file_path) : history_file_path(history_file_path) {}

std::shared_ptr<TestHistory> TestHistoryLoader::load() const {
    auto test_history = std::make_shared<TestHistory>();
    std::ifstream file(history_file_path);

    if (!file.is_open())
        return test_history;

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

    return test_history;
}