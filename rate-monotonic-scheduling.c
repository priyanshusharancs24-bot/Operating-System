#include <stdio.h>
#include <math.h>

// Function to calculate GCD
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("1WA24CS223\n");

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst[20], period[20], rem_burst[20];

    printf("Enter the CPU burst times:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
    }

    printf("Enter the time periods:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &period[i]);
        rem_burst[i] = 0;
    }

    // Calculate LCM of all periods
    int total_time = period[0];
    for(int i = 1; i < n; i++) {
        total_time = lcm(total_time, period[i]);
    }

    printf("\nLCM = %d\n\n", total_time);

    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);
    }

    // Utilization check
    double utilization = 0;
    for(int i = 0; i < n; i++) {
        utilization += (double)burst[i] / period[i];
    }

    double bound = n * (pow(2.0, 1.0 / n) - 1.0);

    printf("\nUtilization = %.6f\n", utilization);
    printf("Bound = %.6f\n", bound);

    if (utilization <= bound)
        printf("Schedulable: TRUE\n");
    else
        printf("Schedulable: FALSE\n");

    printf("\nScheduling occurs for %d ms\n\n", total_time);

    int current_process = -1;

    for (int t = 0; t < total_time; t++) {

        // Release new jobs
        for (int i = 0; i < n; i++) {
            if (t % period[i] == 0) {
                rem_burst[i] = burst[i];
            }
        }

        // Find highest priority (smallest period)
        int highest_priority = -1;
        int min_period = 999999;

        for (int i = 0; i < n; i++) {
            if (rem_burst[i] > 0 && period[i] < min_period) {
                min_period = period[i];
                highest_priority = i;
            }
        }

        // Print only when process changes
        if (highest_priority != current_process) {
            if (highest_priority == -1)
                printf("%d ms onwards: CPU is idle\n", t);
            else
                printf("%d ms onwards: Process %d running\n", t, highest_priority + 1);

            current_process = highest_priority;
        }

        // Execute process
        if (current_process != -1) {
            rem_burst[current_process]--;
        }
    }

    return 0;
}

/*
OUTPUT

Enter the number of processes: 2
Enter the CPU burst times:
20 35
Enter the time periods:
50 100
  
1WA24CS223
Enter the number of processes: 2
Enter the CPU burst times:
20 35
Enter the time periods:
50 100

LCM = 100

Rate Monotone Scheduling:
PID     Burst   Period
1       20      50
2       35      100

Utilization = 0.750000
Bound = 0.828427
Schedulable: TRUE

Scheduling occurs for 100 ms

0 ms onwards: Process 1 running
20 ms onwards: Process 2 running
50 ms onwards: Process 1 running
70 ms onwards: Process 2 running
75 ms onwards: CPU is idle
*/
