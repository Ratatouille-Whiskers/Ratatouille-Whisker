#include <MLX90393.h>
#include <math.h>

// mlxA.begin(0x18, DRDY_pinA, Wire);
// mlxB.begin(0x19, DRDY_pinB, Wire);
// mlxC.begin(0x1A, DRDY_pinC, Wire);

#define DRDY_pinA 21
#define DRDY_pinB 26
#define DRDY_pinC 27

#define TOUCH_pinA 6
#define TOUCH_pinB 7
#define TOUCH_pinC 8

#define SDA_pin 16
#define SCL_pin 17

MLX90393 mlxA;
MLX90393 mlxB;
MLX90393 mlxC;

MLX90393::txyzRaw rawDataA;
MLX90393::txyzRaw rawDataA_offset;
MLX90393::txyz dataA;
MLX90393::txyzRaw rawDataB;
MLX90393::txyzRaw rawDataB_offset;
MLX90393::txyz dataB;
MLX90393::txyzRaw rawDataC;
MLX90393::txyzRaw rawDataC_offset;
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
// const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;
const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG;

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

void offsetDataA(){
    uint16_t i = 0;
    for (uint16_t i = 0; i < 1000; i++)
    {
        dataReadyA = false;
        while(!dataReadyA);
        status_flag = mlxA.readMeasurement(axisFlags,rawDataA);
        if(mlxA.isOK(status_flag)){
            rawDataA_offset.x = (rawDataA_offset.x >> 1) + (rawDataA.x >> 1);
            rawDataA_offset.y = (rawDataA_offset.y >> 1) + (rawDataA.y >> 1);
            rawDataA_offset.z = (rawDataA_offset.z >> 1) + (rawDataA.z >> 1);
        }
    }
}

void offsetDataB(){
    uint16_t i = 0;
    for (uint16_t i = 0; i < 1000; i++)
    {
        dataReadyB = false;
        while(!dataReadyB);
        status_flag = mlxB.readMeasurement(axisFlags,rawDataB);
        if(mlxB.isOK(status_flag)){
            rawDataB_offset.x = (rawDataB_offset.x >> 1) + (rawDataB.x >> 1);
            rawDataB_offset.y = (rawDataB_offset.y >> 1) + (rawDataB.y >> 1);
            rawDataB_offset.z = (rawDataB_offset.z >> 1) + (rawDataB.z >> 1);
        }
    }
}

void offsetDataC(){
    uint16_t i = 0;
    for (uint16_t i = 0; i < 1000; i++)
    {
        dataReadyC = false;
        while(!dataReadyC);
        status_flag = mlxC.readMeasurement(axisFlags,rawDataC);
        if(mlxC.isOK(status_flag)){
            rawDataC_offset.x = (rawDataC_offset.x >> 1) + (rawDataC.x >> 1);
            rawDataC_offset.y = (rawDataC_offset.y >> 1) + (rawDataC.y >> 1);
            rawDataC_offset.z = (rawDataC_offset.z >> 1) + (rawDataC.z >> 1);
        }
    }
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
    pinMode(TOUCH_pinA, OUTPUT);
    pinMode(TOUCH_pinB, OUTPUT);
    pinMode(TOUCH_pinC, OUTPUT);

    digitalWrite(TOUCH_pinA, LOW);
    digitalWrite(TOUCH_pinB, LOW);
    digitalWrite(TOUCH_pinC, LOW);

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
    mlxA.setResolution(3, 3, 3);
    mlxA.setTemperatureCompensation(0);
    
    mlxB.setGainSel(0);
    mlxB.setOverSampling(0);
    mlxB.setDigitalFiltering(0);
    mlxB.setResolution(3, 3, 3);
    mlxB.setTemperatureCompensation(0);
    
    mlxC.setGainSel(0);
    mlxC.setOverSampling(0);
    mlxC.setDigitalFiltering(0);
    mlxC.setResolution(3, 3, 3);
    mlxC.setTemperatureCompensation(0);

    mlxA.startBurst(axisFlags);
    mlxB.startBurst(axisFlags);
    mlxC.startBurst(axisFlags);

    delay(500);

    offsetDataA();
    offsetDataB();
    offsetDataC();

}

void readDataA(){
    dataReadyA = false;
    while(!dataReadyA);

    status_flag = mlxA.readMeasurement(axisFlags,rawDataA);
    if(mlxA.isOK(status_flag)){
        rawDataA.x -= rawDataA_offset.x + 0x8000;
        rawDataA.y -= rawDataA_offset.y + 0x8000;
        rawDataA.z -= rawDataA_offset.z + 0x8000;
        // dataA = mlxA.convertRaw(rawDataA);

        if(rawDataA.y > 0x8400 || rawDataA.y < 0x7C00){
            digitalWrite(TOUCH_pinA, HIGH);
        }
        else{
            digitalWrite(TOUCH_pinA, LOW);
        }

        procReadyA = true;
    }
}
void readDataB(){
    dataReadyB = false;
    while(!dataReadyB);

    status_flag = mlxB.readMeasurement(axisFlags,rawDataB);
    if(mlxB.isOK(status_flag)){
        rawDataB.x -= rawDataB_offset.x + 0x8000;
        rawDataB.y -= rawDataB_offset.y + 0x8000;
        rawDataB.z -= rawDataB_offset.z + 0x8000;
        // dataB = mlxB.convertRaw(rawDataB);

        if(rawDataB.y > 0x8400 || rawDataB.y < 0x7C00){
            digitalWrite(TOUCH_pinB, HIGH);
        }
        else{
            digitalWrite(TOUCH_pinB, LOW);
        }

        procReadyB = true;
    }
}
void readDataC(){
    dataReadyC = false;
    while(!dataReadyC);

    status_flag = mlxC.readMeasurement(axisFlags,rawDataC);
    if(mlxC.isOK(status_flag)){
        rawDataC.x -= rawDataC_offset.x + 0x8000;
        rawDataC.y -= rawDataC_offset.y + 0x8000;
        rawDataC.z -= rawDataC_offset.z + 0x8000;
        // dataC = mlxC.convertRaw(rawDataC);

        if(rawDataC.y > 0x8400 || rawDataC.y < 0x7C00){
            digitalWrite(TOUCH_pinC, HIGH);
        }
        else{
            digitalWrite(TOUCH_pinC, LOW);
        }

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
            Serial.printf(">AX: %u\r\n", rawDataA.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">AY: %u\r\n", rawDataA.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">AZ: %u\r\n", rawDataA.z);

        procReadyA = false;

    }
    if (procReadyB)
    {

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">BX: %u\r\n", rawDataB.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">BY: %u\r\n", rawDataB.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">BZ: %u\r\n", rawDataB.z);

        procReadyB = false;
    }
    if (procReadyC)
    {

        if (axisFlags & MLX90393::X_FLAG)
            Serial.printf(">CX: %u\r\n", rawDataC.x);

        if (axisFlags & MLX90393::Y_FLAG)
            Serial.printf(">CY: %u\r\n", rawDataC.y);

        if (axisFlags & MLX90393::Z_FLAG)
            Serial.printf(">CZ: %u\r\n", rawDataC.z);

        procReadyC = false;
    }
}
