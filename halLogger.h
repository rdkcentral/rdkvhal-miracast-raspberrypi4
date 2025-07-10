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

#ifndef _HAL_LOGGER_H_
#define _HAL_LOGGER_H_

#include <string>
#include <mutex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>

class HalLogger {
public:
    enum class LogLevel {
        Error = 0,
        Warning,
        Info,
        Debug
    };

    static HalLogger& instance();
    void setLogFlag(int flag);
    int getLogFlag() const;
    void log(LogLevel level, const char* func, int line, const std::string& msg);
    void configure(const std::string& configFile = "/etc/debug.ini");

private:
    HalLogger();
    void loadConfig(const std::string& configFile);
    std::string logLevelToString(LogLevel level) const;
    int logflag;
    std::mutex mtx;
};

#define HAL_LOG(level, format, ...) \
    do { \
        if (HalLogger::instance().getLogFlag() & (1 << static_cast<int>(HalLogger::LogLevel::level))) { \
            std::ostringstream oss; \
            oss << "[MIRACASTHAL:" << __func__ << ":" << __LINE__ << "] " << format; \
            HalLogger::instance().log(HalLogger::LogLevel::level, __func__, __LINE__, oss.str()); \
        } \
    } while (0)

#define LOG_ERR(format, ...)  HAL_LOG(Error, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) HAL_LOG(Warning, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) HAL_LOG(Info, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)  HAL_LOG(Debug, format, ##__VA_ARGS__)

#endif  /* _HAL_LOGGER_H_ */
