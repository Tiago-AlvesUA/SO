/*
 *  \author Tiago Santos 89356
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void *memWorstFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(407, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            uint32_t biggest = memGetBiggestHole();
            std::list<mem::BLOCK>::iterator biggestHole;
            std::list<mem::BLOCK>::iterator it;
            int flagFirst = 0;
            for (it = mem::blocosLivres.begin(); it != mem::blocosLivres.end(); ++it){
				if(it->size >= size)
				{
                    if(flagFirst == 0) //populate the with the first capable block found
                    {
                        biggestHole = it;
                        flagFirst = 1;
                        continue;
                    }

                    if(it->size == biggest)
                    {
                        biggestHole = it;
                    }
				}
			}
            

            void * auxAddr = NULL;

            if(flagFirst == 1)  //found at least one
            {
                auxAddr = biggestHole->Addr;

                if (biggestHole->size > size){

                    biggestHole->size = biggestHole->size - size;
                    biggestHole->Addr = (uint8_t*) auxAddr + size; 
                    
                }else{

                    mem::blocosLivres.erase(biggestHole);
                    
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

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
