const assert = require('assert').strict;
const { spawnSync } = require('child_process');
const { fromProjectRoot } = require('./utils.js');



const keypairProc = spawnSync('python3', [fromProjectRoot('src/eddsa/keypair.py')]);
console.log('keypair = ' + keypairProc.stdout.toString());
if (keypairProc.status !== 0) {
    console.log("keypair.py:\n" + keypairProc.stderr.toString());
}
assert.equal(keypairProc.status, 0, "key pair generation FAILED");
const keypair = JSON.parse(keypairProc.stdout.toString());



const value = 123;
const signProc = spawnSync('python3', [fromProjectRoot('src/eddsa/sign.py'), value, keypair.secret_key]);
console.log('signature = ' + signProc.stdout.toString());
if (signProc.status !== 0) {
    console.log("sign.py:\n" + signProc.stderr.toString());
}
assert.equal(signProc.status, 0, "signature generation FAILED");
const signature = JSON.parse(signProc.stdout.toString());



const verifyProc = spawnSync('python3', [fromProjectRoot('src/eddsa/verify.py'), value, signature.R[0], signature.R[1], signature.S, keypair.public_key[0], keypair.public_key[1]]);
const result = verifyProc.stdout.toString();
console.log('valid = ' + result);
if (verifyProc.status !== 0) {
    console.log("verify.py:\n" + verifyProc.stderr.toString());
}
assert.equal(verifyProc.status, 0, "signature verification FAILED");
assert.equal(result, 'True\n');
