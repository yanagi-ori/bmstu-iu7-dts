//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#ifndef LAB_02_IO_H
#define LAB_02_IO_H


short int menu(short int *action);

short int load_file(table_t *table);

short int append_student(table_t *table);

void print_table(const table_t table, bool keys);

#endif //LAB_02_IO_H
