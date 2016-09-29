#include "functions.h"

void init ( Nod ** list, char* line ) {
/*  Initializare lista cu elemente transmise prin sirul de caractere */
    char *v;
    *list = (Nod*)malloc(sizeof(Nod));
    Nod *p = (Nod *) malloc(sizeof(Nod));
    Nod *q;
    v = strtok(line, " ");
    (*list)->next = p;
    p->info = v[0];
    p->snod = 'F';
    p->next = NULL;
    v = strtok(NULL, " ");
    /* Despartirea sirului in tokeni, dupa caracterul 'space' si adaugarea
     * nodurilor la lista */
    while (v != NULL) {
        q = (Nod *) malloc(sizeof(Nod));
        q->info = v[0];
        if (strlen(v) == 2)
            q->snod = 'T';
        else
            q->snod = 'F';
        q->next = NULL;
        p->next = q;
        p = p->next;
        v = strtok(NULL, " ");
    }

}

void Insert(Nod** line, int loop, int index, char Val, char Snod) {
    /* Adauga un nod cu parametrii Val si Snod pe pozitia [loop,index] */
    int LoopIndex = 0, ElemIndex = 0;
    Nod *q = NULL;
    Nod *p = *line;
    /* Deplasare pe bucla dorita */
    while ( LoopIndex < loop ) {
        if (p->next->snod == 'T')
            LoopIndex+=1;
        q=p;
        p=p->next;

    }
    /* Deplasare la indexul dorit */
    while (ElemIndex < index ) {
        q=p;
        p = p->next;
        ElemIndex += 1;
    }
    /* Inserare element */
    Nod *nou = (Nod*) malloc (sizeof(Nod));
    nou->info=Val;
    nou->snod=Snod;
    q->next=nou;
    nou->next=p;

}

void InsertParser (char * arg) {
    /* Extrage in sirul de caractere bucla, indexul precum si valorile
     * de adaugat */
    int index, loop, lineindex;
    char value, snod;
    Nod *linie;
    sscanf(arg, "%*s %d %d %d %c %c", &lineindex, &loop, &index, &value, &snod);
    if (lineindex == 1)
        linie = List1;
    else
        linie = List2;
    Insert(&linie, loop, index, value, snod);
}

void PrintLine (Nod* line, FILE* out) {
    /* Aifsarea liniei */
    line=line->next;
    /* Afisez separat primul nod, adaugand spatii inaintea celorlalte pentru
     * a nu avea spatii goale la finalul liniei */
    if (line->snod == 'T')
        fprintf(out, "%c*", line->info);
    else fprintf(out, "%c", line->info);
    line = line->next;
    while (line != NULL) {
        if (line->snod == 'T')
            fprintf(out," %c*",line->info);
        else fprintf(out, " %c", line->info);
    line=line->next;
    }
    printf("\n");
}

void citire(char* filename) {
    /* Citirea datelor din fisierul transmis ca parametru */
    FILE *input;
    input = freopen(filename,"r",stdin);
    char line[1000];
    fgets(line, 1000, input);
    /* Citirea liniei 1 */
    line[strlen(line)-1]='\0';
    init (&List1, line);
    fflush(input);
    fgets(line, 1000, input);
    /* Citirea liniei 2 */
    line[strlen(line) - 1] = '\0';
    init(&List2, line);
    fflush(stdout);
    fclose(input);
}

int ValidLink ( Nod *A, Nod *B) {
    /* Verifica daca doua noduri A, din lista 1 si B, din lista 2
     * formeaza o legatura valida */
    int True=1;
    if (A->snod!=B->snod)
        True=0;
    if  ((A->info=='A') && (B->info!='T') )
        True=0;
    if ((A->info == 'T') && (B->info != 'A'))
        True = 0;
    if ((A->info == 'C') && (B->info != 'G'))
        True = 0;
    if ((A->info == 'G') && (B->info != 'C'))
        True = 0;
    return True;

}

void PrintValidation(){
    /* Validarea liniilor. Porneste din stanga, verifica fiecare pereche de noduri
     * pana cand gaseste o legatura invalida sau listele se termina */
    int Result = 1;
    Nod *P, *Q;
    P = List1->next;
    Q = List2->next;
    while (P != NULL && Q!=NULL) {
        if (ValidLink(P, Q) == 0) {
            Result = 0;
            break;
        }
        P = P->next;
        Q = Q->next;
    }
    if (P != NULL || Q!= NULL)
        Result = 0;
    if (Result == 1 )
        printf("true\n");
    else
        printf("false\n");
}
void EditElement(Nod ** line, int loop, int index, char value, char snod) {
    /* Modifica elementul de pe pozitia [ loop, index ], cu valorile value
     * si snod */
    int LoopIndex = 0, ElemIndex = 0;
    Nod *p = *line;
    /* Deplasare pe bucla loop */
    while (LoopIndex < loop) {
        if (p->next->snod == 'T')
            LoopIndex += 1;
        p = p->next;
    }
    /* Deplasare la elementul index */
    while (ElemIndex < index ) {
        p = p->next;
        ElemIndex += 1;
    }
    /* Modificare valori */
    p->info = value;
    p->snod = snod;
}
void  EditElementParser(char *arg){
    /* Parsare comanda de editare
     * Se extrag din sir bucla, indexul, valoarea si snod */
    int index, loop, lineindex;
    char value, snod;
    Nod *linie;
    sscanf(arg, "%*s %d %d %d %c %c", &lineindex, &loop, &index, &value, &snod);
    if (lineindex == 1)
        linie = List1;
    else
        linie = List2;
    /* Se apeleaza functia de editare */
    EditElement(&linie, loop, index, value, snod);
}
void DeleteParser (char *arg){
    /* Parsarea comenzii de stergere.
     * Se extrag bucla si indexul care vor fi sterse*/
    int index, loop, lineindex;
    Nod *linie;
    sscanf(arg, "%*s %d %d %d", &lineindex, &loop, &index);
    if (lineindex == 1)
        linie = List1;
    else
        linie = List2;
    Delete(&linie, loop, index);

}
void Delete(Nod **line, int loop, int index){
    /* Se sterge elementul de pe bucla si indexul primite ca parametri */
    int LoopIndex = 0, ElemIndex = 1;
    Nod *p = *line, *q;
    /* Verificarea stergerii elementului de pe prima pozitie */
    if (loop==0 && index ==1 ) {
        q = p->next;
        p->next = q->next;
        free(q);
    }
    else {
        p = *line;
        do {
            p = p->next;
            if (p->next->snod == 'T') {
                LoopIndex += 1;
                ElemIndex = 0;
            }

        }
        while (LoopIndex < loop);



        while (ElemIndex < index) {
            p = p->next;
            ElemIndex += 1;
        }
        /*Deplasarea pe pozitia anterioara elementului care va fi sters*/
        q = p->next;
        p->next = q->next;
        free(q);
    }

}
Nod* Retriever (int line, int loop, int index) {
    /* Returneaza adresa de memorie a elementului dorit */
    int LoopIndex=0, ElemIndex=0;
    Nod *p;
    if (line == 1)
        p = List1;
    else
        p = List2;
    /*Deplasare pe bucla si indexul cerut */
    while (LoopIndex < loop) {
        if (p->next->snod == 'T')
            LoopIndex += 1;
        p = p->next;
    }
    while (ElemIndex < index) {
        p = p->next;
        ElemIndex += 1;
    }
    return p;
}

char* Invert (char* v){
    /* Creeaza comanda inversa a lui v, care va fi adaugata pe stiva pentru undo
     * Returneaza sirul nou */
    char* inverted=malloc(20);
    inverted[0]='\0';
    int line, loop, index, val, snod;
    Nod *p;
    /* Inversa lui instert = delete */
    if (strncmp(v,"ie",2)==0){
        sscanf(v,"%*s %d %d %d", &line, &loop, &index);
        sprintf(inverted,"de %d %d %d", line, loop, index);
    }
    /* Inversa lui edit = edit */
    if (strncmp(v, "ee", 2) == 0) {
        sscanf(v, "%*s %d %d %d", &line, &loop, &index);
        p = Retriever(line,loop,index);
        val = p->info;
        snod = p->snod;
        sprintf(inverted, "ee %d %d %d %c %c", line, loop, index, val, snod);
    }
    /* Inversa lui delete = insert */
    if (strncmp(v, "de", 2) == 0){
        sscanf(v, "%*s %d %d %d", &line, &loop, &index);
        p = Retriever(line, loop, index);
        val = p->info;
        snod = p->snod;
        sprintf(inverted, "ie %d %d %d %c %c", line, loop, index, val, snod);
    }
    /* Inversa lui reverse  = reverse */
    if (strncmp(v, "rs", 2) == 0)
        strcpy (inverted,v);
    return inverted;

}
void Parse (char *v, int AddToStack){
    /* Parsarea comenzii citite din fisier.
     * Parametrul AddToStack decide daca se va pune sau nu pe stiva comanda.
     * -> din main -> AddToStack = 1;
     * -> din stiva -> AddToStack = 0;
     Se trimite sirul catre parserul specific fiecarei comenzi, insert, delete
     sau edit, ori executa afisarea */
    char decide[3];
    Nod *target;
    strncpy(decide, v, 2);
    decide[2] = '\0';
    if (strcmp(decide, "ie") == 0) {
        if (AddToStack)
        pushStack(v, &Commands, Invert(v));
        InsertParser(v);
    }
    if (strcmp(decide, "ee") == 0){
        if (AddToStack)
            pushStack(v, &Commands, Invert(v));
        EditElementParser(v);
    }
    if (strcmp(decide, "de") == 0) {
        if (AddToStack)
            pushStack(v, &Commands, Invert(v));
        DeleteParser(v);
    }
    if (strcmp(decide, "pl") == 0) {
        if (v[3] == '1')
            target=List1;
        else
            target=List2;
        PrintLine(target,stdout);
        if (AddToStack)
            pushStack(v, &Commands, Invert(v));
    }
    if (strcmp(decide, "pr") == 0) {
        if (v[3] == '1')
            target = List1;
        else
            target = List2;
        PrintReverse(target->next,stdout);
        pushStack(v, &Commands, Invert(v));
        printf("\n");
    }
    if (strcmp(decide, "rs") == 0) {
        Reverse(&List1);
        Reverse(&List2);
        if (AddToStack)
            pushStack(v, &Commands, Invert(v));
    }
    if (strcmp(decide, "pv") == 0){
        PrintValidation();
        if (AddToStack)
            pushStack(v, &Commands, Invert(v));
    }
    if (strcmp(decide, "ps") == 0)
        printStack(Commands);
    if (strcmp(decide, "un") == 0)
        popStack(&Commands);

}

void PrintReverse (Nod *list, FILE* out) {
    /* Afisarea inversa a listei. Se merge recursiv pana la final, apoi se afiseaza
     * nodurile in ordine inverse */
    if (list==NULL)
        return;
    PrintReverse(list->next, out);
    if (list == List1->next || list == List2->next)
        if (list->snod == 'T')
            fprintf(out, "%c*", list->info);
        else fprintf(out, "%c", list->info);
    else
        if (list->snod == 'T')
           fprintf(out, "%c* ", list->info);
        else fprintf(out, "%c ", list->info);
}

void Reverse(Nod **list) {
    /* Inversarea listei . Fiecare nod va fi plasat inaintea fostului sau
     * predecesor. In final, lista va avea pe prima pozitie ultimul nod, iar pe ultima
     * primul nod */
    Nod *prev = NULL;
    Nod *curent = (*list)->next;
    Nod *next;
    while (curent != NULL) {
        next = curent->next;
        curent->next = prev;
        prev = curent;
        curent = next;
    }
    (*list)->next = prev;
}
void ex(){
    /* Finalizarea programului. Se sterg nodurile din liste si se elibereaza
     * stiva de comenzi */
    Nod *q = List1;
    Nod *p;
    Stack *x,*y;
    while (q!=NULL){
        p=q;
        q=q->next;
        free(p);
    }
    q = List2;
    while (q != NULL) {
    p = q;
    q = q->next;
    free(p);
    }
    x = Commands;
    while (x != NULL){
        y = x;
        x = x->next;
        free(y);
    }
}

int main (int argc, char *Argv[]) {
    FILE *commands;
    FILE *out;
    out = freopen(Argv[3],"w",stdout);
    char v[50], decide[3];
    setbuf(stdout, NULL);
    citire(Argv[1]);
    commands = freopen(Argv[2],"r",stdin);
    fflush(stdin);
    fgets(v,50, stdin);
    v[strlen(v)-1]='\0';
        while (strncmp(v,"ex",2)!=0) {
            Parse(v,1);
            fgets(v, 50, stdin);
            v[strlen(v)-1] = '\0';
    }
    ex();

}
