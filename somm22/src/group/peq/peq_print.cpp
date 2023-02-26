/*
 *  \author Tiago Alves, 104110
 */

#include "somm22.h"
#include "peq_module.h"
#include <cstring>

namespace somm22
{

    namespace group 
    {
 
	static void print_peq_table(FILE * outFile)
	{
		peq::event_list.sort([](const Event &f, const Event &s) { return f.eventTime < s.eventTime; });
		for (const auto &i : peq::event_list) {	
			fprintf(outFile, "|");
			fprintf(outFile,"%10d",i.eventTime);
			fprintf(outFile, " | ");
			fprintf(outFile, "%-10s",peqEventTypeAsString(i.eventType));
			fprintf(outFile, "|");
			fprintf(outFile, "%6d",i.pid);				
			fprintf(outFile, " |\n");
		}
		fprintf(outFile, "+===============================+\n");
		fprintf(outFile, "\n");
	}
// ================================================================================== //

        void peqLog()
        {
            soProbe(302, "%s()\n", __func__);
			
			FILE * stream = logGetStream();
			fprintf(stream,"+===============================+\n");
			fprintf(stream,"|      Process Event Queue      |\n");
			fprintf(stream,"+-----------+-----------+-------+\n");
			fprintf(stream,"| eventTime | eventType |  PID  |\n");
			fprintf(stream,"+-----------+-----------+-------+\n");
			print_peq_table(stream);
			
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void peqLogEvent(Event *e, const char *msg)
        {
            soProbe(302, "%s(...)\n", __func__);
            
			//logEvent(e->pid,e->eventTime,e->eventType);
			logPrint(msg);
			logPrint(": (%s, %d, %d)\n", peqEventTypeAsString(e->eventType), e->eventTime, e->pid);
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        void peqPrint(const char *fname, PrintMode mode)
        {
            soProbe(302, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            /* ACTION POINT: Replace next instruction with your code */
			if (mode == NEW){ 
				FILE * f = fopen(fname,"w");
				fprintf(f,"+===============================+\n");
				fprintf(f,"|      Process Event Queue      |\n");
				fprintf(f,"+-----------+-----------+-------+\n");
				fprintf(f,"| eventTime | eventType |  PID  |\n");
				fprintf(f,"+-----------+-----------+-------+\n");
				print_peq_table(f);
				fclose(f);
			}
			else if (mode == APPEND){
				FILE * f = fopen(fname,"a");	
				print_peq_table(f);
				fclose(f);
			} 
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

