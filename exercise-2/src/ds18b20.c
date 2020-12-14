#include "ds18b20.h"


bool ds18b20_initialise(Resolution resolution)
{
}


ds18b20_ROM_t ds18b20_read_rom(void)
{
}

void ds18b20_do_conversion(void)
{
}

bool ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data)
{
}

float ds18b20_convert(uint16_t digital)
{
}


uint8_t ds18b20_calculate_CRC(const uint8_t* data, uint32_t num_of_bytes)
{
}


