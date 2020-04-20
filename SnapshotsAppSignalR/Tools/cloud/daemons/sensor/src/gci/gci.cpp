#include "gci.h"

/** debug function */
void Gci::print_header() {
    cout << "_______________ HEADER content _______________" << endl;
    uint8_t *ptr = &_header.handle;
    for (unsigned int x = 0 ; x < sizeof(header_t) ; x ++) {
        stringstream ss;
        ss << *ptr + 0;
        cout << ss.str() << " pos: " << x << endl;
        ptr++;
    }
    cout << "______ finished printing header content ______" << endl;
}

/** debug function */
void Gci::print_crc() const {
    cout << "_______________ CRC content _______________" << endl;
    cout << "CRC_value:" << _crc.CRC << endl;
    cout << "______ finished printing crc content ______" << endl;
}