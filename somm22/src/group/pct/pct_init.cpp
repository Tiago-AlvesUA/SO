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

        void pctInit(const char *fname) 
        {
            soProbe(201, "%s(\"%s\")\n", __func__, fname);
            /* ACTION POINT: Replace next instruction with your code */
	   //throw Exception(ENOSYS, __func__);
        	pctInsert(111,0,0,0x200);	
	}

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

