/*
 *  \author 98600
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{
    namespace group 
    {
        namespace mem
        {
            AllocationPolicy politica;
            uint32_t chunkSize;
            uint32_t OSSize;	
            uint32_t maxMemory;
            std::list<BLOCK> blocosAlocados;
            std::list<BLOCK> blocosLivres;
            
        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

