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

        	
        void mergeBlocks()
        {
            std::list<mem::BLOCK>::iterator itLivre = mem::blocosLivres.begin();
            //void * previousAddr = nullptr;
            while(itLivre != mem::blocosLivres.end())
            {
                auto nextBlock = std::next(itLivre, 1);
                if((uint8_t*) itLivre->Addr + itLivre->size == nextBlock->Addr)
                {
                    itLivre->size += nextBlock->size;
                    mem::blocosLivres.erase(nextBlock);
                    itLivre = mem::blocosLivres.begin(); // volta ao inicio para voltar a verificar
                    continue;
                }
                 
                itLivre++;
            }
        }


        void memFree(void *addr)
        {
            soProbe(408, "%s(addr: %p)\n", __func__, addr);

            require(addr != NULL, "addr must be non-null");

            std::list<mem::BLOCK>::iterator itAlocados;
			for (itAlocados = mem::blocosAlocados.begin(); itAlocados != mem::blocosAlocados.end(); ++itAlocados){
				if(itAlocados->Addr == addr)
				{
					mem::blocosAlocados.erase(itAlocados);
                   
                    mem::BLOCK aux;	
                    aux.pid = 0;
                    aux.size = itAlocados->size;
                    aux.Addr = itAlocados->Addr;
                    mem::blocosLivres.push_back(aux);
                    
                    mem::blocosAlocados.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
					mem::blocosLivres.sort([](const mem::BLOCK &f, const mem::BLOCK &s) { return f.Addr < s.Addr; });
                    mergeBlocks();
					break;
				}
			}




            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

       

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

