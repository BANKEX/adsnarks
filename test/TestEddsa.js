const assert = require('assert').strict;
const { spawnSync } = require('child_process');


const keypairProc = spawnSync('python3', ['../src/eddsa/keypair.py']);
const keypair = JSON.parse(keypairProc.stdout.toString());
console.log(keypair);

const value = 123;
const signProc = spawnSync('python3', ['../src/eddsa/sign.py', value, keypair.secret_key]);
const signature = JSON.parse(signProc.stdout.toString());
console.log(signature);

const verifyProc = spawnSync('python3', ['../src/eddsa/verify.py', value, signature.R[0], signature.R[1], signature.S, keypair.public_key[0], keypair.public_key[1]]);
const result = verifyProc.stdout.toString();
console.log(result);

assert.equal(result, 'True\n');
