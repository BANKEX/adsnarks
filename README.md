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