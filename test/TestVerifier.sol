pragma solidity ^0.4.24;

import "truffle/Assert.sol";
import "../depends/ethsnarks/contracts/Verifier.sol";

contract TestVerifier
{
	function testVerifyProof () public
	{
		Verifier.ProofWithInput memory pwi;
		_getStaticProof(pwi);

		Verifier.VerifyingKey memory vk;
		_getVerifyingKey(vk);

		Assert.isTrue(Verifier.Verify(vk, pwi), "Verification failed");
	}

	function _getVerifyingKey (Verifier.VerifyingKey memory vk)
	internal pure
	{
		vk.beta = Pairing.G2Point([0xca4b719548f29284b3aa6e5c8cd3d8e17c6592410bbe10aa7d3b4c2db01ae45, 0x2ab57c4311803d13c0cf3672215f6650a31d94c6743596ca960132a1d8efce5f], [0x21360e2607df7f1534f73d6a0fcccff45109d0c619348d4a0ced0cf3e139aefc, 0x2a47fb500341afeae7ab3d003f4fab53e2cabe89c4ce66aed8acba454e6e09f8]);
		vk.gamma = Pairing.G2Point([0x2a76a71ba946046351872fcbe9b327df8d7e1445f1bb233194048bcb0da0818c, 0x3e3e3fd14d14261875d07a2a028e4dbd6214a805eabecb3825b08f33b611c74], [0xb3505f2b569770350c4ce26193a9de9f193b5f54ceae36bdeec1b13f2ad1aa5, 0xe79c032a2ab44a76837c84e1a2e2b36f75523852e7d8e37022b60c098960fc]);
		vk.delta = Pairing.G2Point([0x14c29fb9ae0ae00a2eaeebe85760330cbda4022a3eadfb349c206d0f99b85673, 0x176aea4ead1f81631d51a53b0c381a05914b4b2e806318450fd5f3161860c843], [0x13ef61ee7fd1c98e21959d73053f7ffa7d2569d614a1c4240a4ba9d7f0e9d3c9, 0x2e6a763c30cbb192aabe8292b13ae4dccb21654047a4989dedfdc7058ccb4019]);
		vk.alpha = Pairing.G1Point(0xdecf66e670862851a94f9e7919bdead2b744ca2cfa93df1c27576fd90f5d23c, 0x1b480b22b5a19d0222f718c4651bff4cb5d710fa376d6c0a7ea0c65a97a0de5d);
		vk.gammaABC = new Pairing.G1Point[](9);
		vk.gammaABC[0] = Pairing.G1Point(0x298518f200a92a0bed3aec46817eedec46485c71a65e6f24cc5369884a7c462a, 0x1670dd12c243149db2579e19e7f746f3ecd8a5841d2895415deca4ac79309842);
		vk.gammaABC[1] = Pairing.G1Point(0x15dce148bd125e29c2a32a67df2129f79bd61048324bb17fcc1e7a279c781d47, 0x234ce41125bdd490a9c0b616dd11dccc0d42b023d75fe5cadb9dac72eb550115);
		vk.gammaABC[2] = Pairing.G1Point(0x1e86c3ddf91f03d68f0dca313750e47b92c77f1bda2c00ae6aed4a0249181737, 0xf08df1d5427b7866b2c964ca765bfb0fdda7bcc2be707ff62c6ae8c36461dc6);
		vk.gammaABC[3] = Pairing.G1Point(0x7edda4b56c5504b1b6712a2616d333ca249b1d29b783d8844ffe3d0b5b887cf, 0x9ef74170464f18d16684d4950beedffa9107a63017936c1abb37b017799211);
		vk.gammaABC[4] = Pairing.G1Point(0x1f28c38275a2b6cdb4ab38ea2c12079eea7841b464c27faf10eff62f847d23bb, 0x14692b0e9233ce8873e197671b0d565d1b08235ca8f4d1c70f91866080c20d3a);
		vk.gammaABC[5] = Pairing.G1Point(0xdead21f594bedcd51697a7f31d3b3aa69a0de8865735bced2c08dc31fe80288, 0x127e0bef23d74c7928977a6e990ce736b4cb282a074c3154af9ac8d737359233);
		vk.gammaABC[6] = Pairing.G1Point(0x11f57530eadb5c1023c0ad224d9afa856d422e1d6fec27afb51894b38869c6e2, 0x1002062a0b7422438a020fc7d24cb88a4207601eddcc0ffa5668896abd1ba64f);
		vk.gammaABC[7] = Pairing.G1Point(0x13d4cfb7d1f39939915cbaf5ed4caa870c7b3eff53eebd417116da90ee498d83, 0x2e93eec50029aae8b638f4a1a878e499c91b0e92b76b8ecc011a40b4909a3425);
		vk.gammaABC[8] = Pairing.G1Point(0x1ae8683dd9d6c09ef6b5e79bfd222bfe391af06575fa6e8c9cbce78618d804f6, 0x2f3fe7dfb96b77ac1e8fb635f689e03fc9c32eae21b2d5248bb67b5c52f4af1b);
	}

	function _getStaticProof (Verifier.ProofWithInput memory output)
	internal pure
	{
		Verifier.Proof memory proof = output.proof;
		proof.B = Pairing.G2Point([0xef0665723394f73aa7672e5620e29c9383da0dd5a76dc11fa7ab514b316afbe, 0x1cc1df3f7b644fd3d38fee79691612aa7fcb810c46b23150677b124bf4c139fc], [0x1f1bd6f5d456b6543c8f4bf8de9db5f4736e8f035c348ae20cd8dc0fd33266a7, 0x84264235cbf5e4955a209ed6846816b05841040140f2398ff70b8203f67f5f5]);
		proof.A = Pairing.G1Point(0x230f2c89a3af037bbf56a90529e9b49c960fb71096e30d7df8092cdcdde330cc, 0x946037eec5a9fca3dcad795a3e30908e5558928953c8175a7be98cf30ac235e);
		proof.C = Pairing.G1Point(0x18ee3e7f5dc276ff8f7e79097cf7d2f94e7537d44737f6a78614b3781db917d8, 0x1f62dcc1a4b37a4abc5fefc2807ffcc7b21c6c36d6d6822bad41dc60c7101700);
		output.input = new uint256[](8);
		output.input[0] = 0x159;
		output.input[1] = 0x1176dc00d8172e1212f6a78e45c4071c1e1242680473b7a6fc6214f6fbbab840;
		output.input[2] = 0x1cb4095259cac185f5b9a0be5f8174fea601ca96fc4f43f8ac7d98c967673b80;
		output.input[3] = 0xbb79a68d4a7c0a5f265cbbe642cfb5251621a4287290a1d1fe9c10933293fca;
		output.input[4] = 0xad880c98d8d1da7760c3e4a5f8f1ec105289d01f8a9bc04f6ef9145815b1a55;
		output.input[5] = 0xd12c302a2d62f32e6b0a06cdc75ba8af9c0f82cd4fa5cd060f5e8706ea6524c;
		output.input[6] = 0x1828457a3bd727ea5a0a4e27369d7fdd559537d0d3accd32552f479a40ee86ae;
		output.input[7] = 0x5c7b;
	}
}