typedef enum WorkType {
    PROSTHETICS,
    FILLINGS,
    IMPLANTS,
    INSPECTION,
    EXTRACTION
} WorkType;

typedef enum Status {
    OK,
    NULL_POINTER,
    SIZE_LIMIT,
    ELEMENT_ALREADY_EXISTS,
    INPUT_ERROR,
    ELEMENT_NOT_FOUND,
    NO_ELEMENTS
} Status;

typedef struct PatientData {
    char name[150];
    unsigned card_number;
    WorkType type;
    float cost;
    float paid;
    float debt;
} PatientData;

typedef struct ListNode {
    PatientData *data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

Status destructor(List *list);

Status push(List *list, PatientData *node);

Status pop(List *list);

Status write_from_console(PatientData **result);

Status get_element_by_name(List *list, char name[], ListNode **result);

Status modify_data(List *list, ListNode *client);

Status delete_no_debtors(List *list);

Status write_to_console(PatientData *data);

Status print_list(List *list);

Status print_debtors_type(List *list);

Status print_debtors_debt(List *list);
