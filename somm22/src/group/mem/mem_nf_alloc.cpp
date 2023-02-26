/*
 *  \author Tiago Alves, 104110
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {
	static void *lastUsedBlockAddr;
// ================================================================================== //

        void *memNextFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(405, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

			void * Addr = nullptr;
			bool blockFound = false;
			if (lastUsedBlockAddr == 0)
			{
				lastUsedBlockAddr = mem::blocosLivres.front().Addr;
			}
				
			
			std::list<mem::BLOCK>::iterator it = mem::blocosLivres.begin();
			printf("Iterator Addr1: %p\n",it->Addr); 
			for (; it != mem::blocosLivres.end(); ++it){
				if(it->Addr < lastUsedBlockAddr)
				{
					continue;
				}
				if(it->size >= size)
				{
					blockFound = true;
					mem::blocosLivres.erase(it);
					mem::BLOCK aux;	
					void * auxAddr = it->Addr;			
					if (it->size > size)
					{			
						aux.pid = 0;
						aux.size = it->size - size;
						aux.Addr = (uint8_t*)auxAddr + size;
						mem::blocosLivres.push_back(aux);					
					}

					aux.pid = pid;
					aux.size = size;
					aux.Addr = auxAddr;
					mem::blocosAlocados.push_back(aux);
					Addr = auxAddr;
					lastUsedBlockAddr = auxAddr;
					printf("lastAddr = %p\n", lastUsedBlockAddr);
					mem::blocosAlocados.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
					mem::blocosLivres.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
					break;
				}
			}
			if (blockFound == false){
				std::list<mem::BLOCK>::iterator it;
				for (it = mem::blocosLivres.begin(); it != mem::blocosLivres.end(); ++it){
					if(it->size >= size)
					{
						blockFound = true;
						mem::blocosLivres.erase(it);
						mem::BLOCK aux;	
						void * auxAddr = it->Addr;			
						if (it->size > size)
						{			
							aux.pid = 0;
							aux.size = it->size - size;
							aux.Addr = (uint8_t*)auxAddr + size;
							mem::blocosLivres.push_back(aux);
						}
						aux.pid = pid;
						aux.size = size;
						aux.Addr = auxAddr;
						mem::blocosAlocados.push_back(aux);
						Addr = auxAddr;
						lastUsedBlockAddr = auxAddr;
						mem::blocosAlocados.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
						mem::blocosLivres.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
						break;
					}
				}
			}
			return Addr;
			
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
