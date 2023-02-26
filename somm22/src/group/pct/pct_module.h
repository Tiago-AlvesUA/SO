/*
 *  \author ...
 *  Nuno Vidal 98600
 */

#ifndef __SOMM22__MODULE__PCT__GROUP__
#define __SOMM22__MODULE__PCT__GROUP__

#include "somm22.h"

#include <list>
#include <stdio.h>
#include <map>

namespace somm22
{
    
    namespace group 
    {
		#define PCT_NULL_TIME 9999999
        namespace pct
        {
            /* ACTION POINT: Declare here your module's data structure as external */
			struct PCT_T 
			{
				uint32_t pid;
				uint32_t arrivalTime;
				uint32_t duration;
				uint32_t addrSpaceSize;
				ProcessState state;
				uint32_t startTime;
				void * memAddr;		
			};
			extern std::map<uint32_t,PCT_T>process_table;
        } // end of namespace pct

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__PCT__GROUP__ */

