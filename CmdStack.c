#include "functions.h"

void printStack(Stack *node) {
    /* Afisarea comenzilor executate anterior si care se gasesc pe stiva */
    while (node!=NULL) {
        if (node->next == NULL)
            printf("%s", node->name);
        else
            printf("%s ", node->name);
         node = node->next;
    }
    printf("\n");
}

void pushStack(char *cmd, Stack **Commands, char *inverse) {
    /* Adaugarea unui nou nod in stiva. Se tin minte comanda executata
     * precum si inversa, care va fi executata la undo */
    Stack *nou = (Stack *) malloc(sizeof(Stack));
    strcpy(nou->command, cmd);
    strncpy(nou->name,nou->command,2);
    strcpy(nou->command, inverse);
    free(inverse);
    nou->name[2]='\0';
    nou->next = *Commands;
    (*Commands) = nou;
}

void popStack(Stack **Commands) {
    /*Executia comenzii de undo. Se parseaza sirul de caractere din campul
     * command, cu parametrul AddToStack 0, pentru a nu se adauga din nou pe stiva*/
    Stack *p;
    if ( (*Commands) != NULL) {
        p = *Commands;
        Parse((*Commands)->command, 0);
        *Commands = (*Commands)->next;
        free(p);
    }
}


