#include <iostream>
#include <chrono>

using namespace std;
#define CHANNEL 3

// functions
int max(int a, int b);						// function for get max value
int relu(int x);						// RELU function

int main(int argc, char* argv[]) {
	int filter_num, row, col;
	int inputX, inputY;
	int**** filter;
	int*** inArray;
	int*** outArray;

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

	// input filter
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
					cin>> filter[i][j][k][l];
				}
			}
		}
	}


	// Allocate memory for input array
	// increase row, col by 2 to do zero-padding
	cin >> inputX >> inputY;
	if (inputX<0 || inputX>20000) {
		cout<<"Wrong input row condtion!"<<endl;
		return -1;
	}
	else if (inputY<0 || inputY>20000) {
		cout<<"Wrong input column condition!"<<endl;
		return -1;
	}

	inArray = new int**[CHANNEL];
	for (int i=0; i<CHANNEL; i++) {
		inArray[i] = new int*[inputX+2];
		for (int j=0; j<(inputX+2); j++) {
			inArray[i][j] = new int[inputY+2];
			for (int k=0; k<(inputY+2); k++) {
				inArray[i][j][k] = 0;
			}
		}
	}

	// Allcate memory for output array
	outArray = new int**[filter_num];
	for (int i=0; i<filter_num; i++) {
		outArray[i] = new int*[(inputX+3-row)];
		for (int j=0; j<(inputX+3-row); j++) {
			outArray[i][j] = new int[(inputY+3-col)];
		}
	}
	
	// input array
	for (int i=0; i<CHANNEL; i++) {
		for (int j=1; j<(inputX+1); j++) {
			for (int k=1; k<(inputY+1); k++) {
				cin>> inArray[i][j][k];
			}
		}
	}

	// Start Time
	auto start123 = chrono::high_resolution_clock::now();

	// Convolution calculation	
	// for each filter
	int sum;
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<CHANNEL; j++) {
			for (int k=0; k<(inputX+3-row); k++) {
				for (int l=0; l<(inputY+3-col); l++) {
					sum = 0;
					for (int a=0; a<row; a++) {
						for (int b=0; b<col; b++) {
							sum += inArray[j][k+a][l+b] * filter[i][j][a][b];
						}
					}
					outArray[i][k][l] += sum;
				}
			}
		}
	}

	// Apply ReLU function
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<(inputX+3-row); j++) {
			for (int k=0; k<(inputY+3-col); k++) {
				outArray[i][j][k] = relu(outArray[i][j][k]);
			}
		}
	}

	// End Time
	auto end123 = chrono::high_resolution_clock::now();
	chrono::duration<long, milli> diff = chrono::duration_cast<chrono::milliseconds>(end123-start123);

	// show result
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<(inputX+3-row); j++) {
			for (int k=0; k<(inputY+3-col); k++) {
				cout<<outArray[i][j][k]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	// total calculation time
	cout<<diff.count()<<endl;

	// free the memory for filter and inArray and outArray
	for (int i=0; i<filter_num; i++) {
		for (int j=0; j<(inputX+3-row); j++) {
			delete[] outArray[i][j];
		}
		delete[] outArray[i];
	}
	delete[] outArray;

	for (int i=0; i<CHANNEL; i++) {
		for (int j=0; j<(inputX+2); j++) {
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

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int relu(int x) {
	return max(0, x);
}
