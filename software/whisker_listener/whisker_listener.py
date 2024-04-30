import serial
from datetime import datetime
import argparse


def read_serial_port(port, baud_rate):
    try:
        ser = serial.Serial(port, baud_rate)
        print(f"Reading from serial port {port} at {baud_rate} baud rate...\n")

        x_val = None
        y_val = None
        z_val = None

        timestamp = datetime.now().strftime("%Y-%m-%d_%H_%M_%S")
        with open(f"whisker_{timestamp}.csv", "a") as datafile:
            datafile.write("timestamp,x,y,z\n")
            while True:
                timestamp = datetime.now().strftime("%Y-%m-%d_%H:%M:%S.%f")
                line = ser.readline().decode("utf-8").strip()

                if "X" in line:
                    x_val = line.split(" ")[-1]

                if x_val is None: continue

                if "Y" in line:
                    y_val = line.split(" ")[-1]

                if y_val is None: continue

                if "Z" in line:
                    z_val = line.split(" ")[-1]

                if z_val is None: continue
                
                datafile.write(f"{timestamp},{x_val},{y_val},{z_val}\n")

    except serial.SerialException as e:
        print(f"Error: {e}")
        ser = serial.Serial(None)

    finally:
        if ser.is_open:
            ser.close()
            print("Serial port closed.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Read data from a serial port.")
    parser.add_argument(
        "serial_port", type=str, help="Serial port name (e.g., COM3 or /dev/ttyACM0)"
    )
    parser.add_argument(
        "-b",
        dest="baud_rate",
        type=int,
        default=115200,
        help="Baud rate (default is 115200)",
    )

    args = parser.parse_args()

    read_serial_port(args.serial_port, args.baud_rate)
