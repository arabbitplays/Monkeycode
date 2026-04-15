#ifndef MONKEYCODE_TESTHISTORYLOADER_HPP
#define MONKEYCODE_TESTHISTORYLOADER_HPP
#include "model/TestHistory.hpp"

#include <filesystem>

class TestHistoryLoader {
  public:
    explicit TestHistoryLoader(const std::filesystem::path &history_file_path);

    std::shared_ptr<TestHistory> load() const;

  private:
    std::filesystem::path history_dir;
};

#endif // MONKEYCODE_TESTHISTORYLOADER_HPP
