//
// Created by swasilyev on 11/6/18.
//

#include "oracle_protoboard.hpp"

namespace ethsnarks {

    oracle_protoboard::oracle_protoboard(const size_t n) :
            n(n),
            pk_x_bins(n),
            pk_y_bins(n),
            r_x_bins(n),
            r_y_bins(n),
            ss(n),
            ms(n) {

        median.allocate(*this, "median");

        const size_t pks_size = 2 * n * 256;
        const size_t pks_packed_size = libff::div_ceil(pks_size, FieldT::capacity());
        pks_packed.allocate(*this, pks_packed_size, "pks_packed");

        this->set_input_sizes(1 + pks_packed_size);

        for (size_t i = 0; i < n; i++) {
            pk_x_bins[i].allocate(*this, 256, FMT("", "pk_x_bin_%zu", i)); //FMT("", "%zu", i)
            pk_y_bins[i].allocate(*this, 256, FMT("", "pk_y_bin_%zu", i));
            r_x_bins[i].allocate(*this, 256, FMT("", "r_x_bin_%zu", i));
            r_y_bins[i].allocate(*this, 256, FMT("", "r_y_bin_%zu", i));
            ss[i].allocate(*this, 256, FMT("", "s_%zu", i));
            ms[i].allocate(*this, 256, FMT("", "m_%zu", i));
            // we don't allocate pks_unpacked at the protoboard, just populate it with references to existing inputs
            pks_unpacked.insert(pks_unpacked.end(), pk_x_bins[i].begin(), pk_x_bins[i].end());
            pks_unpacked.insert(pks_unpacked.end(), pk_y_bins[i].begin(), pk_y_bins[i].end());
        }

        _oracle_gadget.reset(
                new oracle_gadget(*this, n, median, pk_x_bins, pk_y_bins, r_x_bins, r_y_bins, ss,
                                                 ms)); //TODO: annotation
        pks_packer.reset(
                new libsnark::multipacking_gadget<FieldT>(*this, pks_unpacked, pks_packed, FieldT::capacity(), "pks_packer"));

        assert(pks_unpacked.size() == pks_size);
        assert(pks_packed_size == pks_packer->num_chunks);
    }

    void oracle_protoboard::generate_r1cs_constraints() {
        _oracle_gadget->generate_r1cs_constraints();
        pks_packer->generate_r1cs_constraints(false); //TODO: bitness
    }

    void oracle_protoboard::generate_r1cs_witness() {
        _oracle_gadget->generate_r1cs_witness();
        pks_packer->generate_r1cs_witness_from_bits();
        assert(pks_packed.get_vals(*this) ==
               libff::pack_bit_vector_into_field_element_vector<FieldT>(pks_unpacked.get_bits(*this)));
    }
}