#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patientsList.h"
#include "menu.h"

#define LINE_WIDTH 120

char types[5][60] = {
        "Prosthetics",
        "Tooth filling",
        "Implants",
        "Medical exam",
        "Tooth removal"
};

Status destructor(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *tmp;
    while (!list->head) {
        tmp = list->head->next;
        free(list->head);
        list->head = tmp;
    }
    return OK;
}

Status push(List *list, PatientData *data) {
    if (!list || !data)
        return NULL_POINTER;

    ListNode *cur = list->head;
    while (cur) {
        if (!strcmp(cur->data->name, data->name) || cur->data->card_number == data->card_number)
            return ELEMENT_ALREADY_EXISTS;
        cur = cur->next;
    }
    ListNode *tmp = (ListNode *) malloc(sizeof(ListNode));
    tmp->data = data;
    tmp->next = list->head;
    list->head = tmp;
    return OK;
}

Status pop(List *list) {
    if (!list) {
        return NULL_POINTER;
    }
    ListNode *prev = NULL;
    prev = list->head;
    list->head = list->head->next;
    free(prev);
    return OK;
}

Status modify_data(List *list, ListNode *client) {
    if (!list) {
        return NULL_POINTER;
    }
    PatientData *tmp = client->data;
    printf("\nInput modified data:");
    printf("Procedure types: ");
    for (int i = 0; i < 5; i++)
        printf("\n%d. %s", i + 1, types[i]);
    unsigned type;
    while (1) {
        printf("Input procedure's number: \n");
        scanf("%u", &type);

        if (type <= 5 && type != 0)
            break;
        else
            printf("Input error. There's no procedure with this number. Please, choose another one. \n");
    }
    tmp->type = type;
    printf("Input cost of competed procedure (in hryvnia): \n");
    scanf("%f", &(tmp->cost));
    printf("Input paid sum (in hryvnia): \n");
    scanf("%f", &(tmp->paid));

    if (tmp->paid < tmp->cost) {
        tmp->debt = tmp->cost - tmp->paid;
        printf("Debt is %.2f hryvna.\n", tmp->debt);
    } else {
        tmp->debt = 0;
        printf("You don't have debts.\n");
    }
    return OK;
}

Status write_from_console(PatientData **result) {
    if (!result)
        return NULL_POINTER;

    printf("\nData input:");
    PatientData *tmp = (PatientData *) malloc(sizeof(PatientData));
    printf("\nInput name and/or last name of patient: \n");
    getchar();
    scanf("%s", &(tmp->name));
    printf("Input patient's card number: \n");
    scanf("%u", &(tmp->card_number));
    printf("Procedure types: ");
    for (int i = 0; i < 5; i++)
        printf("\n%d. %s", i + 1, types[i]);
    unsigned type;
    while (1) {
        printf("Input procedure's number: \n");
        scanf("%u", &type);

        if (type <= 5 && type != 0)
            break;
        else
            printf("Input error. There's no procedure with this number. Please, choose another one. \n");
    }
    tmp->type = type;
    printf("Input cost of competed procedure (in hryvnia): \n");
    scanf("%f", &(tmp->cost));
    printf("Input paid sum (in hryvnia): \n");
    scanf("%f", &(tmp->paid));

    if (tmp->paid < tmp->cost) {
        tmp->debt = tmp->cost - tmp->paid;
        printf("Debt is %.2f hryvna.\n", tmp->debt);
    } else {
        tmp->debt = 0;
        printf("You don't have debts.\n");
    }

    *result = tmp;
    return OK;
}

Status get_element_by_name(List *list, char name[], ListNode **result) {
    if (!list || !result)
        return NULL_POINTER;

    ListNode *cur = list->head;
    while (cur) {
        if (!strcmp(cur->data->name, name)) {
            *result = cur;
            return OK;
        }
        cur = cur->next;
    }
    return ELEMENT_NOT_FOUND;
}

Status write_to_console(PatientData *data) {
    if (!data)
        return NULL_POINTER;

    print_line(LINE_WIDTH);
    printf("|%15s|", data->name);
    printf("|%14d|", data->card_number);
    printf("|%15s|", types[data->type]);
    printf("|%25.2f|", data->cost);
    printf("|%21.2f|", data->paid);
    printf("|%18.2f|", data->debt);
    return OK;
}

Status print_list(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *cur = list->head;

    if (!cur)
        return NO_ELEMENTS;

    while (cur) {
        write_to_console(cur->data);
        cur = cur->next;
    }
    return OK;
}

Status print_debtors_type(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *cur = list->head;

    unsigned empty = 1;

    while (cur) {
        if (cur->data->debt) {
            empty = 0;
            printf("\n%s: %s", cur->data->name, types[cur->data->type]);
        }
        cur = cur->next;
    }

    if (empty)
        return NO_ELEMENTS;

    return OK;
}

Status print_debtors_debt(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *cur = list->head;

    unsigned empty = 1;

    while (cur) {
        if (cur->data->debt) {
            empty = 0;
            printf("\n%s: %.2f", cur->data->name, cur->data->debt);
        }
        cur = cur->next;
    }

    if (empty)
        return NO_ELEMENTS;

    return OK;
}

Status delete_no_debtors(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *cur = list->head;
    unsigned empty = 1;

    while (cur) {
        if (cur->data->debt == 0) {
            empty = 0;
        }
        cur = cur->next;
    }

    if (empty)
        return NO_ELEMENTS;

    return OK;
}