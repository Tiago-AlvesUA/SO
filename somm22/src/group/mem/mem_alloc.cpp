/*
 *  \author Nuno VIdal
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void *memAlloc(uint32_t pid, uint32_t size)
        {
			soProbe(403, "%s(%u, 0x%x)\n", __func__, pid, size);

			require(pid > 0, "process ID must be non-zero");
	
			uint32_t resto = size % mem::chunkSize;
			if (resto != 0)
				size = size + mem::chunkSize - resto;

			switch(mem::politica)
			{
				case FirstFit:
					return memFirstFitAlloc(pid,size);
				break;
				case NextFit:
					return memNextFitAlloc(pid,size);
				break;
				case BestFit:
					return memBestFitAlloc(pid,size);
				break;
				case WorstFit:
					return memWorstFitAlloc(pid,size);
				break;
				default:
					throw Exception(EINVAL, __func__);
		}
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

