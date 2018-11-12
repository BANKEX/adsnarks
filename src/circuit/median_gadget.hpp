//
// Created by swasilyev on 11/12/18.
//

#ifndef AD_SNARK_MEDIAN_GADGET_HPP
#define AD_SNARK_MEDIAN_GADGET_HPP

#include <ethsnarks.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>

namespace ethsnarks {

    class median_gadget : public GadgetT {

    private:

        VariableArrayT less_mask;
        VariableArrayT less_or_eq_mask;

        std::vector<libsnark::comparison_gadget<FieldT>> comparators;

    public:

        const size_t n;

        VariableT median;
        std::vector<VariableT> values;

        median_gadget(
                ProtoboardT &pb,
                const size_t n,
                const VariableT &median,
                const std::vector<VariableT> &values,
                const std::string &annotation_prefix);

        void generate_r1cs_constraints();

        void generate_r1cs_witness(const size_t median_index);
    };
}

#endif //AD_SNARK_MEDIAN_GADGET_HPP
