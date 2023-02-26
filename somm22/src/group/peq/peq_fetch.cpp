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

        Event peqFetchNext(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(305, "%s(%s)\n", __func__, maskStr);

			if (peqIsEmpty(mask)){
				throw Exception(EINVAL, __func__);
			}
			
            Event smallest = peqPeekNext(mask);

            std::list<Event>::iterator it;
			for (it = peq::event_list.begin(); it != peq::event_list.end(); ++it){ 
                if (it->pid == smallest.pid){
					  peq::event_list.erase(it);
                      break;
                }
            }

            return smallest;

        }

// ================================================================================== //

        Event peqPeekNext(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(305, "%s(%s)\n", __func__, maskStr);

			if (peqIsEmpty(mask)){
				throw Exception(EINVAL, __func__);
			}
			
            Event smallest;
            int maskExist = 0;
            for(auto &i: peq::event_list){
                if ((mask & i.eventType) == i.eventType){

                    if (maskExist == 0)
                    {
                        smallest = i;
                        maskExist = 1;
                        continue;
                    }

                    if (i.eventTime < smallest.eventTime || (i.eventTime == smallest.eventTime && i.pid < smallest.pid))
                    {
                        smallest = i;
                    }  
                }
            }

            return smallest;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
