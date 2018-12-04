import argparse, json

from generate import sign


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Signs the value with the secret key")
    parser.add_argument("value", type=int, help="should be a positive integer")
    parser.add_argument("k", type=int, help="secret key")
    args = parser.parse_args()
    R, S = sign(args.value, args.k)
    print(json.dumps({"R": [str(R.x.n), str(R.y.n)], "S": str(S)}))