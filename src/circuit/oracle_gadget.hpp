//
// Created by swasilyev on 11/6/18.
//

#ifndef AD_SNARK_ORACLE_GADGET_HPP
#define AD_SNARK_ORACLE_GADGET_HPP


#include <ethsnarks.hpp>
#include <jubjub/eddsa.hpp>
#include <gadgets/sha256_full.cpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>

namespace ethsnarks {

    class oracle_gadget : public GadgetT {

        typedef sha256_full_gadget_512 HashT;

    private:
        const jubjub::Params params;

        std::vector<jubjub::eddsa<HashT>> signature_verifiers;
        std::vector<VariableT> packed_messages;
        std::vector<libsnark::packing_gadget<FieldT>> packers;
        VariableArrayT less;
        VariableArrayT less_or_eq;
        std::vector<libsnark::comparison_gadget<FieldT>> comparators;

    public:
        const size_t n;

        VariableT median;

        VariableT a;
        VariableT d;
        VariableT base_x;
        VariableT base_y;

        std::vector<VariableArrayT> pk_x_bins;
        std::vector<VariableArrayT> pk_y_bins;
        std::vector<VariableArrayT> r_x_bins;
        std::vector<VariableArrayT> r_y_bins;
        std::vector<VariableArrayT> ss;
        std::vector<VariableArrayT> ms;

        oracle_gadget(ProtoboardT &pb,
                      const size_t n,
                      const VariableT &median,
                      const std::vector<VariableArrayT> &pk_x_bins,
                      const std::vector<VariableArrayT> &pk_y_bins,
                      const std::vector<VariableArrayT> &r_x_bins,
                      const std::vector<VariableArrayT> &r_y_bins,
                      const std::vector<VariableArrayT> &ss,
                      const std::vector<VariableArrayT> &ms
        );

        void generate_r1cs_constraints();

        void generate_r1cs_witness();
    };
}

#endif //AD_SNARK_ORACLE_GADGET_HPP
