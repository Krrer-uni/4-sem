import json
from base64 import b64encode
from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
plaintext = bytearray(128)
# plaintext=plaintext.zfill(128).encode('utf-8')
key = b'Wojciech'
key = bytearray(32 - len(key)) + key
# key = get_random_bytes(32)
# key=key.zfill(32).encode('utf-8')
print(key)

cipher = ChaCha20.new(key=key, nonce= bytearray(12))
ciphertext = cipher.encrypt(plaintext)
print(ciphertext)

with open("output.txt", 'wb+') as file:
    file.write(ciphertext)