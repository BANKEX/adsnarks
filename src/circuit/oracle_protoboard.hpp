//
// Created by swasilyev on 11/6/18.
//

#ifndef AD_SNARK_ORACLE_PROTOBOARD_HPP
#define AD_SNARK_ORACLE_PROTOBOARD_HPP

#include <ethsnarks.hpp>
#include "oracle_gadget.hpp"

namespace ethsnarks {

    class oracle_protoboard : public ProtoboardT {
    public:
        const size_t n;
        jubjub::EdwardsPoint B;
        
        VariableT median;

        std::vector<jubjub::VariablePointT> As;
        std::vector<jubjub::VariablePointT> Rs;
        std::vector<VariableArrayT> ss;
        std::vector<VariableArrayT> ms;

        std::shared_ptr<oracle_gadget> _oracle_gadget;

        oracle_protoboard(const size_t n);

        void generate_r1cs_constraints();

        void generate_r1cs_witness();
    };

}
#endif //AD_SNARK_ORACLE_PROTOBOARD_HPP
