#include <iostream>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>

using namespace std;
#define CHANNEL 3

// main
int main(int argc, char* argv[]) {		// argv[0] = program name
	int pro = atoi(argv[1]);		// get total process number
	int filter_num, row, col;
	int**** filter;
	int*** inArray;
	int*** outArray;
	int inputX, inputY;
	string file_name;
	string nw = "output";


	// input number of filter, row, column
	cin >> filter_num >> row >> col;
	if (row<0 || row>100) {
		cout<<"Wrong filter row condition!"<<endl;
		return -1;
	}
	else if (col<0 || col>100) {
		cout<<"Wrong filter column condtion!"<<endl;
		return -1;
	}

	// filter array memory allocation
	filter = new int***[filter_num];
	for (int i=0; i<filter_num; i++) {
		filter[i] = new int**[CHANNEL];
		for (int j=0; j<CHANNEL; j++) {
			filter[i][j] = new int*[row];
			for (int k=0; k<row; k++) {
				filter[i][j][k] = new int[col];
			}
		}
	}


	// cin filter
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<CHANNEL; j++) {
			for (int k=0; k<row; k++) {
				for (int l=0; l<col; l++) {
					cin >> filter[i][j][k][l];
				}
			}
		}
	}

	// get input data row, column
	cin >> inputX >> inputY;
	if (inputX<0 || inputX>20000) {
		cout<<"Wrong input row condtion!"<<endl;
		return -1;
	}
	else if (inputY<0 || inputY>20000) {
		cout<<"Wrong input column condition!"<<endl;
		return -1;
	}

	// variables for division of filters to each processes
	int div = (filter_num / pro);
	int remain = (filter_num % pro);

	// input array memory allocation
	inArray = new int**[CHANNEL];
	for (int i=0; i<CHANNEL; i++) {
		inArray[i] = new int*[inputX];
		for (int j=0; j<inputX; j++) {
			inArray[i][j] = new int[inputY];
		}
	}

	// cin input data
	for (int i=0; i<CHANNEL; i++) {
		for (int j=0; j<inputX; j++) {
			for (int k=0; k<inputY; k++) {
				cin>> inArray[i][j][k];
			}
		}
	}

	// variable for process input file name
	string name;
	int stk = 0;
	int fstk = 0;
	// divide filters to use in each processes
	// the number of filters < the number of processes
	if (div == 0) {
		for (int i=0; i<remain; i++) {
			pro = remain;					// reduce process number because we do not have that many filters
			name = to_string(i);
			ofstream outFile(name);

			outFile << "1" << " " << row << " " << col << "\n";	
			for (int j=0; j<CHANNEL; j++) {
				for (int k=0; k<row; k++) {
					for (int l=0; l<col; l++) {
						outFile << filter[i][j][k][l] << " ";
					}
					outFile << "\n";
				}
			}

			outFile << inputX << " " << inputY << "\n";
			for (int j=0; j<CHANNEL; j++) {
				for (int k=0; k<inputX; k++) {
					for (int l=0; l<inputY; l++) {
						outFile << inArray[j][k][l] << " ";
					}
					outFile << "\n";
				}
			}
			outFile.close();
		}
	}
	// the number of filters > the number of processes
	else {
		for (int i=0; i<pro; i++) {
			name = to_string(i);
			ofstream outFile(name);
			int num = div;
			if (stk < remain) {
				num++;							// if there is remain, process gets one more filter
				stk++;
			}

			outFile << num << " " << row << " " << col << "\n";
			for (int j=0; j<num; j++) {
				for (int k=0; k<CHANNEL; k++) {
					for (int l=0; l<row; l++) {
						for (int m=0; m<col; m++) {
							outFile << filter[fstk][k][l][m] << " ";
						}
						outFile << "\n";
					}
				}
				fstk++;
			}

			outFile << inputX << " " << inputY << "\n";
			for (int j=0; j<CHANNEL; j++) {
				for (int k=0; k<inputX; k++) {
					for (int l=0; l<inputY; l++) {
						outFile << inArray[j][k][l] << " ";
					}
					outFile << "\n";
				}
			}
			outFile.close();
		}
	}

	// Start Time
	auto start123 = chrono::high_resolution_clock::now();

	// Process allocation
	int statloc;
	pid_t *pid = new pid_t[pro];

	// execute program1 in each processes
	for (int i=0; i<pro; i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			int in, out;
			char program[] = "./program1";
			char* const args[] = {program, NULL};
			// open input and output files
			string file_name1 = to_string(i);
			string file_name2 = to_string(i)+nw;

			in = open(file_name1.c_str(), O_RDONLY);
			out = open(file_name2.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

			// replace standard input with input file
			dup2(in, 0);

			// replace standard output with output file
			dup2(out, 1);

			// close unused file descriptors
			close(in);
			close(out);

			// execute program 1
			execvp("./program1", args);
		}
	}
	
	// wait for child process to end
	for (int i=0; i<pro; i++) {
		if(pid[i]>0) {
			pid_t got_pid= waitpid(pid[i],&statloc,0);
		}
	}

	// End Time
	auto end123 = chrono::high_resolution_clock::now();
	chrono::duration<long, milli> diff = chrono::duration_cast<chrono::milliseconds>(end123-start123);

	// allocate memory for output 
	outArray = new int**[filter_num];
	for (int i=0; i<filter_num; i++) {
		outArray[i] = new int*[(inputX+3-row)];
		for (int j=0; j<(inputX+3-row); j++) {
			outArray[i][j] = new int[inputY+3-col];
		}
	}

	// add the result of each processes
	int outstack = 0;
	int* t = new int[pro];

	for (int i=0; i<pro; i++) {
		file_name = to_string(i) + nw;
		ifstream readFile;	
		readFile.open(file_name);			// open the ith process result txt
		if (readFile.is_open()) {			// if it is open
			if (i>(remain-1)) {
				for (int j=0; j<div; j++) {
					for (int k=0; k<(inputX+3-row); k++) {
						for (int l=0; l<(inputY+3-col); l++) {
							readFile >> outArray[outstack][k][l];		// get output data
						}
					}
					outstack++;
				}
				// store the time value for each processes
				readFile >> t[i];
			}
			else {
				for (int j=0; j<(div+1); j++) {
					for (int k=0; k<(inputX+3-row); k++) {
						for (int l=0; l<(inputY+3-col); l++) {
							readFile >> outArray[outstack][k][l];		// get output data
						}
					}
					outstack++;
				}
				// store the time value for each processes
				readFile >> t[i];
			}
		}
		readFile.close();
	}

	// show output
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<(inputX+3-row); j++) {
			for (int k=0; k<(inputY+3-col); k++) {
				cout << outArray[i][j][k] << " ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	// get time value for each processes
	for (int i=0; i<pro; i++) {
		cout<<t[i]<<" ";
	}
	// total calculation time
	cout<<endl<<diff.count()<<endl;


	// Remove the temporary files
	for (int i=0; i<pro; i++) {
		file_name = to_string(i); 
		const int nResult = remove(file_name.c_str());
		if (nResult != 0) {
			cout<<"File remove fail!"<<endl;
			return -1;
		}
	}
	for (int i=0; i<pro; i++) {
		file_name = to_string(i) + nw;
		const int nResult = remove(file_name.c_str());
		if (nResult != 0) {
			cout<<"File remove fail!"<<endl;
			return -1;
		}
	}


	// free memory
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<(inputX+3-row); j++) {
			delete[] outArray[i][j];
		}
		delete[] outArray[i];
	}
	delete[] outArray;

	for (int i=0; i<CHANNEL; i++) {
		for (int j=0; j<inputX; j++) {
			delete[] inArray[i][j];
		}
		delete[] inArray[i];
	}
	delete[] inArray;

	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<CHANNEL; j++) {
			for (int k=0; k<row; k++) {
				delete[] filter[i][j][k];
			}
			delete[] filter[i][j];
		}
		delete[] filter[i];
	}
	delete[] filter;

	return 0;
}
