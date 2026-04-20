import serial
import time
import numpy as np
from pathlib import Path

SERIAL_PORT = "/dev/ttyUSB0"
BAUD_RATE = 115200
TIMEOUT = 5
DATA_DIR = Path(__file__).parent / "data"

def connect(port=SERIAL_PORT, baud=BAUD_RATE):
    DATA_DIR.mkdir(exist_ok=True)
    ser = serial.Serial(port, baud, timeout=TIMEOUT)
    time.sleep(2)
    return ser

def request_capture(ser, mode="CAPTURE"):
    ser.write(f"{mode}\n".encode())
    
    lines = []
    collecting = False

    while True:
        line = ser.readline().decode().strip()
        if line == "BEGIN":
            collecting = True
            continue
        if line == "END":
            break
        if collecting and line:
            lines.append(line)

    return np.array([int(x) for x in lines], dtype=np.float32)

def save_sample(samples, label):
    timestamp = int(time.time())
    path = DATA_DIR / f"{label}_{timestamp}.csv"
    np.savetxt(path, samples, delimiter=",", fmt="%.2f")
    return path

def collect_dataset(ser, label, n=50, mode="CAPTURE"):
    print(f"Collecting {n} samples for label '{label}'...")
    for i in range(n):
        samples = request_capture(ser, mode)
        path = save_sample(samples, label)
        print(f"  [{i+1}/{n}] saved → {path.name}")
        time.sleep(0.1)
    print("Done.")

if __name__ == "__main__":
    ser = connect()
    label = input("Enter sample label (e.g. saltwater, lemon, tap): ").strip()
    n = int(input("How many samples to collect? "))
    mode = input("Mode — CAPTURE or SWEEP: ").strip().upper()
    collect_dataset(ser, label, n=n, mode=mode)
    ser.close()
