/*
 *  \author Tiago Santos 89356
 */

#include "somm22.h"
#include "peq_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        bool peqIsEmpty(uint32_t mask) 
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(303, "%s(%s)\n", __func__, maskStr);

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);

            if(peq::event_list.empty() == true){
                return true;
            }

            if (mask != 0)
            {
                for(auto &i: peq::event_list){
                    if ((mask & i.eventType) == i.eventType){
                        return false;
                    }
                }
                return true;
            }

            return false;
        }

     



// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

