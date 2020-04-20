#ifndef NETWORK_GCI_QUERY_SNAPSHOTV2_H
#define NETWORK_GCI_QUERY_SNAPSHOTV2_H

#include "query.h"
/** \addtogroup Parser
 *  @{
 */

/**
 * @class GciQuerySnapshotV2
 *
 * @brief Specializes in Querying the SnapshotV2 command
 *
 */
class GciQuerySnapshotV2 : public GciQuery {
public:
    GciQuerySnapshotV2() {};

    void        enable_snapshot_query();
    void        disable_snapshot_query();
    void        create_crc(string &);
    string      serialize_data();
private:

	typedef struct data_t {
		/* 0 = disable, 1 = enable */
		uint8_t data_switch = 0x01;
		uint8_t data_lsb = 0x01;
		uint8_t data_msb = 0x00;
	} data_s;

    data_t      _data_to_send;
};

#endif //NETWORK_GCI_QUERY_SNAPSHOTV2_H
