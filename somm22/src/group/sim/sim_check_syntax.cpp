/*
 *  \author 
    Pedro Santos 98158
    Gonçalo Sousa 98152
 */

#include "somm22.h"
#include "sim_module.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstring>
#include <set>
#include <typeinfo>

namespace somm22
{

    namespace group
    {
        // Input File is a sequence of lines, each one representing a different process and containing the following fields:
            // the PID of a process;
            // the time of its arrival to the system;
            // the duration of its execution;
            // the size in bytes of its address space.
        // The field separator is the semi-colon (;)
        // Lines starting with an # are comments and are discarded.

        bool simCheckInputFormat(const char *fname)
        {
            soProbe(502, "%s(\"%s\")\n", __func__, fname);

            /* ACTION POINT: Replace next instruction with your code */
            std::ifstream ficheiro(fname); 
            std::string processo;
            std::set<uint32_t> valid_pid;
            uint32_t num_line = 0;
            bool valid = false;
            if ( ficheiro.is_open() ) 
            {
                while ( std::getline(ficheiro,processo)) 
                {
		            if(processo[0] == '#')
		            {
		    	        // std::cout << "Linha comentario " << processo << std::endl;
		    	        continue;
		            }
                    num_line++;
   
                    char * car = new char [processo.length()+1];
                    std::strcpy (car, processo.c_str());
                    std::array<std::string, 4> aux;
                    std::array<uint32_t,4> el;

                    int iter = 0;
                    while(*car != '\0' && *car != ' ')
                    {
                        if(*car == ';')
                        {
                            iter++;
                            car++;
                            continue;
                        } 
                        aux[iter] += *car;
                        car ++;
                        if(aux[0] == "0"){
                            std::cerr << "-- Semantic error at line " << num_line << ": PID can't be 0\n";
                            return false;
                        }
                        else if(aux[0] == ""){
                            std::cerr << "-- Syntax error at line " << num_line << " \"" << processo << "\"\n";
                            return false;
                        }
                        else if(aux[2] == "0"){
                            std::cerr << "-- Semantic error at line " << num_line << " (duration is 0): \"" << processo << "\"\n";
                            return false;
                        }
                        else if(aux[3] == "0x0"){
                            std::cerr << "-- Semantic error at line " << num_line << " (address space size is 0): \"" << processo << "\"\n";
                            return false;
                        }
                    }

                    for(long unsigned int i = 0; i < aux.size(); i++)
                    {
                        if(i == 3)
                        {
                            el[i] = (uint32_t)strtol(aux[3].c_str(),NULL,0);
                            continue;
                        }
                        el[i] = (uint32_t)atoi(aux[i].c_str());
                    }

                    // ADICIONAR PID AO SET E VERIFICAR SE EXISTE
                    valid_pid.insert(el[0]);
                    if(num_line != valid_pid.size()){
                        std::cerr << "-- Semantic error at line " << num_line << " (pid " << el[0] << " is repeated): \"" << processo << "\"\n";
                        return false;
                    }
                    valid = true;
                }
            }
            
            return valid;
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
