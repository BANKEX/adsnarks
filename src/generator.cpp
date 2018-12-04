#include <fstream>
#include "circuit/oracle_protoboard.hpp"
#include <export.hpp>
#include "utils.cpp"

int main(int argc, char *argv[]) {

    const size_t n = static_cast<size_t >(std::stoi(argv[1]));

    std::string pk_in_path = absolute_path("keys/libsnark/pk");
    if (std::ifstream(pk_in_path)) {
        std::cout << pk_in_path << " is already present" << std::endl;
        return 0;
    }

    ethsnarks::ppT::init_public_params();

    ethsnarks::oracle_protoboard pb(n);

    pb.generate_r1cs_constraints();

    libff::print_header("R1CS GG-ppzkSNARK Generator");
    libsnark::r1cs_gg_ppzksnark_zok_keypair<ethsnarks::ppT> keypair = libsnark::r1cs_gg_ppzksnark_zok_generator<ethsnarks::ppT>(pb.get_constraint_system());
    printf("\n");
    libff::print_indent();
    libff::print_mem("after generator");

    std::cout << "Total constraints: " << pb.num_constraints() << std::endl;

    std::ofstream pk_dump(absolute_path("keys/libsnark/pk"));
    pk_dump << keypair.pk;

    std::ofstream vk_dump(absolute_path("keys/libsnark/vk"));
    vk_dump << keypair.vk;

    ethsnarks::vk2json_file(keypair.vk, absolute_path("keys/ethsnarks/vk.json"));

    return 0;
}