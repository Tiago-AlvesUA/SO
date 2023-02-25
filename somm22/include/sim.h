/**
 * \defgroup sim Scheduling simulation
 *
 * \details
 *   - The simulation is driven by an input file, that represents a set of processes,
 *     including their execution data.
 *   - Syntactically, an input file is a sequence of lines, 
 *     each one representing a different process and containing the following fields:
 *     - the PID of a process;
 *     - the time of its arrival to the system;
 *     - the duration of its execution;
 *     - the size in bytes of its address space.
 *   - The field separator is the semi-colon (\c ;)
 *   - Lines starting with an # are comments ans discarded.
 *
 *   The interface of this module is predefined, being composed of the following functions:
 *   <table>
 *   <tr> <th> \c function <th align="center"> function ID <th> role
 *   <tr> <td> \c simSetBinaryMode <td align="center"> 500 <td> Enable/Disable the binary version of \c sim functions;
 *   <tr> <td> \c simInit <td align="center"> 501 <td> initializes the support internal data structure;
 *   <tr> <td> \c simCheckInputFormat <td align="center"> 502 <td> Check the syntax of the scheduling simulation description file;
 *   <tr> <td> \c simRun <td align="center"> 503 <td> Run a given number of simulation steps;
 *   <tr> <td> \c simGetCurrentSimTime <td align="center"> 504 <td> Return the current simulation time;
 *   <tr> <td> \c simGetCurrentSimStep <td align="center"> 504 <td> Return the current simulation step;
 *   <tr> <td> \c simGetCurrentSimMask <td align="center"> 504 <td> Return the current simulation mask;
 *   </table>
 *
 *  \author Artur Pereira - 2022
 */

#ifndef __SOMM22_SIM__
#define __SOMM22_SIM__


namespace somm22
{
    
    /** @{ */

// ================================================================================== //

    /**
     * \brief Initializes the internal data structure
     * \details
     *   - It is up to the implementer to decide which data structure to use,
     *     and initialize it accordingly
     *
     */
    void simInit();

// ================================================================================== //

    /**
     * \brief Check the syntax of the input file 
     * \details
     *  - Must check the syntax of every line in the file
     *  - Must check if all PIDs are different
     *  - In case of an error, an error message should be sent to \c stderr and an exception must be thrown.
     *
     * \param [in] fname Path to the file whose syntax is to be checked
     * \return \c true, if file is valid syntactically; \c false, otherwise
     */
    bool simCheckInputFormat(const char *fname);

// ================================================================================== //

    /**
     * \brief Run the simulation for a given number of events
     * \details
     *   - If the given number is zero, run til the end
     *
     * \param [in] cnt Number of events to simulate
     */
    void simRun(uint32_t cnt);

// ================================================================================== //

    /**
     * \brief Get the current simulation step
     * \details
     *   - This modules keeps internally the number of events already processed.
     *     The current simulation step corresponds to the number of events already
     *     processed by the module.
     * \return The current simulation step
     */
    uint32_t simGetCurrentSimStep();

// ================================================================================== //

    /**
     * \brief Get the current simulation time
     * \details
     *   - On consequence of the execution of events, the current simulation time
     *     advances. 
     * \return The current simulation time
     */
    uint32_t simGetCurrentSimTime();

// ================================================================================== //

    /**
     * \brief Get the current simulation mask
     * \details
     *   - At every step, the type of events that can be processed may change.
     *     The event mask is a bitwise-or of those possible.
     * \return The current simulation mask
     */
    uint32_t simGetCurrentSimMask();

// ================================================================================== //

    /**
     * \brief Enable/Disable the binary version of the \c sim functions
     * \details
     *   - 
     *
     * \param [in] state New state: \c true to enable; \c false to disable
     */
    void simSetBinaryMode(bool state);

// ================================================================================== //

    /** @} */

};

#endif /* __SOMM22_SIM__ */

