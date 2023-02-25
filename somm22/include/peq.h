/**
 * \defgroup peq Process Event Queue (peq)
 *
 * \details 
 *   During a simulation, two type of events can occur:
 *   - the arrival of a process;
 *   - the termination of execution of a process that is running.
 *
 *   The Process Event Queue (\c peq) module is responsible for storing these events and
 *   allowing them to be accessed in chronological order.
 *
 *   <b>It is up to the implementer to decide which data structure to use, 
 *   as long as, at least, the following information is present</b>:
 *   - the time at which the event will occur;
 *   - the type of event, being one of arrival (\c ARRIVAL) or termination (\c TERMINATE);
 *   - the identification of the associated process (\c PID).
 *
 *   The interface of this module is predefined, being composed of the following functions:
 *   <table>
 *   <tr> <th> \c function <th align="center"> function ID <th>role
 *   <tr> <td> \c peqSetBinaryMode <td align="center"> 300 <td> Enable/Disable the binary version of \c peq functions;
 *   <tr> <td> \c peqInit <td align="center"> 301 <td> initializes the support internal data structure;
 *   <tr> <td> \c peqLog <td align="center"> 302 <td> logs the internal state of the process event queue.
 *   <tr> <td> \c peqLogEvent <td align="center"> 302 <td> logs the given event.
 *   <tr> <td> \c peqPrint <td align="center"> 302 <td> prints the internal state of the process event queue.
 *   <tr> <td> \c peqIsEmpty <td align="center"> 303 <td> indicates if the queue is empty;
 *   <tr> <td> \c peqInsert <td align="center"> 304 <td> inserts a new event in the queue;
 *   <tr> <td> \c peqPeekNext <td align="center"> 305 <td> Peeks first event covered by mask;
 *   <tr> <td> \c peqFetchNext <td align="center"> 305 <td> Fetches first event covered by mask ;
 *   <tr> <td> \c peqGetFirstPostponedProcess <td align="center"> 306 <td> returns the pid of the first postponed process;
 *   <tr> <td> \c peqEventTypeAsString <td align="center"> 397 <td> returns the given event type as a string
 *   <tr> <td> \c peqEventMaskAsString <td align="center"> 397 <td> returns the given event mask as a string
 *   </table>
 *
 *  \author Artur Pereira - 2022
 */

#ifndef __SOMM22_PEQ__
#define __SOMM22_PEQ__

namespace somm22
{

    /** @{ */

// ================================================================================== //

    /**
     * \brief Type of events
     * \details
     *   - Type ANY is used in the peek and pop operations to specify any type
     */
    enum EventType { 
        ARRIVAL = 0b001,   ///< The arrival of a process to the system
        POSTPONED = 0b010, ///< Due to lack of memory the event was postponed
        TERMINATE = 0b100  ///< A running process terminates its execution
    };

// ================================================================================== //

    /**
     * \brief Process Event Queue entry
     * \details
     *   - The support register to implement the queue
     */
    struct Event 
    {
        uint32_t eventTime; ///< Time at which event will occur
        EventType eventType; ///< Type of the event
        uint32_t pid; ///< Identification of the process
    };

// ================================================================================== //

    /**
     * \brief Initializes the internal data structure
     * \details
     *   - It is up to the implementer to decide which data structure to use,
     *     and initialize it accordingly
     *
     * \param [in] fname Path to the file containing the simulation data
     */
    void peqInit(const char *fname);

// ================================================================================== //

    /**
     * \brief Log the internal state of the process event queue
     * \id 302
     * \effort ...
     * \details
     *
     */
    void peqLog();

// ================================================================================== //

    /**
     * \brief Log the given event
     * \id 302
     * \effort ...
     * \details
     * \param [in] e Pointer to the event object to log
     * \param [in] msg Message to print before the event data
     */
    void peqLogEvent(Event *e, const char *msg = "Event");

// ================================================================================== //

    /**
     * \brief Prints the internal state of the process event queue
     * \details
     *   - If print mode is NEW, print to a new file (zapping if necessary)
     *   - If print mode is APPEND, append printing to the end of the file
     *
     * \param [in] fname Path to file where printing must be written to
     * \param [in] mode How to print (one of peq::NEW or peq::APPEND)
     */
    void peqPrint(const char *fname, PrintMode mode);

// ================================================================================== //

    /**
     * \brief Indicates the emptiness state of the queue
     * \details 
     *   - If type is 0, returns \c true if the whole queue is empty;
     *   - Otherwise, returns \c true if no event covered by \c mask exist.
     *   
     * \param [in] mask Bitwise-or of the types to be considered
     */
    bool peqIsEmpty(uint32_t mask = 0);

// ================================================================================== //

    /**
     * \brief Inserts an entry in queue
     * \param [in] type The type of event to be inserted (one of ARRIVAL, TERMINATE)
     * \param [in] time Time at which event will occur
     * \param [in] pid Id of process associated to the event
     */
    void peqInsert(EventType type, uint32_t time, uint32_t pid);

// ================================================================================== //

    /**
     * \brief Peek the first event covered by given mask
     * \details
     *   - The event is <b>not</b> removed from the queue
     *   - throws an exception if no event exists
     * \param [in] mask Bitwise-or of the types to be considered
     * \return The first entry covered by mask
     */
    Event peqPeekNext(uint32_t mask);

// ================================================================================== //

    /**
     * \brief Fetch the first event covered by given mask
     * \details
     *   - The event is removed from the queue
     *   - throws an exception if no event exists
     * \param [in] mask Bitwise-or of the types to be considered
     * \return The first entry covered by mask
     */
    Event peqFetchNext(uint32_t mask);

// ================================================================================== //

    /**
     * \brief Get PID of first postponed process 
     * \return The PID of the first postponed process or zero if no postponed process exist
     */
    uint32_t peqGetFirstPostponedProcess();

// ================================================================================== //

    /**
     * \brief Return the given event type as a string
     * \param type The event type
     * \return The event type as a string
     */
    const char *peqEventTypeAsString(EventType type);

// ================================================================================== //

    /**
     * \brief Return the given event mask as a string
     * \param mask The event mask
     * \return The event mask as a string
     */
    const char *peqEventMaskAsString(uint32_t mask);

// ================================================================================== //

    /**
     * \brief Enable/Disable the binary version of the \c peq functions
     * \details
     *   - 
     *
     * \param [in] state New state: \c true to enable; \c false to disable
     */
    void peqSetBinaryMode(bool state);

// ================================================================================== //

    /** @} */

};


#endif /* __SOMM22_PEQ__ */

