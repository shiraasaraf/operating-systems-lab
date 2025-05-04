#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Recursive function to create the process tree based on the given array
void create_process_tree(int* tree, int size, int index) {
    // Each process prints its logical index, PID, and PPID
    printf("Process index = %d, PID = %d, PPID = %d\n", index, getpid(), getppid());

    int num_children = tree[index];     // Number of children for the current process
    int current_index = index + 1;      // Logical index of the next process in the array

    // Loop to create all children of the current process
    for (int i = 0; i < num_children; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            // Error occurred while forking
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process: continue building its own subtree
            create_process_tree(tree, size, current_index);
            exit(0); // Exit after finishing its own subtree
        } else {
            // Parent process: skip over the entire subtree of the child

            // Count descendants of the child (only direct children for simplicity)
            int descendants = 1;
            int sub_index = current_index;

            for (int j = 0; j < tree[sub_index]; j++) {
                descendants += 1; // Count each direct child
                sub_index++;
            }

            // Move to the next logical index for the next child
            current_index += descendants;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_children; i++) {
        wait(NULL);
    }
}

int main() {
    int size;

    // Get size of the process tree
    printf("Enter number of processes (nodes in tree): ");
    scanf("%d", &size);

    // Allocate dynamic memory for the tree array
    int* tree = malloc(size * sizeof(int));
    if (!tree) {
        perror("malloc failed");
        return 1;
    }

    // Get number of children for each process (level-order)
    printf("Enter number of children for each process (Level Order):\n");
    for (int i = 0; i < size; i++) {
        printf("Process %d: ", i);
        scanf("%d", &tree[i]);
    }

    printf("\n--- Creating process tree ---\n");

    // Start building the tree from the root (process index 0)
    create_process_tree(tree, size, 0);

    // Free allocated memory
    free(tree);
    return 0;
}

