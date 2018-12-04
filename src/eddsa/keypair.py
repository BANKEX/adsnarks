import argparse, json

from generate import keypair


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generates a new baby_jubjub eddsa key pair")
    k, A = keypair()
    print(json.dumps({"k": str(k), "A": [str(A.x.n), str(A.y.n)]}))
