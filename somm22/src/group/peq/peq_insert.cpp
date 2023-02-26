/*
 *  \author 
 * 	Tiago Alves, 104110
 */

#include "somm22.h"
#include "peq_module.h"

using namespace std;


namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void peqInsert(EventType type, uint32_t time, uint32_t pid)
        {
            soProbe(304, "%s(%s, %u, %u)\n", __func__, peqEventTypeAsString(type), time, pid);
		// adicionar ao queue: queuename::push(value)
            require(pid > 0, "process ID must be non-zero");
			Event e;
			e.eventType = type;
			e.eventTime = time;
			e.pid = pid;
			peq::event_list.push_back(e);
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
