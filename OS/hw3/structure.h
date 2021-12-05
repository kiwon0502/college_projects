#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <vector>
using namespace std;

typedef struct {
	int time;		// time that the code is scheduled
	int pid = -1;		// check the input's target pid
	char proc_name[20];	// process name
} Instruction;

typedef struct {
	char name[20];			// process name
	int pid;			// process ID
	int** set;			// [opcode] [argument]
	int inst_num;			// Instruction number
	int job_index = 0;		// index for how many jobs executed
	bool is_finish = false;		// true if (the process is end) == if (job_index == inst_num-1)
	int sleep_cycle = -1;		// if sleep_cycle = 0, process awakes
	bool sleep = false;		// true if the process is sleeping
	bool wait = false;		// true if the process is IO waiting
	int elapsed_time = 0;		// elapsed time after the process scheduled
	double cpu_burst = 0;		// T(n)
	double burst_num = 0;		// burst number : n
	bool is_first = true;		// check if the process bursted for the first time
	bool busy_waiting = false;	// check if the process is busy waiting
	int* pg_aid;			// page table (Allocation ID)
	int* pg_valid;			// page table (Valid bit)
} Process;

#endif
