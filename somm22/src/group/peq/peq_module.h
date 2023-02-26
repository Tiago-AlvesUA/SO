/*
 *  \author Tiago Santos 89356
 *          Tiago Alves 104110
 */

#ifndef __SOMM22__MODULE__PEQ__GROUP__
#define __SOMM22__MODULE__PEQ__GROUP__

#include "somm22.h"

#include <list>
#include <stdio.h>
#include <deque>

namespace somm22
{

    namespace group 
    {

        namespace peq
        {
            /* ACTION POINT: Declare here your module's data structure as external */
		struct EVENT
		{
			//Event evento;
		};
		extern std::list<Event>event_list;
		
        } // end of namespace peq

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__PEQ__GROUP__ */

