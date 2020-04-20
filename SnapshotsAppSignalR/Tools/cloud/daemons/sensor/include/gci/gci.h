
#ifndef NETWORK_GCI_H
#define NETWORK_GCI_H

#include <sstream>
#include <iostream>
#include <cstdint>

#include "logs.h"
#include "errors.h"
#include "timer.h"

using namespace std;

/** \addtogroup Parser
 * @{
 * \class Gci
 * \brief Contains the minimum every sub class from gci need.
 */
class Gci {
public:
    Gci() {};

    void        print_header();
    void        print_crc() const;
/** \struct header_s
 *  \brief Structure containing GCI protocol header.
 *  Refer to GCI protocol documentation if you want details about this structure.
 */
    typedef struct header_s {
		//HEADER
        uint8_t handle = 0x13;
        uint8_t support_type = 0x04;
        uint8_t protocol_version = 0x02;
        uint8_t block_number = 0x00;
        uint8_t source_address = 0x00;
        uint8_t destination_address = 0x00;
        uint8_t length_lsb = 0x10; //
        uint8_t length_msb = 0x00;
        uint8_t functionality = 0x11; //mbscope
        uint8_t command = 0xF1; //collect ssv2
        uint8_t subcommand = 0x01; //query
    } header_t;

    typedef struct crc_s {
        uint16_t CRC = 0x00;
    } crc_t;

    header_t    get_header() { return _header; }
    crc_t       get_crc() { return _crc; }
    Timer       &get_timer() { return _timer; }
protected:
    header_t    _header;
    crc_t       _crc;
    Timer       _timer;
};
/** @}*/

#endif //NETWORK_GCI_H
