/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "halLogger.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <iostream>

HalLogger::HalLogger() : logflag(0)
{
    configure();
}

HalLogger& HalLogger::instance()
{
    static HalLogger logger;
    return logger;
}

void HalLogger::setLogFlag(int flag)
{
    std::lock_guard<std::mutex> lock(mtx);
    logflag = flag;
}

int HalLogger::getLogFlag() const {
    return logflag;
}

void HalLogger::log(LogLevel level, const char* func, int line, const std::string& msg)
{
    (void)func;
    (void)line;
    std::lock_guard<std::mutex> lock(mtx);
    std::string prefix = logLevelToString(level);
    std::cout << prefix << ":" << msg << std::endl;
}

void HalLogger::configure(const std::string& configFile)
{
    loadConfig(configFile);
}

void HalLogger::loadConfig(const std::string& configFile)
{
    logflag = 0;
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "MIRACASTHAL HalLogger::loadConfig error opening " << configFile << std::endl;
        return;
    }
    std::string line;
    struct LogLevelEntry {
        std::string nameEnabled;
        std::string nameDisabled;
        int flag;
    };
    LogLevelEntry log_levels[] = {
        {"ERROR", "!ERROR", 1 << static_cast<int>(LogLevel::Error)},
        {"WARNING", "!WARNING", 1 << static_cast<int>(LogLevel::Warning)},
        {"INFO", "!INFO", 1 << static_cast<int>(LogLevel::Info)},
        {"DEBUG", "!DEBUG", 1 << static_cast<int>(LogLevel::Debug)}
    };
    while (std::getline(file, line)) {
        line.erase(line.find_last_not_of("\n\r") + 1);
        if (line.compare(0, 13, "LOG.RDK.MIRACAST") == 0) {
            for (const auto& entry : log_levels) {
                if (line.find(entry.nameEnabled) != std::string::npos) {
                    logflag |= entry.flag;
                } else if (line.find(entry.nameDisabled) != std::string::npos) {
                    logflag &= ~entry.flag;
                }
            }
            break;
        }
    }
    file.close();
    std::cout << "MIRACASTHAL HalLogger::loadConfig logflag: 0x" << std::hex << logflag << std::dec << std::endl;
}

std::string HalLogger::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::Error: return "MIRACASTHAL-ERROR";
        case LogLevel::Warning: return "MIRACASTHAL-WARNING";
        case LogLevel::Info: return "MIRACASTHAL-INFO";
        case LogLevel::Debug: return "MIRACASTHAL-DEBUG";
        default: return "MIRACASTHAL-DEFAULT";
    }
}

// C++-style static object for automatic logger configuration at load time
struct HalLoggerInitializer {
    HalLoggerInitializer() {
#if defined(GIT_SHA)
        std::cout << __FUNCTION__ << ":" << __LINE__ << ": MIRACASTHAL SHA:'" << GIT_SHA << "'" << std::endl;
#endif
        HalLogger::instance().configure();
    }
};
static HalLoggerInitializer halLoggerInitializer;
