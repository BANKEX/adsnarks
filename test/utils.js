const {resolve} = require("path");
const {spawnSync} = require('child_process');

const flatten_list = (l) => {
    return [].concat.apply([], l);
};

exports.flatten_vk = (vk) => {
    return [
        flatten_list([
            vk.alpha[0], vk.alpha[1],
            flatten_list(vk.beta),
            flatten_list(vk.gamma),
            flatten_list(vk.delta),
        ]),
        flatten_list(vk.gammaABC)
    ];
};

exports.flatten_proof = (proof) => {
    return flatten_list([
        proof.A,
        flatten_list(proof.B),
        proof.C
    ]);
};

// converts the path relative to the project root to the absolute path
exports.fromProjectRoot = (relativePath) => {
    return resolve(__dirname, '..', relativePath);
};

const spawnOptions = {env: {PYTHONPATH: exports.fromProjectRoot('depends/ethsnarks')}};

exports.python3 = (script, ...args) => spawnSync('python3', [exports.fromProjectRoot(script), ...args], spawnOptions);
