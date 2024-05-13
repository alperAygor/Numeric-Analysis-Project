#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }  // '\n' veya EOF'a kadar tüm karakterleri oku ve atla
}
// struct yapýlarýnýn prototipleri
typedef struct List_Node List_Node;
typedef struct Tree_Node Tree_Node;
// brackets_controller fonksiyonunun prototipi
void brackets_controller(int *first_brackets_count, int *sec_brackets_count, char *data, int *i);
// in_brackets_controller fonksiyonunun prototipi
void in_brackets_controller(int *first_brackets_count, int *sec_brackets_count, char *data, int *i, int *out_brackets);
void create_dataTree(List_Node *node);
void create_data(Tree_Node *node);
List_Node *func_controller(char *input,Tree_Node *node,List_Node *root);
char *func_separater(int index,char *data, char *temp);
List_Node *create_dataList(char *data);
// add_list_node fonksiyonunun prototipi
Tree_Node *tree_calc(Tree_Node *curr,double x);
void tree_reader(List_Node *node,double x);
double func_reader(int x,List_Node *root);
Tree_Node *list_calc(List_Node *curr);
Tree_Node *list_reader(List_Node *root,double x);
void free_data(List_Node *root);
void free_tree(Tree_Node *node);
void free_list(List_Node *node);
void process_trigonometric_function(Tree_Node *curr, double x);
double func_calc(double x,char *function);
void bi_section_method();
void numerical_deritative();
void bisection_method(double start, double end, double epsilon, int iteration, char* function, int stop_choice);
List_Node *add_list_node(List_Node *node, char data[]);
double forward_difference_deritative(double x, double h,char *function);
double backward_difference_deritative(double x, double h,char *function);
double central_difference_deritative(double x, double h,char *function);
void regula_falsi_method(double start, double end, double epsilon, int iteration, char* function, int stop_choice);
void regula_falsi();
void newton_raphson();
double simpson_method_1(double top,double bot,char *function);
double simpson_method_2(double top,double bot,char *function);
void newton_raphson_method(double root, double epsilon, int iteration, char* function);
double trapezoidal_calc(double top,double bot,char *function);
void trapezoidal_method(char* function,int count,double top ,double bot);
void trapezoidal();
void simpson();
void simpson_method(char* function,int choice,int count,double top ,double bot);
double *get_vector(int dimension);
void gauss_seidal();
void reverse_matrix();
void gauss_elimination();
int menu();
int printMenu();
int get_max_by_col(double **matrix,int col_num,int dimension);
void swap_rows(double **matrix, double *vector, int row1, int row2, int dimension);
typedef struct Tree_Node{
    char *data;
    double value;
    int is_calc;
    Tree_Node *parent;
    Tree_Node *left;
    Tree_Node *right;
    List_Node *in;
    List_Node *out;
}Tree_Node;

typedef struct List_Node{
    char *data;
    double value;
    int is_calc;
    List_Node *prev;
    List_Node *next;
    Tree_Node *tree_in;
    Tree_Node *tree_out;
}List_Node;

double logbase(double main, double base)
{
   return log(main) / log(base);
}

char *get_input() {
    char *data = (char *)malloc(100 * sizeof(char));
    printf("Enter your function:\n");
    fgets(data, 100, stdin);

    int i = 0, j = 0;
    while (data[i] != '\0') {
        if (!isspace(data[i])) {
            data[j] = tolower(data[i]); // Karakter küçük harfe dönüþtürülüp atanýyor
            j++;
        }
        i++;
    }
    data[j] = '\0'; // Sonuçtaki karakter dizisini sonlandýrýyoruz
    return data;
}

List_Node *create_data_on_list(List_Node *curr,int *i,char *data,char *temp,int a){
     if (temp == NULL || curr == NULL || i == NULL) {
        return NULL; // Invalid input
    }
    curr->data = (char*)malloc((strlen(temp)+1) * sizeof(char));
    if (curr->data == NULL) {
        return NULL; // Memory allocation failed
    }
    strncpy(curr->data,temp,a);
    curr->data[a]='\0';
    char *data_=(char*)malloc(sizeof(char)*2);
    if(data_==NULL){
        return NULL;
    }
    if(data==NULL){
        curr->next=NULL;
        free(data_);
        data_=NULL;
        return curr;
    }
    else{
        List_Node *new_node1=(List_Node*)malloc(sizeof(List_Node));
        if(new_node1==NULL){
            free(data_);
            free(curr->data);
            return NULL;
        }
        new_node1->next=NULL;
        new_node1->prev=NULL;
        new_node1->value=0;
        new_node1->data=NULL;
        new_node1->is_calc=0;
        new_node1->tree_in=NULL;
        new_node1->tree_out=NULL;
        new_node1->data=(char *)malloc(2 * sizeof(char));
        if (new_node1->data == NULL) {
            free(new_node1);
            free(data_);
            free(curr->data);
            return NULL; // Memory allocation failed
    }

        data_[0]=data[(*i)];
        data_[1]='\0';
        List_Node *new_node2=(List_Node*)malloc(sizeof(List_Node));
        if (new_node2== NULL) {
            free(new_node1->data);
            free(new_node1);
            free(data_);
            free(curr->data);
            return NULL; // Memory allocation failed
        }
        new_node2->next=NULL;
        new_node2->prev=NULL;
        new_node2->value=0;
        new_node2->data=NULL;
        new_node2->is_calc=0;
        new_node2->tree_in=NULL;
        new_node2->tree_out=NULL;
        strncpy(new_node1->data,data_,1);
        new_node1->data[1]='\0';
        new_node1->prev=curr;
        curr->next=new_node1;
        new_node2->prev=new_node1;
        new_node1->next=new_node2;
        new_node2->next=NULL;
        new_node2->data=NULL;
        curr=new_node2;
        free(data_);
        data_=NULL;
        return curr;
    }
}
List_Node *create_dataList(char *data){
    int a;
    int *first_brackets_count=(int*)malloc(sizeof(int)),
    *sec_brackets_count=(int*)malloc(sizeof(int)),
    *i=(int*)malloc(sizeof(int)),
    *j=(int*)malloc(sizeof(int)),
    *z=(int*)malloc(sizeof(int)),
    *input_info=(int*)malloc(sizeof(int)),
    *out_brackets=(int*)malloc(sizeof(int));
    *out_brackets=0;
    *j=0;
    *i=0;
    *z=0;
    *input_info=0;
    if (!first_brackets_count || !sec_brackets_count || !i || !j || !z || !input_info || !out_brackets) {
        free(first_brackets_count);
        free(sec_brackets_count);
        free(i);
        free(j);
        free(z);
        free(input_info);
        free(out_brackets);
        return NULL; // Memory allocation failed
    }

    List_Node *curr=(List_Node *)malloc(sizeof(List_Node));
    if(curr==NULL){
        free(i);
        free(j);
        free(z);
        free(input_info);
        free(out_brackets);
        free(first_brackets_count);
        free(sec_brackets_count);
        return NULL;
    }
    curr->prev=NULL;
    curr->value=0;
    curr->next=NULL;
    curr->is_calc=0;
    curr->tree_in=NULL;
    curr->tree_out=NULL;
    curr->data=NULL;
    while((*input_info)!=1){
        char *temp;
        *out_brackets=0,*first_brackets_count=0,*sec_brackets_count=0,
        *j=0;
        brackets_controller(first_brackets_count,sec_brackets_count,data,i);
        if(*sec_brackets_count == *first_brackets_count){
        temp=(char*)malloc(sizeof(char)*((*i)-(*z)+1));
        if(temp==NULL){
            free(curr);
            free(i);
            free(j);
            free(z);
            free(input_info);
            free(out_brackets);
            free(first_brackets_count);
            free(sec_brackets_count);
            return NULL;
        }
       //printf("\n\nstrlendata :%d",strlen(data));
        //printf("\n\nstrlentemp :%d",strlen(temp));
        *j=0;
        a=(*i)-(*z);
        while((*z)!=(*i)){
            temp[(*j)]=data[(*z)];
            (*j)++;
            (*z)++;
            }
        temp[a] = '\0';
        // we separated function good job!,
        //now our b pointing "+" in data!!!! be careful not in temp
             if(data[(*i)]=='\0'){
                curr=create_data_on_list(curr,i,NULL,temp,a);
                *input_info=1;
                 free(temp);
                }
            else{
                curr=create_data_on_list(curr,i,data,temp,a);
                free(temp);
                }
            (*i)++;
            (*z)++;
        }
        else{

            in_brackets_controller(first_brackets_count,sec_brackets_count,data,i,out_brackets);

            *out_brackets=0;
            brackets_controller(first_brackets_count,sec_brackets_count,data,i);
            if((*sec_brackets_count == *first_brackets_count)){
                // we separated function good job!,
                //now our b pointing "+" in data!!!! be careful not in temp
                temp=(char*)malloc(sizeof(char)*((*i)-(*z)+1));
                if(temp==NULL){
                    free(curr);
                    free(i);
                    free(j);
                    free(z);
                    free(input_info);
                    free(out_brackets);
                    free(first_brackets_count);
                    free(sec_brackets_count);
                    return NULL;
                }
                *j=0;
                a=(*i)-(*z);
                while((*z)!=(*i)){
                    temp[(*j)]=data[(*z)];
                    (*j)++;
                    (*z)++;
                }
                temp[a] = '\0';
                if(data[(*i)]=='\0'){
                        curr=create_data_on_list(curr,i,NULL,temp,a);
                         *input_info=1;
                          free(temp);
                    }
                else{
                        curr=create_data_on_list(curr,i,data,temp,a);
                        free(temp);
                    }
                (*i)++;
                (*z)++;
            }
            else{
                in_brackets_controller(first_brackets_count,sec_brackets_count,data,i,out_brackets);
                *out_brackets=0;
                brackets_controller(first_brackets_count,sec_brackets_count,data,i);
                if((*sec_brackets_count == *first_brackets_count)){
                    // we separated function good job!,
                    //now our b pointing "+" in data!!!! be careful not in temp
                    a=(*i)-(*z);
                    temp=(char*)malloc(sizeof(char)*((*i)-(*z)+1));
                    *j=0;
                    while((*z)!=(*i)){
                        temp[(*j)]=data[(*z)];
                        (*j)++;
                        (*z)++;
                    }
                    temp[a] = '\0';
                    if(data[(*i)]=='\0'){
                        curr=create_data_on_list(curr,i,NULL,temp,a);
                         *input_info=1;
                          free(temp);
                    }
                    else{
                        curr=create_data_on_list(curr,i,data,temp,a);
                        free(temp);
                    }
                    (*i)++;
                    (*z)++;
                }
                else{
                    in_brackets_controller(first_brackets_count,sec_brackets_count,data,i,out_brackets);
                    // we separated function good job!,
                    //now our b pointing "+" in data!!!! be careful not in temp
                    brackets_controller(first_brackets_count,sec_brackets_count,data,i);
                    a=(*i)-(*z);
                   temp=(char*)malloc(sizeof(char)*((*i)-(*z)+1));
                    *j=0;
                    while((*z)!=(*i)){
                        temp[(*j)]=data[(*z)];
                        (*j)++;
                        (*z)++;
                    }

                    temp[a] = '\0';
                    if(data[(*i)]=='\0'){
                        curr=create_data_on_list(curr,i,NULL,temp,a);
                        *input_info=1;
                        free(temp);
                    }
                    else{
                        curr=create_data_on_list(curr,i,data,temp,a);
                        free(temp);
                    }
                   (*i)++;
                   (*z)++;
                }
            }
        }
    }

    free(sec_brackets_count);
    free(first_brackets_count);
    free(z);
    free(i);
    free(j);
    free(out_brackets);
    free(input_info);
    while(curr->prev!=NULL){
        curr=curr->prev;
    }
    return curr;
}

void brackets_controller(int *first_brackets_count,int *sec_brackets_count,char *data,int *i){
    int data_length = strlen(data); // data dizisinin uzunluðunu belirleyin

    while((data[(*i)]!='+' && data[(*i)]!='-' && data[(*i)]!='/' && data[(*i)]!='*'&& data[(*i)]!='\0')&&(*i) < strlen(data)){

        if(data[(*i)]=='(')
        {
            (*first_brackets_count)++;

        }
        if(data[(*i)]==')')
        {
            (*sec_brackets_count)++;

        }
        (*i)++;
    }

}
void in_brackets_controller(int *first_brackets_count,int *sec_brackets_count,char *data,int *i,int *out_brackets){
    int data_len=strlen(data);
    while((*out_brackets)==0 && data_len>(*i)){
        while((*sec_brackets_count!=*first_brackets_count)&&data_len>(*i)){
        if(data[(*i)]=='('){
            (*first_brackets_count)++;
        }
        if(data[(*i)]==')'){
            (*sec_brackets_count)++;
        }
        (*i)++;
        }
        if(*sec_brackets_count==*first_brackets_count){
            *out_brackets=1;
            return;
        }
    }
}

void create_data(Tree_Node *node){
    char *temp=NULL;
    char *all_data=NULL;
    int data_len=strlen(node->data);
    all_data=(char*)malloc(sizeof(char)*(data_len+1));
    if(all_data==NULL){
        return;
    }
    strncpy(all_data,node->data,data_len);
    all_data[data_len]='\0';
    int i;
    int j;
    int len;
    char* temp_node_data=NULL;
    i=0;
    if(all_data[0]=='l' && all_data[1]=='n'){

        len=strlen("ln");
        temp_node_data=realloc(node->data,(len+1));
        node->data=temp_node_data;
        strncpy(node->data,"ln",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);
        return;

        //devamý
    }
    else if (all_data[0]=='l'&&all_data[1]=='o'&&all_data[2]=='g')
    {

        node->right=(Tree_Node*)malloc(sizeof(Tree_Node));
        node->left=(Tree_Node*)malloc(sizeof(Tree_Node));
        node->right->parent=node;
        node->left->parent=node;
        len=strlen("log");
        temp_node_data=realloc(node->data,(len+1));
        node->data=temp_node_data;
        strncpy(node->data,"log",len);
        node->data[len]='\0';
        char *base=(char*)malloc(sizeof(char)*(20));
        char *main=(char*)malloc(sizeof(char)*(20));

        if(all_data[3]=='_'){
            if(all_data[4]=='('){
                //LOG_()()
                j=0;
                i=5;
                while (all_data[i]!=')'&&all_data[i+1]!='(')
                {
                    base[j]=all_data[i];
                    i++;
                    j++;
                }
                base[j]='\0';
                j=0;
                i=i+2;
                while (all_data[i+1]!='\0')
                {
                    main[j]=all_data[i];
                    i++;
                    j++;
                }
                main[j]='\0';
                //Done

            }
            else{
                i=4;
                j=0;
                while(all_data[i]!='('){
                    base[j]=all_data[i];
                    i++;
                    j++;
                }
                base[j]='\0';
                i++;
                j=0;
                while (all_data[i+1]!='\0')
                {
                    main[j]=all_data[i];
                    i++;
                    j++;
                }
                main[j]='\0';
            }
            int len_base=strlen(base);
            int len_main=strlen(main);
            node->left->data=(char*)malloc(sizeof(char)*(len_base)+1);
            node->right->data=(char*)malloc(sizeof(char)*(len_main)+1);
            strncpy(node->left->data,base,len_base);
            strncpy(node->right->data,main,len_main);
            node->left->data[len_base]='\0';
            node->right->data[len_main]='\0';
            List_Node *root_base=NULL;
            List_Node *root_main=NULL;
            root_base=func_controller(base,node->left,NULL);
            root_main=func_controller(main,node->right,NULL);
        }
        else{
            main=func_separater(3,all_data,main);
            int len_main=strlen(main);
           node->left->data=(char*)malloc(sizeof(char)*3);
            node->right->data=(char*)malloc(sizeof(char)*(len_main+1));
            node->left->value=10.0;
            strncpy(node->left->data,"10",2);
            node->left->data[2]='\0';
            strncpy(node->right->data,main,len_main);
            node->right->data[len_main]='\0';
            node->left->in=NULL;
            List_Node *root_main=NULL;
            root_main=func_controller(main,node->right,NULL);
        }
        if(base!=NULL){
            free(base);
        }
        if(main!=NULL){
            free(main);
        }
        return;
        //log
    }
    else if (all_data[0]>= 'c'&& all_data[3]=='e')
    {
        len=strlen("cosec");
        temp_node_data=realloc(node->data,(len+1));
        node->data=temp_node_data;
        strncpy(node->data,"cosec",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        //free(temp);
        return;
        //COSEC()
    }
    else if (all_data[0]=='c' &&all_data[2]=='s')
    {
        len=strlen("cos");
        temp_node_data=realloc(node->data,(len+1));
        node->data=temp_node_data;
        strncpy(node->data,"cos",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);
        return;
        //cos
    }
    else if (all_data[0]=='s')
    {
        len=strlen("sin");
        temp_node_data=realloc(node->data,(len+1));
        node->data=temp_node_data;
        strncpy(node->data,"sin",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);
        return;
        //sin
    }
    else if (all_data[0]=='t')
    {

        len=strlen("tan");
        temp_node_data=realloc(node->data,len+1);
        node->data=temp_node_data;
        strncpy(node->data,"tan",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);

        return;
        //tan
    }
    else if (all_data[0]=='c' && all_data[2]=='t')
    {
        len=strlen("cot");
        temp_node_data=realloc(node->data,len+1);
        node->data=temp_node_data;
        strncpy(node->data,"cot",len);
        node->data[len]='\0';
        temp=func_separater(len,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);
        return;
        //cot
    }
    else if (all_data[0]=='(')
    {
        len=strlen("()");
        temp_node_data=realloc(node->data,len+1);
        node->data=temp_node_data;
        strncpy(node->data,"()",len);
        node->data[len]='\0';
        temp=func_separater(0,all_data,temp);
        List_Node *root=func_controller(temp,node,NULL);
        free(all_data);
        return;
    }
    else if(all_data[0]=='a'&&all_data[1]=='r'&& all_data[2]=='c')
    {
        if(all_data[3]=='c' && all_data[6]=='e'){

            len=strlen("arccosec");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arccosec",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
           List_Node *root=func_controller(temp,node,NULL);
           free(all_data);

            return;
        }
        else if(all_data[3]=='c' && all_data[5]=='s'){

            len=strlen("arccos");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arccos",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
            List_Node *root=func_controller(temp,node,NULL);
            free(all_data);
            return;
            //arccos
        }
        else if(all_data[3]=='s'&& all_data[4]=='e'){
            len=strlen("arcsec");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arcsec",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
            List_Node *root=func_controller(temp,node,NULL);
            free(all_data);

            return;
            //arcsec
        }
        else if(all_data[3]=='s'){
            len=strlen("arcsin");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arcsin",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
           List_Node *root=func_controller(temp,node,NULL);
            free(all_data);
            return;
                //Done
        }
           //arcsin
        else if(all_data[3]=='t'){
            len=strlen("arctan");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arctan",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
            List_Node *root=func_controller(temp,node,NULL);
            free(all_data);

            return;
                            //arctan
        }
        else if(all_data[3]=='c' && all_data[5]=='t'){
            len=strlen("arccot");
            temp_node_data=realloc(node->data,len+1);
            node->data=temp_node_data;
            strncpy(node->data,"arccot",len);
            node->data[len]='\0';
            temp=func_separater(len,all_data,temp);
            List_Node *root=func_controller(temp,node,NULL);
            free(all_data);

            return;
            //arccot
        }
        else
        {
            printf("hata");
            return;
        }
    }
    else{
        //this is come from power
        List_Node *root=func_controller(all_data,node,NULL);

        return;
    }

}

char  *func_separater(int index,char *data,char *temp){

    int j=0;
    int i=0;
    if(data==NULL){
        return NULL;
    }
    temp=(char*)malloc(sizeof(char)*((strlen(data)-index+2)));
    if(temp==NULL){
        return NULL;
    }
    if(data[index]=='('){
        i=index+1;
        while(data[i+1]!='\0'){
            temp[j]=data[i];
            i++;
            j++;
        }
        temp[j]='\0';
        return temp;
        }
    else{
            i=index;
            j=0;
            while(data[i]!='\0'){
            temp[j]=data[i];
            i++;
            j++;
        }
        temp[j]='\0';
        return temp;
        }

}





void create_dataTree(List_Node *node){

    int power_info=1;
    char *data=NULL;
    int data_len;
    if(node->data!=NULL){
        data_len=strlen(node->data);
    }
    else{
        return;
    }
    data=(char*)malloc((data_len+1)*sizeof(char));
    strncpy(data,node->data,data_len);
    data[data_len]='\0';
    char*temp1=(char*)malloc(sizeof(char)*10);
    char*temp2=(char*)malloc(sizeof(char)*25);
    char*temp3=(char*)malloc(sizeof(char)*20);
    if(temp1==NULL || temp2==NULL || temp3==NULL){
        free(temp1);
        free(temp2);
        free(temp3);
        free(data);
        return;
    }
    int i=0;

    while((data[i]>='0'&& data[i]<='9')||(data[i]=='.')||(data[i]==',')&&data[i]!='\0'){
        temp1[i]=data[i];
        i++;
    }
    temp1[i]='\0';
    if(strlen(temp1)==0){
        free(temp1);
        temp1=NULL;
    }
    int j=i;
    int a=0;
    int brackets_in=0,brackets_out=0;
    if(data[i]=='\0'){
        power_info=0;
    }
    if(data[i]!='\0'){
        while(((data[i]!='^')||(brackets_in!=brackets_out))&&power_info==1){
            if(data[i]=='('){
                brackets_in++;
            }
            if(data[i]==')'){
                brackets_out++;
            }
            temp2[a]=data[i];
            a++;
            i++;
            if (data[i]=='\0')
            {
                power_info=0;
            }
        }
    }
    temp2[a]='\0';
    if(strlen(temp2)==0){
        free(temp2);
        temp2=NULL;
    }
    int z=i;
    int k=0;
    int power_bracket=0;
    if(power_info==1){
    i++;
    while (data[i]!='\0')
    {
        temp3[k]=data[i];
        k++;
        i++;
    }
    if(power_bracket==1){
        temp3[k-1]='\0';
    }
    else{
        temp3[k]='\0';
    }
    }
    else{
        free(temp3);
        temp3=NULL;
    }
    int temp1_len = (temp1 == NULL) ? 0 : strlen(temp1);
    int temp2_len = (temp2 == NULL) ? 0 : strlen(temp2);
    int temp3_len = (temp3 == NULL) ? 0 : strlen(temp3);
    Tree_Node *tree_node=(Tree_Node*)malloc(sizeof(Tree_Node));

    tree_node->out=NULL;
    tree_node->is_calc=0;
    tree_node->parent=NULL;
    tree_node->value=0;
    if (tree_node == NULL) {
        free(data);
        free(temp1);
        free(temp2);
        free(temp3);
        return;  // Memory allocation failed
    }
    tree_node->left=(Tree_Node*)malloc(sizeof(Tree_Node));
    tree_node->right=(Tree_Node*)malloc(sizeof(Tree_Node));
    tree_node->left->in=NULL;
    tree_node->right->in=NULL;
    tree_node->left->out=NULL;
    tree_node->right->out=NULL;
    tree_node->left->is_calc=0;
    tree_node->right->is_calc=0;
    tree_node->left->value=0;
    tree_node->right->value=0;
    if (tree_node->left == NULL || tree_node->right == NULL) {
        free(tree_node);
        free(data);
        free(temp1);
        free(temp2);
        free(temp3);
        return;  // Memory allocation failed
    }
    tree_node->right->left=(Tree_Node*)malloc(sizeof(Tree_Node));
    tree_node->right->right=(Tree_Node*)malloc(sizeof(Tree_Node));

    tree_node->right->left->out=NULL;
    tree_node->right->right->out=NULL;
    tree_node->right->right->is_calc=0;
    tree_node->right->left->is_calc=0;
    tree_node->right->right->value=0;
    tree_node->right->left->value=0;
    if (tree_node->right->left == NULL || tree_node->right->right == NULL) {
        free(tree_node->left);
        free(tree_node->right);
        free(tree_node);
        free(data);
        free(temp1);
        free(temp2);
        free(temp3);
        return;  // Memory allocation failed
    }
    tree_node->left->parent=tree_node;
    tree_node->right->parent=tree_node;
    node->tree_in=tree_node;
    tree_node->out=node;
    tree_node->right->left->parent=tree_node->right;
    tree_node->right->right->parent=tree_node->right;

    tree_node->data=(char*)malloc(sizeof(char)*2);
    tree_node->right->data=(char*)malloc(sizeof(char)*2);

    if (tree_node->data == NULL || tree_node->right->data == NULL) {
        free(tree_node->right->left);
        free(tree_node->right->right);
        free(tree_node->left);
        free(tree_node->right);
        free(tree_node);
        free(data);
        free(temp1);
        free(temp2);
        free(temp3);
        return;  // Memory allocation failed
    }

    strncpy(tree_node->data,"*",1);
    strncpy(tree_node->right->data,"^",1);
    tree_node->data[1]='\0';
    tree_node->right->data[1]='\0';
    if(temp2_len==0){
        tree_node->right->left->data=(char*)malloc((temp1_len+1)*sizeof(char));
        tree_node->left->data=(char*)malloc(sizeof(char)*2);
        strncpy(tree_node->left->data,"1",1);
        tree_node->left->data[1]='\0';
        strncpy(tree_node->right->left->data,temp1,temp1_len);
        tree_node->right->left->data[temp1_len]='\0';
        tree_node->right->left->in=NULL;
        if(temp1_len!=0&&temp3_len!=0){
            i=0;
            int is_number=1;
            while((temp3[i]!='\0')&&(is_number==1)){
                if(!((temp3[i]>='1'&&temp3[i]<='9')||(temp3[i]=='.')||(temp3[i]==','))){
                is_number=0;
                }
                i++;
            }
            if(is_number==1){
                tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                strncpy(tree_node->right->right->data,temp3,temp3_len);
                tree_node->right->right->data[temp3_len]='\0';
                tree_node->right->right->in=NULL;
            }
            else{
                // here we can decrease line of code but for now we have to understand whats going on !
                if(temp3[0]=='x'||temp3[0]=='e'||(temp3[0]=='p'&&temp3[1]=='i')){
                    tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                    strncpy(tree_node->right->right->data,temp3,temp3_len);
                    tree_node->right->right->data[temp3_len]='\0';
                    tree_node->right->right->in=NULL;
                }
                else{
                     tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                     strncpy(tree_node->right->right->data,temp3,temp3_len);
                     tree_node->right->right->data[temp3_len]='\0';
                    create_data(tree_node->right->right);
                }
            }
        }
        if(temp3_len==0&&temp1_len!=0){
            tree_node->right->right->data=(char*)malloc(sizeof(char)*2);
            strncpy(tree_node->right->right->data,"1",1);
            tree_node->right->right->data[1]='\0';
            tree_node->right->right->in=NULL;
        }


    }
    else
    {
        if(temp1_len==0){

            tree_node->left->data=(char*)malloc(sizeof(char)*2);
            strncpy(tree_node->left->data,"1",1);
            tree_node->left->data[1]='\0';
            tree_node->left->in=NULL;
        }
        else{
            tree_node->left->data=(char*)malloc((temp1_len+1)*sizeof(char));
            strncpy(tree_node->left->data,temp1,temp1_len);
            tree_node->left->data[temp1_len]='\0';
            tree_node->left->in=NULL;
        }

        if(temp3_len==0){
            tree_node->right->right->data=(char*)malloc(sizeof(char)*2);
            strncpy(tree_node->right->right->data,"1",1);
            tree_node->right->right->data[1]='\0';
            tree_node->right->right->in=NULL;
        }
        else{
            i=0;
            int is_number=0;
            while((temp3[i]!='\0')&&(is_number==1)){
                if(!((temp3[i]>='1'&&temp3[i]<='9')||(temp3[i]=='.')||(temp3[i]==','))){
                is_number==1;
                }
                i++;
            }
            if(is_number==1){
                tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                strncpy(tree_node->right->right->data,temp3,temp3_len);
                tree_node->right->right->data[temp3_len]='\0';
                tree_node->right->right->in=NULL;
            }
            else{
                    if(temp3[0]=='x'||temp3[0]=='e'||temp3[0]=='p'){
                        tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                        strncpy(tree_node->right->right->data,temp3,temp3_len);
                        tree_node->right->right->data[temp3_len]='\0';
                        tree_node->right->right->in=NULL;
                    }
                    else{
                        tree_node->right->right->data=(char*)malloc((temp3_len+1)*sizeof(char));
                        strncpy(tree_node->right->right->data,temp3,temp3_len);
                        tree_node->right->right->data[temp3_len]='\0';

                        create_data(tree_node->right->right);
                     }
                //power control
                //control power function and recursive
            }

        }
        if(temp2[0]=='x'||temp2[0]=='e'||temp2[0]=='p'){
            tree_node->right->left->data=(char*)malloc((temp2_len+1)*sizeof(char));
            strncpy(tree_node->right->left->data,temp2,temp2_len);
            tree_node->right->left->data[temp2_len]='\0';
            tree_node->right->left->in=NULL;
        }
        else{
            tree_node->right->left->data=(char*)malloc((temp2_len+1)*sizeof(char));
            strncpy(tree_node->right->left->data,temp2,temp2_len);
            tree_node->right->left->data[temp2_len]='\0';
            create_data(tree_node->right->left);
            //control base function //recursive
        }
    }//Control base function //recursive
    free(data);
    free(temp1);
    free(temp2);
    free(temp3);
    return;
}

List_Node *func_controller(char *input,Tree_Node *node,List_Node *root){
    List_Node *this_root=NULL;
    this_root=create_dataList(input);
    if (this_root == NULL) {
        return NULL;
    }

    List_Node *curr=this_root;
    if(node!=NULL){
        node->in=this_root;
        this_root->tree_out=node;
    }
    if(root!=NULL){
        root=this_root;
    }
    if(curr->next==NULL){
        create_dataTree(curr);
        if(node!=NULL){
            if(node->parent->data[0]=='l'){
                return curr;
             }
             free(input);
             input=NULL;
            }
        return curr;

    }
    while (curr!=NULL){
        create_dataTree(curr);
        if(curr->next==NULL){
            while(curr->prev!=NULL){
                curr=curr->prev;
            }
            if(node!=NULL){
             if(node->parent->data[0]=='l'){
                return curr;
             }
             free(input);
            input=NULL;
            }
            return curr;
        }
        else{
            curr=curr->next->next;
        }
    }
}
Tree_Node *list_calc(List_Node *curr){
    int check_next=1;
    if(curr==NULL){
        return NULL;
    }
    if(curr->next==NULL){
        curr->is_calc=0;
        if(curr->tree_out!=NULL){
            curr->tree_out->value=curr->value;
            curr->tree_out->is_calc=1;
            return curr->tree_out;
        }
        else{
         curr->tree_out = (Tree_Node*)malloc(sizeof(Tree_Node));
         if(curr->tree_out==NULL){
            return NULL;
         }
         curr->tree_out->value=curr->value;
         curr->tree_out->is_calc=1;
         return curr->tree_out;
        }
    }
    while(check_next!=0){
            if(curr->data==NULL){
                return NULL;
            }
            if(curr->data[0]=='*'){
                double num1=curr->prev->value;
                double num2=curr->next->value;
                double result=num1*num2;
                free(curr->data);
                curr->data=(char*)malloc(sizeof(char)*2);
                if(curr->data==NULL){
                    return NULL;
                }
                strncpy(curr->data,"+",1);
                curr->data[1]='\0';
                curr->prev->value=0;
                curr->next->value=result;
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
            else if (curr->data[0]=='/')
            {
                double num1=curr->prev->value;
                double num2=curr->next->value;
                double result=num1/num2;
                free(curr->data);
                curr->data=(char*)malloc(sizeof(char)*2);
                if(curr->data==NULL){
                    return NULL;
                }
                strncpy(curr->data,"+",1);
                curr->data[1]='\0';
                curr->prev->value=0;
                curr->next->value=result;
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
            else{
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
    }
    while(curr->prev!=NULL){
        curr=curr->prev;
    }
    check_next=1;
        while (check_next!=0)
        {
           if(curr->data[0]=='+'){
                double num1=curr->prev->value;
                double num2=curr->next->value;
                double result=num1+num2;
                curr->prev->value=0;
                curr->next->value=result;
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
            else if (curr->data[0]=='-')
            {
                double num1=curr->prev->value;
                double num2=curr->next->value;
                double result=num1-num2;
                free(curr->data);
                curr->data=(char*)malloc(sizeof(char)*2);
                 if(curr->data==NULL){
                    return NULL;
                }
                strncpy(curr->data,"+",1);
                curr->data[1]='\0';
                curr->prev->value=0;
                curr->next->value=result;
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
            else{
                if(curr->next==NULL){
                    check_next=0;
                }
                else{
                    curr=curr->next;
                }
            }
        }
    while(curr->prev!=NULL){
        curr->prev->value=curr->value;
        curr->value=0;
        curr->is_calc=0;
        curr=curr->prev;
        //free(curr->next->data);
        //curr->next->data=NULL;
        //free(curr->next);
        //curr->next=NULL;
    }
    curr->is_calc=0;
    if(curr->tree_out!=NULL){
        curr->tree_out->value=curr->value;
        curr->tree_out->in=curr;
        curr->tree_out->is_calc=1;
        return curr->tree_out;
    }
    else{
         curr->tree_out = (Tree_Node*)malloc(sizeof(Tree_Node));
         if(curr->tree_out==NULL){
            return NULL;
         }
         curr->tree_out->in=curr;
         curr->tree_out->value=curr->value;
         curr->tree_out->is_calc=1;
         return curr->tree_out;
    }
}


Tree_Node *list_reader(List_Node *curr,double x){
    int check_next=0;
    double data_float;
if(curr==NULL){
    return NULL;

}
if(curr->next==NULL){
     tree_reader(curr,x);
     curr->tree_out=list_calc(curr);
     return curr->tree_out;
}
    while(check_next!=1){
        if(curr->is_calc==1){
            if(curr->next!=NULL&&curr->next->next!=NULL){
                curr=curr->next->next;
            }
            else{
                check_next=1;
            }
        }
        else{
            tree_reader(curr,x);
            if(curr->next!=NULL &&curr->next->next!=NULL){
                curr=curr->next->next;
            }
            else{
                check_next=1;
            }
        }
    }
    while(curr->prev!=NULL){
        curr=curr->prev;
    }
    curr->tree_out=list_calc(curr);
    return curr->tree_out;
}

//yarýn burdayýz
//create data ve data tree de memory leak var kontrol et;
Tree_Node *tree_calc(Tree_Node *curr,double x){
    if(curr==NULL){
        return NULL;
    }
    if(curr->in==NULL){
        if(curr->data[0]=='x')
        {
              curr->value=x;
              return curr;
        }
        else if(curr->data[0]=='e')
        {
            curr->value=2.71828182850;
            return curr;
        }
        else if(curr->data[0]=='p')
        {
            curr->value=3.14159265359;
            return curr;
        }
        else
        {
            //number
            //printf("curr:%s\n",curr->data);
            if(curr->data==NULL)return NULL;
            curr->value=atof(curr->data);
            return curr;
        }

        }
    else
        {
            curr=list_reader(curr->in,x);
            if(curr==NULL){
                return NULL;
            }
            return curr;
        }
}

void tree_reader(List_Node *node,double x){
if (node == NULL || node->tree_in == NULL || node->data == NULL || node->tree_in->left==NULL || node->tree_in->right==NULL || node->tree_in->right->left==NULL ) {
    printf("Hata: Geçersiz düğüm\n");
    return;
}
Tree_Node *curr=NULL;
curr=node->tree_in->right->left;

if(node==NULL || node->data==NULL){
    printf("hata");
    return;
}
double num1=0,num2=0;

if(curr->data[2]=='g'){
    if(curr->left==NULL || curr->right==NULL)return;
    curr->left=tree_calc(curr->left,x);
    curr->right=tree_calc(curr->right,x);
    curr->value=logbase(curr->right->value,curr->left->value);
    num1=curr->value;
    if(curr->parent->right==NULL)return;
    curr->parent->right=tree_calc(curr->parent->right,x);
    num2=curr->parent->right->value;
    num1=pow(num1,num2);
    if(curr->parent->parent->left->data==NULL)return;
    num2=atof(curr->parent->parent->left->data);
    num1=num1*num2;
    curr->parent->parent->out->is_calc=1;
    curr->parent->parent->out->value=num1;
}
else if(curr->data[0]=='a'&&curr->data[5]=='c'){
            //arcsec
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=acos(1/curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;
    }
else if(curr->data[0]=='a'&&curr->data[4]=='c'&&curr->data[6]=='e'){
         //arccosec
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=asin(1/curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='a'&&curr->data[3]=='t'){
         //arctan
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=atan(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='a'&&curr->data[5]=='t'){
         //arccot
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=atan(1/curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='a'&&curr->data[4]=='i'){
         //arcsin
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=asin(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='a'&&curr->data[3]=='c'){
         //arccos
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value = acos(1 / curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='c'&&curr->data[3]=='e'){
            //cosec
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=1/sin(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[0]=='c'&&curr->data[2]=='s'){
            //cos

        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=cos(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[1]=='i'){
            //sin
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=sin(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;;

    }
else if(curr->data[0]=='t'){
            //tan

        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=tan(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[2]=='t'){
            //cot
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=1/tan(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[2]=='c'){
            //sec
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=1/cos(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }
else if(curr->data[1]=='n'){
        curr=tree_calc(curr,x);
        if(curr->parent->right==NULL)return ;
        curr->parent->right=tree_calc(curr->parent->right,x);
        curr->value=log(curr->value);
        num1=pow(curr->value,curr->parent->right->value);
        if(curr->parent->parent->left->data==NULL)return;
        num2=atof(curr->parent->parent->left->data);
        node->value=num1*num2;
        node->is_calc=1;

    }

else if(curr->data[0]=='('){
        process_trigonometric_function(curr,x);

    }
else{
        process_trigonometric_function(curr,x);
    }
    return;
}
void process_trigonometric_function(Tree_Node *curr, double x) {
    curr = tree_calc(curr, x);
    if(curr->parent->right==NULL)return ;
    curr->parent->right = tree_calc(curr->parent->right, x);
    double num1 = pow(curr->value, curr->parent->right->value);
    if(curr->parent->parent->left->data==NULL)return;
    double num2 = atof(curr->parent->parent->left->data);
    curr->parent->parent->out->value = num1 * num2;
    curr->parent->parent->out->is_calc = 1;
}
double func_calc(double x,char *function){

    double result;
    List_Node *root=NULL;
    root=func_controller(function,NULL,(List_Node*)malloc(sizeof(List_Node)));
    if(root==NULL){
        free(function);
        return 0;
    }
    Tree_Node *result_node=(Tree_Node*)malloc(sizeof(Tree_Node));

    if(result_node==NULL){
        free_data(root);
        free(function);
        return 0;
    }
    root->tree_out=result_node;
    result_node=list_reader(root,x);
    result=result_node->value;
    free_data(root);
    free(result_node);
    result_node=NULL;
    return result;
}

int main()
{

    int value;
    int choice=printMenu();
       switch(choice) {
        case 1:
            bi_section_method();
            break;
        case 2:
            regula_falsi();
            break;
        case 3:
            newton_raphson();
            break;
        case 4:
            reverse_matrix();
            break;
        case 5:
            gauss_elimination();
            break;
        case 6:
            gauss_seidal();
            break;
        case 7:
            numerical_deritative();
            break;
        case 8:
            simpson();
            break;
        case 9:
            trapezoidal();
            break;
        case 10:
            printf("\nThis option not available.\n");
            break;
        case 0:
            return 0;

    }
    while(1){
    printf("\nIf you'd like to continue press 1 or not press 0 ");
    scanf("%d",&value);
    clear_input_buffer();
    if(value==0){
        return 0;
    }
    if(value==1){
        //clear console
        main();
    }
    }
}



int menu(){
    int choice;
    printf("0)Quit-\n");
    printf("1)Bisection-\n");
    printf("2)Regula-Falsi-\n");
    printf("3)Newton Raphson-\n");
    printf("4)Inverse Matrix-\n");
    printf("5)Gauss-Elimination-\n");
    printf("6)Gauss-Seidel-\n");
    printf("7)Numerical Differentiation-\n");
    printf("8)Simpson's Rule-\n");
    printf("9)Trapezoidal Rule-\n");
    printf("10)Gregory-Newton-\n");
    printf("Choice:");
    scanf("%d",&choice);
    clear_input_buffer();
    return choice ;
}


int printMenu(){
    int choice=0,choice_controller=1;
    choice=menu();
    while(choice_controller){
        if(choice==0){
            exit(0);
        }
        else if(choice>10|| choice<0){
            //clear console
            printf("\nWrong choice\n\n");
            choice=menu();
        }
        else{
            choice_controller=0;
            return choice;
        }
    }
}
void bi_section_method() {
    double epsilon, start, end;
    int iteration, stop_choice;
    char *function=NULL;
    function = get_input();
    printf("\nStart:");
    scanf("%lf", &start);
    clear_input_buffer();
    printf("\nEnd:");
    scanf("%lf", &end);
    clear_input_buffer();
    printf("\nEpsilon:");
    scanf("%lf", &epsilon);
    clear_input_buffer();
    printf("\nIteration count:");
    scanf("%d", &iteration);
    clear_input_buffer();
    printf("\nStopping criterion:\n");
    printf("f(x) <= epsilon --> 1\n");
    printf("(end - start) / 2^n <= epsilon --> 2\n");
    printf("Choice:");
    scanf("%d", &stop_choice);

    while (stop_choice != 1 && stop_choice != 2) {
        printf("\nInvalid choice. Please choose 1 or 2, or 0 to exit.\n");
        printf("Choice: ");
        scanf("%d", &stop_choice);
        if (stop_choice == 0) {
            printf("Exiting program.\n");
            return;
        }
    }

    if (stop_choice == 1) {
        bisection_method(start, end, epsilon, iteration, function, 1);
    } else {
        bisection_method(start, end, epsilon, iteration, function, 2);
    }
}

void bisection_method(double start, double end, double epsilon, int iteration, char* function, int stop_choice) {
    if(start==end){
        printf("Wrong intervals!");
        return;
    }
    int i = 0, stop_condition = 0;
    double f_start,f_mid,f_end,mid,start_,end_;
    start_=start;
    end_=end;
    while (iteration != i-1 && stop_condition != 1) {
        mid = (start_ + end_) / 2;
        f_start=func_calc(start_,function);
        f_end=func_calc(end_,function);
        f_mid=func_calc(mid,function);
        printf("------------------\n");
        printf("start: %lf\n", start_);
        printf("end: %lf\n", end_);
        printf("middle: %lf\n", mid);
        printf("F(start): %lf\n", f_start);
        printf("F(end): %lf\n", f_end);
        printf("F(middle): %lf\n", f_mid);
        printf("Iteration: %d\n", i + 1);
        printf("------------------\n");

        if ((stop_choice == 1 && fabs(f_mid) < epsilon) || (stop_choice == 2 && fabs((end - start) / pow(2, i + 1)) < epsilon) || f_mid==0) {
            stop_condition = 1;
            printf("result: %lf\n", mid);
            printf("------------------\n");
        }
        else {
            if (f_mid * f_start < 0) {
                end_= mid;
            } else if (f_mid * f_end < 0) {
                start_ = mid;
            } else {
                printf("\nNo root in this interval.\n");
                return;
            }
        }
        i++;
    }
free(function);
}
double get_double_input(int i, int j) {
    double value;
    int read_count;
    printf("\nEnter value for [%d][%d]: ", i, j);
    read_count = scanf("%lf", &value);
    clear_input_buffer();
    while (read_count != 1) { // Eğer scanf başarılı değilse, kullanıcıdan tekrar iste
        while(getchar() != '\n'); // Hatalı girdiyi temizle
        printf("Invalid input. Please enter a double value for [%d][%d]: ", i, j);
        read_count = scanf("%lf", &value);
    }
    return value;
}

double **get_input_matrix(int dimension) {
    double **matrix = (double**) malloc(dimension * sizeof(double *));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for matrix rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimension; i++) {
        matrix[i] = malloc(dimension * sizeof(double));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed for matrix columns at row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] = get_double_input(i, j); // Güvenli girdi alma
        }
    }

    return matrix;
}
void free_tree(Tree_Node *node) {
    Tree_Node *curr;
    curr=node->right->left;
    if(curr->data[2]=='g'){
        curr=curr->left;
        if(curr->in!=NULL){
            free_list(curr->in);
        }
        curr=curr->parent->right;
        if(curr->in!=NULL){
            free_list(curr->in);
        }
        curr=curr->parent;
        if(curr->left->data!=NULL){
            free(curr->left->data);
            curr->left->data=NULL;
        }
        if(curr->left!=NULL){
            curr->left->parent=NULL;
            free(curr->left);
            curr->left=NULL;
        }
        if(curr->right->data!=NULL){
            free(curr->right->data);
            curr->right->data=NULL;
        }
        if(curr->right!=NULL){
            curr->right->parent=NULL;
            free(curr->right);
            curr->right=NULL;
        }
        curr=curr->parent->right;

        if(curr->in!=NULL){
            free_list(curr->in);
        }
        curr=curr->parent;
         if(curr->left->data!=NULL){
            free(curr->left->data);
            curr->left->data=NULL;
        }
        if(curr->left!=NULL){
            curr->left->parent=NULL;
            free(curr->left);
            curr->left=NULL;
        }
        if(curr->right->data!=NULL){
            free(curr->right->data);
            curr->right->data=NULL;
        }
        if(curr->right!=NULL){
            curr->right->parent=NULL;
            free(curr->right);
            curr->right=NULL;
        }
        curr=curr->parent;
         if(curr->left->data!=NULL){
            free(curr->left->data);
            curr->left->data=NULL;
        }
        if(curr->left!=NULL){
            curr->left->parent=NULL;
            free(curr->left);
            curr->left=NULL;
        }
        if(curr->right->data!=NULL){
            free(curr->right->data);
            curr->right->data=NULL;
        }
        if(curr->right!=NULL){
            curr->right->parent=NULL;
            free(curr->right);
            curr->right=NULL;
        }
        free(curr->data);
        curr->data=NULL;
        free(curr);
        curr=NULL;
    }
    else{
        if(curr->in!=NULL){
            free_list(curr->in);
        }
        curr=curr->parent;
        if(curr->left->data!=NULL){
            free(curr->left->data);
            curr->left->data=NULL;
        }
        if(curr->left!=NULL){
            curr->left->parent=NULL;
            free(curr->left);
            curr->left=NULL;
        }
        curr=curr->right;
        if(curr->in!=NULL){
            free_list(curr->in);
        }
        curr=curr->parent;
        if(curr->right->data!=NULL){
            free(curr->right->data);
            curr->right->data=NULL;
        }
        if(curr->right!=NULL){
            curr->right->parent=NULL;
            free(curr->right);
            curr->right=NULL;
        }
        curr=curr->parent;
        if(curr->right->data!=NULL){
            free(curr->right->data);
            curr->right->data=NULL;
        }
        if(curr->right!=NULL){
            curr->right->parent=NULL;
            free(curr->right);
            curr->right=NULL;
        }
        if(curr->left->data!=NULL){
            free(curr->left->data);
            curr->left->data=NULL;
        }
        if(curr->left!=NULL){
            curr->left->parent=NULL;
            free(curr->left);
            curr->left=NULL;
        }
        free(curr->data);
        curr->data=NULL;
        free(curr);
        curr=NULL;
    }
}


void free_list(List_Node *node) {
    if(node==NULL){
            return;
    }
    if(node->next== NULL){
        free_tree(node->tree_in);
        node->tree_in = NULL;
    }
    while (node->next != NULL) {
        node= node->next;
    }
    while(node->prev!=NULL){
        if (node->tree_in != NULL) {
            free_tree(node->tree_in);
            node->tree_in = NULL;
        }
        node=node->prev;
        free(node->next->data);
        node->next->data=NULL;
        free(node->next);
        node->next=NULL;
    }
    free(node->data);
    node->data=NULL;
    free(node);
    node=NULL;
}
void free_data(List_Node *root) {
    if(root!=NULL){
        free_list(root);
        return;
    }
}
void regula_falsi() {
    double epsilon, start, end;
    int iteration, stop_choice;
    char *function;
    function = get_input();
    printf("\nStart:");
    scanf("% lf", &start);
    clear_input_buffer();
    printf("\nEnd:");
    scanf("%lf", &end);
    clear_input_buffer();
    printf("\nEpsilon:");
    scanf("%lf", &epsilon);
    clear_input_buffer();
    printf("\nIteration count:");
    scanf("%d", &iteration);
    clear_input_buffer();
    printf("\nStopping criterion:\n");
    printf("f(x) <= epsilon --> 1\n");
    printf("(end - start) <= epsilon --> 2\n");
    printf("Choice:");
    scanf("%d", &stop_choice);

    while (stop_choice != 1 && stop_choice != 2) {
        printf("\nInvalid choice. Please choose 1 or 2, or 0 to exit.\n");
        printf("Choice: ");
        scanf("%d", &stop_choice);
        if (stop_choice == 0) {
            printf("Exiting program.\n");
            return;
        }
    }

    if (stop_choice == 1) {
        regula_falsi_method(start, end, epsilon, iteration, function, 1);
    } else {
        regula_falsi_method(start, end, epsilon, iteration, function, 2);
    }
}
void regula_falsi_method(double start, double end, double epsilon, int iteration, char* function, int stop_choice) {
    if(start==end){
        printf("Wrong intervals!");
        return;
    }
    int i = 0, stop_condition = 0;
    double f_start,f_mid,f_end,mid,start_,end_;
    start_=start;
    end_=end;
    while (iteration != i-1 && stop_condition != 1) {
        f_start=func_calc(start_,function);
        f_end=func_calc(end_,function);
        mid = start_-(f_start * (end_ - start_) /(f_end-f_start));
        f_mid=func_calc(mid,function);
        printf("------------------\n");
        printf("start: %lf\n", start_);
        printf("end: %lf\n", end_);
        printf("middle: %lf\n", mid);
        printf("F(start): %lf\n", f_start);
        printf("F(end): %lf\n", f_end);
        printf("F(middle): %lf\n", f_mid);
        printf("Iteration: %d\n", i + 1);
        printf("------------------\n");

        if ((stop_choice == 1 && fabs(f_mid) < epsilon) || (stop_choice == 2 && fabs((end - start)) < epsilon)) {
            stop_condition = 1;
            printf("result: %f\n", mid);
            printf("------------------\n");
        }
        else {
            if (f_mid * f_start < 0) {
                end_= mid;
            } else if (f_mid * f_end < 0) {
                start_ = mid;
            } else {
                printf("\nNo root in this interval.\n");
                return;
            }
        }
        i++;
    }
free(function);
}
void numerical_deritative(){
double h, x;
int h_choice;
int d_choice;
char *function=NULL;
double result;
function = get_input();

    printf("\nEnter ""x"" value:\n");
    scanf("%lf", &x);
    clear_input_buffer();
    printf("\n1)Standart Epsilon: 2.2 x 10^(-16)\n");
    printf("2)Your own Epsilon: (?)\n");
    printf("Choice:");
    scanf("%d",&h_choice);
    clear_input_buffer();
    while (h_choice != 1 && h_choice != 2) {
        printf("\nInvalid choice. Please choose 1 or 2, or 0 to exit.\n");
        printf("Choice: ");
        scanf("%d", &h_choice);
        clear_input_buffer();
        if (h_choice == 0) {
            printf("\nExiting program.\n");
            return;
        }
    }
    if(h_choice==1){
        h=2.2*pow(10,-16);
        h=sqrt(h);
    }
    else{
        printf("\nEpsilon:");
        scanf("%lf", &h);
        clear_input_buffer();
        h=sqrt(h);
    }
    printf("\n1)Forward Difference Deritative:");
    printf("\n2)Backward Difference Deritative:");
    printf("\n3)Central Diffrence Deritative:");
    printf("\nChoice:");
    scanf("%d",&d_choice);
    clear_input_buffer();
    while (d_choice != 1 && d_choice != 2 && d_choice!=3) {
        printf("\nInvalid choice. Please choose 1 or 2 or 3, or 0 to exit.\n");
        printf("Choice: ");
        scanf("%d", &d_choice);
        if (d_choice == 0) {
            printf("\nExiting program.\n");
            return;
        }
    }
    if(d_choice==1){
        result=forward_difference_deritative(x,h,function);
    }
    else if(d_choice==2){
        result=backward_difference_deritative(x,h,function);
    }
    else{
        result=central_difference_deritative(x,h,function);
    }
    printf("\nResult:%lf",result);
    return;

}
double forward_difference_deritative(double x, double h,char *function) {
    return (func_calc(x + h,function) - func_calc(x,function)) / (h);
}
double backward_difference_deritative(double x, double h,char *function) {
    return (func_calc(x,function) - func_calc(x - h,function)) / (h);
}
double central_difference_deritative(double x, double h,char* function) {
    return (func_calc(x + h,function) - func_calc(x - h,function)) / (2 * h);
}void newton_raphson() {
    double epsilon, start;
    int iteration;
    char *function=NULL;
    function = get_input();

    printf("\nStart value:");
    scanf("%lf", &start);
    clear_input_buffer();
    printf("\nEpsilon:");
    scanf("%lf", &epsilon);
    clear_input_buffer();
    printf("\nIteration count:");
    scanf("%d", &iteration);
    clear_input_buffer();


    newton_raphson_method(start, epsilon, iteration, function);

}
void newton_raphson_method(double root, double epsilon, int iteration, char* function) {
    int i = 0, stop_condition = 0;
    double f_root,f_newroot,root_,newroot_;
    root_=root;
    while (iteration > i && stop_condition != 1) {
        f_root=func_calc(root_,function);
        newroot_=root-(f_root/forward_difference_deritative(root_,pow(10,-5),function));
        f_newroot=func_calc(newroot_,function);

        printf("------------------\n");
        printf("x_1: %f\n", root_);
        printf("x_2: %f\n", newroot_);
        printf("F(x_1): %lf\n", f_root);
        printf("F(x_2): %lf\n", f_newroot);
        printf("Iteration: %d\n", i + 1);
        printf("------------------\n");

        if (( fabs(f_newroot) < epsilon) || ( fabs((newroot_ - root_)) < epsilon)) {
            stop_condition = 1;
            printf("result: %lf\n", newroot_);
            printf("------------------\n");
        }
        else {
            root_=newroot_;
        }
        i++;
    }
free(function);
}
double simpson_method_1(double a, double b, char* function) {
    double mid = (a + b) / 2;
    return (b - a) / 6.0 * (func_calc(a, function) + 4 * func_calc(mid, function) + func_calc(b, function));
}

double simpson_method_2(double a, double b, char* function) {
    double h = (b - a) / 3;
    return (b - a) / 8.0 * (func_calc(a, function) + 3 * func_calc(a + h, function) + 3 * func_calc(a + 2 * h, function) + func_calc(b, function));
}

void simpson_method(char* function, int choice, int count, double top, double bot) {
    if (top == bot) {
        printf("\nResult: 0\n");
        return;
    }
    if ((choice == 1 && count % 2 != 0) || (choice == 2 && count % 3 != 0)) {
        printf("Error: Segment count must be even for Simpson 1/3 and a multiple of 3 for Simpson 3/8.\n");
        return;
    }

    double interval = (top - bot) / count;
    double all_sum = 0;
    for (int i = 0; i < count; i++) {
        double a = bot + interval * i;
        double b = a + interval;
        if (choice == 1) {
            all_sum += simpson_method_1(a, b, function);
        } else {
            all_sum += simpson_method_2(a, b, function);
        }
    }
    printf("\nResult: %lf\n", all_sum);
}

void simpson() {
    char* function = get_input();
    int method_choice, count;
    double top, bot;
    printf("Enter top value for function: ");
    scanf("%lf", &top);
    clear_input_buffer();
    printf("Enter bottom value for function: ");
    scanf("%lf", &bot);
    clear_input_buffer();
    printf("\n1) Simpson -> 1/3\n2) Simpson -> 3/8\nChoice: ");
    scanf("%d", &method_choice);
    clear_input_buffer();
    while (method_choice != 1 && method_choice != 2) {
        printf("\nInvalid choice. Please choose 1 or 2, or 0 to exit.\nChoice: ");
        scanf("%d", &method_choice);
        clear_input_buffer();
        if (method_choice == 0) {
            printf("\nExiting program.\n");
            return;
        }
    }
    printf("\nHow many parts do you want to divide? --> (if you give a high number it will be more accurate)\n");
    scanf("%d", &count);
    clear_input_buffer();
    simpson_method(function, method_choice, count, top, bot);
}
void trapezoidal(){
    char *function;
    function=get_input();

    int count;
    double top,bot;
    printf("Enter top value for function:");
    scanf("%lf",&top);
    clear_input_buffer();
    printf("Enter bottom value for function:");
    scanf("%lf",&bot);
    clear_input_buffer();
    printf("\nHow many parts do you want to divide? --> (if you give high number it will be more true)\n");
    scanf("%d",&count);
    clear_input_buffer();
    trapezoidal_method(function,count,top,bot);

}
void trapezoidal_method(char* function,int count,double top ,double bot){
    if(top==bot){
        printf("\nResult:0");
        return;
    }
    double interval =(top-bot)/count;
    double all_sum=0;

    for(int i=0;i<count;i++){
        double x1=bot+interval * (i);
        double x2=x1+interval;
        all_sum=all_sum+trapezoidal_calc(x2,x1,function);

    }
    printf("\nResult:%lf",all_sum);
    return;
}
double trapezoidal_calc(double x2,double x1,char *function){
    return (func_calc(x2,function)+func_calc(x1,function))*(x2-x1)/2;
}
void swap_rows(double **matrix, double *vector, int row1, int row2, int dimension) {
    // Satırları değiştir
    double *temp_row = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp_row;

    // Eğer bir vektör varsa, onun elemanlarını da değiştir
    if (vector != NULL) {
        double temp_val = vector[row1];
        vector[row1] = vector[row2];
        vector[row2] = temp_val;
    }
}
void reverse_matrix() {
    int dimension;
    printf("\nWrite dimension of matrix:");
    scanf("%d", &dimension);
    clear_input_buffer();
    double **matrix = get_input_matrix(dimension);

    printf("\n\nOriginal Matrix\n");
    for (int i = 0; i < dimension; i++) {
        printf("[ ");
        for (int j = 0; j < dimension; j++) {
            printf(" %lf ", matrix[i][j]);
        }
        printf(" ]\n");
    }

    double matrix_1[dimension][dimension];
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix_1[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < dimension; i++) {
        if (matrix[i][i] == 0) {  // Check for zero diagonal element
            // Find a row to swap
            int swap_row = -1;
            for (int k = i + 1; k < dimension; k++) {
                if (matrix[k][i] != 0) {
                    swap_row = k;
                    break;
                }
            }
            if (swap_row == -1) {
                printf("Matrix is singular and cannot be reversed.\n");
                return;
            }
            swap_rows(matrix,NULL,i, swap_row, dimension);
            swap_rows(matrix_1,NULL, i, swap_row, dimension);
        }

        // Normalize the diagonal element to 1
        double diag = matrix[i][i];
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] /= diag;
            matrix_1[i][j] /= diag;
        }

        // Eliminate all other elements in the current column
        for (int k = 0; k < dimension; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < dimension; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    matrix_1[k][j] -= factor * matrix_1[i][j];
                }
            }
        }
    }

    printf("\n\nReversed Matrix\n");
    for (int i = 0; i < dimension; i++) {
        printf("[ ");
        for (int j = 0; j < dimension; j++) {
            printf(" %lf ", matrix_1[i][j]);
        }
        printf(" ]\n");
    }

    // Free the allocated memory
    for (int i = 0; i < dimension; i++) {
        free(matrix[i]);
    }
    free(matrix);
}




void gauss_elimination() {
    int dimension;
    printf("\nWrite dimension of matrix:");
    scanf("%d", &dimension);
    clear_input_buffer();
    double **matrix = get_input_matrix(dimension);
    double *vector = get_vector(dimension);

    for (int i = 0; i < dimension; i++) {
        if (fabs(matrix[i][i]) < 1e-6) {  // Check if the diagonal element is too small or zero
            int swap_row = -1;
            for (int k = i + 1; k < dimension; k++) {
                if (fabs(matrix[k][i]) > 1e-6) {
                    swap_row = k;
                    break;
                }
            }
            if (swap_row == -1) {
                printf("No suitable pivot found. The system may be singular or poorly conditioned.\n");
                return;
            }
            swap_rows(matrix, vector, i, swap_row, dimension);
        }

        double point = matrix[i][i];
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] /= point;
        }
        vector[i] /= point;

        for (int k = 0; k < dimension; k++) {
            if (k != i) {
                double point_2 = -matrix[k][i];
                for (int j = 0; j < dimension; j++) {
                    matrix[k][j] += matrix[i][j] * point_2;
                }
                vector[k] += vector[i] * point_2;
            }
        }
    }

    // Print the root vector
    printf("\nRoot Vector:");
    for (int i = 0; i < dimension; i++) {
        printf("\n[ %lf ]", vector[i]);
    }

    // Free allocated memory
    for (int i = 0; i < dimension; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
}
void gauss_seidal() {
    int dimension;
    printf("\nWrite dimension of matrix:");
    scanf("%d", &dimension);
    clear_input_buffer();

    double **matrix = get_input_matrix(dimension);
    double *vector_root = get_vector(dimension);
    double *start_root = malloc(dimension * sizeof(double));
    double *temp = calloc(dimension, sizeof(double));

    int iteration = 0, i = 0, j = 0, choice;

    printf("\n\n 1)Default Start Roots:");
    printf("\n 2)Your Own Start Roots:");
    printf("\nChoice:");
    scanf("%d", &choice);
    clear_input_buffer();
    if (choice == 1) {
        for (i = 0; i < dimension; i++) {
            start_root[i] = 0;
        }
    } else if (choice == 2) {
        start_root = get_vector(dimension);
    } else {
        printf("\nInvalid choice, please enter a valid choice!");
        while (choice != 1 && choice != 2) {
            printf("\nChoice:");
            scanf("%d", &choice);
            clear_input_buffer();
            if (choice == 1) {
                for (i = 0; i < dimension; i++) {
                    start_root[i] = 0;
                }
            } else if (choice == 2) {
                start_root = get_vector(dimension);
            } else {
                printf("Exiting program ");
                return;
            }
        }
    }

    printf("\nEnter the number of iterations: ");
    scanf("%d", &iteration);
    clear_input_buffer();

    while (iteration > 0) {
        for (i = 0; i < dimension; i++) {
            temp[i] = vector_root[i]; // Reset temp for current row calculation
            for (j = 0; j < dimension; j++) {
                if (i != j) {
                    temp[i] -= matrix[i][j] * start_root[j];
                }
            }
            start_root[i] = temp[i] / matrix[i][i];
        }
        iteration--;
    }

    printf("\nResult Vector:");
    for (i = 0; i < dimension; i++) {
        printf("\n[ %lf ]", start_root[i]);
    }

    // Clean up memory
    for (i = 0; i < dimension; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(start_root);
    free(temp);
}
double *get_vector(int dimension){
    printf("\nEnter vector values!\n");
    double *vector_root=(double*)malloc(sizeof(double)*(dimension+1));
    for (int i = 0; i <dimension; i++)
    {
        printf("\n");
        scanf("%lf",&vector_root[i]);
        clear_input_buffer();
    }
    return vector_root;
}
int get_max_by_col(double **matrix,int col_num,int dimension){
int row_num=0,i,j;
int max=matrix[0][col_num];
for(i=0;i<dimension;i++){
   if( matrix[i][col_num]>max){
    max=matrix[i][col_num];
    row_num=i;
   }
}
return row_num;
}
/*void newton_gregory_inter(){
    int choice;
    double x;

    printf("\nEnter ""x"" for interpolation:" );
    scanf("%lf",&x);
    printf("\n1)Newton-Gregory Forward İnterpolation");
    printf("\n2)Newton-Gregory Backward İnterpolation");
    printf("\nChoice:");
    scanf("%d",&choice);
    if(choice==1){
        forward_newton(function,x);
    }
    else if(choice==2){
        backward_newton(function,x);
    }
    else{
        printf("\n Invalid choice!");
        while(choice!=1 &&choice!=2){
            if(choice==0){
                printf("exiting program");
                return;
            }
        }
        if(choice==1){
            forward_newton(function,x);
        }
        else{
            backward_newton(function,x);

        }
    }
    return;
}

void forward_newton(char *function, double x){

}
void backward_newton(char *function, double x){
double result=func_calc(x,function);
printf("\n\nResult:%lf",)
}*/
