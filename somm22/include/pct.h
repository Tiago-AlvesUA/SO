/**
 * \defgroup pct Process Control Table (pct)
 *
 * \details
 *   The Process Control Table (\c pct) is a mapping that associates a process with a tuple of data.
 *   The process itself is identified by a unique integer value, called Process Identification (\c PID).
 *   To every process, the following data is considered:
 *   - the time a which the process arrived to the system;
 *   - the time the process takes to execute;
 *   - the size in bytes of the process' address space;
 *   - the start address, when the process is resident in memory and after termination;
 *   - the state of execution, being one of TO_COME, RUNNING, SWAPPED, or FINISHED.
 *
 *   <b>It is up to the implementer to decide how to store this data</b>.
 *
 *   Note that, to be executed, a process needs its address space to be resident in memory.
 *   If no free region of memory, big enough to host its address space, exist, 
 *   the process must wait until one is available.
 *   Thus, the time at which a process starts to execute may be different from its arrival time.
 *
 *   It is the responsibility of the memory management module to assign a block of memory to
 *   the process, in order to host its address space.
 *   The time required by the memory management module to select the block of memory 
 *   is assumed to be negligible.
 *
 *   The interface of this module is predefined, being composed of the following functions:
 *   <table>
 *   <tr><th>function <th> function ID <th>role
 *   <tr> <td> \c pctSetBinaryMode <td align="center"> 200 <td> Enable/Disable the binary version of \c pct functions;
 *   <tr><td>\c pctInit <td align="center"> 201 <td> initializes the support internal data structure
 *   <tr><td>\c pctLog <td align="center"> 202 <td> log the internal state of the PCT table, sorted in ascending order of PID.
 *   <tr><td>\c pctPrint <td align="center"> 202 <td> prints the internal state of the PCT table, sorted in ascending order of PID.
 *   <tr><td>\c pctInsert <td align="center"> 203 <td> inserts a new entry in the PCT table
 *   <tr><td>\c pctGetProcessDuration <td align="center"> 204 <td> returns the time of execution of a process
 *   <tr><td>\c pctGetProcessAddressSpaceSize <td align="center"> 205 <td> returns the size of the address space of a process
 *   <tr><td>\c pctGetProcessMemAddress <td align="center"> 206 <td> returns the memory address where the process was hosted
 *   <tr><td>\c pctSetProcessMemAddress <td align="center"> 207 <td> sets the memory address where the process will be hosted
 *   <tr><td>\c pctSetProcessState <td align="center"> 208 <td> sets the state of a process
 *   <tr><td>\c pctSetProcessStartTime <td align="center"> 209 <td> sets the start time of a process
 *   <tr><td>\c pctGetStateName <td align="center"> 210 <td> returns the state as a string, given de pid
 *   <tr><td>\c pctStateAsString <td align="center"> 291 <td> returns the state as a string. given the state
 *   </table>
 *
 *  \author Artur Pereira - 2022
 */

#ifndef __SOMM22_PCT__
#define __SOMM22_PCT__

namespace somm22
{

    /** @{ */

    /**
     * \brief Possible states a process can be.
     * \ingroup pct
     * \details
     *   The possible values for the process state are:
     */
    enum ProcessState { 
        TO_COME, ///< the process hasn't arrive to the system yet
        RUNNING, ///< the process is executing
        SWAPPED, ///< enough memory is not available, so process is waiting for space
        FINISHED, ///< the process has already finished its execution
        DISCARDED ///< the process has an address space bigger than the whole available memory
    };

// ================================================================================== //

    /**
     * \brief Initialize the internal data structure
     * \id 201
     * \effort ...
     * \details
     *   - It is up to the implementer to decide which data structure to use,
     *     and initialize it accordingly
     *     
     * \param [in] fname Path to the file containing simulation data
     */
    void pctInit(const char *fname);

// ================================================================================== //

    /**
     * \brief Log the internal state of the pct
     * \id 202
     * \effort ...
     * \details
     *
     */
    void pctLog();

// ================================================================================== //

    /**
     * \brief Print the internal state of the pct
     * \id 202
     * \effort ...
     * \details
     *   - If print mode is NEW, print to a new file (zapping if necessary)
     *   - If print mode is APPEND, append printing to the end of the file
     *
     * \param [in] fname Path to file where printing must be written to
     * \param [in] mode How to print (one of pct::NEW or pct::APPEND)
     */
    void pctPrint(const char *fname, PrintMode mode);

// ================================================================================== //

    /**
     * \brief Inserts a new entry in the PCT table
     * \id 303
     * \effort ...
     * \details
     *  - an exception should be thrown, if an entry for the given pis already exists
     *  - field \c memAddr should be put at \c NULL
     *  - field \c state should be put at \c TO_COME
     * \param [in] pid Id of process associated to the entry
     * \param [in] arrivalTime Time at which the process is submitted
     * \param [in] duration Time the process takes to run
     * \param [in] addrSpaceSize Size of the process' address space
     */
    void pctInsert(uint32_t pid, uint32_t arrivalTime, uint32_t duration, uint32_t addrSpaceSize);

// ================================================================================== //

    /**
     * \brief Get process execution duration
     * \param [in] pid PID of the process
     * \return the process execution duration
     */
    uint32_t pctGetProcessDuration(uint32_t pid);

    /**
     * \brief Get process address space size
     * \param [in] pid PID of the process
     * \return the process address space size
     */
    uint32_t pctGetProcessAddressSpaceSize(uint32_t pid);

// ================================================================================== //

    /**
     * \brief Get process execution memory address
     * \param [in] pid PID of the process
     * \return the process execution memory address
     */
    void *pctGetProcessMemAddress(uint32_t pid);

// ================================================================================== //

    /**
     * \brief Set process execution memory address
     * \param [in] pid PID of the process
     * \param [in] memAddr The process execution memory address
     */
    void pctSetProcessMemAddress(uint32_t pid, void *memAddr);

// ================================================================================== //

    /**
     * \brief Set process state
     * \param [in] pid PID of the process
     * \param [in] state The process new state
     */
    void pctSetProcessState(uint32_t pid, ProcessState state);

// ================================================================================== //

    /**
     * \brief Set process start time
     * \param [in] pid PID of the process
     * \param [in] time The process start time
     */
    void pctSetProcessStartTime(uint32_t pid, uint32_t time);

// ================================================================================== //

    /**
     * \brief Return the process state as a string
     * \param [in] pid PID of the process
     * \return The process state as a string
     */
    const char *pctGetStateName(uint32_t pid);

// ================================================================================== //

    /**
     * \brief Return the state as a string
     * \param [in] state The state to be returned as a string
     * \return The process state as a string
     */
    const char *pctStateAsString(ProcessState state);

// ================================================================================== //

    /**
     * \brief Enable/Disable the binary version of the \c pct functions
     * \details
     *   - 
     *
     * \param [in] state New state: \c true to enable; \c false to disable
     */
    void pctSetBinaryMode(bool state);

// ================================================================================== //

    /** @} */

};

#endif /* __SOMM22_PCT__ */

