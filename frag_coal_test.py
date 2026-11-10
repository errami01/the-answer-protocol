import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 4242))

# 1. Receive the initial greeting
print("Server:", s.recv(1024).decode())

# 2. Send only HALF the command (NO newline!)
print("Sending first half...")
s.send(b"connect ")
time.sleep(2) # Wait to ensure the server hasn't processed it yet

# 3. Send the rest of the command + newline
print("Sending second half...")
s.send(b"bob\n")

# 4. Check for response
print("Server response:", s.recv(1024).decode())
s.close()