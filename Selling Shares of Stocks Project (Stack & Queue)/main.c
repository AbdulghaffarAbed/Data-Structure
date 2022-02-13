#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct shareNode* listPtr;// Define listPtr as a shareNode pointer
typedef listPtr list ;//Define list as a shareNode pointer using listPtr
//struct consist list components
struct shareNode
{
    char data[80];//String line of data
    int numberOfShares;
    double price;
    char company[25];
    char date[9];
    int day;
    int month;
    int year;
    listPtr next;//list pointer refe;r to the next node in the list
};

/*To insert element in linked list */
void Insert(char tempVarData[80],listPtr position)
{
    listPtr temp;
    temp=(listPtr)malloc(sizeof(struct shareNode));
    temp=(listPtr)malloc(sizeof(struct shareNode));//Allocate memory for temp pointer
    strcpy(temp->data,tempVarData);//copy string data into the list
    /*split each element depending on constant character */
    temp->numberOfShares= atoi( strtok(tempVarData,";"));// atio function in c that convert string to integer type
    temp->price=atof(strtok(NULL,";"));// atof function in c that convert string to double type
    strcpy(temp->company,strtok(NULL,";"));
    strcpy(temp->date,strtok(NULL,";"));
    temp->day=atoi(strtok(temp->date,"-"));
    temp->month=atoi(strtok(NULL,"-"));
    temp->year=atoi(strtok(NULL,"\n"));
    temp->next=position->next;
    position->next=temp;

}

/*to find the previous node using data of the next node */
listPtr findPrevious(char value[80], list head)
{
    listPtr temp;
    temp=head;
    while(temp->next != NULL && temp->next->data!=value )//Stop the loop when the next node include the value
        temp=temp->next;
    return temp ;
};

/* Delete node from the linked list and delete its data*/
void Delete(char data[80],listPtr head)
{
    listPtr temp, previous ;
    previous=findPrevious(data,head);//previous pointer refer to the node before the required node
    if(previous->next!=NULL)//check if the required node in the list or not
    {
        temp=previous->next;
        previous->next=temp->next;
        free(temp);
    }
}

/*Append to add node in the end of the  list */
void append(listPtr head,char purchaseInformation[80] )
{
    listPtr position=head;
    listPtr temp;
    temp=(listPtr)malloc(sizeof(struct shareNode));//Allocate memory for the additional node
    strcpy(temp->data,purchaseInformation);//copy data to the new node
    temp->numberOfShares= atoi( strtok(purchaseInformation,";"));
    temp->price=atof(strtok(NULL,";"));
    strcpy(temp->company,strtok(NULL,";"));
    strcpy(temp->date,strtok(NULL,";"));
    while(position->next != NULL)//find the last node in the given list
        position=position->next;
    position->next=temp;//put the additional node in the last of the list
    temp->next=NULL;
}

/*Allocate list in the memory */
listPtr makeEmpty(list head)
{
    if (head != NULL)
        deleteList(head);
    head= (listPtr)malloc(sizeof(struct shareNode));
    if(head== NULL)
        printf("Failed to insert element. Out of memory \n");
    head-> next = NULL ;
    return head ;
}
/*To sort the list of data depending on the date */
listPtr sortList(list head)
{
    int length=size(head),c1,c2,c3;
    listPtr arrayOfShares[length],tempList=head->next;//Define array of nodes
    listPtr temp=makeEmpty(NULL);
    for(c1=0; c1<length; c1++)//Fill array of nodes from list
    {
        arrayOfShares[c1]=(listPtr)malloc(sizeof(struct shareNode));//Allocate memory for each place(index) in the array
        arrayOfShares[c1]->next=tempList;//put list node inside the array
        tempList=tempList->next;
    }
//Sort Ascending with priority to year , month , day respectively
    for(c1=0; c1<length; c1++)
    {
        for(c2=0; c2<length-1; c2++)
        {
            if(arrayOfShares[c2]->next->year > arrayOfShares[c2+1]->next->year)//check the value of the year
            {
                temp=arrayOfShares[c2]->next;//use temp as mediator carry data from to
                arrayOfShares[c2]->next=arrayOfShares[c2+1]->next;//put the small value before the big
                arrayOfShares[c2+1]->next=temp;
            }
            if(arrayOfShares[c2]->next->year == arrayOfShares[c2+1]->next->year)//if the years are equal track the priority
                if(arrayOfShares[c2]->next->month > arrayOfShares[c2+1]->next->month)//check the value of the month
                {   //the same steps as year
                    temp=arrayOfShares[c2]->next;
                    arrayOfShares[c2]->next=arrayOfShares[c2+1]->next;
                    arrayOfShares[c2+1]->next=temp;

                }
            if(arrayOfShares[c2]->next->year == arrayOfShares[c2+1]->next->year && arrayOfShares[c2]->next->month == arrayOfShares[c2+1]->next->month )
                if(arrayOfShares[c2]->next->day >arrayOfShares[c2+1]->next->day)//check the day value
                {   //the same steps as year and month
                    temp=arrayOfShares[c2]->next;
                    arrayOfShares[c2]->next=arrayOfShares[c2+1]->next;
                    arrayOfShares[c2+1]->next=temp;
                }
        }
    }
    list finalList = makeEmpty(NULL);//create new list to put data inside it
    listPtr finalPtr=finalList;
    for(c3=0 ; c3<length ; c3++)//copy data from arrayOfShares to the list - finalList -
    {
           Insert(arrayOfShares[c3]->next->data,finalPtr);
           finalPtr=findPrevious(arrayOfShares[c3]->next->data,finalList);
    }

return finalList;//return the final order list
}


/*To delete the list from the memory*/
void deleteList(listPtr head)
{
    listPtr temp, p;
    p=head->next ;
    head->next =NULL ;
    while (p!=NULL)
    {
        temp = p-> next ;
        free(p);
        p= temp ;
    }
}

/*To find the number of words in the list */
int size(list head)
{
    int counter=0;
    listPtr temp;
    temp=head;
    while(temp->next !=NULL)
    {
        temp=temp->next;
        counter++;
    }
    return counter ;
}


/*Stack node implementation*/
typedef struct stackNode* stackPtr;// Define stackPtr as a stackNode pointer
typedef stackPtr Stack ;//Define Stack as a stackNode pointer using stackPtr
//struct consist stack components
struct stackNode
{
    char data[80];
    int numberOfShares;
    double price ;
    char company[25];
    char date[9];
    stackPtr next;//stack pointer refer to the next node in the stack
};

//Allocate memory for stack
Stack createStack()
{
    Stack s ;
    s =(stackPtr)malloc(sizeof(struct stackNode));//Allocate memory to the stack with s reference
    if(s==NULL)
        printf("Out of memory ! \n");
    s->next=NULL ;
    return s ;
}
/*Check if the stack include elements or not */
int isEmpty(Stack s)
{
    return s->next==NULL;
}
/*Push function to add data in the stack */
void push(Stack s,char data[80])
{
    stackPtr tempStack ;
    tempStack=(stackPtr)malloc(sizeof(struct stackNode));//Allocate memory to the additional data
    if(tempStack==NULL)//Exception to check allocation for the additional node
        printf("Out of memory !! \n");
    strcpy(tempStack->data,data);//copy data into the additional stack node
    /*split each element depending on constant character */
    tempStack->numberOfShares= atoi( strtok(data,";"));//atoi function in c that convert string to integer type
    tempStack->price=atof(strtok(NULL,";"));//atof function in c that convert string to double type
    strcpy(tempStack->company,strtok(NULL,";"));
    strcpy(tempStack->date,strtok(NULL,";"));
    tempStack->next=s->next;
    s->next=tempStack;
}
/*Pop function to delete node with its data from the stack */
void pop(Stack s)
{
    stackPtr firstCell;
    if(isEmpty(s))//Exception because delete from empty stack cause error
        printf("Empty stack \n");
    else
    {
        firstCell = s->next;//first cell refer to the top of the stack
        s->next=s->next->next;//top of the stack becomes the second node after the previous top
        free(firstCell);//free the previous top
    }
}
/*Return the top node of the stack */
stackPtr Top(Stack s)
{
    if(!isEmpty(s))
        return s->next;
    else
        printf("Empty stack !!\n");
    return " ";
}

/*Delete all information from the stack */
void makeStackEmpty(Stack s)
{
    if(s==NULL)
        printf("Out of space \n");
    else
        while(!isEmpty(s))
            pop(s);
}

//Delete the stack structure and its data from the memory
void DisposeStack(Stack s)
{
    makeStackEmpty(s);
    free(s);
}

//Queue implementation
typedef struct queueNode* queuePtr ;// Define queuePtr as a queueNode pointer
typedef queuePtr Queue;//Define Queue as a queueNode pointer using queuePtr
//Queue component in struct
struct queueNode
{
    int front ;
    int capacity ;
    int rear ;
    int size;
    listPtr array;//array include data with the structure of the listPtr variables
};
/*Check if the queue include any type of data */
int queueIsEmpty(Queue q)
{
    return q->size==0;
}
/* Allocate queue in the memory and made its structure */
queuePtr createQueue()
{
    Queue temp;
    temp=(queuePtr)malloc(sizeof(struct queueNode));//Allocate temp in memory
    if(temp==NULL)
        printf("memory out of space !!\n");
    temp->array=(listPtr)malloc(sizeof(struct shareNode)*100);//Allocate array size in memory
    if(temp->array==NULL)
        printf("memory out of space !!\n");
    temp->capacity=100;//the highest number of elements in the array and queue
    makeQueueEmpty(temp);
    return temp;
}
/*Make the queue empty with initial values*/
void makeQueueEmpty(queuePtr Q)
{
    Q->size=0;//initially the queue is empty size =0
    Q->front=1;//front refer to the first position in array
    Q->rear=0;//rear initially position before front
}
/*Successor to check addition and deletion operations according to the capacity of the queue
*Responsible for circular Queue
*/
int Successor(Queue Q,int value)
{
    if(value++==Q->capacity)//if the Queue cannot accept any element put reference on the first location in array
        value=0;
    return value;
}
/*Enqueue function used to add element in the queue*/
void Enqueue(char data[80],Queue Q)
{
    if(Q->size==Q->capacity)//check if the queue is full
        printf("Full Queue \n");
    else
    {
        Q->size++;//increment size for each added element
        Q->rear=Successor(Q,Q->rear);//use rear as reference to the addition operation
        strcpy(Q->array[Q->rear].data,data);//copy data into the queue
        /*split each element depending on constant character */
        Q->array[Q->rear].numberOfShares= atoi( strtok(data,";"));// atio function in c that convert string to integer type
        Q->array[Q->rear].price=atof(strtok(NULL,";"));// atof function in c that convert string to double type
        strcpy(Q->array[Q->rear].company,strtok(NULL,";"));
        strcpy(Q->array[Q->rear].date,strtok(NULL,";"));
    }
}
/*Dequeue function used to delete element from the queue*/
void Dequeue (Queue Q)
{
    if(queueIsEmpty(Q))//if the queue is empty delete from it cause an error
        printf("Empty queue !!\n");//exception message
    else
    {
        Q->size--;//decrement size
        Q->front=Successor(Q,Q->front);//use front as reference to the deletion operation
    }
}

/*Project functions*/
void readStocksTransaction(list head);
void buyShares(list head );
double sellOldSharesFirst(list head,Queue Q);
double sellNewSharesFirst(list head,Stack s);
void gainOrLose(double credit,listPtr head);
void updateShares(list head);
void pritList(list head);

int main()
{
    int choice ;
    double Credit,sellOldcredit=0,sellNewCredit=0;
    list head=makeEmpty(NULL);//Allocate list in the memory
    Stack newStack=createStack();//Allocate stack in the memory
    Queue newQueue=createQueue();//Allocate queue in the memory
    while(2)
    {
        //show Menu on the screen
        printf("============================================================================\n");
        printf("Enter your choice number :-\n");
        printf("1.Read stocks transaction \n");
        printf("2.Buy shares\n");
        printf("Sell shares \n");
        printf("\t3.Sell old shares first \n");
        printf("\t4.Sell new shares first \n");
        printf("5.Total capital gain/loss\n");
        printf("6.Update currently held shares \n");
        printf("7.Exit \n==> ");
        scanf("%d",&choice);//get choice number from the user
        Credit=sellNewCredit+sellOldcredit;//Credit money from the selling operation

        switch(choice)//shows cases depending on the choice value
        {
        case 1:
        {
            readStocksTransaction(head);
            if(head!=NULL)
                {printf("The file has been read \n");
                head=sortList(head);}
            else
                printf("error !! The list is Empty \n");
        }
        break;
        case 2:
        {
            buyShares(head);
            printf("The purchase has been ended \n");
        }
        break;
        case 3:
            sellOldcredit=sellOldSharesFirst(head,newQueue);
            break;
        case 4:
            sellNewCredit=sellNewSharesFirst(head,newStack);
            break;
        case 5:
            gainOrLose(Credit,head);
            break;
        case 6:
            updateShares(head);
            break;
        case 7 :
            exit(1);
            break;
        default :
            printf("Unknown input !! please enter one of the choices number \n");//if the user enter a number that is not in the menu
        }
    }
}

/*Read data from the file and save it in list */
void readStocksTransaction(list head)
{
    listPtr temp;
    temp=head;
    FILE*file;//define file variable
    file=fopen("shares.txt","r");//make file variable refer to shares file and use it in reading
    char tempVariableData [80];//temporary variable contain the data from shares file
    while(fgets(tempVariableData,80,file)!=NULL)//stop iteration when arrive the end of file
    {
        Insert(tempVariableData,temp);//insert the element into the liked list
        temp=findPrevious(tempVariableData,head);//temp pointer refer to find previous function to create the correct bonding between the nodes
    }
}
/*Buy shares with specified data taken from the user*/
void buyShares(list head )
{
    listPtr temp;
    temp=head;
    char number[10],cash[10],theDate[20],companyName[25];//variable to data from the user
    char purchaseInformation[50],tempNameOfCompany;
    int quit=1;
    while(quit!=0)
    {
        //ask user about shares information
        printf("Enter number of shares >");
        scanf("%s",&number);//number variable expresses number of shares
        strcpy(number,strcat(number,";"));//append semi colon to the data as the form of data from the file
        printf("Enter the price for single share >");
        scanf("%s",&cash);//cash variable expresses price of each share
        strcpy(cash,strcat(cash,";"));//append semi colon to the data as the form of data from the file
        printf("Enter name of company >");
        scanf("%c",&tempNameOfCompany);//temporary variable help to take name of company if it's consist space
        scanf("%[^\n]",companyName);//companyName variable expresses company that user want to buy shares from it
        strcpy(companyName,strcat(companyName,";"));//append semi colon to the data as the form of data from the file
        printf("Enter the date of the purchase space on the form day-month-year :\n");
        scanf("%s",theDate);//theDate variable expresses time of buying the shares
        //Recover data with the base form
        strcpy(purchaseInformation,strcat(number,cash));
        strcat(purchaseInformation,strcat(companyName,theDate));
        strcat(purchaseInformation,"\n");//for style
        //Update currently list
        append(temp,purchaseInformation);//add data to the list
        printf("Enter 0 to stop buy 1 to continue \n");
        scanf("%d",&quit);//Ask if the user want to buy another shares
    }
}

/*Using to sell shares starting from the old one using Queue */
double sellOldSharesFirst(list head,Queue Q)
{
    listPtr tempList=head->next;//the basic list that consist the data
    listPtr finalList=head;
    list newList=makeEmpty(NULL);//another list to make adjustments
    listPtr listPosition = newList;
    queuePtr tempQueue=Q;//Q as a reference on the Queue
    //local variables
    char tempData[80],companyName[25],tempNameOfCompany;
    int shareNumber=0, counter =0,c=1;
    double chac,gainLose,bigger=0,priceDifference;
    makeQueueEmpty(tempQueue);//if we want to by more than one time to start from empty queue
    if(head->next == NULL)//Exception that we cannot sell shares if we don't have any share
        printf("Empty List !! you don't have any share to sell\n");
    else//print the data from linked list to the queue
    {   while(tempList!=NULL)
        {   Enqueue(tempList->data,tempQueue);
            tempList=tempList->next;
            counter++;//counter equal number of elements in the list number of nodes thats include data
        }
        //Ask user information about selling operation
        printf("Enter number of shares that you want to sell it >");
        scanf("%d",&shareNumber);
        printf("Enter price for each share >");
        scanf("%lf",&chac);
        printf("Enter name of company >");
        scanf("%c",&tempNameOfCompany);
        scanf("%[^\n]",companyName);
        while(shareNumber!=0 && c<=counter )//stop iteration when sell all the shares , no company found or number of shares too big
        {
            if(strcmp(companyName,tempQueue->array[tempQueue->front].company)==0)//if the enter company equal the name of company in the list go inside if
            {   if(shareNumber==tempQueue->array[tempQueue->front].numberOfShares)
                {
                    priceDifference=chac-tempQueue->array[tempQueue->front].price;//the difference in the price between price of shares in the list and from the user
                    gainLose=(priceDifference*shareNumber)+bigger;//expresses the credit money after sell in this case
                    printf("Gain/Lose : %.2f * %d + %.2f = %.2f\n",priceDifference,shareNumber,bigger,gainLose);
                    shareNumber=0;
                    Dequeue(tempQueue);//delete the node from the queue that has been soled
                    c++;
                }
                else if( shareNumber < tempQueue->array[tempQueue->front].numberOfShares)
                {
                    char temporaryNumber[12],date[12],company[30],numOfShare[12],money[17];
                    tempQueue->array[tempQueue->front].numberOfShares= tempQueue->array[tempQueue->front].numberOfShares - shareNumber;
                    priceDifference = chac - tempQueue->array[tempQueue->front].price ;//the difference in the price between price of shares in the list and from the user
                    gainLose=(priceDifference*shareNumber)+bigger;
                    printf("Gain/Lose : %.2f * %d + %.2f = %.2f\n",priceDifference,shareNumber,bigger,gainLose);
                    sprintf(temporaryNumber,"%d",tempQueue->array[tempQueue->front].numberOfShares);//Convert number of share from integer to string type in temporary variable
                    //Update the line of Strings data
                    strcpy(numOfShare,strtok(tempQueue->array[tempQueue->front].data,";"));
                    //Split data for modify the number of share in the linked list
                    strcpy(money,strtok(NULL,";"));
                    strcpy(company,strtok(NULL,";"));
                    strcpy(date,strtok(NULL,";"));
                    strcat(temporaryNumber,";");
                    strcat(money,";");
                    strcat(company,";");
                    strcpy(temporaryNumber,strcat(temporaryNumber,money));
                    strcpy(temporaryNumber,strcat(temporaryNumber,company));
                    strcpy(temporaryNumber,strcat(temporaryNumber,date));
                    strcpy(tempQueue->array[tempQueue->front].data,temporaryNumber);
                    shareNumber=0;
                    c++;
                }
                else//shareNumber greater than tempQueue->array[tempQueue->front].numberOfShares
                {   priceDifference=chac-tempQueue->array[tempQueue->front].price;//the difference in the price between price of shares in the list and from the user
                    bigger=tempQueue->array[tempQueue->front].numberOfShares * priceDifference + bigger;//store the gain and lose value when we use more than one node
                    gainLose=bigger;
                    printf("Gain/Lose : %.2f * %d = %.2f\n",priceDifference,tempQueue->array[tempQueue->front].numberOfShares,bigger);
                    shareNumber=shareNumber-tempQueue->array[tempQueue->front].numberOfShares;//modify share number value
                    Dequeue(tempQueue);
                    c++;
                }
            }
            else// If the company name did not match with the name of company from user
            {   Insert(tempQueue->array[tempQueue->front].data,listPosition);//insert the node in another list
                listPosition=findPrevious(tempQueue->array[tempQueue->front].data,newList);//find previous to the addition node
                Dequeue(tempQueue);//delete the node from the queue
                c++;
            }
        }
        deleteList(finalList);//delete the basic list
        listPtr endListPtr = head;
        char finalData [80];
        while(tempQueue->front<=tempQueue->rear){//print the element from the  queue to the temporary list
                strcpy(finalData,tempQueue->array[tempQueue->front].data);
                 Insert(finalData,endListPtr);
                 endListPtr=findPrevious(finalData,head);
                Q->front++;//increment front counter to go to the next element in the queue
         }
          listPtr tempPrint;
          tempPrint=newList->next;
         while(tempPrint!=NULL){
            append(head,tempPrint->data);
            tempPrint=tempPrint->next;
         }
    }
       if(shareNumber!=0)
        printf("The shares that you have expired and remained %d share \n",shareNumber);
return gainLose;
}
/*Using to sell shares starting from the last one (the new one) using Stack */
double sellNewSharesFirst(list head,Stack s)
{
    //define some local variable
    listPtr tempList=head->next, finalList = head;
    stackPtr tempStack = s;
    stackPtr topStack=createStack(),popStack=createStack();
    makeStackEmpty(s);
    char companyName[25],tempNameOfCompany;
    int shareNumber=0, counter =0,c1,popStackSize=0,c=1;
    double chas,gainLose,bigger=0,priceDifference;

    if(head->next == NULL)//check if the list is empty or not
        printf("Empty List !! you don't have any share to sell\n");
    else//if the list consist data
    {
        while(tempList != NULL)
        {
            push(s,tempList->data);//insert data from linked list to the stack
            tempList=tempList->next;
            counter++;//number of nodes in the stack
        }//Ask user information about selling operation
        printf("Enter number of shares that you want to sell it >");
        scanf("%d",&shareNumber);
        printf("Enter price for each share >");
        scanf("%lf",&chas);
        printf("Enter name of company >");
        scanf("%c",&tempNameOfCompany);
        scanf("%[^\n]",companyName);
        while(shareNumber!=0 && c<=counter )//keep iterate to the end of the stack or when sell all the shares
        {
            topStack=Top(tempStack);//get the first node in the stack
            if(strcmp(companyName,topStack->company)==0 && c<=counter)//stop iteration when sell all the shares , no company found or number of shares too big
            {
                if(shareNumber==topStack->numberOfShares)
                {
                    priceDifference=chas-topStack->price;
                    gainLose=(priceDifference*shareNumber)+bigger;//the gain or lose from the selling operation
                    printf("Gain/Lose : %.2f * %d + %.2f = %.2f\n",priceDifference,shareNumber,bigger,gainLose);
                    shareNumber=0;//in this case all the share was soled
                    pop(tempStack);//because case all the share was soled
                    c++;//counter
                }
                else if( shareNumber < topStack->numberOfShares )
                {
                    char temporaryNumber[12],date[12],company[30],numOfShare[12],money[17];
                    topStack->numberOfShares= topStack->numberOfShares-shareNumber;
                    priceDifference=chas-topStack->price;
                    gainLose=(priceDifference*shareNumber)+bigger;
                    printf("Gain/Lose : %.2f * %d + %.2f = %.2f\n",priceDifference,shareNumber,bigger,gainLose);
                    sprintf(temporaryNumber,"%d",topStack->numberOfShares);//Convert number of share from integer to string type in temporary variable
                    //Update the line of Strings data
                    strcpy(numOfShare,strtok(topStack->data,";"));
                    strcpy(money,strtok(NULL,";"));
                    strcpy(company,strtok(NULL,";"));
                    strcpy(date,strtok(NULL,";"));
                    strcat(temporaryNumber,";");
                    strcat(money,";");
                    strcat(company,";");
                    strcpy(temporaryNumber,strcat(temporaryNumber,money));
                    strcpy(temporaryNumber,strcat(temporaryNumber,company));
                    strcpy(temporaryNumber,strcat(temporaryNumber,date));
                    strcpy(topStack->data,temporaryNumber);
                    shareNumber=0;
                    c++;
                }
                else//number of shares to sell more than number of shares in the node ( in the line of data )
                {
                    priceDifference=chas-topStack->price;
                    bigger=topStack->numberOfShares * priceDifference + bigger;
                    gainLose=bigger;
                    printf("Gain/Lose : %.2f * %d = %.2f\n",priceDifference,topStack->numberOfShares,bigger);
                    shareNumber=shareNumber-topStack->numberOfShares;
                    pop(tempStack);
                    c++;
                }
            }
            else//when the enter company didn't identical the company in the node
            {
                push(popStack,topStack);//add the node inside another stack(popStack)
                pop(tempStack);//delete the node from the original stack
                popStackSize++;//number of nodes in the popStack
                c++;//increment counter
            }
        }
//insert elements popped when search on identical company to the stack
        for(c1=0; c1<popStackSize; c1++)
        {
            topStack=Top(popStack);
            push(tempStack,topStack);
            pop(popStack);
        }
        deleteList(finalList);//Delete the original list
        stackPtr ptr=tempStack->next;
        while(ptr!=NULL)
        {
            Insert(ptr->data,finalList);//add without find previous method that will reverse the order of the stack to save data in linked list
            ptr=ptr->next;
        }
    }

    if(shareNumber!=0)
        printf("The shares that you have expired and remained %d share \n",shareNumber);

    DisposeStack(popStack);//To clear the data by get rid of popStack
    return gainLose;//return the credit money
}
/*Show the credit after financial operations */
void gainOrLose(double credit,listPtr head)
{
    if(head->next==NULL)
        printf("This list is Empty !! there is no financial operations\n");
    else{
    //The classification depends on the number sign
    printf("Your final balance is : %.2f $\n",credit);
    if(credit<0)
        printf("You lose %.2f $\n",(-1*credit));
    else if(credit>0)
        printf("You gain %.2f $\n",credit);
    else
        printf("You did not gain or lose any dollar \n");
    }
}
/*Update shares data in the file*/
void updateShares(list head)
{
    listPtr temp;
    temp=head->next;
    FILE*inp;
    inp=fopen("shares.txt","w");//open file to write inside it
    if(temp==NULL)
        printf("This list is empty !!\n");
    else
    {
        while(temp!=NULL)//keep iterate to the end of the file
        {
            fprintf(inp,"%s\n",temp->data);//print new data inside the file
            temp=temp->next;
        }
        printf("The file has been update\n");
    }
}
void pritList(list head)
{
    listPtr temp;
    temp=head->next;
    if(temp==NULL)
        printf("This list is empty !!\n");
    while(temp!=NULL)
    {
        printf("%s\n",temp->data);
        temp=temp->next;
    }
}


