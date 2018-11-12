const utils = require('./utils.js');

const TestContract = artifacts.require('TestContract');

let list_flatten = (l) => {
    return [].concat.apply([], l);
};


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
