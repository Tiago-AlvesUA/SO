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

        const char *memAllocationPolicyAsString(AllocationPolicy policy)
        {
            soProbe(490, "%s(\"%u\")\n", __func__, policy);
			switch(policy)
			{
				case FirstFit:
					return "FIRST FIT";
				break;
				case NextFit:
					return "NEXT FIT";
				break;
				case BestFit:
					return "BEST FIT";
				break;
				case WorstFit:
					return "WORST FIT";
				break;
				default:
					throw Exception(EINVAL, __func__);
			}
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

