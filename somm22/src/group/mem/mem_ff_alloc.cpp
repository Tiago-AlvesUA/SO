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

        void *memFirstFitAlloc(uint32_t pid, uint32_t size)
        {
			soProbe(404, "%s(%u, 0x%x)\n", __func__, pid, size);

			require(pid > 0, "process ID must be non-zero");
			
			void * newBlockAddr = nullptr;
			
			std::list<mem::BLOCK>::iterator it;
			for (it = mem::blocosLivres.begin(); it != mem::blocosLivres.end(); ++it){
				if(it->size >= size)
				{
					newBlockAddr = it->Addr;			
					if (it->size > size) //redimensionar bloco 
					{
						it->size = it->size - size ;
						it->Addr = (uint8_t*) newBlockAddr + size;
					}else{
						mem::blocosLivres.erase(it);
					}
					
					mem::BLOCK aux;	
					aux.pid = pid;
					aux.size = size;
					aux.Addr = newBlockAddr;
					
					mem::blocosAlocados.push_back(aux);
					mem::blocosAlocados.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
					mem::blocosLivres.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
					break;
				}
			}

			return newBlockAddr;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
