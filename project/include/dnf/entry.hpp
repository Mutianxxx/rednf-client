#pragma once
#ifdef _WIN32
#include <string>
#include <vector>
#include <windows.h>
#define DNF_ENTRY(impl)                                                                                      \
    int wmain(int argc, wchar_t **wide) {                                                                    \
        std::vector<std::string> storage;                                                                    \
        for (int i = 0; i < argc; i++) {                                                                     \
            int n = WideCharToMultiByte(CP_UTF8, 0, wide[i], -1, nullptr, 0, nullptr, nullptr);              \
            std::string s(n, 0);                                                                             \
            WideCharToMultiByte(CP_UTF8, 0, wide[i], -1, s.data(), n, nullptr, nullptr);                     \
            s.pop_back();                                                                                    \
            storage.push_back(s);                                                                            \
        }                                                                                                    \
        std::vector<char *> argv;                                                                            \
        for (auto &s : storage)                                                                              \
            argv.push_back(s.data());                                                                        \
        return impl(argc, argv.data());                                                                      \
    }
#else
#define DNF_ENTRY(impl)                                                                                      \
    int main(int argc, char **argv) { return impl(argc, argv); }
#endif
