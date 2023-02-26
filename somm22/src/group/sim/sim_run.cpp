/*
 *  \author 
    Pedro Santos 98158
    Gonçalo Sousa 98152
 */

#include "somm22.h"
#include "sim_module.h"
#include "pct.h"
#include "peq.h"
#include "mem.h"
#include "queue"

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        /*
         * Solution may be based on a state machine with two states, which are related to the
         * type of events that are fetched from the Process Event Queue.
         * The meaningful cases are:
         * - ARRIVAL | TERMINATE
         * - POSTPONED
         */

        void process(Event evento){
            pctSetProcessState(evento.pid,ProcessState::RUNNING);
            pctSetProcessStartTime(evento.pid, sim::time);
            pctSetProcessMemAddress(evento.pid, memAlloc(evento.pid, pctGetProcessAddressSpaceSize(evento.pid)));
            peqInsert(EventType::TERMINATE, sim::time + pctGetProcessDuration(evento.pid), evento.pid); // nao tenho a certeza se o tempo esta bem
            sim::mask = EventType::ARRIVAL | EventType::TERMINATE;
        }

        void run(){
            sim::step = sim::step + 1;
            uint32_t pidPostPoned = peqGetFirstPostponedProcess();
            Event evento = peqFetchNext(simGetCurrentSimMask());
            
            uint32_t space = pctGetProcessAddressSpaceSize(evento.pid);
            if(space > memGetMaxAllowableSize()){
                pctSetProcessState(evento.pid, ProcessState::DISCARDED);
                return;
            }

            if (sim::time < evento.eventTime){
                sim::time = evento.eventTime;
            }

            uint32_t biggestHole = memGetBiggestHole();
            
            switch(evento.eventType){
                case ARRIVAL:
                    if(biggestHole < space){
                        pctSetProcessState(evento.pid, ProcessState::SWAPPED);
                        peqInsert(EventType::POSTPONED, evento.eventTime, evento.pid);
                    }
                    else{   
                        if(pidPostPoned == 0)
                        {
                            process(evento);
                        }else{
                            pctSetProcessState(evento.pid, ProcessState::SWAPPED);
                            peqInsert(EventType::POSTPONED, evento.eventTime, evento.pid);
                        }
                    }
                    
                    break;
                
                case POSTPONED:
                    if(biggestHole < space){
                        peqInsert(EventType::POSTPONED, evento.eventTime, evento.pid);
                    }
                    else{
                        process(evento); //processa seguinte
                    }
                    break;
                
                case TERMINATE:
                {
                    memFree(pctGetProcessMemAddress(evento.pid));
                    pctSetProcessState(evento.pid, ProcessState::FINISHED);
                    uint32_t biggestHoleUpdate = memGetBiggestHole();
                    if (pidPostPoned != 0 && biggestHoleUpdate >= pctGetProcessAddressSpaceSize(pidPostPoned))
                    {
                        sim::mask = EventType::POSTPONED;
                    }
                }
                    break;
                default:
                    break;
            }
            
        }


        void simRun(uint32_t cnt)
        {
            soProbe(503, "%s(cnt: %u)\n", __func__, cnt);

            /* ACTION POINT: Replace next instruction with your code */
            
            if(cnt != 0){
                for (uint32_t i = 0; i < cnt; i++)
                {
                    run();
                }
            }
            else{
                while(!peqIsEmpty()){
                    run();
                }
            }

            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
