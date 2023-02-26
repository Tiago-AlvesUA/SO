/*
 *  \author ...
 * 	Tiago Alves 104110
 */

#include "somm22.h"
#include "pct_module.h"
#include <iostream>
#include <fstream>
#include <iomanip> //setw
#include <cstring>


using namespace std;

namespace somm22
{

    namespace group 
    {
		static void print_pct_table(FILE * outFile)
		{
			for (const auto& p : pct::process_table) {
				//printf("pid: %d\n",p.first);
				fprintf(outFile, "|");
				fprintf(outFile,"%6d",p.second.pid);
				fprintf(outFile, " |");
				fprintf(outFile, "%12d",p.second.arrivalTime);
				fprintf(outFile, " |");
				fprintf(outFile, "%9d",p.second.duration);
				fprintf(outFile, " |");
				fprintf(outFile, "%8s 0x%x","",p.second.addrSpaceSize);
				fprintf(outFile, " | ");
				//const char *stateAsString = pctStateAsString(p.second.state);
				fprintf(outFile, "%-10s",pctStateAsString(p.second.state));
				fprintf(outFile, "|");
				if (p.second.startTime == PCT_NULL_TIME)
				{
					fprintf(outFile, "%8s","(nil)");
					fprintf(outFile, "   |");	
				}else{
					fprintf(outFile, "%10d",p.second.startTime);
					fprintf(outFile, " |");
				}

				fprintf(outFile, "%10p",p.second.memAddr);
				fprintf(outFile, " |\n");
			}
			fprintf(outFile, "+====================================================================================+\n");
			fprintf(outFile, "\n");
		}



        void pctPrint(const char *fname, PrintMode mode)
        {
            soProbe(202, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            /* ACTION POINT: Replace next instruction with your code */
            // buscar full tabela state
            
		if (mode == NEW){ 
			FILE * f = fopen(fname,"w");
			fprintf(f,"+====================================================================================+\n");
			fprintf(f,"|                               Process Control Table                                |\n");
			fprintf(f,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");
			fprintf(f,"|  PID  | arrivalTime | duration | addrSpaceSize |   state   | startTime |  memAddr  |\n");
			fprintf(f,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");
			print_pct_table(f);
			fclose(f);
		}
		else if (mode == APPEND){
			FILE * f = fopen(fname,"a");
			print_pct_table(f);
			fclose(f);
		} 
            
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void pctLog()
        {
            soProbe(202, "%s()\n", __func__);
            // throw Exception(ENOSYS, __func__);
	    FILE * stream = logGetStream();
		fprintf(stream,"+====================================================================================+\n");
		fprintf(stream,"|                               Process Control Table                                |\n");
		fprintf(stream,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");
		fprintf(stream,"|  PID  | arrivalTime | duration | addrSpaceSize |   state   | startTime |  memAddr  |\n");
		fprintf(stream,"+-------+-------------+----------+---------------+-----------+-----------------------+\n");
	    print_pct_table(stream);
        }




// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
