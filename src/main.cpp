#include "r1cs_gg_ppzksnark_zok/r1cs_gg_ppzksnark_zok_pp.hpp"
#include "r1cs_gg_ppzksnark_zok/examples/run_r1cs_gg_ppzksnark_zok.hpp"

template<typename ppT>
void test_r1cs_gg_ppzksnark_zok(size_t num_constraints,
                                size_t input_size) {
    libff::print_header("(enter) Test R1CS GG-ppzkSNARK");

    const bool test_serialization = true;
    libsnark::r1cs_example<libff::Fr<ppT> > example = libsnark::generate_r1cs_example_with_binary_input<libff::Fr<ppT> >(
            num_constraints, input_size);
    const bool bit = libsnark::run_r1cs_gg_ppzksnark_zok<ppT>(example, test_serialization);
    assert(bit);

    libff::print_header("(leave) Test R1CS GG-ppzkSNARK");
}

int main() {
    libsnark::default_r1cs_gg_ppzksnark_zok_pp::init_public_params();
    libff::start_profiling();
    test_r1cs_gg_ppzksnark_zok<libsnark::default_r1cs_gg_ppzksnark_zok_pp>(1000, 100);
    return 0;
}