import argparse, os.path

from generate import toBinaryString, verify


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Converts the signature to the libsnark format")
    parser.add_argument("value", type=int)
    parser.add_argument("R", help="point part of the signature", type=int, nargs=2)
    parser.add_argument("S", help="scalar part of the signature", type=int)
    parser.add_argument("pk", help="public key", type=int, nargs=2)
    args = parser.parse_args()
    with open(os.path.join(os.path.dirname(__file__), '../../keys/signature'), 'w') as f:
        print(toBinaryString(args.value), file = f)
        print(toBinaryString(args.pk[0]), file = f)
        print(toBinaryString(args.pk[1]), file = f)
        print(toBinaryString(args.R[0]), file = f)
        print(toBinaryString(args.R[1]), file = f)
        print(toBinaryString(args.S)[::-1], file = f)