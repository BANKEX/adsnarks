#include <fstream>
#include "circuit/oracle_protoboard.hpp"
#include <export.hpp>

int main() {
    ethsnarks::ppT::init_public_params();

    const size_t n = 3;

    ethsnarks::oracle_protoboard pb(n);

    pb.generate_r1cs_constraints();

    libff::print_header("R1CS GG-ppzkSNARK Generator");
    libsnark::r1cs_gg_ppzksnark_zok_keypair<ethsnarks::ppT> keypair = libsnark::r1cs_gg_ppzksnark_zok_generator<ethsnarks::ppT>(pb.get_constraint_system());
    printf("\n");
    libff::print_indent();
    libff::print_mem("after generator");

    std::cout << "Total constraints: " << pb.num_constraints() << std::endl;

    std::ofstream pk_dump("../keys/libsnark/pk");
    pk_dump << keypair.pk;

    std::ofstream vk_dump("../keys/libsnark/vk");
    vk_dump << keypair.vk;

    ethsnarks::vk2json_file(keypair.vk, "../keys/ethsnarks/vk.json");

    return 0;
}