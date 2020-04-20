//
// Created by cjdcoy on 4/19/19.
//

#include "query_snapshotv2.h"

/**
 * @param serialized the packet that will be sent (header + data)
 *
 * the CRC is needed by the GCI PROTOCOL in order to verify the packets integrity
 */
void            GciQuerySnapshotV2::create_crc(std::string &serialized)
{
    uint16_t    checksum = 0xFF;
    for (size_t i = 0; i < serialized.size() ; i++) {
        checksum = checksum ^ serialized[i];
    }
    serialized += checksum;
    serialized += 0xff;
}

/**
 * @return the packet serialized (header + data)
 */
string          GciQuerySnapshotV2::serialize_data()
{
    string      serialized;
    uint8_t *   ptr = &_header.handle;
    size_t      x = 0;
    for (; x < sizeof(header_t) ; x ++) {
        serialized += (*ptr);
        ptr++;
    }
    ptr = &_data_to_send.data_switch;
    for (x = 0; x < sizeof(data_t) ; x++) {
        serialized += (*ptr);
        ptr++;
    }
    create_crc(serialized);
    return serialized;
}

/**
 * @brief fill header in order to enable to snapshot query
 */
void GciQuerySnapshotV2::enable_snapshot_query() {
    _header.handle = 0x13;
    _header.support_type = 0x04;
    _header.protocol_version = 0x02;
    _header.block_number = 0x00;
    _header.source_address = 0x00;
    _header.destination_address = 0x00;
    _header.length_lsb = 0x10; //
    _header.length_msb = 0x00;
    _header.functionality = 0x11; //mbscope
    _header.command = 0xF1; //collect ssv2
    _header.subcommand = 0x01; //query
    _data_to_send.data_switch = 0x01;
}

/**
 * @brief fill header in order to disable to snapshot query
 */
void GciQuerySnapshotV2::disable_snapshot_query() {
    _header.handle = 0x13;
    _header.support_type = 0x04;
    _header.protocol_version = 0x02;
    _header.block_number = 0x00;
    _header.source_address = 0x00;
    _header.destination_address = 0x00;
    _header.length_lsb = 0x10;
    _header.length_msb = 0x00;
    _header.functionality = 0x11; //mbscope
    _header.command = 0xF1; //collect ssv2
    _header.subcommand = 0x01; //query
    _data_to_send.data_switch = 0x00;
}