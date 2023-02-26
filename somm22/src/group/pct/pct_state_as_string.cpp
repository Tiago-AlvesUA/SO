/*
 *  \author 
    Pedro Santos, Gonçalo Sousa
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *pctStateAsString(ProcessState state)
        {
            soProbe(291, "%s(\"%u\")\n", __func__, state);

            /* ACTION POINT: Replace next instruction with your code */
            // throw Exception(ENOSYS, __func__);
            switch (state)
            {
                case TO_COME:
                    return "TO_COME";
                case RUNNING:
                    return "RUNNING";
                case SWAPPED:
                    return "SWAPPED";
                case FINISHED:
                    return "FINISHED";
                case DISCARDED:
                    return "DISCARDED";
                default:
                    return "ERRO";
                }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

