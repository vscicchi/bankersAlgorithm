// The Banker's Algorithm
#include <stdio.h>

int main() {
  // Setting variables for algorithm
  int n = 5; // Number of processes
  int r = 3; // Number of resource types (A, B, and C)
  
  // Setting the current allocation size of each process and resource (2D Array)
  int allocation[5][3] = {{0, 1, 0}, // P0
                          {2, 0, 0}, // P1
                          {3, 0, 2}, // P2
                          {2, 1, 1}, // P3
                          {0, 0, 2}}; // P4
  
  // Setting maximum allocation for each process/resource (2D Array)
  int maximum[5][3] = {{7, 5, 3}, // P0
                       {3, 2, 2}, // P1
                       {9, 0, 2}, // P2
                       {2, 2, 2}, // P3
                       {4, 3, 3}}; // P4
  
  // Setting avaliable resources
  int avaliable[3] = {3, 3, 2};
  
  int finished[n], ans[n], ind = 0;
  for (k = 0; k < n; k++) {
    finished[k] = 0;
  }
  
  // Determine the resource need by each process (need = maximum - current allocation)
  int needed[n][m];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      needed[i][j] = maximum[i][j] - allocation[i][j];
  }
  
  // Determine the safety of each process and resource allocation
  int y = 0;
  for (k = 0; k < 5; k++) { // Need to loop five times for each process
    for (i = 0; i < n; i++) { // Each process
      if (finished[i] == 0) { If the process hasn't completed its operation (0 = false, 1 = true)
        int flag = 0; // Reset flag after every loop
        for (j = 0; j < m; j++) { // Loop for each resource
          if (need[i][j] > avaliable[j]) { // If needed resources cannot be allocated in full
            flag = 1; // Flag the process as unsafe
            break;
          }
        }
        if (flag = 0) { // If no unsafe detections in resources
          ans[ind++] = i; // Add process to the safe sequence (if full system will be safe at the end)
          for (y = 0; y < m; y++)
            avaliable[y] += alloc[i][y]; // The process returns its allocation to make them avaliable again
          finished[i] = 1; // The process has finished and its resources have been returned
        }
      }
    }
  }

  // Determine if whole system isn't in a safe state
  int flag = 1;
  for (int i = 0; i < n; i++) {
    if (f[i] == 0) { // If every process hasn't finished its execution, the system isn't safe
      flag = 0;
      printf("The System isn't in a Safe State!");
      break;
    }
  }
  if (flag == 1) { // If the whole system is safe
    printf("Safe Sequence:\n");
    for (int i = 0; i < n - 1; i++)
      printf("P%d ->", ans[i]); // %d = ans[i]
    printf(" P%d", ans[n - 1]); // Print last process in sequence
  }
  return(0);
}
