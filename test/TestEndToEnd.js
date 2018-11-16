const { fromProjectRoot, flatten_vk, flatten_proof } = require('./utils.js');
const assert = require('assert').strict;
const { spawnSync } = require('child_process');

const TestContract = artifacts.require('TestContract');



contract('Oracle', () => { it("works", async () => {



console.log('1. The Oracle chooses the circuit size N and performs trusted setup');
const N = 1;
const generatorProc = spawnSync(fromProjectRoot('bin/generator'), [N]);
generatorProc.status === 0
    ? console.log(generatorProc.stdout.toString())
    : console.log("FAILURE:\n" + generatorProc.stderr.toString());
assert.equal(generatorProc.status, 0);



console.log('2. The Oracle uses the generated verifying key to deploy the contract');
const vk = require('../keys/ethsnarks/vk.json');
const contract = await TestContract.new(...flatten_vk(vk));



console.log('3. A data provider generates a key pair and sends the public key to the Oracle');
const keypairProc = spawnSync('python3', [fromProjectRoot('src/eddsa/keypair.py')]);
console.log('keypair = ' + keypairProc.stdout.toString());
if (keypairProc.status !== 0) {
    console.log("keypair.py:\n" + keypairProc.stderr.toString());
}
assert.equal(keypairProc.status, 0, "key pair generation FAILED");
const keypair = JSON.parse(keypairProc.stdout.toString());



console.log('4. The oracle submits the public key to the contract');
await contract.setPublicKey(keypair.public_key[0], keypair.public_key[1]);



console.log('5. The data provider generates a new value, signs it, and sends the value together with the signature to the oracle');
const value = 123;
const signProc = spawnSync('python3', [fromProjectRoot('src/eddsa/sign.py'), value, keypair.secret_key]);
console.log('signature = ' + signProc.stdout.toString());
if (signProc.status !== 0) {
    console.log("sign.py:\n" + signProc.stderr.toString());
}
assert.equal(signProc.status, 0, "signature generation FAILED");
const signature = JSON.parse(signProc.stdout.toString());



console.log('6. The oracle converts the signature to the libsnark format and feeds it to the prover');
const convertProc = spawnSync('python3', [fromProjectRoot('src/eddsa/convert.py'),
    value, signature.R[0], signature.R[1], signature.S, keypair.public_key[0], keypair.public_key[1]]);
if (convertProc.status !== 0) {
    console.log("convert.py:\n" + convertProc.stderr.toString());
}
assert.equal(convertProc.status, 0, "signature conversion FAILED");



console.log('7. The prover generates the proof');
const proverProc = spawnSync(fromProjectRoot('bin/prover'), [N]);
proverProc.status === 0 || console.log("prover failed:\n" + proverProc.stderr.toString());
assert.equal(proverProc.status, 0);



console.log('8. The oracle submits the new median and the proof to the contract');
const proof = require('../keys/ethsnarks/proof.json');
await contract.UpdateMedian(value, flatten_proof(proof));



console.log('9. The contract verifies the proof and updates the median');
const median = await contract.median();
assert.strictEqual(median.toNumber(), value);

})});