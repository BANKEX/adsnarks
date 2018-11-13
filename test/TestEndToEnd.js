const utils = require('./utils.js');
const assert = require('assert').strict;
const { spawnSync } = require('child_process');

const TestContract = artifacts.require('TestContract');


console.log('1. The Oracle chooses the circuit size N and performs trusted setup');
const N = 1;
const generatorProc = spawnSync('../bin/generator', [N]);
assert.equal(generatorProc.status, 0);


console.log('1. A data provider generates a key pair and sends the public key to the Oracle');
const keypairProc = spawnSync('python3', ['../src/eddsa/keypair.py']);
const keypair = JSON.parse(keypairProc.stdout.toString());
console.log(keypair);

//TODO: console.log('2. The oracle submits the public key to the contract');

console.log('3. The data provider generates a new value, signs it, and sends the value together with the signature to the oracle');
const value = 123;
const signProc = spawnSync('python3', ['../src/eddsa/sign.py', value, keypair.secret_key]);
const signature = JSON.parse(signProc.stdout.toString());
console.log(signature);

console.log('4. The oracle converts the signature to the libsnark format and feeds it to the prover');
const convertProc = spawnSync('python3',
    ['src/eddsa/convert.py', value, signature.R[0], signature.R[1], signature.S, keypair.public_key[0], keypair.public_key[1]],
    {cwd: '..'});
assert.equal(convertProc.status, 0);

console.log('5. The prover generates the proof');
const proverProc = spawnSync('../bin/prover', [N]);
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