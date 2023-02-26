/*
 *  \author Nuno Vidal 98600
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        uint32_t memGetBiggestHole()
        {
            soProbe(409, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);

		    uint32_t maxBlock = 0; //total memory including OS 
	    	for (mem::BLOCK b: mem::blocosLivres)
            {
                if(b.size > maxBlock)
                {
                    maxBlock = b.size;
                }
	    	}

		    return maxBlock;
        }

// ================================================================================== //

        uint32_t memGetMaxAllowableSize()
        {
            soProbe(409, "%s()\n", __func__);
            return mem::maxMemory - mem::OSSize;
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
