#include <fstream>
#include "circuit/oracle_protoboard.hpp"
#include "utils.cpp"
#include <export.hpp>

int main(int argc, char *argv[]) {

    const size_t n = static_cast<size_t >(std::stoi(argv[1]));

    ethsnarks::ppT::init_public_params();

    ethsnarks::oracle_protoboard pb(n);

    pb.generate_r1cs_constraints();

    const std::string &signaturePath = absolute_path("keys/signature");
    std::ifstream file(signaturePath);
    if (!file) {
        std::cerr << signaturePath << " is missing" << std::endl;
        return 1;
    }
    
    std::string message_bin, pk_x_bin, pk_y_bin, r_x_bin, r_y_bin, S_bin;
    for (size_t i = 0; i < n; i++) {
        file >> message_bin >> pk_x_bin >> pk_y_bin >> r_x_bin >> r_y_bin >> S_bin;
        pb.ss[i].fill_with_bits(pb, from_binary_string(S_bin));
        pb.ms[i].fill_with_bits(pb, from_binary_string(message_bin));
        pb.pk_x_bins[i].fill_with_bits(pb, from_binary_string(pk_x_bin));
        pb.pk_y_bins[i].fill_with_bits(pb, from_binary_string(pk_y_bin));
        pb.r_x_bins[i].fill_with_bits(pb, from_binary_string(r_x_bin));
        pb.r_y_bins[i].fill_with_bits(pb, from_binary_string(r_y_bin));
    }

    pb.generate_r1cs_witness();

    assert(pb.is_satisfied());

    libsnark::r1cs_gg_ppzksnark_zok_proving_key<ethsnarks::ppT> pk;
    std::ifstream pk_dump(absolute_path("keys/libsnark/pk"));
    pk_dump >> pk;

    libff::print_header("R1CS GG-ppzkSNARK Prover");
    libsnark::r1cs_gg_ppzksnark_zok_proof<ethsnarks::ppT> proof = libsnark::r1cs_gg_ppzksnark_zok_prover<ethsnarks::ppT>(pk, pb.primary_input(), pb.auxiliary_input());
    printf("\n");
    libff::print_indent();
    libff::print_mem("after prover");

    std::cout << "Median: " << pb.val(pb.median) << std::endl;
    std::cout << "Total constraints: " << pb.num_constraints() << std::endl;

    std::ofstream proof_dump(absolute_path("keys/libsnark/proof"));
    proof_dump << proof;

    std::ofstream proof_json_dump(absolute_path("keys/ethsnarks/proof.json"));
    ethsnarks::PrimaryInputT primary_input = pb.primary_input();
    proof_json_dump << ethsnarks::proof_to_json(proof, primary_input);

    return 0;
}
