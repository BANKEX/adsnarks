const assert = require('assert').strict;
const { python3 } = require('./utils.js');



const keypairProc = python3('src/eddsa/keypair.py');
console.log('keypair = ' + keypairProc.stdout.toString());
if (keypairProc.status !== 0) {
    console.log("keypair.py:\n" + keypairProc.stderr.toString());
}
assert.equal(keypairProc.status, 0, "key pair generation FAILED");
const keypair = JSON.parse(keypairProc.stdout.toString());



const value = 123;
const signProc = python3('src/eddsa/sign.py', value, keypair.k);
console.log('signature = ' + signProc.stdout.toString());
if (signProc.status !== 0) {
    console.log("sign.py:\n" + signProc.stderr.toString());
}
assert.equal(signProc.status, 0, "signature generation FAILED");
const signature = JSON.parse(signProc.stdout.toString());



const verifyProc = python3('src/eddsa/verify.py', value, signature.R[0], signature.R[1], signature.S, keypair.A[0], keypair.A[1]);
const result = verifyProc.stdout.toString();
console.log('valid = ' + result);
if (verifyProc.status !== 0) {
    console.log("verify.py:\n" + verifyProc.stderr.toString());
}
assert.equal(verifyProc.status, 0, "signature verification FAILED");
assert.equal(result, 'True\n');
