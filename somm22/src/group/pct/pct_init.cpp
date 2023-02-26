/*
 *  \author ...
 *  Nuno Vidal 98600
 */

#include "somm22.h"
#include "pct_module.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstring>

namespace somm22
{

    namespace group 
    {

// ================================================================================== //
        std::array<uint32_t,4> sanitizeCSVLine(std::string csvline)  //use of std array instead of vector because less overhead
        {
            //pass to c string like
            char * cstr = new char [csvline.length()+1];
            std::strcpy (cstr, csvline.c_str());
            
            std::array<std::string, 4> aux;
            int indexer = 0;
            while(*cstr != '\0')
            {
                if(*cstr == '#') //é comentario
                {
                    break;
                }

                if(*cstr == ';')
                {
                    indexer ++;
                    cstr ++;
                    continue;
                } 
                aux[indexer] += *cstr;
                cstr ++;
            }

            std::array<uint32_t,4> result;
            for(long unsigned int i = 0; i < aux.size(); i++)
            {
                if(i == 3)
                {
                    result[i] = (uint32_t)strtol(aux[3].c_str(),NULL,0);
                    continue;
                }
                result[i] = (uint32_t)atoi(aux[i].c_str());
            }

            return result;
        }

        void pctInit(const char *fname) 
        {
            soProbe(201, "%s(\"%s\")\n", __func__, fname);
        	
            std::ifstream ficheiro (fname); 
            std::string processo;
            if ( ficheiro.is_open() ) 
            {
                while ( std::getline(ficheiro,processo )) 
                {
                    if(processo[0] == '#')
                    {
                        std::cout << "Linha comentario " << processo << std::endl;
                        continue;
                    }

                    std::array<uint32_t,4> elements = sanitizeCSVLine(processo);
                    pctInsert(elements[0],elements[1],elements[2],elements[3]);
                }
            }
	    }

        
// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

