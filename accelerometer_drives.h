#include<Arduino.h>
#include<Wire.h>

class AccelDrives
{
    private:
        #define accell_index 0x52
        uint8_t buffer[6];

    public:
        void _init();
        uint8_t read_data();
        uint8_t decoder(uint8_t);
        uint8_t accell_x();
        uint8_t accell_y();
        uint8_t accell_z();
};

void AccelDrives::_init()
{
    Wire.beginTransmission(accell_index);
    Wire.write(0x40);
    Wire.write(0x00);
    Wire.endTransmission();
}

uint8_t AccelDrives::decoder(uint8_t x)
{
    return (x ^ 0x17) + 0x17;
}

uint8_t AccelDrives::read_data()
{
    uint8_t i;
    Wire.requestFrom(accell_index, 6);
    for (i = 0; i < 6 && Wire.available(); ++i)
    {
        buffer[i] = decoder(Wire.read());
    }
    Wire.beginTransmission(accell_index);
    Wire.write(0x00);
    Wire.endTransmission();
    return i == 6;
}

uint8_t AccelDrives::accell_x()
{
    return ((uint16_t) buffer[2] << 2) | ((buffer[5] >> 2) & 3);
}

uint8_t AccelDrives::accell_y()
{
    return ((uint16_t) buffer[3] << 2) | ((buffer[5] >> 4) & 3);
}

uint8_t AccelDrives::accell_z()
{
    return ((uint16_t) buffer[4] << 2) | ((buffer[5] >> 6) & 3);
}

