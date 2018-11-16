pragma solidity ^0.4.24;

import "../depends/ethsnarks/contracts/Verifier.sol";


// Please note, it saves a lot of gas to use the `vk2sol`
// utility to generate Solidity code, hard-coding the
// verifying key avoids the cost of loading from storage.

contract TestContract
{
    uint256[14] m_vk;
    uint256[] m_gammaABC;

    uint256 public pk_x;
    uint256 public pk_y;
    uint256 public median;

    constructor(uint256[14] in_vk, uint256[] in_gammaABC)
        public
    {
        m_vk = in_vk;
        m_gammaABC = in_gammaABC;
    }

    function TestVerify (uint256[14] in_vk, uint256[] vk_gammaABC, uint256[8] in_proof, uint256[] proof_inputs)
        public view returns (bool)
    {
        return Verifier.Verify(in_vk, vk_gammaABC, in_proof, proof_inputs);
    }


    function GetVerifyingKey ()
        public view returns (uint256[14] out_vk, uint256[] out_gammaABC)
    {
        return (m_vk, m_gammaABC);
    }

    // TODO: onlyOracle?
    function setPublicKey(uint256 _pk_x, uint256 _pk_y) public {
        pk_x = _pk_x;
        pk_y = _pk_y;
    }

    // TODO: onlyOracle?
    function UpdateMedian(uint256 _median, uint256[8] in_proof) public {
        uint256[] memory proof_inputs = new uint256[](4);
        proof_inputs[0] = _median;
        proof_inputs[1] = pk_x << 3 >> 3;
        proof_inputs[2] = pk_x >> 253 | pk_y << 6 >> 3;
        proof_inputs[3] = pk_y >> 250;
        require(Verifier.Verify(m_vk, m_gammaABC, in_proof, proof_inputs));
        median = _median;
    }
}
