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

		pct::PCT_T *record = new pct::PCT_T();

		record->pid = pid;
		record->arrivalTime = arrivalTime;
		record->duration = duration;
		record->addrSpaceSize = addrSpaceSize;
		record->state = TO_COME;
		record->startTime = -1;
		record->memAddr = -1;
		pct::process_table.insert({pid,*record});
		//TUTORIAL: PERCORRER MAPA -> p.first é a key do mapa, p.second é o mapa e da para aceder aos elementos p.second.(atributo)
		/*for (const auto& p : pct::process_table) {

			printf("%d\n",p.first);
			printf("0x%x\n",p.second.addrSpaceSize);
		    // p.second is Employee object.
		}*/
	}

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
