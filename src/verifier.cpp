//
// Created by swasilyev on 11/6/18.
//

#include <fstream>
#include <ethsnarks.hpp>
#include "utils.cpp"

int main() {
    ethsnarks::ppT::init_public_params();

    const size_t n = 3;

    libsnark::r1cs_gg_ppzksnark_zok_verification_key<ethsnarks::ppT> vk;
    std::ifstream vk_dump("../keys/libsnark/vk");
    vk_dump >> vk;

    libsnark::r1cs_gg_ppzksnark_zok_proof<ethsnarks::ppT> proof;
    std::ifstream proof_dump("../keys/libsnark/proof");
    proof_dump >> proof;

    std::ifstream file("../keys/signature");
    std::string S_bin, message_bin, pk_x_bin, pk_y_bin, r_x_bin, r_y_bin, pk;
    for (size_t i = 0; i < n; i++) {
        file >> S_bin >> message_bin >> pk_x_bin >> pk_y_bin >> r_x_bin >> r_y_bin;
        pk += pk_x_bin + pk_y_bin;
    }

    std::vector<ethsnarks::FieldT> public_input;
    public_input.emplace_back(345); //TODO
    for (auto b : libff::pack_bit_vector_into_field_element_vector<ethsnarks::FieldT>(from_binary_string(pk))) {
        public_input.emplace_back(b);
    }

    libff::print_header("R1CS GG-ppzkSNARK Verifier");
    const bool ans = libsnark::r1cs_gg_ppzksnark_zok_verifier_strong_IC<ethsnarks::ppT>(vk, public_input, proof);
    printf("\n");
    libff::print_indent();
    libff::print_mem("after verifier");

    printf("* The verification result is: %s\n", (ans ? "PASS" : "FAIL"));

    return 0;
}
