#ifndef NETWORK_GCI_QUERY_H
#define NETWORK_GCI_QUERY_H

#include "gci.h"
#include <cstdlib>
#include <cstring>

using namespace std;


/** \addtogroup Parser
 *  @{
 */

/**
 * \brief Contains the minimum every sub gci query class need.
 *
 * as of today this class only exist in case of further development.
 */
class GciQuery : public Gci {
public:
    GciQuery() {};

protected:
private:

};

/** @}*/

#endif //NETWORK_GCI_QUERY_H
