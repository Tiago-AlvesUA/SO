/*
 *  \author 98600
 */

#ifndef __SOMM22__MODULE__MEM__GROUP__
#define __SOMM22__MODULE__MEM__GROUP__

#include "somm22.h"
#include <list>

namespace somm22
{
    
    namespace group 
    {

        namespace mem
        {
		extern AllocationPolicy politica;
		extern uint32_t chunkSize;
		extern uint32_t OSSize;
		extern uint32_t maxMemory;				
		struct BLOCK
		{
			uint32_t pid;
			void * Addr;
			uint32_t size;
		};

		extern std::list<BLOCK> blocosAlocados;
		extern std::list<BLOCK> blocosLivres;
            /* ACTION POINT: Declare here your module's data structure as external */

        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__MEM__GROUP__ */


