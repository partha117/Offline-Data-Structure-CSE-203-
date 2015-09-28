#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    struct listNode *prev=0,*temp,*temp1;
    temp=(struct listNode*)malloc(sizeof(struct listNode));
    temp->item=item;
    temp1=list;

    for(;temp1!=0;)
    {
        //printf("in the loop\n");
        prev=temp1;
        temp1=temp1->next;
    }
    temp->next=temp1;
    if(prev==0)
    {
        //printf("it is\n");
       list=temp;
    }
    else
    {
        prev->next=temp;
    }


    return SUCCESS_VALUE;
}

int insertAfter(int oldItem, int newItem)
{
    struct listNode *temp1,*temp;
    temp1=(struct listNode*)malloc(sizeof(struct listNode));
    temp1->item=newItem;
    temp=list;
    for(;(temp!=0)&&(temp->item!=oldItem);)
    {

        temp=temp->next;
    }
    if(temp==0)
    {
        return NULL_VALUE;
    }
    if(temp->item==oldItem)
    {
        temp1->next=temp->next;
        temp->next=temp1;
        return SUCCESS_VALUE;
    }


}

int deleteLast()
{
    struct listNode *prev=0,*temp;
    if(list==0)
    {
        return NULL_VALUE;
    }
    temp=list;
    for(;temp->next!=0;)
    {
        prev=temp;
        temp=temp->next;
    }
    if(prev==0)
    {
        free(list);
        list=0;
        return SUCCESS_VALUE;
    }
    //printf("got it\n");
    free(temp);
    prev->next=0;
    return SUCCESS_VALUE;

}

int deleteFirst()
{
    if(list==0)
    {
        return NULL_VALUE;
    }
    else
    {
        struct listNode *temp;
        temp=list->next;
        free(list);
        list=temp;
        return SUCCESS_VALUE;

    }
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. insertAfter. 6. deleteFirst.\n");
        printf("7. deleteLast 8. print. 9. exit\n");

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
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d",&item);
            insertLast(item);
        }
        else if(ch==5)
        {
            int item,item1;
            scanf("%d%d",&item,&item1);
            insertAfter(item,item1);
        }
        else if(ch==6)
        {
            deleteFirst();
        }
         else if(ch==7)
        {
            deleteLast();
        }
        else if(ch==8)
        {
            printList();
        }
        else if(ch==9)
        {
            exit(0);
        }
    }

}
