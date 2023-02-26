/*
 *  \author Tiago Alves, 104110
 *  Tiago Santos 89356
 */

#include "somm22.h"
#include "peq_module.h"
#include <iostream>

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *peqEventTypeAsString(EventType type)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, type);
			

			switch (type)
            {
				case ARRIVAL:
					//std::cout << "ARRIVAL";
					return "ARRIVAL";
				case POSTPONED:
					return "POSTPONED";
				case TERMINATE:
					return "TERMINATE";
                default:
                    return "Invalid";
			}

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

        const char *peqEventMaskAsString(uint32_t mask)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, mask);
            require((mask | 0b111) == 0b111, "wrong event mask");

			//return to_string(mask);
            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);

            switch (mask)
            {
            case 0b000:
                return "ARRIVAL | POSTPONED | TERMINATE";
            case 0b001:
                return "ARRIVAL";
            case 0b010:
                return "POSTPONED";
            case 0b011:
				return "ARRIVAL | POSTPONED";
            case 0b100:
                return "TERMINATE";
            case 0b101:
				return "ARRIVAL | TERMINATE";
			case 0b110: 
				return "POSTPONED | TERMINATE";
			case 0b111:
				return "ARRIVAL | POSTPONED | TERMINATE";
            default:
                throw Exception(ENOSYS, __func__);
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

