//
// Created by cjdcoy on 4/8/19.
//


#ifndef NETWORK_GCI_RESPONSE_H
#define NETWORK_GCI_RESPONSE_H

#include <cstdlib>
#include <cstring>

#include "gci.h"


using namespace std;

/** \addtogroup Parser
 *  @{
 */

/**
 * \brief Contains the minimum every sub gci response class need.
 */
class GciResponse : public Gci {
public:
    GciResponse() {};
    GciResponse(const char *content) {
        crc_handler(content);
    };

    void        run(const char *content, int);
protected:
    void        reset_response();
    uint64_t    get_int(const char *hexstr, int begin, int end);
    uint16_t    reverse_2bytes(uint16_t value);
    void        fill_header(uint16_t value_dec, int pos);
    void        fill_crc(uint16_t value_dec);
    void        crc_handler(const char *content);
    void        header_handler(const char *content);
    virtual void data_handler(const char *content) = 0;

    bool        _header_is_full = false;
    int         _pos = 0;
    int         _content_size;
	/** since a variable can be split between two packets this variable's here to tell us that the beginning of the next packet we'll receive is the second half of our variable */
    bool        _unfinished = false;
	/** stocks the first byte of our split variable */
	uint8_t     _unfinished_value;
private:
};

/** @}*/

#endif //NETWORK_GCI_RESPONSE_H
