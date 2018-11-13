import argparse, json

from generate import keypair


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generates a new baby_jubjub eddsa key pair")
    sk, pk = keypair()
    print(json.dumps({"secret_key": sk, "public_key": pk}))
