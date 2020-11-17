#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 400

int front = -1,rear = -1;
int V,i,j,n,place;
int origin ,destin;
int arr[MAX][MAX]; /*Adjacency Matrix*/


int main()
{

    int i,j,v;

    FILE * fPtr;

// ΑΝΟΙΓΜΑ ΑΡΧΕΙΟΥ
    fPtr = fopen("test3.txt", "r");

    // fopen() return NULL if last operation was unsuccessful
    if(fPtr == NULL)
    {
        // Unable to open file hence exit
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    // File open success.
    printf("File opened.\n\n");

    int node_id;
    char word1[4];


    for(i=0; i<1; i++){ // Διαβάζει το πρώτα νούμερΟ απο το αρχείο το οποίο είναι οι κόμβοι
        fscanf(fPtr,"%s%*[^\n]",word1);
        printf("Number of nodes: %s\n",word1); // έλεγχος αν το διάβασε σωτσά
    }

    int V = atoi(word1); // μετατροπή του string σε int για να μπει σαν όρισμα στο πίνακα
    printf("After conversion of the string into a number V is: %d\n\n",V); // έλεγχος αν μετατράπηκε



//ΑΡΧΙΚΟΠΟΙΗΣΗ ΤΟΥ ΜΗΤΡΩΟΥ ΓΕΤΝΙΑΣΗΣ

    for(i = 0; i < V; i++)
        for(j = 0; j < V; j++)
            arr[i][j] = 0;


//ΕΙΣΑΓΩΓΗ ΑΚΜΩΝ

        while(!feof(fPtr)) {
            for(i=0; i<1; i++){fscanf(fPtr, "%*[^\n]\n");}
            fscanf(fPtr,"%d %d", &origin,&destin);
            arr[origin][destin]=1;
        }


//ΤΥΠΩΜΑ ΜΗΤΡΩΟΥ

   printf("\n\n");

   for(i = 0; i < V; i++)
        {
            for(j = 0; j < V; j++)
            {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }


//ΤΟΠΟΛΟΓΙΚΗ

//ΑΡΧΙΚΟΠΙΗΣΗ ΟΥΡΑΣ S

    int queueS[V];

    for(i=0;i<V;i++){
        queueS[i]=0;
    }

//ΑΡΧΙΚΟΠΟΙΗΣΗ ΠΙΝΑΚΑ ΤΟΠΟΛΟΓΙΚΗΣ

    int topo_order[V];

    for(i=0;i<V;i++){
        topo_order[i]=0;
    }


//ΕΙΣΑΓΩΓΗ ΚΟΜΒΩΝ ΣΤΗΝ S

    void insert_queue(int v){
        if(rear == V-1 ){
            printf("Not enough space ");
        }
        else{
            if(front == -1){
                front=front+1;
            }
            rear=rear+1;
            queueS[rear]=v;
        }
    }


//ΣΒΗΣΙΜΟ ΚΟΜΒΩΝ ΑΠΟ ΤΗΝ S

    int delete_queue(){
        int del_vert;
        del_vert=queueS[front];
        queueS[front]=0;
        front=front+1;
        return del_vert;
        //if(front==rear-1){
            //printf("\n\nS is done");
           // front=-1;
        //}
    }

//ΕΥΡΕΣΗ ΒΑΘΜΩΝ

    int degrees[V];

    for(i=0;i<V;i++){
        int sum=0;
        for(j=0;j<V;j++){
            sum	+=	arr[j][i];
            degrees[i]=sum;
        }
    }

    printf("\n\nDegrees of nodes are:\n"); //ΤΥΠΩΜΑ ΓΙΑ ΕΛΕΓΧΟ
    for(i=0;i<V;i++){
        printf("%d ", degrees[i]);
    }


//ΤΟΠΟΛΟΓΙΚΗ ΒΑΣΙΚΟ ΚΟΜΜΑΤΙ

    for(i=0;i<V;i++){
        if(degrees[i]==0)
            insert_queue(i);
    }

    place=0;

    while(front!=-1){
        v=delete_queue();
        topo_order[place]=v;
        if(front==V){front=-1;}
        place=place+1;
        for(j=0; j<V; j++){
            if(arr[v][j]==1){
                arr[v][j]=0;
                degrees[j]=degrees[j]-1;
                if(degrees[j]==0)
                    insert_queue(j);
            }
        }
    }

    printf("\n\nTopological order is: ");
    for(i=0; i<V; i++)
        printf( "%d ",topo_order[i] );


    printf( "\n\n");
    printf( "front is: %d \n",front);
    printf( "rear is: %d ",rear );


//ΚΛΕΙΣΙΜΟ ΑΡΧΕΙΟΥ

    fclose(fPtr);

  return 0;
}//End of main()
