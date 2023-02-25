/**
 * \defgroup mem Memory Management (mem)
 *
 * \details
 *   Initially, the memory is empty, meaning that no process address space is hosted there.
 *   Thus, memory can be seen as a single region with a given dimension.
 *   In order for a process to be executed, a block of memory must be assigned to it,
 *   which is used to host its address space. 
 *   For that, the initial empty region is divided into two blocks, one
 *   assigned to the process and another with the remaining empty part.
 *   If more processes have their address spaces hosted in memory, the empty part is
 *   successively divided.
 *
 *   A running process eventually terminates its execution.
 *   Then, its assigned block of memory can be released, becoming available to other processes.
 *   But, the most likely, such block is not contiguous to an empty region, 
 *   creating a hole in the memory.
 *   However, if the released block is contiguous to one or two holes, a merging must take place.
 *
 *   Thus, one can see the memory as a set of used blocks plus a set of available
 *   blocks, managing it with two lists:
 *   - a list of blocks allocated and assigned to processes;
 *   - a list of available (not used) blocks.
 *   Both lists must be sorted in such a way to facilitate their manipulation.
 *
 *   <b>It is up to the implementer to decide how to store these lists</b>.
 *
 *   The following policies must be available for the allocation algorithm:
 *   - <b>first fit</b>, in which the first, big enough block is used;
 *   - <b>next fit</b>, similar to the previous, but starting the search in the last used block;
 *   - <b>best fit</b>, in which the smallest, big enough block is used;
 *   - <b>worst fit</b>, in which the largest block is used.
 *
 *   In any case, if bigger than the size required, the block used must be divided into two,
 *   being the lowest part assigned to the process and the remaining part kept as an empty block.
 *   In order to minimize its external fragmentation, memory is managed in chunks bigger
 *   than a single byte.
 *   This means that the amount of memory assigned to the process is the round up
 *   of the required amount to the chunk size.
 *
 *   The interface of this module is predefined, being composed of the following functions:
 *   <table>
 *   <tr> <th> \c function <th align="center"> function ID <th>role
 *   <tr> <td> \c memSetBinaryMode <td align="center"> 400 <td> Enable/Disable the binary version of \c mem functions;
 *   <tr> <td> \c memInit <td align="center"> 401 <td> initializes the support internal data structure;
 *   <tr> <td> \c memLog <td align="center"> 402 <td> log the internal state of the lists, sorted in ascending order of memory address
 *   <tr> <td> \c memPrint <td align="center"> 402 <td> prints the internal state of the lists, sorted in ascending order of memory address
 *   <tr> <td> \c memAlloc <td align="center"> 403 <td> forwards to the appropriate allocation function, base on the active allocation policy;
 *   <tr> <td> \c memFirstFitAlloc <td align="center"> 404 <td> allocates a block of memory of the required size, using the first fit algorithm;
 *   <tr> <td> \c memNextFitAlloc <td align="center"> 405 <td> allocates a block of memory of the required size, using the next fit algorithm;
 *   <tr> <td> \c memBestFitAlloc <td align="center"> 406 <td> allocates a block of memory of the required size, using the best fit algorithm;
 *   <tr> <td> \c memWorstFitAlloc <td align="center"> 407 <td> allocates a block of memory of the required size, using the worst fit algorithm;
 *   <tr> <td> \c memFree <td align="center"> 408 <td> frees a previously allocated block of memory;
 *   <tr> <td> \c memGetBiggestHole <td align="center"> 409 <td> returns the size of the biggest hole;
 *   <tr> <td> \c memGetMaxAllowableSize <td align="center"> 409 <td> returns the maximum size allowable for the size of the address space of a process;
 *   <tr> <td> \c memAllocationPolicyAsString <td align="center"> 490 <td> returns the allocation policy as a string. given the policy
 *   </table>
 *
 *  \author Artur Pereira - 2022
 */


#ifndef __SOMM22_MEM__
#define __SOMM22_MEM__

#include <stdint.h>

namespace somm22
{

    /** @{ */

    /**
     * \brief Allocation policy
     * \details
     *   - ...
     */
    enum AllocationPolicy { FirstFit=0, NextFit, BestFit, WorstFit };

// ================================================================================== //

    /**
     * \brief Initialize the internal data structure
     * \details
     *   - It is up to the implementer to decide which data structure to use,
     *     and initialize it accordingly
     *
     * \param [in] memSize Total amount of memory available
     * \param [in] memSizeOS The amount of memory used by the operating system
     * \param [in] chunkSize The unit of allocation
     * \param [in] policy The allocation policy to be used
     */
    void memInit(uint32_t memSize, uint32_t memSizeOS, uint32_t chunkSize, AllocationPolicy policy);

// ================================================================================== //

    /**
     * \brief Log the internal state of the memory management module
     * \id 402
     * \effort ...
     * \details
     *
     */
    void memLog();

// ================================================================================== //

    /**
     * \brief Print the internal state of the memory management module
     * \details
     *   - If print mode is NEW, print to a new file (zapping if necessary)
     *   - If print mode is APPEND, append printing to the end of the file
     *
     * \param [in] fname Path to file where printing must be written to
     * \param [in] mode How to print (one of NEW or APPEND)
     */
    void memPrint(const char *fname, PrintMode mode);

// ================================================================================== //

    /**
     * \brief Allocate a block of memory of the given size
     * \details
     *   - forward function that calls the appropriate allocation function, base on the active allocation policy
     *   - the given amount of memory is round up to smallest multiple of chunk size
     *
     * \param [in] pid PID of the process requesting memory
     * \param [in] size Size of the block to be allocated
     */
    void *memAlloc(uint32_t pid, uint32_t size);

// ================================================================================== //

    /**
     * \brief Allocate a block of memory of the given size, using the first fit algorithm
     * \details
     *   - the given amount of memory is round up to smallest multiple of chunk size
     *
     * \param [in] pid PID of the process requesting memory
     * \param [in] size Size of the block to be allocated
     */
    void *memFirstFitAlloc(uint32_t pid, uint32_t size);

// ================================================================================== //

    /**
     * \brief Allocate a block of memory of the given size, using the next fit algorithm
     * \details
     *   - the given amount of memory is round up to smallest multiple of chunk size
     *
     * \param [in] pid PID of the process requesting memory
     * \param [in] size Size of the block to be allocated
     */
    void *memNextFitAlloc(uint32_t pid, uint32_t size);

// ================================================================================== //

    /**
     * \brief Allocate a block of memory of the given size, using the best fit algorithm
     * \details
     *   - the given amount of memory is round up to smallest multiple of chunk size
     *
     * \param [in] pid PID of the process requesting memory
     * \param [in] size Size of the block to be allocated
     */
    void *memBestFitAlloc(uint32_t pid, uint32_t size);

// ================================================================================== //

    /**
     * \brief Allocate a block of memory of the given size, using the worst fit algorithm
     * \details
     *   - the given amount of memory is round up to smallest multiple of chunk size
     *
     * \param [in] pid PID of the process requesting memory
     * \param [in] size Size of the block to be allocated
     */
    void *memWorstFitAlloc(uint32_t pid, uint32_t size);

// ================================================================================== //

    /**
     * \brief Free a block of memory
     * \details
     *   - if the freed block is contiguous to an empty block, merging must take place
     *
     * \param [in] addr Fisr address of the block to be freed
     */
    void memFree(void *addr);

// ================================================================================== //

    /**
     * \brief Get biggest hole
     * \details 
     *   - 
     * \return The size of the biggest block in the free list
     */
    uint32_t memGetBiggestHole();

// ================================================================================== //

    /**
     * \brief Get maximum allowable size for a process address space size
     * \details 
     *   - 
     * \return The maximum allowable size for a process address space size
     */
    uint32_t memGetMaxAllowableSize();

// ================================================================================== //

    /**
     * \brief Return the allocation policy as a string
     * \param policy The allocation policy
     * \return The allocation policy as a string
     */
    const char *memAllocationPolicyAsString(AllocationPolicy policy);

// ================================================================================== //

    /**
     * \brief Enable/Disable the binary version of the \c mem functions
     * \details
     *   - 
     *
     * \param [in] state New state: \c true to enable; \c false to disable
     */
    void memSetBinaryMode(bool state);

// ================================================================================== //

    /** @} */

};

#endif /* __SOMM22_MEM__ */


