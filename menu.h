typedef enum MenuElement {
    EXIT,
    ADD_CLIENT,
    DELETE_CLIENT,
    MODIFY_CLIENT,
    PRINT_ALL,
    PRINT_CLIENT,
    PRINT_DEBTORS,
    REMOVE_DEBTLESS,
    SORT_BY_DEBT,
} MenuElement;

void print_head(void);

void print_line(unsigned len);

void print_line_to_file(unsigned len, FILE *f);

void print_menu(void);

MenuElement scan_command(void);

void press_to_continue(void);
