#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i;
    double salary = 0.0;
    double totalSalary = 0.0;
    double averageSalary;
    double highestSalary = 0.0;
    double lowestSalary = 0.0;

    if (employeeCount == 0) {
        printf("\nNo employee data available.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        salary = calculateSalary(Employees[i]);
        totalSalary += salary;

        if (i == 0 || salary > highestSalary) {
            highestSalary = salary;
        }
        if (i == 0 || salary < lowestSalary) {
            lowestSalary = salary;
        }
    }

    averageSalary = totalSalary / employeeCount;

    printf("\n============= EMPLOYEE REPORT ==============\n");
    printf("Total employees: %d\n", employeeCount);
    printf("Average salary: N$ %.2f\n", averageSalary);
    printf("Highest salary: N$ %.2f\n", highestSalary);
    printf("Lowest salary:  N$ %.2f\n", lowestSalary);
}

void budgetReport(void)
{
    int i;
    int exceeded = 0;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    double remaining;

    if (budgetCount == 0) {
        printf("\nNo budget data available.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocated;
        totalExpenditure += budgets[i].expenditure;
    }
    remaining = totalAllocated - totalExpenditure;

    printf("\n=================== BUDGET =====================\n");
    printf("Total Allocated Budget: N$ %.2f\n", totalAllocated);
    printf("Total Expenditure:      N$ %.2f\n", totalExpenditure);
    printf("Remaining Budget:       N$ %.2f\n", remaining);

    printf("\nDepartments Exceeding Budget:\n");
    for (i = 0; i < budgetCount; i++) {
        if (!isWithinBudget(budgets[i])) {
            printf("- %s (over by N$ %.2f)\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].allocated);
            exceeded++;
        }
    }
    if (exceeded == 0) {
        printf("None.\n");
    }
}

void supplierReport(void)
{
    printf("\n=============== SUPPLIER REPORT ================\n");
    printf("Registered Suppliers: %d\n", supplierCount);
    displaySuppliers();
}

void assetReport(void)
{
    printf("\n=============== ASSET REPORT ================\n");
    printf("Registered Assets: %d\n", assetCount);
    displayAssets();
}

void fullReport(void)
{
    printf("\n\n=========================================\n");
    printf("       MUNICIPAL FINANCIAL SUMMARY\n");
    printf("=========================================\n");

    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();

    printf("\n=========================================\n");
}

void reportsMenu(void)
{
    int choice;
    do {
        printf("\n==================== REPORTS ====================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Full Report\n");
        printf("6. Return to Main Menu\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n') {}
            continue;
        }
        while (getchar() != '\n') {}

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: fullReport();     break;
            case 6: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}