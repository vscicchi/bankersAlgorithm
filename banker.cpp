// Banker's Algorithm Project
// Vincent Scicchitano

#include <iostream>
#include <fstream>

void safe(int[], int[], int[][3], int[][3]);
const int p = 5, r = 3; // Constant number of processes/resource types

int main() {
	std::ifstream alloc("allocation.txt"), aval("avaliable.txt"), max("maximum.txt");

	int process[5] = { 0, 1, 2, 3, 4 };
	int allocation[p][r], avaliable[r], maximum[p][r]; // Setting up matrices for each table
	int num, countP = 0, countR = 0;

  // Load data from text files
	while (alloc >> num) {
		allocation[countP][countR] = num;
		if (countR == 2) {// Reset resources
			if (countP == 4)
				break;
			countR = 0;
			++countP;
		}
		else
			++countR;
	}

	countP = 0;
	countR = 0;

	while (max >> num) {
		maximum[countP][countR] = num;
		if (countR == 2) {// Reset resources
			if (countP == 4)
				break;
			countR = 0;
			++countP;
		}
		else
			++countR;
	}

	countR = 0;

	while (aval >> num) {
		avaliable[countR] = num;
		if (countR == 2) // Reset resources
			break;
		++countR;
	}

	countR = 0;
	int j = 0;

	// Done getting data, close files
	alloc.close();
	aval.close();
	max.close();

	// Execute function to determine if system is safe
	safe(process, avaliable, maximum, allocation);

	return 0;
}

void safe(int process[], int avaliable[], int maximum[][3], int allocation[][3]) {
	// Calculate the need of the processes ( Need = Max - Allocated )
	int need[p][r];

	for (int i = 0; i < p; ++i) {
		for (int j = 0; j < r; ++j) {
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}

	bool done[p] = {false}; // Need to determine if all processes have finished executing (returning their resources)
	int safeSequence[p]; // If the system is safe, sequences of processes exeecuting is stored here

	// Copy avaliable resources ( Don't modify avaliable array otherwise it will mess up the system)
	int work[3] = { avaliable[0], avaliable[1], avaliable[2] };

	int count = 0; // Loop through each process
	while (count < p) {
		// Need to find unfinished processes and see if they can finish
		// Determined by their current allocation, and the amount of resources currently avaliable
		bool found = false;
		for (int i = 0; i < p; ++i) {
			if (done[i] == 0) { // If a process is finished
				int j;
				for (j = 0; j < r; ++j)
					// If the needed resources for a given process > Avaliable resources
					//		The process cannot finish
					// Else, the process can finish and its allocation can be return to the OS
					if (need[i][j] > work[j])
						break;
				if (j == r) {
					for (int k = 0; k < r; ++k)
						work[k] += allocation[i][k];
					// Add the process to the safe sequence since it has finished
					safeSequence[count++] = i;
					done[i] = true; // Process has finished
					found = true;
				}
			}
		}

		// If there was no process to add to the safe sequence
		//    The system cannot be in a safe state
		if (!found) {
			std::cout << "System is not in a safe state";
			return; // Leave function
		}
	}

	// If all process have finished safely, output safe status and safe sequence
	std::cout << "System is in a Safe State!\nSafe Sequence: ";
	for (int i = 0; i < p; ++i) {
		if (i == p - 1)
			std::cout << "P" << safeSequence[i] << std::endl;
		else
			std::cout << "P" << safeSequence[i] << ", ";
	}
	return;
}
