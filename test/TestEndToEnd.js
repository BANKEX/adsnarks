const utils = require('./utils.js');
const assert = require('assert').strict;
const { spawnSync } = require('child_process');
const path = require("path");

const TestContract = artifacts.require('TestContract');

// converts the path relative to the directory containing the current module to the absolute path
const absolutePath = (relativePath) => {
    return path.resolve(__dirname, relativePath);
};


console.log('1. The Oracle chooses the circuit size N and performs trusted setup');
const N = 1;
const generatorProc = spawnSync(absolutePath('../bin/generator'), [N]);
generatorProc.status === 0
    ? console.log(generatorProc.stdout.toString())
    : console.log("FAILURE:\n" + generatorProc.stderr.toString());
assert.equal(generatorProc.status, 0);


console.log('1. A data provider generates a key pair and sends the public key to the Oracle');
const keypairProc = spawnSync('python3', [absolutePath('../src/eddsa/keypair.py')]);
keypairProc.status === 0
    ? console.log(keypairProc.stdout.toString())
    : console.log("FAILURE:\n" + keypairProc.stderr.toString());
assert.equal(keypairProc.status, 0);
const keypair = JSON.parse(keypairProc.stdout.toString());
// console.log(keypair);

//TODO: console.log('2. The oracle submits the public key to the contract');

console.log('3. The data provider generates a new value, signs it, and sends the value together with the signature to the oracle');
const value = 123;
const signProc = spawnSync('python3', [absolutePath('../src/eddsa/sign.py'), value, keypair.secret_key]);
signProc.status === 0
    ? console.log(signProc.stdout.toString())
    : console.log("FAILURE:\n" + signProc.stderr.toString());
assert.equal(signProc.status, 0);
const signature = JSON.parse(signProc.stdout.toString());
console.log(signature);

console.log('4. The oracle converts the signature to the libsnark format and feeds it to the prover');
const convertProc = spawnSync('python3',
    [absolutePath('../src/eddsa/convert.py'),
        value, signature.R[0], signature.R[1], signature.S, keypair.public_key[0], keypair.public_key[1]],
    {cwd: '..'});
console.log(convertProc.stdout.toString());
convertProc.status === 0 || console.log("convert.py failed:\n" + convertProc.stderr.toString());
assert.equal(convertProc.status, 0);

console.log('5. The prover generates the proof');
const proverProc = spawnSync(absolutePath('../bin/prover'), [N]);
proverProc.status === 0 || console.log("prover failed:\n" + proverProc.stderr.toString());
assert.equal(proverProc.status, 0);

contract("TestContract", () => {

    describe("verifies a valid proof", () => {

        it("", async () => {

            const testContract = await TestContract.deployed();

            const vk = require('../keys/ethsnarks/vk.json');
            const [vk_flat, vk_flat_IC] = utils.flatten_vk(vk);

            const proof = require('../keys/ethsnarks/proof.json');

            const args = [
                vk_flat,                    // (alpha, beta, gamma, delta)
                vk_flat_IC,                 // gammaABC[]
                utils.flatten_proof(proof), // A B C
                proof.input
            ];

            console.log(args);
            const result = await testContract.TestVerify(...args);
            assert.strictEqual(result, true);
        });
    });
});