#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

//Define ptr and list as a node pointer using typedef
typedef struct node*ptr;
typedef ptr list ;
//build node using struct that include data and next pointer
struct node
{
    char data[16];
    ptr next;
};

/* Allocate memory for node */
ptr makeEmpty(list head)
{
    if (head != NULL)
        deleteList(head);
    head= (struct node*)malloc(sizeof(struct node));//Allocate memory for the node pointer head
    if(head== NULL)//Exception to check accurate of the allocation
        printf("Failed to insert element. Out of memory \n");

    head-> next = NULL ;
    return head ;
}

/*To delete the list from the memory*/
void deleteList(ptr head)
{
    ptr temp;
    ptr p;
    p=head->next ;
    head->next =NULL ;
    while (p!=NULL)
    {
        temp = p-> next ;
        free(p);
        p= temp ;
    }
}
/*To insert element in linked list */
void Insert(char name[16],ptr p)
{
    ptr temp;
    temp=(ptr)malloc(sizeof(struct node));
    strcpy(temp->data,name); //strcoy method from string library because the data is string
    temp->next=p->next;
    p->next=temp;
}
/*to find the previous node using data of the next node */
ptr findPrevious(char value[16], list head)
{
    ptr temp;
    temp=head;
    while(temp->next != NULL && temp->next->data != value)//Stop the loop when the next node include the value
        temp=temp->next;
    return temp ;
};

/*To find the number of words in the list */
int size(list head)
{
    int counter=0;
    ptr temp;
    temp=head;
    while(temp->next !=NULL)//keep iterate to the end of the list
    {
        temp=temp->next;
        counter++;//increment counter when find data in the node
    }
    return counter ;//return size of the list-nodes number-
}
/*To add data to the end of the list */
void append(ptr arr[],char letter[] )
{
    ptr p=arr;
    ptr temp;
    temp=(ptr)malloc(sizeof(struct node));//Allocate memory to the addition node
    while(p->next != NULL)//to find the last node in the list
        p=p->next;

    p->next=temp;//put additional node at the end of the list
    strcpy(temp->data,letter);//copy data into the additional node
    temp->next=NULL;
}

/* Project Functions */
void ReadTheInputFile(list head);
void printBeforeSorting(list head);
ptr SortTheStrings(list head);
void printTheStoredStrings(ptr sortedList);
//General counter
int c0,c1,c2,c3,c4,c5,c6,c7,c8,c9 ;

int main()
{
    list head, sortedList;
    head=makeEmpty(NULL);//Allocate memory for head of the linked list
    sortedList=head;
    int  length=size(head);//Length equal number of elements in the list
    char choice;
    while (2)
    {
        /*Display the menu */
        printf("**********************************************************\n");
        printf("Enter your choice number :- \n");
        printf("1.Read the input file \n");
        printf("2.Print the strings before sorting \n");
        printf("3.Sort the strings \n");
        printf("4.Print the stored strings \n");
        printf("5.Quit \n");
        scanf("%c",&choice);
        printf("\n");
        switch (choice)
        {
        case '1' :
        {
            head=makeEmpty(NULL);
            ReadTheInputFile(head);
            if(head!=NULL)//An exception to check reading operation
                printf("The file has been read \n");
            else
                printf("error in reading operation ,The list is Empty there is no data !!\n");
        }
        break ;
        case '2' :
        {
            printBeforeSorting(head);
            printf("\n");
        }
        break ;
        case '3' :
            if(head->next==NULL)
                printf("You don't have  data to be sorted!!\n");
            else
            {
                sortedList=SortTheStrings(head);
                printf("The elements have been sorted \n");
            }
        break ;
    case '4' :
        {
            printTheStoredStrings(sortedList);
            printf("\n");
        }
        break ;
    case '5' :
        exit(1);//Function in c language to exit from the program
        break;
    default :
        printf(" unknown input !! Please choose one of the options numbers \n");
       // break ;
    }
}
return 0;
}

/*Read the elements from the file and store it into linked list */
void ReadTheInputFile(list head)
{
    ptr temp = head ;
    char name[16];
    FILE*file;
    file=fopen("text.txt","r");
    while(fgets(name,16,file)!= NULL)//Fgets to read the elements to the end of the line
    {
        Insert(name,temp);//insert the element into the liked list
        temp=findPrevious(name,head);//find the previous node for name data
    }
    fclose(file);
}
//Print the list
void printBeforeSorting(list head)
{
    ptr temp;
    temp=head->next;
    if(head->next==NULL)
        printf("This list is empty ! Please read the file before print it ");
    else
        while(temp!= NULL)//keep reading to the end of the list
        {
            printf("-->%s",temp->data);
            temp=temp->next;
        }
}
//Sort the list alphabet order
ptr SortTheStrings(list head)
{
    ptr temp,sortedList, temp1;
    sortedList=makeEmpty(NULL);
    temp1=sortedList;
    temp=head->next;
    ptr arr[37];//Define array of nodes
    int length=size(head);
    int maxNumberOfLetter ;
    char listAsArray[length][16] ,copyList[length][16] , finalList[length][16];
    char letter[16];

    for(c0=0 ; c0<length ; c0++)
    {
        strcpy(listAsArray[c0],temp->data);
        temp=temp->next;
    }
    //Made a copy from the array of strings
    for(c1=0 ; c1<length ; c1++)
    {
        strcpy(copyList[c1],listAsArray[c1]);
        strlwr(copyList[c1]);
    }
    //to find the largest number of letter in one word from file
    for(c2=1; c2<length; c2++)
    {
        maxNumberOfLetter=strlen(listAsArray[0]);//initialize max number of letter variable
        if(strlen(listAsArray[c2])>maxNumberOfLetter)//compare with the other words
            maxNumberOfLetter=strlen(listAsArray[c2]);
    }

//Allocate memory to the array of nodes
    for(c3=0; c3<37; c3++)
    {
        arr[c3]=(struct node*)malloc(sizeof(struct node));
        arr[c3]->next=NULL;
    }
    /*Use Max number of letter as a counter to reduce number of iteration instead of
    *take always the largest number of character
    */

//iteration with respect to the number of letters
    for(c4=maxNumberOfLetter; c4>=0; c4--)
    {
        //iteration with respect to the number of words
        for(c5=0; c5<length; c5++)
        {
            strcpy(letter,copyList[c5]);//copy letter into char variable because switch take only integer and character
            if(47<letter[c4]&&letter[c4]<58)//check if the input character is number
                /*appending position depending on the ASCII code of the number with simple mathematical operation to specify the index
                *numbers from 0 to 9 has index domain from 1 to 10 */
                append(arr[letter[c4]-47],listAsArray[c5]);//if it's number append the string of these character in the list
            else if (96<letter[c4]&&letter[c4]<123)//check if the input character is letter
            //Also in this case the index depending on the ASCII value the indexes from 11 to 37
                append(arr[letter[c4]-86],listAsArray[c5]);//if it's letter append the string of these character in the list
            else
                append(arr[0],listAsArray[c5]);//If the character neither number nor letter append it at the first position in the list
        }
//copy the data from array of nodes to array of strings
        for(c6=0,c7=0; c6<length, c7<37; c7++)
        {
            ptr temp;
            temp=arr[c7]->next;
            while(temp!=NULL)//inner loop because of array of nodes may include more than one node
            {
                strcpy(finalList[c6],temp->data);
                temp=temp->next;
                c6++;
            }
        }
//to delete the connected data with the array of nodes
        for(c8=0; c8<37; c8++)
            deleteList(arr[c8]);

    }
//copy sorted array to linked list to make it easy to work with it
    for(c9=0; c9<length; c9++)
    {
        Insert(finalList[c9],temp1);
        temp1=findPrevious(finalList[c9],sortedList);
    }

    return sortedList;
}

//Print the sorted list
void printTheStoredStrings(ptr sortedList)
{
    ptr temp;
    temp=sortedList->next;
    if(sortedList->next==NULL)//check if the list has elements or Empty
        printf("This list is empty ! You should sort list before print it \n");
    else
    {
        printf("-->%s\n\n",temp->data);
        temp=temp->next;
        while(temp!= NULL)//keep iterate to the end of the list
        {
            printf("-->%s\n",temp->data);//Print data on the screen
            temp=temp->next;//pass to the other node

        }
    }
}


