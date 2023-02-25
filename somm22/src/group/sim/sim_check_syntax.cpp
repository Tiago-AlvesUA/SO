/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        bool simCheckInputFormat(const char *fname)
        {
            soProbe(502, "%s(\"%s\")\n", __func__, fname);

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
