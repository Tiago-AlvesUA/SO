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

        void *memBestFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(406, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

			std::list<mem::BLOCK>::iterator smallestHole; 
            int flagFirst = 0;
			std::list<mem::BLOCK>::iterator it;

			for (it = mem::blocosLivres.begin(); it != mem::blocosLivres.end(); ++it){
				if(it->size >= size)
				{
                    if(flagFirst == 0) //populate the with the first capable block found
                    {
                        smallestHole = it;
                        flagFirst = 1;
                        continue;
                    }

                    if(it->size < smallestHole->size)
                    {
                        smallestHole = it;
                    }
				}
			}

            
            void * auxAddr = NULL;

            if(flagFirst == 1)  //found at least one
            {
                auxAddr = smallestHole->Addr;

                if (smallestHole->size > size)
                {
                    smallestHole->size = smallestHole->size - size;
                    smallestHole->Addr = (uint8_t*) auxAddr + size ; 
                }else{
                    mem::blocosLivres.erase(smallestHole);
                }
                
                mem::BLOCK aux;		
                aux.pid = pid;
                aux.size = size;
                aux.Addr = auxAddr;
                mem::blocosAlocados.push_back(aux);
                
                mem::blocosAlocados.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
                mem::blocosLivres.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });

            }	
           
            

			return auxAddr;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
