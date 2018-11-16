import argparse, os.path

from generate import represent


int16 = lambda x: int(x, 16)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Converts the signature to the libsnark format")
    parser.add_argument("value", type=int)
    parser.add_argument("R", help="point part of the signature", type=int16, nargs=2)
    parser.add_argument("S", help="scalar part of the signature", type=int16)
    parser.add_argument("pk", help="public key", type=int16, nargs=2)
    args = parser.parse_args()
    with open(os.path.join(os.path.dirname(__file__), '../../keys/signature'), 'w') as f:
        for s in represent(args.value, args.pk, args.R, args.S):
            print(s, file = f)