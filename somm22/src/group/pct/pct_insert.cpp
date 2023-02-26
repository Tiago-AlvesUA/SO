/*
 *  \author ...
 *  Nuno Vidal 98600
 */

#include "somm22.h"
#include "pct_module.h"
namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void pctInsert(uint32_t pid, uint32_t arrivalTime, uint32_t duration, uint32_t addrSpaceSize)
        {
			soProbe(203, "%s(%d, %u, %u, 0x%x)\n", __func__, pid, arrivalTime, duration, addrSpaceSize);

			if (pct::process_table.count(pid) > 0){
				throw Exception(EINVAL, __func__);
			}

			pct::PCT_T record;

			record.pid = pid;
			record.arrivalTime = arrivalTime;
			record.duration = duration;
			record.addrSpaceSize = addrSpaceSize;
			record.state = TO_COME;
			record.startTime = PCT_NULL_TIME;
			record.memAddr = NULL;
			pct::process_table[pid] = record;
		
		}

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
