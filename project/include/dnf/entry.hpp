#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include "dnf/temp_paths.hpp"
#ifdef _WIN32
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
// Suite entry points only. Product entry points keep DNF_ENTRY: they must
// honour the caller's working directory.
//
// Every relative artifact path a suite writes is resolved against the working
// directory, so a hand-run binary used to litter the repository root with
// fixture directories. Entering <temp>/test-runs/<tag>-<pid> moves all of them
// at once, and keeps read/write symmetric because nothing else changes.
//
// Arguments that already point at an existing path are made absolute first, so
// `dnf_tests ../DNF1031客户端 --group 3` still finds the client from the new
// directory. Selectors such as `--group` and `3` carry no separator and are
// left alone.
#define DNF_TEST_ENTRY(tag, impl)                                                                            \
    int wmain(int argc, wchar_t **wide) {                                                                    \
        std::vector<std::string> storage;                                                                    \
        storage.reserve(static_cast<size_t>(argc));                                                          \
        for (int i = 0; i < argc; i++) {                                                                     \
            int n = WideCharToMultiByte(CP_UTF8, 0, wide[i], -1, nullptr, 0, nullptr, nullptr);              \
            std::string s(static_cast<size_t>(n), 0);                                                        \
            WideCharToMultiByte(CP_UTF8, 0, wide[i], -1, s.data(), n, nullptr, nullptr);                     \
            s.pop_back();                                                                                    \
            storage.push_back(std::move(s));                                                                 \
        }                                                                                                    \
        for (size_t i = 1; i < storage.size(); i++) {                                                        \
            if (storage[i].find('/') == std::string::npos && storage[i].find('\\') == std::string::npos)     \
                continue;                                                                                    \
            std::error_code ec;                                                                              \
            const auto candidate = std::filesystem::u8path(storage[i]);                                      \
            if (std::filesystem::exists(candidate, ec))                                                      \
                storage[i] = std::filesystem::absolute(candidate, ec).u8string();                            \
        }                                                                                                    \
        dnf::testOriginDirectory();                                                                          \
        std::vector<char *> argv;                                                                            \
        argv.reserve(storage.size());                                                                        \
        for (auto &s : storage)                                                                              \
            argv.push_back(s.data());                                                                        \
        dnf::ScopedWorkingDirectory working(dnf::testRunDirectory(tag));                                     \
        return impl(argc, argv.data());                                                                      \
    }
#else
#define DNF_ENTRY(impl)                                                                                      \
    int main(int argc, char **argv) { return impl(argc, argv); }
#define DNF_TEST_ENTRY(tag, impl)                                                                            \
    int main(int argc, char **argv) {                                                                        \
        std::vector<std::string> storage;                                                                    \
        storage.reserve(static_cast<size_t>(argc));                                                          \
        for (int i = 0; i < argc; i++) {                                                                     \
            std::string item = argv[i];                                                                      \
            if (i > 0 && (item.find('/') != std::string::npos || item.find('\\') != std::string::npos)) {    \
                std::error_code ec;                                                                          \
                const auto candidate = std::filesystem::u8path(item);                                        \
                if (std::filesystem::exists(candidate, ec))                                                  \
                    item = std::filesystem::absolute(candidate, ec).u8string();                              \
            }                                                                                                \
            storage.push_back(std::move(item));                                                              \
        }                                                                                                    \
        dnf::testOriginDirectory();                                                                          \
        std::vector<char *> args;                                                                            \
        args.reserve(storage.size());                                                                        \
        for (auto &s : storage)                                                                              \
            args.push_back(s.data());                                                                        \
        dnf::ScopedWorkingDirectory working(dnf::testRunDirectory(tag));                                     \
        return impl(argc, args.data());                                                                      \
    }
#endif
