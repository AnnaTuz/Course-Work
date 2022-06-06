#include <stdlib.h>
#include <stdio.h>
#include "patientsList.h"
#include "menu.h"

List patients_list;

void executor(MenuElement command);

void delete_no_client(void);

void add_client(void);

void delete_client(void);

void get_client(void);

void print_all(void);

void print_debtors(void);

void modify_client(void);



int main() {

    while (1) {
        print_menu();
        MenuElement command = scan_command();
        executor(command);
    }
}

void executor(MenuElement command) {
    switch (command) {
        case EXIT:
            printf("\nProgram was stopped");
            destructor(&patients_list);
            exit(0);
        case DELETE_CLIENT:
            delete_client();
            break;
        case REMOVE_DEBTLESS:
            delete_no_client();
            break;
        case SORT_BY_DEBT:
            printf("\nFunction is developing");
            press_to_continue();
            break;
        case ADD_CLIENT:
            add_client();
            break;
        case PRINT_ALL:
            print_all();
            break;
        case PRINT_CLIENT:
            get_client();
            break;
        case PRINT_DEBTORS:
            print_debtors();
            break;
        case MODIFY_CLIENT:
            modify_client();
            break;
        default:
            printf("\nThere is no such command. Try again: ");
    }
}

void add_client() {
    printf("\nAdd client to list. Choose input method: \n1. From console\n2. From file\n");
    unsigned method;
    while (1) {
        scanf("%u", &method);

        if (method != 1 && method != 2)
            printf("There is no such command. Try again ");
        else
            break;
    }

    PatientData *data;

    if (method == 1) {
        Status status1 = write_from_console(&data);
        if (status1 == NULL_POINTER) {
            printf("\nНе вдалося прочитати інформацію.");
            return;
        }
    } else {
        printf("\nFunction is developing");
        return;
    }

    Status status = push(&patients_list, data);

    switch (status) {
        case OK:
            printf("\nPatient was added.");
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case ELEMENT_ALREADY_EXISTS:
            printf("\nSuch patient is already exists.");
            break;
        default:
            printf("\nUnknown Error.");
    }

    press_to_continue();
}

void delete_client() {
    printf("\nDelete client from list.");

    char name[150];
    printf("\nInput name \n");
    getchar();
    scanf("%s", name);
    ListNode *client;
    Status status = get_element_by_name(&patients_list, name, &client);
    pop(&patients_list);

    switch (status) {
        case OK:
            printf("\nPatient was deleted.");
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case ELEMENT_NOT_FOUND:
            printf("\nThere's no such patient with that name.");
            break;
        default:
            printf("\nUnknown Error.");
    }

    press_to_continue();
}
void delete_no_client() {
    printf("\nDelete no debt client from list.");

    Status status = delete_no_debtors(&patients_list);
    pop(&patients_list);

    switch (status) {
        case OK:
            printf("\nPatient was deleted.");
            delete_no_client();
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case ELEMENT_NOT_FOUND:
            printf("\nThere's no such patient with that name.");
            break;
        default:
            printf("\nUnknown Error.");
    }

    press_to_continue();
}
void get_client() {
    printf("\nOutput client to list. Choose input method: \n1. From console\n2. From file\n");
    unsigned method;
    while (1) {
        scanf("%u", &method);

        if (method != 1 && method != 2)
            printf("There is no such command. Try again ");
        else
            break;
    }

    if (method == 2) {
        printf("\nFunction is developing");
        return;
    }

    char name[150];
    printf("\nInput name \n");
    getchar();
    scanf("%s", name);
    ListNode *client;
    Status status = get_element_by_name(&patients_list, name, &client);

    switch (status) {
        case NULL_POINTER:
            printf("\nError.");
            break;
        case ELEMENT_NOT_FOUND:
            printf("\nThere's no such patient with that name.");
            break;
        case OK: {
            Status status1 = write_to_console(client->data);
            if (status1 == NULL_POINTER) {
                printf("\nError.");
                return;
            }
            print_line(70);
            press_to_continue();
            break;
        }
        default:
            printf("\nUnknown Error.");
    }
}

void print_all() {
    printf("\nPatient list:\n");

    print_head();

    Status status = print_list(&patients_list);

    switch (status) {
        case NO_ELEMENTS:
            printf("\nList is empty...");
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case OK:
            print_line(120);
            break;
        default:
            printf("\nUnknown Error.");
    }

    press_to_continue();
}

void print_debtors() {
    printf("By which criteria output debtors? \n1. Procedure type \n2. Amount of debt\n");
    unsigned method;

    while (1) {
        scanf("%u", &method);

        if (method != 1 && method != 2)
            printf("There is no such command. Try again ");
        else
            break;
    }

    printf("\nList of debtors:\n");
    Status status;
    switch (method) {
        case 1:
            status = print_debtors_type(&patients_list);
            break;
        case 2:
            status = print_debtors_debt(&patients_list);
            break;
    }

    switch (status) {
        case NO_ELEMENTS:
            printf("\nList is empty...");
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case OK:
            print_line(120);
            break;
        default:
            printf("\nUnknown Error.");
    }
    press_to_continue();
}

void modify_client() {
    printf("\nModify client from list.\n");

    char name[150];
    printf("\nInput name \n");
    getchar();
    scanf("%s", name);
    ListNode *client;
    Status status = get_element_by_name(&patients_list, name, &client);
    modify_data(&patients_list, client);

    switch (status) {
        case OK:
            printf("\nPatient was modified.");
            break;
        case NULL_POINTER:
            printf("\nError.");
            break;
        case ELEMENT_NOT_FOUND:
            printf("\nThere's no such patient with that name.");
            break;
        default:
            printf("\nUnknown Error.");
    }

    press_to_continue();
}