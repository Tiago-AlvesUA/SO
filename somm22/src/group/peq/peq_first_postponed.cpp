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

        uint32_t peqGetFirstPostponedProcess() 
        {
            soProbe(306, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
			
            Event smallest;
            int postponeExists = 0;
            for(auto &i: peq::event_list){
                if ((i.eventType) == POSTPONED){
                   
                    if (postponeExists == 0)
                    {
                        smallest = i;
                        postponeExists = 1;
                        continue;
                    }

                    if (i.eventTime < smallest.eventTime || (i.eventTime == smallest.eventTime && i.pid < smallest.pid)){
                        smallest = i;
                    }
                }
            }
            
            return  (postponeExists == 1) ? smallest.pid : 0;

        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

