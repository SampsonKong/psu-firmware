/*
 * EEZ PSU Firmware
 * Copyright (C) 2017-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>

#define SD_SCK_HZ(maxSpeed) SPISettings(maxSpeed, MSBFIRST, SPI_MODE0)
#define SD_SCK_MHZ(maxMhz) SPISettings(1000000UL*maxMhz, MSBFIRST, SPI_MODE0)
// SPI divisor constants
/** Set SCK to max rate of F_CPU/2. */
#define SPI_FULL_SPEED SD_SCK_MHZ(50)
/** Set SCK rate to F_CPU/3 for Due */
#define SPI_DIV3_SPEED SD_SCK_HZ(F_CPU/3)
/** Set SCK rate to F_CPU/4. */
#define SPI_HALF_SPEED SD_SCK_HZ(F_CPU/4)
/** Set SCK rate to F_CPU/6 for Due */
#define SPI_DIV6_SPEED SD_SCK_HZ(F_CPU/6)
/** Set SCK rate to F_CPU/8. */
#define SPI_QUARTER_SPEED SD_SCK_HZ(F_CPU/8)
/** Set SCK rate to F_CPU/16. */
#define SPI_EIGHTH_SPEED SD_SCK_HZ(F_CPU/16)
/** Set SCK rate to F_CPU/32. */
#define SPI_SIXTEENTH_SPEED SD_SCK_HZ(F_CPU/32)

namespace eez {
namespace psu {
namespace simulator {
namespace arduino {

#define FILE_READ  1 // O_READ
#define FILE_WRITE 2 // O_READ | O_WRITE | O_CREAT
#define READ_ONLY  3 // O_RDONLY

class FileImpl;

class File {
    friend class SdFat;

public:
    File();
    File(const File &file);
    File(const char *path, uint8_t mode = READ_ONLY);
    File &operator=(const File &file);

    ~File();
    void close();

    operator bool();
    bool getName(char *name, size_t size);
    uint32_t size();
    bool isDirectory();

    void rewindDirectory();
    File openNextFile(uint8_t mode = READ_ONLY);

    bool available();
    bool seek(uint32_t pos);
    int peek();
    int read();
    int read(void *buf, uint16_t nbyte);
    size_t write(const uint8_t *buf, size_t size);

    void print(float value, int numDecimalDigits);
    void print(char value);

private:
    FileImpl *m_impl;
};

class SdFat {
public:
    bool begin(uint8_t cs, SPISettings spiSettings = SPI_FULL_SPEED);
    File open(const char *path, uint8_t mode = FILE_READ);
    bool exists(const char *path);
    bool mkdir(const char *path);
    bool remove(const char *path);
};

}
}
}
} // namespace eez::psu::simulator::arduino;