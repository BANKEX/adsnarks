const utils = require('../test/utils');

const Verifier = artifacts.require('depends/ethsnarks/contracts/Verifier');
const TestContract = artifacts.require('TestContract');


const deploy = async (deployer, network) => {
	await deployer.deploy(Verifier);
	await deployer.link(Verifier, TestContract);

    const vk = require('../keys/ethsnarks/vk.json');

    const [vk_flat, vk_flat_IC] = utils.flatten_vk(vk);
	await deployer.deploy(TestContract, vk_flat, vk_flat_IC);
};


module.exports = function(deployer, network) {
	deployer.then(async () => {
		await deploy(deployer, network);
	});
};
