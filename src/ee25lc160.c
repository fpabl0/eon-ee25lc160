/**
 ******************************************************************************
 * @file    ee25lc160.c
 * @author  EonTeam
 * @version V1.0.2
 * @date    2020
 ******************************************************************************
 */

#include "ee25lc160.h"

// ===============================================================================
// Macros
// ===============================================================================

// Registros de la EEPROM
#define EEPROM_25LC160_REG_READ  0x03 // Read data from memory array beginning at selected address
#define EEPROM_25LC160_REG_WRITE 0x02 // Write data to memory array beginning at selected address
#define EEPROM_25LC160_REG_WREN  0x06 // Set the write enable latch (enable write operations)
#define EEPROM_25LC160_REG_WRDI  0x04 // Reset the write enable latch (disable write operations)
#define EEPROM_25LC160_REG_RDSR  0x05 // Read STATUS register
#define EEPROM_25LC160_REG_WRSR  0x01 // Write STATUS register
#define EEPROM_25LC160_REG_PE    0x42 // Page Erase register erase one page in memory array
#define EEPROM_25LC160_REG_SE    0xD8 // Sector Erase register erase one sector in memory array
#define EEPROM_25LC160_REG_CE    0xC7 // Chip Erase register erase all sectors in memory array
#define EEPROM_25LC160_REG_RDID  0xAB // Release from Deep power-down and read electronic signature
#define EEPROM_25LC160_REG_DPD   0xB9 // Deep Power-Down mode

// ===============================================================================
// Private functions
// ===============================================================================

static inline void eeprom_select(ee25lc160_t *ee) {
  gpio_reset(ee->cs);
}

static inline void eeprom_deselect(ee25lc160_t *ee) {
  gpio_set(ee->cs);
}

static void wait_eeprom_ready(ee25lc160_t *ee) {
  eeprom_select(ee);
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_RDSR);
  while ((spi_read8(ee->SPIx) & 0x01) != 0) {};
  eeprom_deselect(ee);
}

// ===============================================================================
// Public functions
// ===============================================================================

void ee25lc160_init(ee25lc160_t *ee) {
  gpio_mode(ee->cs, OUTPUT_PP, NOPULL, SPEED_HIGH);
  eeprom_deselect(ee);
}

void ee25lc160_write(ee25lc160_t *ee, uint16_t address, uint8_t data) {

  wait_eeprom_ready(ee);

  eeprom_select(ee);
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_WREN);
  eeprom_deselect(ee);

  eeprom_select(ee);
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_WRITE);
  spi_write8(ee->SPIx, (uint8_t) (address >> 8));
  spi_write8(ee->SPIx, (uint8_t) address);
  spi_write8(ee->SPIx, (uint8_t) data);
  eeprom_deselect(ee);
}

uint8_t ee25lc160_read(ee25lc160_t *ee, uint16_t address) {
  uint8_t data = 0;

  wait_eeprom_ready(ee);

  eeprom_select(ee);
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_READ);
  spi_write8(ee->SPIx, (uint8_t) (address >> 8));
  spi_write8(ee->SPIx, (uint8_t) address);
  data = (uint8_t) spi_read8(ee->SPIx);
  eeprom_deselect(ee);

  return (uint8_t) data;
}