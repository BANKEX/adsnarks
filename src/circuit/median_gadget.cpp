//
// Created by swasilyev on 11/12/18.
//

#include "median_gadget.hpp"

namespace ethsnarks {

    median_gadget::median_gadget(
            ProtoboardT &pb,
            const size_t n,
            const VariableT &median,
            const std::vector<VariableT> &values,
            const std::string &annotation_prefix)
            : gadget<FieldT>(pb, annotation_prefix),
              n(n),
              median(median),
              values(values) {
        assert(n > 0);
        assert(n % 2 == 1);
        assert(values.size() == n);

        less_mask.allocate(pb, n, FMT(this->annotation_prefix, ".less_mask"));
        less_or_eq_mask.allocate(pb, n, FMT(this->annotation_prefix, "less_or_eq_mask"));
        for (size_t i = 0; i < n; i++) {
            comparators.emplace_back(
                    libsnark::comparison_gadget<FieldT>(pb, FieldT::capacity(), median, values[i], less_mask[i], less_or_eq_mask[i],
                                                        FMT(this->annotation_prefix, ".comparator_%zu", i)));
        }
    }

    void median_gadget::generate_r1cs_constraints() {
        libsnark::linear_combination<FieldT> less_or_eq_count = libsnark::pb_sum<FieldT>(less_or_eq_mask);
        libsnark::linear_combination<FieldT> more_or_eq_count = n - libsnark::pb_sum<FieldT>(less_mask);
        this->pb.add_r1cs_constraint(ConstraintT(1, less_or_eq_count, more_or_eq_count),
                                     FMT(this->annotation_prefix, " less_or_eq_count == more_or_eq_count"));
        // It implies from the constraint above that the median belongs to the values array.
    }

    void median_gadget::generate_r1cs_witness(const size_t median_index) {
        this->pb.val(median) = this->pb.val(values[median_index]);

        for (size_t i = 0; i < n; i++) {
            comparators[i].generate_r1cs_witness();
            // TODO: IFDEBUG
            std::cout << "i = " << i
                      << ", m = " << this->pb.val(values[i])
                      << ", less = " << this->pb.val(less_mask[i])
                      << ", less_or_eq = " << this->pb.val(less_or_eq_mask[i])
                      << std::endl;
        }
    }
}