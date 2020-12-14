























typedef enum {

    R9 = ~1U,

    R10 = ~3U,

    R11 = ~7U,

    R12 = ~0U

} Resolution;









typedef struct

{

    uint8_t lsb;

    uint8_t msb;

    uint8_t Th;

    uint8_t Tl;

    uint8_t config_reg;

    uint8_t reserved[3];

    uint8_t crc;

} ds18b20_scratchpad_data_t;















_Bool 

    ds18b20_initialise(Resolution resolution);













typedef union

{

    uint8_t bytes[8];

    struct {

        uint8_t family_code;

        uint8_t serial_number[6];

        uint8_t crc;

    }rom_code;

} ds18b20_ROM_t;













ds18b20_ROM_t ds18b20_read_rom(void);









void ds18b20_do_conversion(void);

















_Bool 

    ds18b20_read_scratchpad(ds18b20_scratchpad_data_t * const data);













float ds18b20_convert(uint16_t digital);















uint8_t ds18b20_calculate_CRC(const uint8_t* data, uint32_t num_of_bytes);
