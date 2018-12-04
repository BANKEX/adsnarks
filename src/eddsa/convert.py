import argparse, os.path

from generate import represent



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Converts the signature to the libsnark format")
    parser.add_argument("value", type=int)
    parser.add_argument("R", help="point part of the signature", type=int, nargs=2)
    parser.add_argument("S", help="scalar part of the signature", type=int)
    parser.add_argument("A", help="public key", type=int, nargs=2)
    args = parser.parse_args()
    with open(os.path.join(os.path.dirname(__file__), '../../keys/signature'), 'w') as f:
        for s in represent(args.value, args.A, args.R, args.S):
            print(s, file = f)