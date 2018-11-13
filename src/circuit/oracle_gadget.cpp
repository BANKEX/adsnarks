//
// Created by swasilyev on 11/6/18.
//

#include "oracle_gadget.hpp"

namespace ethsnarks {

    oracle_gadget::oracle_gadget(ProtoboardT &pb,
                                 const size_t n,
                                 const VariableT &median,
                                 const std::vector<VariableArrayT> &pk_x_bins,
                                 const std::vector<VariableArrayT> &pk_y_bins,
                                 const std::vector<VariableArrayT> &r_x_bins,
                                 const std::vector<VariableArrayT> &r_y_bins,
                                 const std::vector<VariableArrayT> &ss,
                                 const std::vector<VariableArrayT> &ms) :
            gadget<FieldT>(pb, "oracle_gadget"),
            n(n),
            median(median),
            pk_x_bins(pk_x_bins),
            pk_y_bins(pk_y_bins),
            r_x_bins(r_x_bins),
            r_y_bins(r_y_bins),
            ss(ss),
            ms(ms) {
        assert(n > 0);
        assert(n % 2 == 1);
        assert(pk_x_bins.size() == n);
        assert(pk_y_bins.size() == n);
        assert(r_x_bins.size() == n);
        assert(r_y_bins.size() == n);
        assert(ss.size() == n);
        assert(ms.size() == n);

        a.allocate(pb, "a");
        d.allocate(pb, "d");
        base_x.allocate(pb, "base x");
        base_y.allocate(pb, "base y");
        
        for (size_t i = 0; i < n; i++) {
            signature_verifiers.emplace_back(
                    jubjub::eddsa<HashT>(pb, params, a, d, pk_x_bins[i], pk_y_bins[i], base_x, base_y, r_x_bins[i], r_y_bins[i],ms[i], ss[i]));
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
        // TODO: reuse params
        this->pb.val(a) = FieldT("168700");
        this->pb.val(d) = FieldT("168696");
        this->pb.val(base_x) = FieldT("17777552123799933955779906779655732241715742912184938656739573121738514868268");
        this->pb.val(base_y) = FieldT("2626589144620713026669568689430873010625803728049924121243784502389097019475");

        for (size_t i = 0; i < n; i++) {
            signature_verifiers[i].generate_r1cs_witness();
            packers[i].generate_r1cs_witness_from_bits();
        }

        _median_gadget->generate_r1cs_witness(0); //TODO!!!
    }
}
