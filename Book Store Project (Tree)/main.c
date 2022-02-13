#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef struct AVLnode *AVLNode;//Define AVLNode as a pointer for AVLnode
struct AVLnode
{
    char bookName[30];
    char autherName[30];
    int publishingDate;
    char publishingAddress[30];
    char category[15];
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};
/* Used to initialize a tree */
AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}
/* Return the position of the smallest key value in the tree */
AVLNode FindMin( AVLNode T )
{
    if( T != NULL )
        while( T->Left != NULL )
            T = T->Left;

    return T;
}
/* Return the position of the largest key value in the tree */
AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}
/* Return the maximum number of edges till a leaf node  */
int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */
AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */
AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */
AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */
AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}
/* This function used to find book from library ( the tree ) depending on the name of the book from the user */
AVLNode FindUsingBookName( char data[30], AVLNode T )
{
    if( T == NULL )
        return NULL;
    if( strcmp(data,T->bookName) < 0 )
    {
        return FindUsingBookName( data, T->Left );
    }
    else if( strcmp(data,T->bookName) > 0 )
    {
        return FindUsingBookName( data, T->Right );
    }
    else
        return T;
}


/* This function used to find book from library ( the tree ) depending on the  author's from the user */
void FindUsingAuthorName( AVLNode t,char author[30])
{
    if( t != NULL)
    {
        FindUsingAuthorName( t->Left,author );
        if(strcmp(t->autherName,author)==0)//if there is match between the name from the user and the name in the library then print book information
            printf("%s\t%s\t%d\t%s\t%s", t->bookName,t->autherName,t->publishingDate,t->publishingAddress,t->category);
        FindUsingAuthorName( t->Right,author );
    }
}

/* This function used to insert (put) data from the file into the tree */
AVLNode Insert( char bookName[30],char autherName[30],int publishingDate,char publishingAddress[30],char category[15], AVLNode T)
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T =(AVLNode)malloc( sizeof( struct AVLnode ) );

        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->bookName,bookName);
            strcpy(T->autherName,autherName);
            T->publishingDate=publishingDate;
            strcpy(T->publishingAddress,publishingAddress);
            strcpy(T->category,category);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    /*Binary search tree bases with balance small than root to the left larger than root to the right */
    else if( strcmp(bookName,T->bookName) < 0 )
    {
        T->Left = Insert( bookName,autherName,publishingDate,publishingAddress,category,T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if(strcmp(bookName,T->Left->bookName) < 0 )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else if( strcmp(bookName,T->bookName) > 0 )
    {
        T->Right = Insert( bookName,autherName,publishingDate,publishingAddress,category,T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( strcmp(bookName,T->Right->bookName) > 0  )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;

}

/* This function used to read the data from the given file */
AVLNode readBooksInformation(AVLNode tree)
{
    char bookName[30],autherName[30],publishingAddress[30],category[15];//define parameters
    int publishingDate;
    FILE*file;
    file=fopen("books.txt","r");
    char tempVariableData [120];//temporary variable contain the data from shares file
    while(fgets(tempVariableData,120,file)!=NULL)// Keep iterate till the end of the file
    {
        strcpy(bookName,strtok(tempVariableData,"|"));
        strcpy(autherName,strtok(NULL,"|"));
        publishingDate=atoi(strtok(NULL,"|"));         // atoi used to convert from string to integer
        strcpy(publishingAddress,strtok(NULL,"|"));
        strcpy(category,strtok(NULL,"|"));
        //stop iteration when arrive the end of file
        tree= Insert(bookName,autherName,publishingDate,publishingAddress,category,tree);//insert the element into the tree

    }
    return tree;
}

/* To insert a new book from the user into the library */
AVLNode InsertNewBook(AVLNode tree)
{
    char bookName[30],authorName[30],publishAddress[30],Date[5],category[15], temp;
    int publishDate;
    printf("Book name : ");
    scanf("%[^\n]",&temp);
    scanf("%s",bookName);
    printf("Author's name : ");
    scanf("%[^\n]",&temp);
    scanf("%s",authorName);
    printf("Publishing year : ");
    scanf("%[^\n]",&temp);
    scanf("%s",Date);
    printf("Publishing address : ");
    scanf("%[^\n]",&temp);
    scanf("%s",publishAddress);
    printf("Category : ");
    scanf("%s",category);
    publishDate=atoi(Date);
    tree=Insert(bookName,authorName,publishDate,publishAddress,category,tree);
    return tree;
}

/* This function used to search for book depending on the book name or author's name from the user */
void  searchForBook( AVLNode tree)
{
    int choice;
    char nameFromUser [30];
    char tempChar;
    AVLNode searchingResult;
    AVLNode authorTree=MakeEmpty(NULL);
    printf("Chose search method :\n");
    printf("1- Using book name\n");
    printf("2- Using author name \n");
    scanf("%d",&choice);
    if(choice==1)//Search using book name with only one result because there is only uniques books in the library
    {
        printf("Enter book name : ");
        scanf("%c",&tempChar);//temporary variable help to take name of company if it's consist space
        scanf("%[^\n]",nameFromUser);
        searchingResult = FindUsingBookName(nameFromUser,tree);
    }
    else if(choice==2)//Search using author's name with this choice may have one or more result
    {
        printf("Enter author name : ");
        scanf("%c",&tempChar);//temporary variable help to take name of company if it's consist space
        scanf("%[^\n]",nameFromUser);
        FindUsingAuthorName(tree,nameFromUser);
        printf("\n");
    }
    else
    {
        printf("Error in choosing !! unknown input try again \n");
    }
    if(searchingResult==NULL)
        printf("The book that you want is not currently available in the library\n");
    else if (choice==1)
        printf("%s\t%s\t%d\t%s\t%s\n",searchingResult->bookName,searchingResult->autherName,searchingResult->publishingDate,searchingResult->publishingAddress,searchingResult->category);

}

/*This function used to delete book from the library and update it to keep it balance */
AVLNode updateOrDelete(char data[30],AVLNode tree)
{
    AVLNode tempCell;
    if(tree==NULL)
        printf("There's no identical book !! Element not found \n");
    else if( strcmp(data,tree->bookName) < 0 )            //if the book value less than key of the root
        tree->Left= updateOrDelete(data,tree->Left);
    else if( strcmp(data,tree->bookName) > 0 )           //if the root value less than key of the book go to the right
        tree->Right= updateOrDelete(data,tree->Right);
    else if(tree->Left && tree->Right)                   //if the node has left and right children update before delete
    {
        tempCell=FindMin(tree->Right);
        strcpy(tree->bookName,tempCell->bookName);
        strcpy(tree->autherName,tempCell->autherName);
        tree->publishingDate=tempCell->publishingDate;
        strcpy(tree->publishingAddress,tempCell->publishingAddress);
        strcpy(tree->category,tempCell->category);
        tree->Right=updateOrDelete(tree->bookName,tree->Right);

    }
    else
    {
        tempCell=tree;
        if(tree->Left==NULL)
            tree=tree->Right;
        else if(tree->Right==NULL)
            tree=tree->Left;
        printf("( %s ) book has been checked and deleted if exist\n\n",data);

        free(tempCell);
    }

    return tree;
}

/* List classification depending on the category to Fiction */
void Fiction( AVLNode t )
{
    if( t != NULL)
    {
        Fiction( t->Left );

        if(strlen(t->category)==8)// depend on the length to avoid upper and lower case issue
            printf("%s\t%s\t%d\t%s\t%s\n", t->bookName,t->autherName,t->publishingDate,t->publishingAddress,t->category);
        Fiction( t->Right );
    }

}

/* List classification depending on the category to non-Fiction */
void nonFiction(AVLNode t)
{
    if( t != NULL)
    {
        nonFiction( t->Left );
        if(strlen(t->category)==12)// depend on the length to avoid upper and lower case issue
            printf("%s\t%s\t%d\t%s\t%s\n", t->bookName,t->autherName,t->publishingDate,t->publishingAddress,t->category);
        nonFiction( t->Right );
    }
}

/*This function used to save and update the library data on the file */
void saveInFile( AVLNode t,FILE*inp)
{
    if( t != NULL)
    {
        saveInFile( t->Left,inp );
        fprintf(inp,"%s \t %s \t %d \t %s \t %s\n", t->bookName,t->autherName,t->publishingDate,t->publishingAddress,t->category);
        saveInFile( t->Right,inp );
    }
}
/* ========================================================== MENU =============================================================== */
void menu(AVLNode tree)
{
    int choice;
    while(2)
    {
        //show Menu on the screen
        printf("================================================================================\n");
        printf("Enter your choice number :-\n");
        printf("1.Read data \n");
        printf("2.Insert a new book to the library\n");
        printf("3.Search for a book \n");
        printf("4.Update/Delete a specific book\n");
        printf("5.List books by category \n");
        printf("6.Height of the tree\n");
        printf("7.save data \n");
        printf("8.Exit \n ==> ");
        scanf("%d",&choice);//get choice number from the user

        switch(choice)//shows cases depending on the choice value
        {
        case 1:
        {
            tree= readBooksInformation(tree);
            if(tree!=NULL)
            {
                printf("The file has been read \n\n");
            }
            else
                printf("error !! The list is Empty \n\n");
        }
        break;
        case 2:
        {
            tree=InsertNewBook(tree);
            printf("\nThe book has been inserted \n\n");
        }
        break;
        case 3:
            searchForBook(tree);
            break;
        case 4:
        {
            char tempName;
            char bookName[30];
            printf("Enter name of book that you want to delete it ==> ");
            scanf("%c",&tempName);
            scanf("%[^\n]",bookName);
            tree=updateOrDelete(bookName,tree);

        }
        break;
        case 5 :
        {
            printf("*********************************************** Fiction *****************************************************\n\n");
            Fiction(tree);
            printf("\n******************************************** Non-fiction ***************************************************\n\n");
            nonFiction(tree);
            printf("\n");
        }
        break;
        case 6:
            printf("Height of the tree : %d\n\n",Height(tree));
            break;
        case 7:
        {
            FILE*inp;
            inp=fopen("books.txt","w");//open file to write inside it
            saveInFile(tree,inp);
            printf("The file has been updated \n\n");

        }
        break;
        case 8 :
            exit(1);
            break;
        default :
            printf("Unknown input !! please enter one of the choices number \n\n");//if the user enter a number that is not in the menu
        }
    }

}

int main()
{
    AVLNode tree;
    tree = MakeEmpty(NULL);
    menu(tree);
    return 0;
}

