#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;
int shrink(void);

void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	int * tempList ;
	if(list==NULL)
    {

        list = (int*)malloc(sizeof(int)*LIST_INIT_SIZE) ;

    }
	else if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    if(list==NULL)
    {

        printf("Current size: 0, current length: %d\n",length);
    }
    else
    {
        printf("Current size: %d, current length: %d\n", listMaxSize, length);
    }
}
int getLength(void)
{
    return length;
}
int insertItemAt(int pos, int item)
{
    if(pos>listMaxSize)
    {
        return NULL_VALUE;
    }
    else if(length+1==listMaxSize)
    {
        int*tempList;
        listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        free(list) ;
        list = tempList ;

    }

    if(pos<length)
    {

        int i;
        for(i=length;i>=pos;i--)
        {
            list[i+1]=list[i];
        }
        list[pos]=item;
        length++;
        return SUCCESS_VALUE;

    }
    else if(pos==length)
    {
        list[pos]=item;
        length++;
        return SUCCESS_VALUE;
    }


}
int shrink(void)
{
    if(length==LIST_INIT_SIZE)
    {
        return NULL_VALUE;
    }
    else if(length<=(listMaxSize/2))
    {
        int *tempList;
        listMaxSize = listMaxSize/2 ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        free(list) ;
        list = tempList ;
        return SUCCESS_VALUE;
    }
    return NULL_VALUE;
}
int deleteLast(void)
{
    int c;
    if(length==0)
    {
        return NULL_VALUE;
    }
    c=list[length-1];

    length--;
    //shrink();
    return c;
}
int clear()
{

    free(list);
    list=0;
    length=0;

    return SUCCESS_VALUE;

}
int deleteAll()
{
    if(length>LIST_INIT_SIZE)
    {
        free(list);
        list=(int*)malloc(sizeof(int)*LIST_INIT_SIZE);
    }
    listMaxSize = LIST_INIT_SIZE;
    length=0;
    return SUCCESS_VALUE;
}
int main(void)//Main function for Task 1-6
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item.\n2. Delete item at.\n3. Delete item.\n");
        printf("4. Delete last.\n5. Clear.\n6. Delete all.\n7. Print.\n8. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            deleteLast();
        }
        else if(ch==5)
        {
            clear();
        }
        else if(ch==6)
        {
            deleteAll();
        }
        else if(ch==7)
        {
            printList();
        }
        else if(ch==8)
        {
            if(list!=0)
            {
                free(list);
            }
            exit(0);
        }
    }

}
/*
int main()//Main function for task 7
{

    char a[100];
    int ch;
    char c;
    while(1)
    {
        printf("1.Postfix operation.\n2.Exit\n");
        scanf("%d%c",&ch,&c);
        if(ch==1)
        {
            initializeList();
            gets(a);
            int i,l;
            l=strlen(a);
            for(i=0;i<l;i++)
            {
                if((a[i]>47)&&(a[i]<58))
                {
                    insertItem(a[i]-48);
                }
                else
                {
                    int c,d;
                    c=deleteLast();
                    d=deleteLast();
                    if(a[i]=='*')
                    {
                        insertItem(c*d);
                    }
                    else if(a[i]=='+')
                    {
                        insertItem(c+d);
                    }
                    else if(a[i]=='-')
                    {
                        insertItem(d-c);
                    }
                    else if(a[i]=='/')
                    {
                        insertItem(d/c);

                    }
                }
            }

            l=getLength();
            int temp[50];
            for(i=l-1;i>=0;i--)
            {
                temp[i]=deleteLast();
            }
            for(i=0;i<l;i++)
            {
                printf("%d",temp[i]);
            }
            printf("\n");
            clear();
        }
        else if(ch==2)
        {
            exit(0);
        }
    }
    return 0;
}*/




