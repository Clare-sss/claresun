#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>



sp_tuples * load_tuples(char* input_file)
{
    // Set space of matrix;
    sp_tuples * matrix=malloc(sizeof(sp_tuples));
    matrix->tuples_head = NULL;
    
    // Open the file for reading;
    FILE *love;
    love=fopen(input_file,"r");
    
    // Scan the row and column and initialize variables & pointers
    fscanf(love,"%d %d",&(matrix->m),&(matrix->n));
    matrix->nz=0;
    
    
    int ROW,COL;
    double VALUE;
    
    // If it's not EOF and non-zero value,we create a new node
    while (fscanf(love,"%d %d %lf",&ROW,&COL,&VALUE)!=EOF){
        
        set_tuples(matrix,ROW,COL,VALUE);
        printf("the value passed was(%d, %d) = %f\n", ROW, COL, VALUE);
        
    }
    fclose(love);
    return matrix;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    
    sp_tuples_node * current = mat_t->tuples_head;
    while(current != NULL)
    {
        if(current->row == row && current-> col == col)
        {
            return current->value;
        }else
            current = current->next;
    }
    return 0;     //why is there a return 0?
}








void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    
    sp_tuples_node *current;
    sp_tuples_node *TEMP;
    sp_tuples_node *previous;
    
    if(mat_t->tuples_head == NULL)
    {
        sp_tuples_node * new = malloc(sizeof(sp_tuples_node));
        mat_t->tuples_head = new;
        mat_t->tuples_head->row = row;
        mat_t->tuples_head->col = col;
        mat_t->tuples_head->value = value;
        mat_t->nz =1;
        mat_t->tuples_head->next = NULL;
        
        printf("the first one\n");
        
    }
    int flag =0;
    current=mat_t->tuples_head;
    while(current != NULL && flag == 0){
        if(value == 0){
            //delete the node at (row,column) if exist
            if(current->row==row && current->col==col){
                previous->next=current->next; //hahahaha
                TEMP=current;
                free(TEMP);
                mat_t->nz-=1;
            }
        }
        else{
            if((row * mat_t->n +col) < (mat_t->tuples_head->row*mat_t->n+mat_t->tuples_head->col)){
                //Insert before HEAD
                TEMP=mat_t->tuples_head;
                mat_t->tuples_head=malloc(sizeof(sp_tuples_node));
                mat_t->tuples_head->row=row;
                mat_t->tuples_head->col=col;
                mat_t->tuples_head->value=value;
                mat_t->tuples_head->next=TEMP;
                mat_t->nz+=1;
                
                printf("before head\n");
            }
            //Value exist at HEAD
            else if(row == mat_t->tuples_head->row && col == mat_t->tuples_head->col){
                mat_t->tuples_head->row=row;
                mat_t->tuples_head->col=col;
                mat_t->tuples_head->value=value;
                printf("overwrite head\n");
            }
            else{ // Now traverse the list
                // Nodes already exists
                if (current->row==row && current->col==col){
                    current->value=value;
                }
                // Add a new node
                else{
                    if((current->row * mat_t->n +current->col) < (row*mat_t->n + col)){
                        TEMP=malloc(sizeof(sp_tuples_node));
                        current->next=TEMP;
                        TEMP->next = current->next;
                        TEMP->col=col;
                        TEMP->row=row;
                        TEMP->value=value;
                        mat_t->nz+=1;
                        
                        flag = 1;
                        printf("just add\n");
                    }
                }
            }
        }
        //for iteration
        printf("been here\n");
        previous=current;
        current=current->next;
        
    }
    
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    sp_tuples_node * current = mat_t->tuples_head;
    FILE * thefile;
    thefile = fopen(file_name, "w");
    
    fprintf(thefile, "%d %d\n", mat_t->m, mat_t->n);
    
    while(current != NULL)
    {
        fprintf(thefile, "%d %d %f\n", current->row, current->col, current->value);
        current = current->next;
    }
    
    fclose(thefile);
    return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    
    sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
    retmat->tuples_head = NULL;
    int i,j;
    double value;
    sp_tuples_node * currentA = matA->tuples_head;
    sp_tuples_node * currentB = matB->tuples_head;
    sp_tuples_node * currentC;
    retmat->m = matB->m;
    retmat->n = matB->n;
    retmat->nz = 0;
    
    //if A or B are NULL, addition is not possible, right????????
    if(currentA == NULL || currentB == NULL)
        return NULL;
    
    
    //travers matA
    while(currentA != NULL)
    {
        //record everything from A
        i = currentA->row;
        j = currentA->col;
        value = currentA->value;
        
        //set it for list C
        set_tuples(retmat, i, j, value);
        currentA = currentA->next;    //update currentA
        
    }
    
    
    
    //put currentC back to the head
    currentC = retmat->tuples_head;
    
    
    
    //traverse matB
    while(currentB != NULL)
    {
        //record everything from currentB
        i = currentB->row;
        j = currentB->col;
        value = currentB->value;
        
        if(currentB->value != 0)   //for non-zero value
        {
            if(currentC == NULL)
            {
                set_tuples(retmat,i,j,value);
                currentC = retmat->tuples_head;
            }else
            {
                int flag = 0;
                while(currentC != NULL)   //fisrt find if there already exists an entry
                {
                    if(currentC->row == i && currentC->col == j)
                    {
                        currentC->value = currentC->value + value;
                        flag = 1;
                        break;
                    }
                    currentC = currentC->next;
                }
                
                if(flag == 0)
                    set_tuples(retmat, i, j, value);       //if there is no such entry, call set_tuples function
            }
        }
        
        
        
        currentB = currentB->next;    //update currentB
    }
    
    return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    
    sp_tuples * retmat = malloc(sizeof(sp_tuples));
    retmat->tuples_head = NULL;
    sp_tuples_node * currentA = matA->tuples_head;
    sp_tuples_node * currentB = matB->tuples_head;
    sp_tuples_node * currentC = retmat->tuples_head;
    int ia,ja,old_ia = -1;
    double value_a, value_b;
    
    //initiate retmat
    retmat->m = matA->m;
    retmat->n = matB->n;
    retmat->nz = 0;
    
    if(currentA == NULL || currentB == NULL)      //if A or B are NULL, multiplication is not possible
        return NULL;
    //traverse matA
    while(currentA != NULL)
    {
        if(currentA->value == 0)
        {
            currentA = currentA->next;
        }else{          //find a non-zero entry of A
            //record information from matA
            ia = currentA->row;
            ja = currentA->col;
            value_a = currentA->value;
            
            //find the corresponding B entry
            value_b = gv_tuples(matB, ja, ia);
            if( value_b != 0)
            {
                if(old_ia != ia)   //visiting the position first time
                {
                    //creating a new node
                    set_tuples(retmat, ia, ia, value_a * value_b);
                    old_ia = ia;
                }else{              //if there already exists the node
                    while(currentC != NULL)
                    {
                        if(currentC->row == ia && currentC->col == ia)
                        {
                            currentC->value = currentC->value + value_a * value_b;
                            break;
                        }
                        currentC = currentC->next;
                    }
                }
            }
            currentA = currentA->next;
        }  //when A reaches NULL
    }
    return retmat;
}

void destroy_tuples(sp_tuples * mat_t){
    // set a TEMP for free;
    sp_tuples_node *TEMP;
    sp_tuples_node * current;
    current=mat_t->tuples_head;
    
    //First traverse and free every node.
    while(current!=NULL){
        TEMP=current;
        current=current->next;
        free(TEMP);                        //Free every node first;
    }
    //Then free the matrix structure
    free(mat_t);
}
