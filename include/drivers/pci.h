#pragma once

#include "lib/types.h"

size_t pci_config_read(uint8_t bus, uint8_t device, uint8_t function,
                       uint8_t offset);
