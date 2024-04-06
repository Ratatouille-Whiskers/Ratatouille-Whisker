#include <MLX90393.h>
#include <math.h>

// mlxA.begin(0x18, DRDY_pinA, Wire);
// mlxB.begin(0x19, DRDY_pinB, Wire);
// mlxC.begin(0x1A, DRDY_pinC, Wire);

#define DRDY_pinA 21
#define DRDY_pinB 26
#define DRDY_pinC 27

#define SDA_pin 16
#define SCL_pin 17

MLX90393 mlxA;
MLX90393 mlxB;
MLX90393 mlxC;

MLX90393::txyzRaw rawDataA;
MLX90393::txyz dataA;
MLX90393::txyzRaw rawDataB;
MLX90393::txyz dataB;
MLX90393::txyzRaw rawDataC;
MLX90393::txyz dataC;

volatile bool dataReadyA = false;
volatile bool dataReadyB = false;
volatile bool dataReadyC = false;

volatile bool procReadyA = false;
volatile bool procReadyB = false;
volatile bool procReadyC = false;

volatile uint8_t status_flag = MLX90393::STATUS_ERROR;

// To include Z-axis measurements use
// MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG
const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;

void mlxInterruptA()
{
    dataReadyA = true;
}

void mlxInterruptB()
{
    dataReadyB = true;
}

void mlxInterruptC()
{
    dataReadyC = true;
}

void setup()
{
    // Serial.begin(115200);
    Serial.begin(460800);
    while (!Serial)
    {
        delay(10);
    }

    pinMode(DRDY_pinA, INPUT_PULLDOWN);
    pinMode(DRDY_pinB, INPUT_PULLDOWN);
    pinMode(DRDY_pinC, INPUT_PULLDOWN);

    attachInterrupt(DRDY_pinA, mlxInterruptA, RISING);
    attachInterrupt(DRDY_pinB, mlxInterruptB, RISING);
    attachInterrupt(DRDY_pinC, mlxInterruptC, RISING);

    Wire.setSDA(SDA_pin);
    Wire.setSCL(SCL_pin);
    Wire.setClock(400000);
    Wire.begin();

    mlxA.begin(0x18, DRDY_pinA, Wire);
    mlxB.begin(0x19, DRDY_pinB, Wire);
    mlxC.begin(0x1A, DRDY_pinC, Wire);

    mlxA.setGainSel(0);
    mlxA.setOverSampling(0);
    mlxA.setDigitalFiltering(0);
    mlxA.setResolution(1, 1, 1);
    mlxA.setTemperatureCompensation(0);
    
    mlxB.setGainSel(0);
    mlxB.setOverSampling(0);
    mlxB.setDigitalFiltering(0);
    mlxB.setResolution(1, 1, 1);
    mlxB.setTemperatureCompensation(0);
    
    mlxC.setGainSel(0);
    mlxC.setOverSampling(0);
    mlxC.setDigitalFiltering(0);
    mlxC.setResolution(1, 1, 1);
    mlxC.setTemperatureCompensation(0);

    mlxA.startBurst(axisFlags);
    mlxB.startBurst(axisFlags);
    mlxC.startBurst(axisFlags);
}

void readDataA(){
    dataReadyA = false;
    while(!dataReadyA);

    status_flag = mlxA.readMeasurement(axisFlags,rawDataA);
    if(mlxA.isOK(status_flag)){
        dataA = mlxA.convertRaw(rawDataA);
        procReadyA = true;
    }
}
void readDataB(){
    dataReadyB = false;
    while(!dataReadyB);

    status_flag = mlxB.readMeasurement(axisFlags,rawDataB);
    if(mlxB.isOK(status_flag)){
        dataB = mlxB.convertRaw(rawDataB);
        procReadyB = true;
    }
}
void readDataC(){
    dataReadyC = false;
    while(!dataReadyC);

    status_flag = mlxC.readMeasurement(axisFlags,rawDataC);
    if(mlxC.isOK(status_flag)){
        dataC = mlxC.convertRaw(rawDataC);
        procReadyC = true;
    }
}

void loop()
{
    // procReady check might be optional
    // it still crashes...
    if(!procReadyA) readDataA();
    if(!procReadyB) readDataB();
    if(!procReadyC) readDataC();
}

void loop1()
{
    if (procReadyA)
    {

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">AX: %f\r\n", dataA.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">AY: %f\r\n", dataA.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">AZ: %f\r\n", dataA.z);

        procReadyA = false;

    }
    if (procReadyB)
    {

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">BX: %f\r\n", dataB.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">BY: %f\r\n", dataB.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">BZ: %f\r\n", dataB.z);

        procReadyB = false;
    }
    if (procReadyC)
    {

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">CX: %f\r\n", dataC.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">CY: %f\r\n", dataC.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">CZ: %f\r\n", dataC.z);

        procReadyC = false;
    }
}
