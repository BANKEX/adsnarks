```git submodule update --init --recursive```

`python3 src/eddsa/generate.py <N>` populates `keys/signature` with N random signatures to be used for testing.
More precisely, it:
* generates N random positive integers `v`
* for each integer `v` produces a signature `(R, S)` using a random key pair `(sk, pk)`
* each signature is represented as 6 binary strings in the following order:
1. the integer signed `v` (in little-endian bit order)
2. x component of the public key `pk.x` (in little-endian bit order)  
3. y component of the public key `pk.y` (in little-endian bit order)  
4. x component of the point part of the signature `R.x` (in little-endian bit order)
5. y component of the point part of the signature `R.y` (in little-endian bit order)
6. scalar part of the signature `S` (in BIG-endian bit order, don't ask me why)

`src/generator.cpp`
* produces proving/verifying keys for the circuit for `N = 3` signatures [TODO] 
* dumps the proving key to `keys/libsnark/pk` in libsnark format. It is used by libsnark prover `src/proover.cpp`
* dumps the proving key to `keys/ethsnarks/vk.json` in ethsnarks format. It is used
    * to deploy the verifier contract, see `migrations/2_deploy_contracts.js`
    * to test the verifier contract, see `tests/TestVerifier.js`
    * to generate Solidity code using `ethsnarks.cli.vk2sol`  
* dumps the verifying key to `keys/libsnark/pk`. It is used by libsnark verifier `src/verifier.cpp`