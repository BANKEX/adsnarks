//
// Created by swasilyev on 11/6/18.
//

#include <fstream>
#include <ethsnarks.hpp>
#include "utils.cpp"

int main(int argc, char *argv[]) {

    const size_t n = static_cast<size_t >(std::stoi(argv[1]));

    ethsnarks::ppT::init_public_params();

    libsnark::r1cs_gg_ppzksnark_zok_verification_key<ethsnarks::ppT> vk;
    std::ifstream vk_dump(absolute_path("keys/libsnark/vk"));
    vk_dump >> vk;

    libsnark::r1cs_gg_ppzksnark_zok_proof<ethsnarks::ppT> proof;
    std::ifstream proof_dump(absolute_path("keys/libsnark/proof"));
    proof_dump >> proof;

    std::vector<ethsnarks::FieldT> public_input;

    std::ifstream file(absolute_path("keys/signature"));
    std::string m, Ax, Ay, Rx, Ry, s;
    for (size_t i = 0; i < n; i++) {
        file >> m >> Ax >> Ay >> Rx >> Ry >> s;
        if (i == 0) { //TODO: median
            public_input.emplace_back(libff::convert_bit_vector_to_field_element<ethsnarks::FieldT>(from_binary_string(m)));
        }
        public_input.emplace_back(ethsnarks::FieldT(Ax.c_str()));
        public_input.emplace_back(ethsnarks::FieldT(Ay.c_str()));
    }

    libff::print_header("R1CS GG-ppzkSNARK Verifier");
    const bool ans = libsnark::r1cs_gg_ppzksnark_zok_verifier_strong_IC<ethsnarks::ppT>(vk, public_input, proof);
    printf("\n");
    libff::print_indent();
    libff::print_mem("after verifier");

    printf("* The verification result is: %s\n", (ans ? "PASS" : "FAIL"));

    return 0;
}
