#include <stdio.h>
#include "Dataframe.h"

int main() {
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 3);
    insert_value(mycol, 9);
    insert_value(mycol, 47);
    print_col(mycol);
    return 0;
}
