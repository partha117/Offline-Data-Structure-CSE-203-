#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)
    {
        return 0;
    }
    return getSize(node->left)+getSize(node->right)+1;

}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    int i;
     if(root==0)
    {
        return FALSE_VALUE;
    }
    for(i=0;(temp!=0)&&(temp->item!=node->item);i++)
    {
        if(temp->item>node->item)
        {
            temp=temp->left;
        }
        else if(temp->item<node->item)
        {
            temp=temp->right;
        }
    }

    return i;

}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode * node = 0;
    node = searchItem(root, item);

    return calcNodeDepth(node);

}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    if(node!=0)
    {
        struct treeNode *target=searchItem(node,item);
        if(node==target)
        {
            if((target->left==0)&&(target->right==0))//  no children
            {
                free(target);
                root=0;
                return TRUE_VALUE;
            }
            else if(target->left==0)//right
            {
                root=target->right;
                free(target);
                return TRUE_VALUE;
            }
            else if(target->right==0)//left
            {
                root=target->left;
                free(target);
                return TRUE_VALUE;
            }
            else// left right both
            {
                struct treeNode *prev,*temp,*prev1;
                temp=target->right;
                for(;temp!=0;)//replacer
                {
                    prev=temp;
                    temp=temp->left;
                }
                if(prev==target->right)// if replacer is the immediate right of target
                {
                    target->item=prev->item;
                    target->right=prev->right;// target is following replacer s child
                    free(target->right);
                    return TRUE_VALUE;
                }
                temp=target->right;
                for(;temp!=prev;)// parent of replacer
                {
                    prev1=temp;
                    temp=temp->left;
                }
                target->item=prev->item;// replacing
                prev1->left=prev->right;// parent of replacer is following replacer s child
                //free(target);//freeing
                //prev1->left=0;

                return TRUE_VALUE;

            }
        }
        else//not root node
        {
            struct treeNode *temp=root,*prev=0;
            for(;(temp!=0)&&(temp->item!=item);)//searching parent of target
            {
                prev=temp;
                if(temp->item>item)
                {
                    temp=temp->left;
                }
                else if(temp->item<item)
                {
                    temp=temp->right;
                }
            }
            if((target->left==0)&&(target->right==0))//  no children
            {
                //free(target);
                //root=0;

                if(prev->left==target)
                {
                    free(prev->left);
                    prev->left=0;

                }
                else if(prev->right==target)
                {
                    free(target);
                    prev->right=0;
                }
                return TRUE_VALUE;

            }
            else if(target->left==0)//right
            {
                /*target=target->right->item;
                free(target->right);
                target->right=0;
                return TRUE_VALUE;*/
                if(prev->left==target)
                {
                    prev->left=target->right;
                    free((target));
                    return TRUE_VALUE;

                }
                else if(prev->right==target)
                {
                    prev->right=target->right;
                    free((target));
                    return TRUE_VALUE;
                }

            }
            else if(target->right==0)//left
            {
                if(prev->left==target)
                {
                    prev->left=target->left;
                    free((target));
                    return TRUE_VALUE;

                }
                else if(prev->right==target)
                {
                    prev->right=target->left;
                    free((target));
                    return TRUE_VALUE;
                }
            }
            else// left right both
            {
                struct treeNode *prev,*temp,*prev1;
                temp=target->right;
                for(;temp!=0;)//replacer
                {
                    prev=temp;
                    temp=temp->left;
                }
                if(prev==target->right)// if replacer is the immediate right of target
                {
                    target->item=prev->item;
                    target->right=prev->right;// target is following replacer s child
                    free(prev);
                    return TRUE_VALUE;
                }
                temp=target->right;
                for(;temp!=prev;)// parent of replacer
                {
                    prev1=temp;
                    temp=temp->left;
                }
                target->item=prev->item;// replacing
                prev1->left=prev->right;// parent of replacer is following replacer s child
                //free(target);//freeing
                //prev1->left=0;
                return TRUE_VALUE;

            }
        }
    }
    else
    {
        return FALSE_VALUE;
    }

}

int getMinItem()
{
    struct treeNode *node,*prev=0;
    node=root;

    for(;node!=0;)
    {
        prev=node;
        node=node->left;
    }
    if(prev==0)
    {
        return FALSE_VALUE;
    }
    else
    {
        return prev->item;
    }

}

int getMaxItem()
{
    struct treeNode *node,*prev=0;
    node=root;

    for(;node!=0;)
    {
        prev=node;
        node=node->right;
    }
    if(prev==0)
    {
        return FALSE_VALUE;
    }
    else
    {
        return prev->item;
    }

}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(node!=0)
    {


        if((node->item>=leftBound)&&(node->item<=rightBound))
        {
            return (1+rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound));
        }
        else if((node->item<=leftBound))
        {
            if(node->item==leftBound)
            {
                return (1+rangeSearch(node->right,leftBound,rightBound));
            }
            else
            {
                return (rangeSearch(node->right,leftBound,rightBound));
            }
        }
        else if((node->item>=rightBound))
        {
            if(node->item==rightBound)
            {
                return (1+rangeSearch(node->left,leftBound,rightBound));
            }
            else
            {
                return (rangeSearch(node->left,leftBound,rightBound));
            }

        }

    }
    else
    {
        return 0;
    }
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("\n1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. Calculate Depth 8. get MinItem. 9. get MaxItem.\n10. Range search. 11. Delete. 12. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==12)
        {
            break;
        }
        else if(ch==7)
        {
            int i;
            scanf("%d",&i);
            printf("depth %d\n",calcDepth(i));
        }


        else if(ch==8)
        {
            printf("min item %d\n",getMinItem());
        }
        else if(ch==9)
        {
            printf("max item %d\n",getMaxItem());
        }
        else if(ch==10)
        {
            int item1,item2;
            scanf("%d%d", &item1,&item2);
            printf("Item number %d",rangeSearch(root,item1,item2));

        }
        else if(ch==11)
        {
            int a;
            scanf("%d",&a);
            deleteItem(root,a);
        }
    }

}
