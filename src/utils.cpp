//
// Created by swasilyev on 11/6/18.
//

#include <libff/common/utils.hpp>

libff::bit_vector from_binary_string(const std::string& s) {
    libff::bit_vector v;
    for (auto b : s) {
        v.emplace_back(b == '1');
    }
    return v;
}

const std::string absolute_path(const char* path) {
    return std::string(PROJECT_ROOT_PATH) + "/" + path;
}