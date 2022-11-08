#include "service.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdint.h>
#include <string.h>

#include "buffer.h"
#include "fifo.h"
#include "process.h"

namespace Service
{
#define N 10

	static Buffer::BUFFER *pool[N];
	static Fifo::FIFO *freeBuffers;
	static Fifo::FIFO *pendingRequests;
	
	void create()
	{
		freeBuffers = Fifo::create();
		pendingRequests = Fifo::create();
		
		for(int i = 0; i<N; i++)
			Fifo::in(*freeBuffers, i);
			
		for(int i = 0; i<N; i++)
			pool[i] = Buffer::create();
	}
	
	void destroy()
	{
		Fifo::destroy(*freeBuffers);
		Fifo::destroy(*pendingRequests);
		for(int i = 0; i<10; i++)
			Buffer::destroy(*pool[i]);
	}
	
	/*			FIFO Functions			*/
	
	static void produceResponse(
	
	
	
	
	
	
