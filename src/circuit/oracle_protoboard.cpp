//
// Created by swasilyev on 11/6/18.
//

#include "oracle_protoboard.hpp"

namespace ethsnarks {

    oracle_protoboard::oracle_protoboard(const size_t n) :
            n(n),
            B(FieldT("16117159321177103813813294286550615556837550473658220567209763364611339839115"),
              FieldT("11465736382824868633493204496205282307637286781164666440541087834417561817657")),
            As(n),
            Rs(n),
            ss(n),
            ms(n) {

        median.allocate(*this, "median");

        for (size_t i = 0; i < n; i++) {
            As[i].x.allocate(*this, FMT("", "As[%zu].x", i));
            As[i].y.allocate(*this, FMT("", "As[%zu].y", i));
        }

        this->set_input_sizes(1 + 2 * n); // (1 x median) + (n x public keys)

        for (size_t i = 0; i < n; i++) {
            Rs[i].x.allocate(*this, FMT("", "Rs[%zu].x", i));
            Rs[i].y.allocate(*this, FMT("", "Rs[%zu].y", i));
            ss[i].allocate(*this, FieldT::size_in_bits(), FMT("", "ss[%zu]", i));
            ms[i].allocate(*this, 240, FMT("", "ms[%zu]", i)); //TODO: size
        }

        _oracle_gadget.reset(new oracle_gadget(*this, n, median, B, As, Rs, ss, ms));
    }

    void oracle_protoboard::generate_r1cs_constraints() {
        _oracle_gadget->generate_r1cs_constraints();
    }

    void oracle_protoboard::generate_r1cs_witness() {
        _oracle_gadget->generate_r1cs_witness();
    }
}