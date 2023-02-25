/*
 *  \author ...
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void pctPrint(const char *fname, PrintMode mode)
        {
            soProbe(202, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void pctLog()
        {
            soProbe(202, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
