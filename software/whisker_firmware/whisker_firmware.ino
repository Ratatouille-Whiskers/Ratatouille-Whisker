#include <MLX90393.h>
#include <math.h>

#define DRDY_pin 21
#define SDA_pin 16
#define SCL_pin 17

MLX90393 mlx;
MLX90393::txyzRaw rawData;
MLX90393::txyz data;

volatile bool dataReady = false;
volatile bool procReady = false;

// To include Z-axis measurements use
// MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG
const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;

void mlxInterrupt()
{
    dataReady = true;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(10);
    }

    pinMode(DRDY_pin, INPUT_PULLDOWN);
    attachInterrupt(DRDY_pin, mlxInterrupt, RISING);

    Wire.setSDA(SDA_pin);
    Wire.setSCL(SCL_pin);
    Wire.setClock(400000);
    Wire.begin();

    byte status = mlx.begin(0x18, DRDY_pin, Wire);

    mlx.setGainSel(0);
    mlx.setOverSampling(0);
    mlx.setDigitalFiltering(0);
    mlx.setResolution(1, 1, 1);
    mlx.setTemperatureCompensation(0);

    mlx.startBurst(axisFlags);
}

void loop()
{
    if (dataReady)
    {
        dataReady = false;
        mlx.readMeasurement(axisFlags,rawData);
        data = mlx.convertRaw(rawData);
        procReady = true;
    }
}

void loop1()
{
    if (procReady)
    {
        procReady = false;

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">X: %f\r\n", data.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">Y: %f\r\n", data.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">Z: %f\r\n", data.z);
    }
}
