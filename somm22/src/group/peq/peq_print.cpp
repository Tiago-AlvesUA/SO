/*
 *  \author ...
 */

#include "somm22.h"
#include "peq_module.h"

namespace somm22
{

    namespace group 
    {
 
// ================================================================================== //

        void peqLog()
        {
            soProbe(302, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void peqLogEvent(Event *e, const char *msg)
        {
            soProbe(302, "%s(...)\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void peqPrint(const char *fname, PrintMode mode)
        {
            soProbe(302, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            /* ACTION POINT: Replace next instruction with your code */
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

