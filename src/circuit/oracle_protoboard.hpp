//
// Created by swasilyev on 11/6/18.
//

#ifndef AD_SNARK_ORACLE_PROTOBOARD_HPP
#define AD_SNARK_ORACLE_PROTOBOARD_HPP

#include <ethsnarks.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include "oracle_gadget.hpp"

namespace ethsnarks {

    class oracle_protoboard : public ProtoboardT {
    public:
        const size_t n;
        ProtoboardT pb;
        VariableT median;
        VariableArrayT pks_packed;
        VariableArrayT pks_unpacked;
        std::vector<VariableArrayT> pk_x_bins;
        std::vector<VariableArrayT> pk_y_bins;
        std::vector<VariableArrayT> r_x_bins;
        std::vector<VariableArrayT> r_y_bins;
        std::vector<VariableArrayT> ss;
        std::vector<VariableArrayT> ms;

        std::shared_ptr<oracle_gadget> _oracle_gadget;
        std::shared_ptr<libsnark::multipacking_gadget<FieldT>> pks_packer;

        oracle_protoboard(const size_t n);

        void generate_r1cs_constraints();

        void generate_r1cs_witness();
    };

}
#endif //AD_SNARK_ORACLE_PROTOBOARD_HPP
