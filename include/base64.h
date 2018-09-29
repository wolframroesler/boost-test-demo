/**
 * @brief Base-64 encoder/decoder header file
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#pragma once

#include <string>

namespace base64 {
    std::string encode(const std::string&);
    std::string decode(const std::string&);
}
