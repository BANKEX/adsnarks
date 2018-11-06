//
// Created by swasilyev on 11/6/18.
//

libff::bit_vector from_binary_string(std::string s) {
    libff::bit_vector v;
    for (auto b : s) {
        v.emplace_back(b == '1');
    }
    return v;
}