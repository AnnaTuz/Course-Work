#include <stdio.h>
#include "menu.h"

#define ITEMS_AMOUNT 10
#define ITEM_MAX_LENGTH 110
#define MENU_WIDTH 120

char menu_items[ITEMS_AMOUNT][ITEM_MAX_LENGTH] = {
        "Choose wanted command",
        "1. Add patient to the list",
        "2. Delete patient from the list",
        "3. Change patient's data",
        "4. Output full list",
        "5. Output patient's data",
        "6. Output debtors",
        "7. Delete patients, if they haven't debt",
        "8. Sort list by debts",
        "0. Exit",
};

void print_head() {
    printf("| Patient'sName |");
    printf("|  CardNumber  |");
    printf("| ProcedureType |");
    printf("| CostOfProcedure, hryvna |");
    printf("|  Repayment, hryvna  |");
    printf("|   Debt, hryvna   |");
}

void print_line(unsigned len) {
    printf("\n");
    for (unsigned i = 0; i < len; i++)
        printf("-");
}

void print_line_to_file(unsigned len, FILE *f) {
    if (!f)
        return;

    fprintf(f, "\n");
    for (unsigned i = 0; i < len; i++)
        fprintf(f, "-");
}

void print_menu() {
    printf("\n");
    print_line(MENU_WIDTH);
    printf("\n\t%s", menu_items[0]);
    print_line(MENU_WIDTH);

    for (int i = 1; i < ITEMS_AMOUNT; i++)
        printf("\n\t%s", menu_items[i]);

    print_line(MENU_WIDTH);
    printf("\n");
}

MenuElement scan_command() {
    printf("Input command number-> ");
    unsigned command;
    scanf("%u", &command);
    return command <= ITEMS_AMOUNT ? command : 10;
}

void press_to_continue() {
    printf("Click Enter to continue... ");
    getchar();
    while (getchar() != '\n') {}
}
