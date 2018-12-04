//
// Created by swasilyev on 11/6/18.
//

#ifndef AD_SNARK_ORACLE_GADGET_HPP
#define AD_SNARK_ORACLE_GADGET_HPP


#include <ethsnarks.hpp>
#include <jubjub/eddsa.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include "median_gadget.hpp"

namespace ethsnarks {

    class oracle_gadget : public GadgetT {

    private:
        const jubjub::Params params;

        std::vector<jubjub::EdDSA_Verify> signature_verifiers;
        std::vector<VariableT> packed_messages;
        std::vector<libsnark::packing_gadget<FieldT>> packers;
        std::shared_ptr<median_gadget> _median_gadget;

    public:
        const size_t n;

        VariableT median;

        std::vector<jubjub::VariablePointT> As;
        std::vector<jubjub::VariablePointT> Rs;
        std::vector<VariableArrayT> ss;
        std::vector<VariableArrayT> ms;

        oracle_gadget(ProtoboardT &pb,
                      const size_t n,
                      const VariableT &median,
                      const jubjub::EdwardsPoint &base,
                      const std::vector<jubjub::VariablePointT> &As,
                      const std::vector<jubjub::VariablePointT> &Rs,
                      const std::vector<VariableArrayT> &ss,
                      const std::vector<VariableArrayT> &ms
        );

        void generate_r1cs_constraints();

        void generate_r1cs_witness();
    };
}

#endif //AD_SNARK_ORACLE_GADGET_HPP
