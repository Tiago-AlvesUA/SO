/*
 *  \author Nuno Vidal 98600
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {
		static void print_mem_table(FILE * outFile)
		{
			fprintf(outFile,"+==============================+\n");
			fprintf(outFile,"|  Memory Management busy list |\n");
			fprintf(outFile, "+-------+-----------+----------+\n");
			fprintf(outFile, "|  PID  |   start   |   size   |\n");
			fprintf(outFile, "+-------+-----------+----------+\n");
			for (mem::BLOCK bloco : mem::blocosAlocados) 
			{
				fprintf(outFile, "|");
				fprintf(outFile,"%7d",bloco.pid);
				fprintf(outFile, "|");
				fprintf(outFile,"%10p ",bloco.Addr);
				fprintf(outFile, "|");
				fprintf(outFile,"%#9x ",bloco.size);
				fprintf(outFile, "|\n");

			}
			fprintf(outFile, "+==============================+\n\n");
			
			fprintf(outFile,"+==============================+\n");
			fprintf(outFile,"|  Memory Management free list |\n");
			fprintf(outFile, "+-------+-----------+----------+\n");
			fprintf(outFile, "|  PID  |   start   |   size   |\n");
			fprintf(outFile, "+-------+-----------+----------+\n");
			for (mem::BLOCK bloco : mem::blocosLivres) 
			{
				fprintf(outFile, "|");
				fprintf(outFile,"%s","  ---  ");
				fprintf(outFile, "|");
				fprintf(outFile,"%10p ",bloco.Addr);
				fprintf(outFile, "|");
				fprintf(outFile,"%#9x ",bloco.size);
				fprintf(outFile, "|\n");

			}
			fprintf(outFile, "+==============================+\n\n");

		}


// ================================================================================== //

        void memLog()
        {
            soProbe(402, "%s()\n", __func__);

			FILE * stream = logGetStream();
			print_mem_table(stream);
        }

// ================================================================================== //

        void memPrint(const char *fname, PrintMode mode)
        {
            soProbe(402, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

			if (mode == NEW){ 
				FILE * f = fopen(fname,"w");
				print_mem_table(f);
				fclose(f);
			}
			else if (mode == APPEND){
				FILE * f = fopen(fname,"a");
				print_mem_table(f);
				fclose(f);
			} 
            
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
