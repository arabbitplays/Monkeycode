#ifndef MONKEYCODE_APPCONTROLLER_HPP
#define MONKEYCODE_APPCONTROLLER_HPP
#include <filesystem>

class AppController {
    public:
    AppController();

    void executeTest();
    void renderHistoryAnalysis();

private:
    void init();

    std::filesystem::path history_file;
};


#endif // MONKEYCODE_APPCONTROLLER_HPP
