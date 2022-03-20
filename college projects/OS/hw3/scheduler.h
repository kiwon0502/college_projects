#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include "structure.h"
using namespace std;

typedef vector<Process*> procVector;
typedef vector<Instruction> Input_instruction;
typedef vector<pair<int, int>> IntPair;

// global variable
FILE* schedule_out;
FILE* memory_out;
procVector::iterator iter;
unsigned int input_pid;
const unsigned int time_quantum = 10;

// set lock table
IntPair lock_table;		// lock table : 1st element = process_pid, 2nd element = lock variable

// for memory access 
// vector for index which has available size for paging
vector<pair<int, int>> buddy_avail;
vector<int> frame_load;
vector<int> page_number;

class Scheduler {
private:
	unsigned int cycle;
	unsigned int event_index;		// index for what process to execute
	unsigned int proc_num;			// number of processes
	unsigned int event_num;			// number of instructions
	unsigned int soption;			// scheduling option
	unsigned int poption;			// paging option
	procVector proc;			// vector for processes
	procVector rq;				// vector for runQueue
	procVector Sl;				// vector for sleep list
	procVector IO;				// vector for IO wait list
	Input_instruction input;		// vector for input instructions
	Process* SP = NULL;			// Scheduled Process
	Process* RP = NULL;			// Running Process
	char* directory;			// Directory
	bool sch_finish = false;		// check if the scheduling is finish
	int buddy_size;
	int pg_size;
	int page_id = 1;
	int* buddy;
	int page_fault = 0;
	bool canaccess= true;
public:
	Scheduler(int num, int eventnum, int sopt, int popt, char* dir, Instruction* in, Process* proc, int bs, int ps);
	~Scheduler();
	void scheduling();
	void paging();
	void checkProcess();
	// execution function
	void allocation(int num);
	void access(int num);
	void release(int num);
	int findlocation(int num);
	bool checkExist();
	bool isbuddyempty();
	int findN(int num);
	// Scheduling Algorithm
	void FCFS();
	void RR();
	void SJF_simple();
	void SJF_EXP();
	// Paging Algorithm
	void FIFO();
	void LRU();
	void LRU_SAMPLED();
	void LFU();
	void MFU();
	void OPTIMAL();
	// output function
	void showInfo_schedule(FILE* file_dir);
	void showInfo_memory(FILE* file_dir);
};

//constructor
Scheduler::Scheduler(int num, int eventnum, int sopt, int popt, char* dir, Instruction* in, Process* process, int bs, int ps) {
	cycle = 1;
	event_index = 1;
	proc_num = num;
	event_num = eventnum;
	soption = sopt;
	poption = popt;
	directory = new char[100];
	strcpy(directory, dir);
	for (int i=0; i < event_num; i++) {
		input.push_back(in[i]);
	}

	for (int i=0; i< proc_num; i++) {
		proc.push_back(&process[i]);
	}
	// physical memory
	buddy_size = bs;
	buddy = new int[buddy_size];
	for (int i=0; i<buddy_size; i++) {
		buddy[i] = -1;
	}						// -1 for empty
	pg_size = ps;
}
//destructor
Scheduler::~Scheduler() {
	delete[] directory;
}

void Scheduler::scheduling() {
	// file open
	char* file_dir = new char[100];
	// scheduler.txt
	strcpy(file_dir, directory);
	strcat(file_dir, "scheduler.txt");
	schedule_out = fopen(file_dir, "w");

	// memory.txt
	strcpy(file_dir, directory);
	strcat(file_dir, "memory.txt");
	memory_out = fopen(file_dir, "w");
	
	switch(this->soption) {
		case 1:
			FCFS();
			break;	
		case 2:
			RR();
			break;
		case 3: 
			SJF_simple();
			break;
		case 4:
			SJF_EXP();
			break;
	}
	// page fault print
	fprintf(memory_out, "page fault = %d\n", page_fault);
	// file close
	fclose(schedule_out);
	fclose(memory_out);
}

void Scheduler::paging() {
	switch(this->poption) {
		case 1:
			FIFO();
			break;	
		case 2:
			LRU();
			break;
		case 3:
			LRU_SAMPLED();
			break;
		case 4:
			LFU();
			break;
		case 5: 
			MFU();
			break;
		case 6:
			OPTIMAL();
			break;
	}
}

// check if every Process is finished
void Scheduler::checkProcess() {
	for (int i=0; i<proc_num; i++) {
		if (proc[i]->is_finish) {
			sch_finish = true;
			continue;
		}
		else {
			sch_finish = false;
			break;
		} 
	}
}

void Scheduler::FCFS() {
	checkProcess();
	while(!sch_finish) {
		//check if there is a process to awake
		for (int i=0; i<Sl.size(); i++) {
			Sl[i]->sleep_cycle--;
			if (Sl[i]->sleep_cycle == 0) {
				// awake
				Sl[i]->sleep = false;
				// push to runQueue
				for (int j=0; j<proc_num; j++) {
					if (Sl[i]->pid == proc[j]->pid) {
						rq.push_back(proc[j]);
						// dequeue from the wait list
						iter = Sl.begin();
						iter += i;
						Sl.erase(iter);
					}
				}
			}				
		}
		// Scheduled Process
		// if input operation appears
		// if the input's time table is same with the cycle
		if (cycle == input[event_index-1].time || (cycle-1) == input[event_index-1].time) {
			// INPUT occurs
			if (!strcmp(input[event_index-1].proc_name, "INPUT")) {
				// check if io list has process
				for (int i=0; i<IO.size(); i++) {
					if (IO[i]->pid == input[event_index-1].pid) {
						rq.push_back(proc[input[event_index-1].pid]);
						// dequeue from the wait list
						iter = IO.begin();
						iter += i;
						IO.erase(iter);
					}
				}
			}
			// process input
			else if (input[event_index-1].pid == -1) {
				Process* p;
				for (int i=0; i<proc_num; i++) {
					if(!strcmp(proc[i]->name, input[event_index-1].proc_name)) {
						p = proc[i];
					}
				}
				// store at runQueue
				rq.push_back(p);
			}
			event_index++;
		}
		// Running Process
		// if there is no running process but runQueue element exits -> Schedule!
		if (RP == NULL && !rq.empty()) {
			iter = rq.begin();
			SP = rq[0];
			RP = SP;
			rq.erase(iter);
		}
		// Execution
		// untill process is finish
		if(RP!=NULL && !RP->is_finish) {
			switch(RP->set[RP->job_index][0]) {
				case 0: //memory allocation
					allocation(RP->set[RP->job_index][1]);
					break;
				case 1: //memory access
					access(RP->set[RP->job_index][1]);
					break;
				case 2: //memory release
					release(RP->set[RP->job_index][1]);
					break;
				case 3: //non-memory instruction
					break;
				case 4: //SLEEP
					RP->sleep_cycle = RP->set[RP->job_index][1];
					RP->sleep = true;
					break;
				case 5: //IO-wait
					RP->wait = true;
					break;
				case 6: //LOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i].second == RP->set[RP->job_index][1]) { // if the variable is already locked
							RP->busy_waiting = true;
							//RP->lock_var.push_back(RP->set[RP->job_index][1]);
						}
					}
					// if the variable is not in the table, include it
					if (!RP->busy_waiting) lock_table.push_back(make_pair(RP->pid, RP->set[RP->job_index][1]));
					break;
				case 7: //UNLOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i] == make_pair(RP->pid, RP->set[RP->job_index][1])) { // if the lock process pid and lock variable are concurrent
							for (int j=0; j<proc_num; j++) {
								if (proc[j]->busy_waiting && lock_table[i].second == proc[j]->set[proc[j]->job_index][1]) {
									// if the process is busy waiting because of the variable lock_table[i].second
									// release busy_waiting, and go to next instruction
									proc[j]->busy_waiting = false;
								}
							}
							vector<pair<int, int>>::iterator lock_table_iter = lock_table.begin();
							lock_table_iter += i;
							lock_table.erase(lock_table_iter);
						}
					}
					break;

			}
			// time elapsed
			RP->elapsed_time++;
			// check if the process is sleeping
			if (RP->sleep) {
				Sl.push_back(RP);
			}
			// check if the process is waiting
			else if (RP->wait) {
				IO.push_back(RP);
			}
			// check if the process is busy waiting
			else if (RP->busy_waiting) {
				RP->job_index--;
			}
			// Running process execution index + 1 
			RP->job_index++;
		}
		// print output
		showInfo_schedule(schedule_out);
		showInfo_memory(memory_out);

		// check if the process is finish
		if (RP != NULL && RP->job_index == RP->inst_num) RP->is_finish = true;
		// set SP, RP initial
		SP = NULL;
		// if IO wait
		if (RP!=NULL && RP->wait) {
			RP->wait = false;
			RP = NULL;
		}
		// if the running process is finished or sleeping
		else if (RP!=NULL) {
			if(RP->is_finish || RP->sleep)	RP = NULL;
		}
		// check if the programs ended
		checkProcess();
		cycle++;
	}
	return;
}

void Scheduler::RR() {
	checkProcess();
	while(!sch_finish) {
		//check if there is a process to awake
		for (int i=0; i<Sl.size(); i++) {
			Sl[i]->sleep_cycle--;
			if (Sl[i]->sleep_cycle == 0) {
				// awake
				Sl[i]->sleep = false;
				// push to runQueue
				for (int j=0; j<proc_num; j++) {
					if (Sl[i]->pid == proc[j]->pid) {
						rq.push_back(proc[j]);
						// dequeue from the wait list
						iter = Sl.begin();
						iter += i;
						Sl.erase(iter);
					}
				}
			}				
		}
		// Scheduled Process
		// if input operation appears
		// if the input's time table is same with the cycle
		if (cycle == input[event_index-1].time || (cycle-1) == input[event_index-1].time) {
			// INPUT occurs
			if (!strcmp(input[event_index-1].proc_name, "INPUT")) {
				// check if io list has process
				for (int i=0; i<IO.size(); i++) {
					if (IO[i]->pid == input[event_index-1].pid) {
						rq.push_back(proc[input[event_index-1].pid]);
						// dequeue from the wait list
						iter = IO.begin();
						iter += i;
						IO.erase(iter);
					}
				}
			}
			// process input
			else if (input[event_index-1].pid == -1) {
				Process* p;
				for (int i=0; i<proc_num; i++) {
					if(!strcmp(proc[i]->name, input[event_index-1].proc_name)) {
						p = proc[i];
					}
				}
				// store at runQueue
				rq.push_back(p);
			}
			event_index++;
		}
		// Running Process
		// if there is no running process but runQueue element exits => Schedule!
		if (RP == NULL && !rq.empty()) {
			iter = rq.begin();
			SP = rq[0];
			RP = SP;
			rq.erase(iter);
		}
		// Execution
		// untill process is finish
		if(RP!=NULL && !RP->is_finish) {
			switch(RP->set[RP->job_index][0]) {
				case 0: //memory allocation
					allocation(RP->set[RP->job_index][1]);
					break;
				case 1: //memory access
					access(RP->set[RP->job_index][1]);
					break;
				case 2: //memory release
					release(RP->set[RP->job_index][1]);
					break;
				case 3: //non-memory instruction
					break;
				case 4: //SLEEP
					RP->sleep_cycle = RP->set[RP->job_index][1];
					RP->sleep = true;
					break;
				case 5: //IO-wait
					RP->wait = true;
					break;
				case 6: //LOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i].second == RP->set[RP->job_index][1]) { // if the variable is already locked
							RP->busy_waiting = true;
							//RP->lock_var.push_back(RP->set[RP->job_index][1]);
						}
					}
					// if the variable is not in the table, include it
					if (!RP->busy_waiting) lock_table.push_back(make_pair(RP->pid, RP->set[RP->job_index][1]));
					break;
				case 7: //UNLOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i] == make_pair(RP->pid, RP->set[RP->job_index][1])) { // if the lock process pid and lock variable are concurrent
							for (int j=0; j<proc_num; j++) {
								if (proc[j]->busy_waiting && lock_table[i].second == proc[j]->set[proc[j]->job_index][1]) {
									// if the process is busy waiting because of the variable lock_table[i].second
									// release busy_waiting, and go to next instruction
									proc[j]->busy_waiting = false;
								}
							}
							vector<pair<int, int>>::iterator lock_table_iter = lock_table.begin();
							lock_table_iter += i;
							lock_table.erase(lock_table_iter);
						}
					}
					break;

			}
			// time elapsed
			RP->elapsed_time++;
			// check if the process is sleeping
			if (RP->sleep) {
				Sl.push_back(RP);
			}
			// check if the process is waiting
			else if (RP->wait) {
				IO.push_back(RP);
			}
			// check if the process is busy waiting
			else if (RP->busy_waiting) {
				RP->job_index--;
			}
			// Running process execution index + 1 
			RP->job_index++;
		}
		// print output
		showInfo_schedule(schedule_out);
		showInfo_memory(memory_out);

		// check if the process is finish
		if (RP != NULL && RP->job_index == RP->inst_num) RP->is_finish = true;
		// set SP, RP initial
		SP = NULL;
		// if IO wait
		if (RP!=NULL && RP->wait) {
			RP->wait = false;
			// initialize the elapsed time
			RP->elapsed_time = 0;
			RP = NULL;
		}
		else if (RP!=NULL) {
			// if the running process is finished or sleeping
			if(RP->is_finish || RP->sleep)	{
				// initialize the elapsed time
				RP->elapsed_time = 0;
				RP = NULL;
			}
			// if the time quantum is over
			else if (RP->elapsed_time == time_quantum) {
				// initialize the elapsed time
				RP->elapsed_time = 0;
				// store in runQueue
				rq.push_back(RP);
				RP = NULL;
			}
		}
		// check if the programs ended
		checkProcess();
		cycle++;
	}
	return;
}

void Scheduler::SJF_simple() {
	checkProcess();
	// S[n] : store for every process
	double* sT = new double[proc_num];
	for (int i=0; i<proc_num; i++) sT[i] = 0;
	double min = 0;
	int temp;
	bool _change = false;
	while(!sch_finish) {
		// check if there is a process to awake
		for (int i=0; i<Sl.size(); i++) {
			Sl[i]->sleep_cycle--;
			if (Sl[i]->sleep_cycle == 0) {
				// awake
				Sl[i]->sleep = false;
				// push to runQueue
				for (int j=0; j<proc_num; j++) {
					if (Sl[i]->pid == proc[j]->pid) {
						rq.push_back(proc[j]);
						// dequeue from the wait list
						iter = Sl.begin();
						iter += i;
						Sl.erase(iter);
					}
				}
			}				
		}
		// Scheduled Process
		// if input operation appears
		_change = false;
		if (cycle == input[event_index-1].time || (cycle-1) == input[event_index-1].time) {
			// INPUT occurs
			if (!strcmp(input[event_index-1].proc_name, "INPUT")) {
				// check if io list has process
				for (int i=0; i<IO.size(); i++) {
					if (IO[i]->pid == input[event_index-1].pid) {
						rq.push_back(proc[input[event_index-1].pid]);
						// dequeue from the wait list
						iter = IO.begin();
						iter += i;
						IO.erase(iter);
					}
				}
			}
			// process input
			else if (input[event_index-1].pid == -1) {
				Process* p;
				for (int i=0; i<proc_num; i++) {
					if(!strcmp(proc[i]->name, input[event_index-1].proc_name)) {
						p = proc[i];
						sT[p->pid] = 5;
					}
				}
				// if there is no running process
				// store at runQueue
				rq.push_back(p);
			}
			event_index++;
		}
		// Running Process
		// if there is no running process but runQueue element exits => Schedule!
		if (RP == NULL && !rq.empty()) {
			iter = rq.begin();
			min = sT[rq[0]->pid];
			for (int i=0; i<rq.size(); i++) {
				if (min > sT[rq[i]->pid]) {
					temp = i;
					_change = true;
				}
			}
			if (!_change) {
				SP = rq[0];
				RP = SP;
				rq.erase(iter);
			}
			else {
				min =sT[rq[temp]->pid];
				SP = rq[temp];
				RP = SP;
				iter += temp;
				rq.erase(iter);
			}
		}
		// if there is the process whose prediced burst time is minimum	=> Schedule!
		else if (RP != NULL && !rq.empty()) {
			iter = rq.begin();
			min = (sT[RP->pid] - RP->cpu_burst);
			for (int i=0; i<rq.size(); i++) {
				if (min > sT[rq[i]->pid]) {
					min =sT[rq[i]->pid];
					iter += i;
					SP = rq[i];
					rq.erase(iter);
					rq.push_back(RP);
					RP = SP;
					_change = true;
				}
			}
		}
		// Execution
		// untill process is finish
		if(RP!=NULL && !RP->is_finish) {
			switch(RP->set[RP->job_index][0]) {
				case 0: //memory allocation
					allocation(RP->set[RP->job_index][1]);
					break;
				case 1: //memory access
					access(RP->set[RP->job_index][1]);
					break;
				case 2: //memory release
					release(RP->set[RP->job_index][1]);
					break;
				case 3: //non-memory instruction
					break;
				case 4: //SLEEP
					RP->sleep_cycle = RP->set[RP->job_index][1];
					RP->sleep = true;
					RP->burst_num++;
					break;
				case 5: //IO-wait
					RP->wait = true;
					RP->burst_num++;
					break;
				case 6: //LOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i].second == RP->set[RP->job_index][1]) { // if the variable is already locked
							RP->busy_waiting = true;
							//RP->lock_var.push_back(RP->set[RP->job_index][1]);
						}
					}
					// if the variable is not in the table, include it
					if (!RP->busy_waiting) lock_table.push_back(make_pair(RP->pid, RP->set[RP->job_index][1]));
					break;
				case 7: //UNLOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i] == make_pair(RP->pid, RP->set[RP->job_index][1])) { // if the lock process pid and lock variable are concurrent
							for (int j=0; j<proc_num; j++) {
								if (proc[j]->busy_waiting && lock_table[i].second == proc[j]->set[proc[j]->job_index][1]) {
									// if the process is busy waiting because of the variable lock_table[i].second
									// release busy_waiting, and go to next instruction
									proc[j]->busy_waiting = false;
								}
							}
							vector<pair<int, int>>::iterator lock_table_iter = lock_table.begin();
							lock_table_iter += i;
							lock_table.erase(lock_table_iter);
						}
					}
					break;

			}
			// time elapsed, cpu_burst decrease
			RP->elapsed_time++;
			RP->cpu_burst++;
			// check if the process is sleeping
			if (RP->sleep) {
				if(RP->is_first) {
					sT[RP->pid] = RP->cpu_burst;
					RP->cpu_burst = 0;
					RP->is_first = false;
					Sl.push_back(RP);
				}
				else {
					sT[RP->pid] *= ((RP->burst_num - 1) / RP->burst_num);
					sT[RP->pid] += (RP->cpu_burst / RP->burst_num);
					RP->cpu_burst = 0;
					Sl.push_back(RP);
				}
			}
			// check if the process is waiting
			else if (RP->wait) {
				if(RP->is_first) {
					sT[RP->pid] = RP->cpu_burst;
					RP->cpu_burst = 0;
					RP->is_first = false;
					IO.push_back(RP);
				}
				else {
					sT[RP->pid] *= ((RP->burst_num - 1) / RP->burst_num);
					sT[RP->pid] += (RP->cpu_burst / RP->burst_num);			
					RP->cpu_burst = 0;
					IO.push_back(RP);
				}
			}
			// check if the process is busy waiting
			else if (RP->busy_waiting) {
				RP->job_index--;
			}
			// Running process execution index + 1 
			RP->job_index++;
		}
		// print output
		showInfo_schedule(schedule_out);
		showInfo_memory(memory_out);

		// check if the process is finish
		if (RP != NULL && RP->job_index == RP->inst_num) RP->is_finish = true;
		// set SP, RP initial
		SP = NULL;
		// if IO wait
		if (RP!=NULL && RP->wait) {
			RP->wait = false;
			RP = NULL;
		}
		// if the running process is sleeping
		else if (RP!=NULL && RP-> sleep) {
			RP = NULL;
		}
		// if the running process is finished or sleeping
		else if (RP!=NULL && RP->is_finish) {
			RP = NULL;
		}
		// check if the programs ended
		checkProcess();
		cycle++;
	}
	return;
}

void Scheduler::SJF_EXP() {
	checkProcess();
	// S[n] : store for every process
	double* sT = new double[proc_num];
	for (int i=0; i<proc_num; i++) sT[i] = 0;
	double min = 0;
	int temp;
	bool _change = false;
	const double alpha = 0.6;
	while(!sch_finish) {
		// check if there is a process to awake
		for (int i=0; i<Sl.size(); i++) {
			Sl[i]->sleep_cycle--;
			if (Sl[i]->sleep_cycle == 0) {
				// awake
				Sl[i]->sleep = false;
				// push to runQueue
				for (int j=0; j<proc_num; j++) {
					if (Sl[i]->pid == proc[j]->pid) {
						rq.push_back(proc[j]);
						// dequeue from the wait list
						iter = Sl.begin();
						iter += i;
						Sl.erase(iter);
					}
				}
			}				
		}
		// Scheduled Process
		// if input operation appears
		_change = false;
		if (cycle == input[event_index-1].time || (cycle-1) == input[event_index-1].time) {
			// INPUT occurs
			if (!strcmp(input[event_index-1].proc_name, "INPUT")) {
				// check if io list has process
				for (int i=0; i<IO.size(); i++) {
					if (IO[i]->pid == input[event_index-1].pid) {
						rq.push_back(proc[input[event_index-1].pid]);
						// dequeue from the wait list
						iter = IO.begin();
						iter += i;
						IO.erase(iter);
					}
				}
			}
			// process input
			else if (input[event_index-1].pid == -1) {
				Process* p;
				for (int i=0; i<proc_num; i++) {
					if(!strcmp(proc[i]->name, input[event_index-1].proc_name)) {
						p = proc[i];
						sT[p->pid] = 5;
					}
				}
				// store at runQueue
				rq.push_back(p);
			}
			event_index++;
		}
		// Running Process
		// if there is no running process but runQueue element exits => Schedule!
		if (RP == NULL && !rq.empty()) {
			iter = rq.begin();
			min = sT[rq[0]->pid];
			for (int i=0; i<rq.size(); i++) {
				if (min > sT[rq[i]->pid]) {
					temp = i;
					_change = true;
				}
			}
			if (!_change) {
				SP = rq[0];
				RP = SP;
				rq.erase(iter);
			}
			else {
				min =sT[rq[temp]->pid];
				SP = rq[temp];
				RP = SP;
				iter += temp;
				rq.erase(iter);
			}
		}
		// if there is the process whose prediced burst time is minimum	=> Schedule!
		else if (RP != NULL && !rq.empty()) {
			iter = rq.begin();
			min = (sT[RP->pid] - RP->cpu_burst);
			for (int i=0; i<rq.size(); i++) {
				if (min > sT[rq[i]->pid]) {
					min =sT[rq[i]->pid];
					iter += i;
					SP = rq[i];
					rq.erase(iter);
					rq.push_back(RP);
					RP = SP;
					_change = true;
				}
			}
		}
		// Execution
		// untill process is finish
		if(RP!=NULL && !RP->is_finish) {
			switch(RP->set[RP->job_index][0]) {
				case 0: //memory allocation
					allocation(RP->set[RP->job_index][1]);
					break;
				case 1: //memory access
					access(RP->set[RP->job_index][1]);
					break;
				case 2: //memory release
					release(RP->set[RP->job_index][1]);
					break;
				case 3: //non-memory instruction
					break;
				case 4: //SLEEP
					RP->sleep_cycle = RP->set[RP->job_index][1];
					RP->sleep = true;
					RP->burst_num++;
					break;
				case 5: //IO-wait
					RP->wait = true;
					RP->burst_num++;
					break;
				case 6: //LOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i].second == RP->set[RP->job_index][1]) { // if the variable is already locked
							RP->busy_waiting = true;
							//RP->lock_var.push_back(RP->set[RP->job_index][1]);
						}
					}
					// if the variable is not in the table, include it
					if (!RP->busy_waiting) lock_table.push_back(make_pair(RP->pid, RP->set[RP->job_index][1]));
					break;
				case 7: //UNLOCK
					for (int i=0; i<lock_table.size(); i++) {
						if (lock_table[i] == make_pair(RP->pid, RP->set[RP->job_index][1])) { // if the lock process pid and lock variable are concurrent
							for (int j=0; j<proc_num; j++) {
								if (proc[j]->busy_waiting && lock_table[i].second == proc[j]->set[proc[j]->job_index][1]) {
									// if the process is busy waiting because of the variable lock_table[i].second
									// release busy_waiting, and go to next instruction
									proc[j]->busy_waiting = false;
								}
							}
							vector<pair<int, int>>::iterator lock_table_iter = lock_table.begin();
							lock_table_iter += i;
							lock_table.erase(lock_table_iter);
						}
					}
					break;

			}
			// time elapsed, cpu_burst decrease
			RP->elapsed_time++;
			RP->cpu_burst++;
			// check if the process is sleeping
			if (RP->sleep) {
				if(RP->is_first) {
					sT[RP->pid] = RP->cpu_burst;
					RP->cpu_burst = 0;
					RP->is_first = false;
					Sl.push_back(RP);
				}
				else {
					sT[RP->pid] *= (1-alpha);
					sT[RP->pid] += RP->cpu_burst * alpha;
					RP->cpu_burst = 0;
					Sl.push_back(RP);
				}
			}
			// check if the process is waiting
			else if (RP->wait) {
				if(RP->is_first) {
					sT[RP->pid] = RP->cpu_burst;
					RP->cpu_burst = 0;
					RP->is_first = false;
					IO.push_back(RP);
				}
				else {
					sT[RP->pid] *= (1-alpha);
					sT[RP->pid] += RP->cpu_burst * alpha;		
					RP->cpu_burst = 0;
					IO.push_back(RP);
				}
			}
			// check if the process is busy waiting
			else if (RP->busy_waiting) {
				RP->job_index--;
			}
			// Running process execution index + 1 
			RP->job_index++;
		}
		// print output
		showInfo_schedule(schedule_out);
		showInfo_memory(memory_out);

		// check if the process is finish
		if (RP != NULL && RP->job_index == RP->inst_num) RP->is_finish = true;
		// set SP, RP initial
		SP = NULL;
		// if IO wait
		if (RP!=NULL && RP->wait) {
			RP->wait = false;
			RP = NULL;
		}
		// if the running process is sleeping
		else if (RP!=NULL && RP-> sleep) {
			RP = NULL;
		}
		// if the running process is finished or sleeping
		else if (RP!=NULL && RP->is_finish) {
			RP = NULL;
		}
		// check if the programs ended
		checkProcess();
		cycle++;
	}
	return;
}

void Scheduler::allocation(int num) {
	int index;
	// check which index is empty in the table
	for (int i=0; i<pg_size; i++) {
		if (RP->pg_aid[i] == -1) {
			index = i;
			break;
		}
	}
	// memory allocate, valid bit set 0
	for (int i=index; i<index+num; i++) {
		RP->pg_aid[i] = page_id;
		RP->pg_valid[i] = 0;
	}
	page_number.push_back(RP->set[RP->job_index][1]);
	page_id++;
}

void Scheduler::access(int num) {	// num : allocation id
	int U = findN(RP->set[RP->job_index][1]);
	int index;
	// if buddy is empty
	if (isbuddyempty()){
		for (int i=0; i<U; i++) {
			buddy[i] = RP->set[RP->job_index][1];
			for (int j=0; j<proc_num; j++) {
				for (int k=0; k<pg_size; k++) {
					if (proc[j]->pg_aid[k] == buddy[i]) {
						proc[j]->pg_valid[k] = 1;
					}
				}
			}
		}
		frame_load.push_back(RP->set[RP->job_index][1]);
		page_fault++;
	}
	else if (!checkExist()) {
		index = findlocation(RP->set[RP->job_index][1]);
		if (index != -1) {
			for (int i=0; i<U; i++) {
				buddy[i] = RP->set[RP->job_index][1];
				for (int j=0; j<proc_num; j++) {
					for (int k=0; k<pg_size; k++) {
						if (proc[j]->pg_aid[k] == buddy[i]) {
							proc[j]->pg_valid[k] = 1;
						}
					}
				}
			}
			frame_load.push_back(RP->set[RP->job_index][1]);
			page_fault++;
		}
		else {
			paging();
		}
	}	
}

void Scheduler::release(int num) {
	for (int i=0; i<buddy_size; i++) {
		if (buddy[i] == num) buddy[i] = -1;
	}
	for (int i=0; i<pg_size; i++) {
		if (RP->pg_aid[i] == num) {
			RP->pg_aid[i] = -1;
			RP->pg_valid[i] = -1;
		}
	}  
}

bool Scheduler::checkExist() {							// check if the page exists in the physical memory
	for (int i=0; i<proc_num; i++) {
		for(int j=0; j<pg_size; j++) {
			if (proc[i]->pg_aid[j] == RP->set[RP->job_index][1]) {
				if(proc[i]->pg_valid[j] == 1) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Scheduler::isbuddyempty() {
	for (int i=0; i<buddy_size; i++) {
		if (buddy[i] != -1) return false;
	}
	return true;
}

int Scheduler::findN(int num) {				// num : aid
	int n;
	for(int i=0; i <buddy_size; i++) {
		n = pow(2, i);
		if (n==buddy_size) return n;
		else if ((n/2) < page_number[num-1] && page_number[num-1] <= n) return n;
	}
	return 0;					// return size of buddies that covers the page
}

int Scheduler::findlocation(int num) {			// num : aid
	int U = findN(num);				// n
	int start, end, delta;
	start = -1;
	end = 0;
	for (int i=0; i<buddy_size; i++) {
		if (buddy[i] == -1) {			// empty buddy search
			if (start < 0) start = i;
			else end = i;
		}
		if (end != 0) {
			buddy_avail.push_back(make_pair(start, end));
			start = -1;
		}
	}
	for (int i=0; i<buddy_avail.size(); i++) {
		delta = buddy_avail[i].second - buddy_avail[i].first;
		if (delta >= U) return buddy_avail[i].first;
	}
	return -1;
}

void Scheduler::FIFO() {
	int start;
	int sw_out;
	int U = findN(RP->set[RP->job_index][1]);
	// first in
	sw_out = frame_load[0];

	for (int i=0; i<buddy_size; i++) {
		if (buddy[i] == sw_out) {
			buddy[i] = -1;							// swap out
		}
	}
	vector<int>::iterator itt = frame_load.begin();
	frame_load.erase(itt);

	page_fault++;
	start = findlocation(RP->set[RP->job_index][1]);
	for (int i=start; i<start + U + 1; i++) {
		buddy[i] = RP->set[RP->job_index][1];					// swap in
	}
	frame_load.push_back(RP->set[RP->job_index][1]);
	for (int i=0; i<proc_num; i++) {
		for (int j=0; j<pg_size; j++) {
			if (proc[i]->pg_aid[j] == sw_out) proc[i]->pg_valid[j] = 0;	// valid bit control
		}
	}	
}	

void Scheduler::LRU() {
}

void Scheduler::LRU_SAMPLED() {	
}

void Scheduler::LFU() {
}

void Scheduler::MFU() {	
}

void Scheduler::OPTIMAL() {
}

// print output function "scheduler.txt"
void Scheduler::showInfo_schedule(FILE* out) {
	if (out == NULL) {
		cout<<"scheduler.txt is not opened"<<endl;
	}
	else {	
		// Line 1
		fprintf(out, "[%d Cycle] Scheduled Process: ", cycle);
		if (SP!=NULL) {
			fprintf(out, "%d %s\n", SP->pid, SP->name);
		}
		else	fprintf(out, "None\n");

		// Line 2
		fprintf(out, "Running Process: ");
		if (RP!=NULL) {
			fprintf(out, "Process#%d running code %s line %d(op %d, arg %d)\n", RP->pid, RP->name, RP->job_index, RP->set[RP[0].job_index-1][0], RP->set[RP[0].job_index-1][1]);
		}
		else	fprintf(out, "None\n");

		// Line 3
		fprintf(out, "RunQueue: ");
		if (rq.empty()) {
			fprintf(out, "Empty");
		}
		else if (!rq.empty()){
			for (int i=0; i < rq.size(); i++)	fprintf(out, "%d(%s) ", rq[i]->pid, rq[i]->name);
		}
		fprintf(out, "\n");

		//Line 4
		fprintf(out, "SleepList: ");
		if (Sl.empty()) {
			fprintf(out, "Empty");
		}
		else if (!Sl.empty()){
			for (int i=0; i < Sl.size(); i++)	fprintf(out, "%d(%s) ", Sl[i]->pid, Sl[i]->name);
		}
		fprintf(out, "\n");

		// Line 5
		fprintf(out, "IOWait List: ");
		if (IO.empty()) {
			fprintf(out, "Empty");
		}
		else if (!IO.empty()) {
			for (int i=0; i < IO.size(); i++)	fprintf(out, "%d(%s) ", IO[i]->pid, IO[i]->name);
		}
		fprintf(out, "\n");

		fprintf(out, "\n");
	}
}

// print output function "memory.txt"
void Scheduler::showInfo_memory(FILE* out) {
	if (out == NULL) {
		cout<<"memory.txt is not opened"<<endl;
	}
	else {
		// instruction output
		int pgnum = 0;
		if (RP != NULL) {
			switch(RP->set[RP->job_index-1][0]) {	// which operation
				case 0: // memory allocation
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [ALLOCATION] Alloc ID[%d] Page Num[%d]\n", cycle, RP->pid, page_id - 1, RP->set[RP->job_index-1][1]);
					break;
				case 1: // memory access
					for (int i=0; i<pg_size; i++) {
						if (RP->pg_aid[i] == RP->set[RP->job_index-1][1]) pgnum++;
					}
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [ACCESS] Alloc ID[%d] Page Num[%d]\n", cycle, RP->pid, RP->set[RP->job_index-1][1], pgnum);
					break;
				case 2: // memory release
					for (int i=0; i<pg_size; i++) {
						if (RP->pg_aid[i] == RP->set[RP->job_index-1][1]) pgnum++;
					}
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [RELEASE] Alloc ID[%d] Page Num[%d]\n", cycle, RP->pid, RP->set[RP->job_index-1][1], pgnum);
					break;
				case 3: // Non-memory instruction
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [NOMEMORY]\n", cycle, RP->pid);
					break;
				case 4: // sleep
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [SLEEP]\n", cycle, RP->pid);
					break;
				case 5: // IO wait
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [IOWAIT]\n", cycle, RP->pid);
					break;
				case 6: // Lock
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [LOCK]\n", cycle, RP->pid);
					break;
				case 7: // Unlock
					fprintf(out, "[%d Cycle] Input : Pid [%d] Function [UNLOCK]\n", cycle, RP->pid);
					break;
				default:
					break;
			}
		}
		// no operation
		else if (RP == NULL) {
			fprintf(out,  "[%d Cycle] Input : Function [NO-OP]\n", cycle);
		}
		// physical memory output
		fprintf(out, "%-30s", ">> Physical Memory : ");
		for (int i=0; i<buddy_size; i++) {
			if (i%4 == 0) {
				fprintf(out, "|");
				if (buddy[i] == -1) fprintf(out, "-");
				else fprintf(out, "%d", buddy[i]);
			}
			else {
				if (buddy[i] == -1) fprintf(out, "-");
				else fprintf(out, "%d", buddy[i]);
			}
		}
		fprintf(out, "|\n");

		// each process virtual memory output
		for (int i=0; i<proc_num; i++) {
			if (!proc[i]->is_finish && proc[i]->job_index > 0) {
				fprintf(out, ">> pid(%d) %-20s", proc[i]->pid, "Page Table(AID) : ");
				for (int j=0; j<pg_size; j++) {
					if (j%4 == 0) {
						fprintf(out, "|");
						if (proc[i]->pg_aid[j] == -1) fprintf(out, "-");
						else fprintf(out, "%d", proc[i]->pg_aid[j]);
					}
					else {
						if (proc[i]->pg_aid[j] == -1) fprintf(out, "-");
						else fprintf(out, "%d", proc[i]->pg_aid[j]);
					}
				}
				fprintf(out, "|\n");

				fprintf(out, ">> pid(%d) %-20s", proc[i]->pid, "Page Table(Valid) : ");
				for (int j=0; j<pg_size; j++) {
					if (j%4 == 0) {
						fprintf(out, "|");
						if (proc[i]->pg_valid[j] == -1) fprintf(out, "-");
						else fprintf(out, "%d", proc[i]->pg_valid[j]);
					}
					else {
						if (proc[i]->pg_valid[j] == -1) fprintf(out, "-");
						else fprintf(out, "%d", proc[i]->pg_valid[j]);
					}
				}
				fprintf(out, "|\n");
			}
		}
		fprintf(out, "\n");
	}
}

#endif


