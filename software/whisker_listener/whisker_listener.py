import serial
from datetime import datetime
import argparse


def read_serial_port(port, baud_rate):
    try:
        ser = serial.Serial(port, baud_rate)
        print(f"Reading from serial port {port} at {baud_rate} baud rate...\n")

        data_labels = ["AX", "AY", "BX", "BY", "CX", "CY"]#, "AZ", "BX", "BY", "BZ", "CX", "CY", "CZ"]#,"X","Y","Z"]
        seen_labels = set()

        timestamp = datetime.now().strftime("%Y-%m-%d_%H_%M_%S")
        with open(f"whisker_{timestamp}.csv", "a") as datafile:
            while True:
                timestamp = datetime.now().strftime("%Y-%m-%d_%H:%M:%S.%f")
                line = ser.readline().decode("utf-8").strip()

                if not seen_labels and data_labels[0] not in line:
                    continue

                for label in data_labels:
                    if label in line:
                        if not seen_labels:
                            datafile.write(f"{timestamp}")

                        if label in seen_labels:
                            datafile.write(f"\n")
                            seen_labels.clear()

                            break

                        line = line.split(" ")[-1]
                        datafile.write(f",{line}")
                        seen_labels.add(label)

                        break

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
