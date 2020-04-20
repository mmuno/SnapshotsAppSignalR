#include "response.h"
#include <chrono>

/**
 * @brief Reset the position of the cursor within the data (_pos), reset buffer.
 */
void        GciResponse::reset_response()
{
    _pos = 0;
    _header_is_full = false;
}

/**
 * @param content - here's the data we need to handle.
 * @param content_size - content size is sent as parameter since the content might have zeros bytes.
 *  we cannot measure it using basic methods (such as strlen).
 *
 * @brief This is the only method we can call outside the class, il process all the data by itself.
 */
void        GciResponse::run(const char *content, int content_size)
{
    _content_size = content_size;
    crc_handler(content);
    /**
     * @note -2 because we substract the crc header (refer to GCI documentation)
     */
	while (_pos < (_content_size - 2)) {
		if (_header_is_full == false)
			header_handler(content);
		else
        	data_handler(content);
    }
    reset_response();
}

/**
 * @param content pointer on the data received
 * @brief Load the header.
 */
void        GciResponse::header_handler(const char *content)
{
	uint16_t dec_value = get_int(content, _pos, _pos + 1);
	fill_header(dec_value, _pos);
	if (_pos == sizeof(header_t) -1) {
		_header_is_full = true;
	}
	_pos+=1;
}

/**
 * @param content
 * @param begin starting pos
 * @param end ending pos
 *
 * @brief This function allows us to convert the bytes we receive into ints
 * (we shift the bits from x char into to_return).
 *
 */
uint64_t    GciResponse::get_int(const char *content, int begin, int end) {
    uint64_t to_return = 0;

    for (int x = 0 ; x < end - begin ; x++)
        to_return = (to_return << 8) | (uint8_t)content[begin + x];
    return (uint64_t) to_return;
}

void        GciResponse::fill_header(uint16_t value_dec, int pos)
{
    unsigned char *ptr = &_header.handle;
    ptr += pos;
    *ptr = value_dec;
}

/** @param value This is the integer we want to convert from lsb to msb
 * @brief MBCSI send data is sent in lsb, this function allows us to go from lsm to msb by shifting bits.
 * @return return the translated integer
 */
uint16_t GciResponse::reverse_2bytes(uint16_t value)
{
    value = (((value & 0x00ff) << 8) & 0xff00) | (((value & 0xff00) >> 8) & 0x00ff);
    return value;
}

/** @param value_dec This is the integer value of the crc in lsb
 * @brief Function responsible to gather the crc.
 */
void        GciResponse::fill_crc(uint16_t value_dec)
{
    _crc.CRC = value_dec;
    _crc.CRC = (((_crc.CRC & 0x00ff) << 8) & 0xff00) | (((_crc.CRC & 0xff00) >> 8) & 0x00ff);
}

void        GciResponse::crc_handler(const char *content)
{
    int offset = 0;

    offset = _content_size - 2;
    fill_crc(get_int(content, offset, offset + 2));
}