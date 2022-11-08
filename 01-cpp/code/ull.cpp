/*
 *
 * \author (2016) Artur Pereira <artur at ua.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "ull.h"

namespace ull
{
    /* ************************************************* */

    /* The information support data structure  */
    struct Register
    {
        uint32_t nmec;       //!< student number
        const char *name;    //!< student name
    };

    /* The linked-list support data structure */
    struct Node 
    {
        Register reg;
        struct Node *next;
    };

    static Node *head = NULL;

    /* ************************************************* */

    void reset()
    {
		Node *pointer = head;
		while(pointer != NULL)
		{
			Node *temp = pointer -> next;
			free((void*)pointer -> reg.name);
			free(pointer);
			pointer = temp;
		}
		head = NULL;
    }

    /* ************************************************* */

    void load(const char *fname)
    {
		FILE *pointer = fopen(fname, "r");
		if(pointer == NULL)
		{
			fprintf(stderr, "File can't be opened!");
		}else{
			ssize_t read;
			int linecount = 1;
			size_t len = 0;
			char *line = NULL;
			while((read = getline(&line, &len, pointer) != -1))
			{
				char *name = new char[50];
				int32_t nmec;
				
				sscanf(line, "%[^;]; %d\n", name, &nmec);
				if(name != NULL)
				{
					insert(nmec, name);
				}
				else{
					fprintf(stderr, "Error reading file, line = %d\n", linecount);
				}
				delete name;
				linecount++;
			}
			delete line;
			fclose(pointer);
		}
    }

    /* ************************************************* */

    void print()
    {
		Node *current = head;
		while(current != NULL)
		{
			printf("{%d , %s}", current->reg.nmec, current->reg.name);
			current = current->next;
		}
    }

    /* ************************************************* */

    void insert(uint32_t nmec, const char *name)
    {
		//edge cases
		if(head == NULL || head->reg.nmec > nmec)
		{
			Node *temp = NULL;
			if(head != NULL && head->reg.nmec > nmec) temp = head;
			head = new Node();
			head->reg.nmec = nmec;
			head->reg.name = strdup(name);
			head->next = temp;
			return;
		}
		Node* pointer = head;
		while(pointer != NULL)
		{
			//insert into end
			if(pointer->next == NULL)
			{
				pointer->next = new Node();
				pointer->next->reg.name = strdup(name);
				pointer->next->reg.nmec = nmec;
				return;
			}
			
			//insert into middle
			if(pointer->next->reg.nmec > nmec)
			{
				Node *temp = pointer->next;
				pointer->next = new Node();
				pointer->next->reg.name = strdup(name);
				pointer->next->reg.nmec = nmec;
				pointer->next->next = temp;
				return;
			}
			pointer = pointer->next;
		}
    }

    /* ************************************************* */

    const char *query(uint32_t nmec)
    {
		Node *pointer = head;
		while(pointer != NULL)
		{
			if(pointer->reg.nmec == nmec)
			{
				return strdup(pointer->reg.name);	
			}
			pointer = pointer->next;
		}
        return NULL;
    }

    /* ************************************************* */

    void remove(uint32_t nmec)
    {
		//base cases
		if(head == NULL)
		{
			fprintf(stderr, "No students!");
			return;
		}
		
		if(head->reg.nmec == nmec)
		{
			Node *temp = head->next;
			free((void*)head->reg.name);
			free(head);	
			head = temp;
			return;
		}
		
		//middle case
		Node *pointer = head;
		while(pointer->next != NULL)
		{
			if(pointer->next->reg.nmec == nmec)
			{
				Node *temp = pointer->next->next;
				free((void*)pointer->next->reg.name);
				free(pointer->next);
				pointer->next = temp;
				return;	
			}
			pointer = pointer->next;
		}
		fprintf(stderr, "Student not found!");
    }

    /* ************************************************* */

}
