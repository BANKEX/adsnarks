#include <fstream>
#include "oracle_protoboard.hpp"
#include "utils.cpp"

int main() {
    ethsnarks::ppT::init_public_params();

    const size_t n = 1;

    ethsnarks::oracle_protoboard pb(n);

    pb.generate_r1cs_constraints();

    std::ifstream file("../keys/signature");
    std::string S_bin, message_bin, pk_x_bin, pk_y_bin, r_x_bin, r_y_bin;
    file >> S_bin >> message_bin >> pk_x_bin >> pk_y_bin >> r_x_bin >> r_y_bin;
    pb.ss[0].fill_with_bits(pb, from_binary_string(S_bin));
    pb.ms[0].fill_with_bits(pb, from_binary_string(message_bin));
    pb.pk_x_bins[0].fill_with_bits(pb, from_binary_string(pk_x_bin));
    pb.pk_y_bins[0].fill_with_bits(pb, from_binary_string(pk_y_bin));
    pb.r_x_bins[0].fill_with_bits(pb, from_binary_string(r_x_bin));
    pb.r_y_bins[0].fill_with_bits(pb, from_binary_string(r_y_bin));

    pb.generate_r1cs_witness();

    assert(pb.is_satisfied());

    libsnark::r1cs_gg_ppzksnark_zok_proving_key<ethsnarks::ppT> pk;
    std::ifstream pk_dump("../keys/libsnark/pk");
    pk_dump >> pk;

    libff::print_header("R1CS GG-ppzkSNARK Prover");
    libsnark::r1cs_gg_ppzksnark_zok_proof<ethsnarks::ppT> proof = libsnark::r1cs_gg_ppzksnark_zok_prover<ethsnarks::ppT>(pk, pb.primary_input(), pb.auxiliary_input());
    printf("\n");
    libff::print_indent();
    libff::print_mem("after prover");

    std::cout << "Median: " << pb.val(pb.median) << std::endl;
    std::cout << "Total constraints: " << pb.num_constraints() << std::endl;

    std::ofstream proof_dump("../keys/libsnark/proof");
    proof_dump << proof;

    return 0;
}