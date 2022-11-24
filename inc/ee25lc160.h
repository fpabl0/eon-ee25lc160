/**
 ******************************************************************************
 * @file    ee25lc160.h
 * @author  EonTeam
 * @version V1.0.2
 * @date    2020
 ******************************************************************************
 */

#ifndef __EEPROM_25LC160_H
#define __EEPROM_25LC160_H

#include "eonOS.h"

// ===============================================================================
// Type
// ===============================================================================

typedef struct {
  SPI_TypeDef *SPIx;
  pin_t cs;
} ee25lc160_t;

// ===============================================================================
// Functions
// ===============================================================================

// Initialize eeprom 25lc160
void ee25lc160_init(ee25lc160_t *ee);
// Write a byte at specific address in the eeprom
void ee25lc160_write(ee25lc160_t *ee, uint16_t address, uint8_t data);
// Read a byte from a specific address of the eeprom
uint8_t ee25lc160_read(ee25lc160_t *ee, uint16_t address);

#endif