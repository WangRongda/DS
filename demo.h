/* ADT */

//constant
typedef enum { FALSE, TRUE }bool;
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//storage structure 
typedef struct {} SS 
typedef - ElemType; 
typedef - Status;  

// Basic Operation
Status Init(SS &T);
Status Destroy(SS &T);
Status Get(SS T, int i, ElemType &e); //get value of i in T
Status Put(SS &T, int i, ElemType e); //change value of i in T

