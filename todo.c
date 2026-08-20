#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_TASKS 100
#define MAX_LENGTH 256


typedef struct {
    char description[MAX_LENGTH];
    int isCompleted; // 0 = not done, 1 = done
} Task;


Task tasks[MAX_TASKS];
int taskCount = 0;


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("List is full! Cannot add more tasks.\n");
        return;
    }

    printf("Enter task description: ");
    fgets(tasks[taskCount].description, MAX_LENGTH, stdin);
    
    // Remove the newline character added by fgets
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = '\0';
    
    tasks[taskCount].isCompleted = 0;
    taskCount++;
    
    printf("Task added successfully!\n");
}


void viewTasks() {
    if (taskCount == 0) {
        printf("The list is empty. Add a new task!\n");
        return;
    }

    printf("\n--- Your To-Do List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%c] %s\n", 
               i + 1, 
               tasks[i].isCompleted ? 'X' : ' ', 
               tasks[i].description);
    }
    printf("------------------------\n");
}


void completeTask() {
    int index;
    viewTasks();
    if (taskCount == 0) return;

    printf("Enter the task number to mark as completed: ");
    scanf("%d", &index);
    while(getchar() != '\n'); // Clear input buffer

    if (index >= 1 && index <= taskCount) {
        tasks[index - 1].isCompleted = 1;
        printf("Task #%d marked as completed!\n", index);
    } else {
        printf("Error: Invalid task number.\n");
    }
}

void deleteTask() {
    int index;
    viewTasks();
    if (taskCount == 0) return;

    printf("Enter the task number to delete: ");
    scanf("%d", &index);
    while(getchar() != '\n'); // Clear input buffer

    if (index >= 1 && index <= taskCount) {
        
        for (int i = index - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
        printf("Task #%d deleted.\n", index);
    } else {
        printf("Error: Invalid task number.\n");
    }
}


int main() {
    int choice;

    while (1) {
        clearScreen();
        printf("\n=== TO-DO LIST MENU ===\n");
        printf("1. Add task\n");
        printf("2. View tasks\n");
        printf("3. Mark as completed\n");
        printf("4. Delete task\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        
        scanf("%d", &choice);
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("Program finished. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
        
        printf("\nPress Enter to return to menu...");
        getchar(); 
    }
    return 0;
}