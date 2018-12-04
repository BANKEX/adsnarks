//
// Created by swasilyev on 11/6/18.
//

#include "oracle_gadget.hpp"

namespace ethsnarks {

    oracle_gadget::oracle_gadget(ProtoboardT &pb,
                                 const size_t n,
                                 const VariableT &median,
                                 const jubjub::EdwardsPoint &base,
                                 const std::vector<jubjub::VariablePointT> &As,
                                 const std::vector<jubjub::VariablePointT> &Rs,
                                 const std::vector<VariableArrayT> &ss,
                                 const std::vector<VariableArrayT> &ms) :
            gadget<FieldT>(pb, "oracle_gadget"),
            n(n),
            median(median),
            As(As),
            Rs(Rs),
            ss(ss),
            ms(ms) {
        assert(n > 0);
        assert(n % 2 == 1);
        assert(As.size() == n);
        assert(Rs.size() == n);
        assert(ss.size() == n);
        assert(ms.size() == n);

        for (size_t i = 0; i < n; i++) {
            signature_verifiers.emplace_back(
                    jubjub::EdDSA_Verify(pb, params, base, As[i], Rs[i], ss[i], ms[i], FMT(this->annotation_prefix, ".signature_verifier_%zu", i)));
        }

        for (size_t i = 0; i < n; i++) {
            packed_messages.emplace_back(VariableT()); //TODO: could be better
            packed_messages[i].allocate(pb, "packed_messages_" + i);
            packers.emplace_back(libsnark::packing_gadget<FieldT>(pb, ms[i], packed_messages[i], "packer_" + i));
        }

        _median_gadget.reset(new median_gadget(pb, n, median, packed_messages, FMT(this->annotation_prefix, ".median_gadget")));
    }

    void oracle_gadget::generate_r1cs_constraints() {
        for (size_t i = 0; i < n; i++) {
            signature_verifiers[i].generate_r1cs_constraints();
            packers[i].generate_r1cs_constraints(false); //TODO: bitness
        }

        _median_gadget->generate_r1cs_constraints();
    }

    void oracle_gadget::generate_r1cs_witness() {
        for (size_t i = 0; i < n; i++) {
            signature_verifiers[i].generate_r1cs_witness();
            packers[i].generate_r1cs_witness_from_bits();
        }

        _median_gadget->generate_r1cs_witness(0); //TODO!!!
    }
}
