#include<iostream>
#include<stdlib.h>
#include<graphics.h>
#include<string>
#include<stdio.h>
#include <sys/time.h>
#include <queue>


struct timeval start2, end2;
using namespace std;

int mob[10];
string name[10];

/*  STRUCTURES USED */

struct phoneb{
char name[11];
char mob[11];
}temp[7];


struct node
{
    char data[11];
    char mob[11];
    struct node *left, *right;
    int ux,uy;
};


int co=0;




/* FUNCTIONS USED*/


void final();

node* insert_wo_delay(node* root,char num[11],char mob[11]);

void exit();

void circ(int x,int y,char data[11],char mob[11]);

struct node* search(node* root,char data[11]);

struct node * minValueNode(struct node* node);

struct node* deleteNode(struct node* root, char key[11]);

node* insert(node* root,char num[11],char mob[11]);

void inorder(node *root);

int add();

int welcome();

void display();

void menu();

void printGivenLevel(struct node* root, int level);

int height(struct node* node);

struct node* newNode(int data);




/*_____________________________FINAL PROGRAM__________________________________*/

void final()
{

    cleardevice();
    rectangle(0,0,999,647);
    setfillstyle(SOLID_FILL,9);
    floodfill(2,2,WHITE);
    /*Bacground ends*/

    /*BORDER*/
    rectangle(20,20,979,627);
    setfillstyle(2,9);
    floodfill(10,10,WHITE);
    /*BORDER ENDS*/
    node *root=NULL;
    cout<<co;
    for(int i=0;i<co;i++)
    {
        if(i==0)
        root=insert(root,temp[i].name,temp[i].mob);
        else
            insert(root,temp[i].name,temp[i].mob);
    }

}



node* insert_wo_delay(node* root,char num[11],char mob[11])
{
    node *temp,*parent;
    int m=300;
    if (root==NULL)
    {
        root = new node;
        strcpy(root->data,num);
        root->left=NULL;
        root->right=NULL;
        root->ux=500;
        root->uy=100;
        strcpy(root->mob,mob);
        temp=root;
        circ(root->ux,root->uy,num,mob);
    }
    else
    {
        temp=root;
        char t[11];
        while (temp!=NULL)
        {
            m=m-70;
            strcpy(t,temp->data);
            if (stricmp(num,t)<=0)
            {
                parent = temp;
                temp=temp->left;
            }
            else
            {
                parent =temp;
                temp=temp->right;
            }
        }

        node *newNode = new node;
        strcpy(newNode->data,num);
        strcpy(newNode->mob,mob);
        newNode->left = NULL;
        newNode->right = NULL;
        if(stricmp(num,t)<=0)
        {
            parent->left = newNode;
            int ux=parent->ux, uy=parent->uy;
            newNode->ux=ux-m;
            newNode->uy=uy+200;
            line(ux,uy+50,ux-m,uy+150);
            circ(ux-m,uy+200,num,mob);
        }
        else
        {
            int ux=parent->ux, uy=parent->uy;
            newNode->ux=ux+m;
            newNode->uy=uy+200;
            parent->right = newNode;
            line(ux,uy+50,ux+m,uy+150);
            circ(ux+m,uy+200,num,mob);
        }
    }
    return root;
}


void exit()
{
    int z;
    cleardevice();
    for(z=0;z<=300;z=z+3)
    {
    setcolor(z%10);
    rectangle(0+z,0+z,997-z,647-z);
    circle(497,325,z);
    delay(30);
    }
    settextstyle(1,0,3);
    setcolor(6);
    cleardevice();
    setbkcolor(7);
    outtextxy(190,200,"THANK YOU FOR USING");
    outtextxy(260,240,"PHONEBOOK");
}



void circ(int x,int y,char data[11],char mob[11])
{
   circle(x,y,50);
    setfillstyle(SOLID_FILL,10);
    floodfill(x,y,WHITE);

    outtextxy( x-60,y-70,data);
    outtextxy(x-60,y-45,mob);
    delay(1000);
}

struct node* search(node* root,char data[11])
{
    struct node *current = root;
    char t[11];
    strcpy(t,current->data);

    while(stricmp(data,t)!=0)
    {
        if(current != NULL)
        {
            circle(current->ux,current->uy,35);
            setfillstyle(6,7);
            floodfill(current->ux,current->uy,WHITE);
            delay(1000);
            if(stricmp(data,t)<0)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
            strcpy(t,current->data);
      }
   }
   return current;
}



struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}



/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, char key[10])
{
    // base case
    if (root == NULL) return root;

    char t[11];
    strcpy(t,root->data);

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (stricmp(key,t)<0)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (stricmp(key,t)>0)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->data ,temp->data);
        strcpy(root->mob,temp->mob);

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}




node* insert(node* root,char num[11],char mob[11])
{
    node *temp,*parent;
    int m=300;
    if (root==NULL)
    {
        root = new node;
        strcpy(root->data,num);
        strcpy(root->mob,mob);
        root->left=NULL;
        root->right=NULL;
        root->ux=500;
        root->uy=100;
        temp=root;
        circ(root->ux,root->uy,num,mob);
        delay(1000);
    }
    else
    {
        temp=root;
        char t[11];
        while (temp!=NULL)
        {
            m=m-70;
            strcpy(t,temp->data);
            if (stricmp(num,t)<=0)
            {
                parent = temp;
                temp=temp->left;
            }
            else
            {
                parent =temp;
                temp=temp->right;
            }
        }

        node *newNode = new node;
        strcpy(newNode->data,num);
        strcpy(newNode->mob,mob);
        newNode->left = NULL;
        newNode->right = NULL;
        if(stricmp(num,t)<=0)
        {
            parent->left = newNode;
            int ux=parent->ux, uy=parent->uy;
            newNode->ux=ux-m;
            newNode->uy=uy+200;
            line(ux,uy+50,ux-m,uy+150);
            delay(1000);
            circ(ux-m,uy+200,num,mob);
            delay(1000);
        }
        else
        {
            int ux=parent->ux, uy=parent->uy;
            newNode->ux=ux+m;
            newNode->uy=uy+200;
            parent->right = newNode;
            line(ux,uy+50,ux+m,uy+150);
            delay(1000);
            circ(ux+m,uy+200,num,mob);
            delay(1000);
        }
    }
    return root;
}




void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->data<<" \n";
        inorder(root->right);
    }
}



int add()
{
int i=co;

char ans;
do{

    cout<<"Enter First Name and Mobile Number"<<endl;
    cin>>temp[i].name>>temp[i].mob;
      name[i]=temp[i].name;
      mob[i]="0";
      
        i++;
    cout<<"Do you want to enter more? (y/n)"<<endl;
    cin>>ans;

}while(ans=='y');

return i;
}



int welcome()
 {
  int s,x,i,c,d,y,j,b,t1,t2,t3,t4;
  initwindow(1000,650,"hhhelo");
  x=getmaxx();
  y=getmaxy();
  //cleardevice();
  x=(x-20)/8;
  y=(y-20)/8;
  line(10,10,10,(y*8)+10);
  line((x*8)+10,10,(x*8)+10,(y*8)+10);
  line(10,10,(x*8)+10,10);
  line(10,(y*8)+10,(x*8)+10,(y*8)+10);
  for(i=1;i<y;i++)
  {
    line(x+10,10+i,(x*2)+10,10+i);
    line((x*5)+10,10+i,(x*6)+10,10+i);
    line((x*3)+10,10+i,(x*4)+10,10+i);
    line((x*7)+10,10+i,(x*8)+10,10+i);
    line(10,y+i+10,x+10,y+i+10);
    line((x*2)+10,y+i+10,(x*3)+10,y+i+10);
    line((x*4)+10,y+i+10,(x*5)+10,y+i+10);
    line((x*6)+10,y+i+10,(x*7)+10,y+i+10);
    line(x+10,(y*2)+10+i,(x*2)+10,(y*2)+10+i);
 line((x*3)+10,y*2+i+10,(x*4)+10,y*2+i+10);
 line((x*5)+10,y*2+i+10,(x*6)+10,y*2+i+10);
 line((x*7)+10,y*2+i+10,(x*8)+10,y*2+i+10);
 line(10,(y*3)+10+i,x+10,(y*3)+10+i);
 line((x*2)+10,y*3+i+10,(x*3)+10,y*3+i+10);
 line((x*4)+10,y*3+i+10,(x*5)+10,y*3+i+10);
 line((x*6)+10,y*3+i+10,(x*7)+10,y*3+i+10);
 line(x+10,(y*4)+10+i,(x*2)+10,(y*4)+10+i);
 line((x*3)+10,y*4+i+10,(x*4)+10,y*4+i+10);
 line((x*5)+10,y*4+i+10,(x*6)+10,y*4+i+10);
 line((x*7)+10,y*4+i+10,(x*8)+10,y*4+i+10);
 line(10,(y*5)+10+i,x+10,(y*5)+10+i);
 line((x*2)+10,y*5+i+10,(x*3)+10,y*5+i+10);
 line((x*4)+10,y*5+i+10,(x*5)+10,y*5+i+10);
 line((x*6)+10,y*5+i+10,(x*7)+10,y*5+i+10);
 line(x+10,(y*6)+10+i,(x*2)+10,(y*6)+10+i);
 line((x*3)+10,y*6+i+10,(x*4)+10,y*6+i+10);
 line((x*5)+10,y*6+i+10,(x*6)+10,y*6+i+10);
 line((x*7)+10,y*6+i+10,(x*8)+10,y*6+i+10);
 line(10,(y*7)+10+i,x+10,(y*7)+10+i);
 line((x*2)+10,y*7+i+10,(x*3)+10,y*7+i+10);
 line((x*4)+10,y*7+i+10,(x*5)+10,y*7+i+10);
 line((x*6)+10,y*7+i+10,(x*7)+10,y*7+i+10);
delay(2);
 }
setcolor(2);
c=(x/2)+10;
d=(y/2)+10;

 delay(3);
 x=getmaxx();
 y=getmaxy();
 setcolor(16);
for(i=x/2,j=10;i>=0;i--)
 {
  line(i,10,i,y);
  line(x-i,10,x-i,y);
  delay(2);
  }
 t1=10;
 t2=8;
 t4=1;
 i=1;
 rectangle(0,0,997,647);
 setfillstyle(1,WHITE);
 floodfill(5,5,WHITE);
 setcolor(WHITE);
settextstyle(DEFAULT_FONT,HORIZ_DIR,10);
setbkcolor(BLACK);
outtextxy(150,150,"Welcome!!");

delay(2000);
return(0);
}


void display()
{
    int gdriver = DETECT, gmode;
    initwindow(1000,650,"madarchodd!!");

    rectangle(0,0,999,647);
    setfillstyle(SOLID_FILL,9);
    floodfill(2,2,WHITE);
    /*Bacground ends*/

    /*BORDER*/
    rectangle(20,20,979,627);
    setfillstyle(2,9);
    floodfill(10,10,WHITE);
    /*BORDER ENDS*/

}

/* Function protoypes */
void printGivenLevel(struct node* root, int level);
int height(struct node* node);
struct node* newNode(int data);

/* Function to print level order traversal a tree*/
void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        printGivenLevel(root, i);
}

/* Print nodes at a given level */
void printGivenLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        {
            strcpy(temp[co].name,root->data);
            strcpy(temp[co].mob,root->mob);
            co++;
        }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

void compareit();

void menu()
{
    cleardevice();
    setcolor(4);
    rectangle(0,0,997,647);
    setfillstyle(1,9);
    floodfill(100,100,WHITE);
    setcolor(3);
    rectangle(20,20,979,627);
    setfillstyle(2,3);
    floodfill(10,10,3);
    setcolor(10);
    setbkcolor(9);
    settextstyle(1,0,2);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
    outtextxy(250,100,"MAIN MENU");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(220,200,"1) Add a new contact.");
    outtextxy(220,230,"2) Search for a contact.");
    outtextxy(220,260,"3) Edit a contact.");
    outtextxy(220,290,"4) Delete a contact.");
    outtextxy(220,320,"5) Compare time of execution");
    outtextxy(220,350,"6) Exit");
    outtextxy(220,380,"Enter your choice ");


    node *root = NULL;

    int p;
    int dp=1;
    char ans;

    do
    {
        cout<<"Enter your choice: ";
        cin>>p;


    switch(p)
    {
        case 1:
        {   int i;
           i=add();

            if(dp==1)
            {
                display();
                dp=0;
            }
            for(int j=co;j<i;j++)
            {
                if(j==0)
                    root=insert(root,temp[j].name,temp[j].mob);
                else
                insert(root,temp[j].name,temp[j].mob);
            }
            co=co+i;
            break;
        }

        case 2:
        {
           char ele[11];
           cout<<"\nEnter the element to be searched: ";
           scanf("%s",ele);

           node * found=search(root,ele);
            circle(found->ux,found->uy,35);
            setfillstyle(8,CYAN);
            floodfill(found->ux,found->uy,WHITE);
            outtextxy(found->ux-30,found->uy+45,"FOUND!!");

            break;
        }


        case 3:
        {
           char ele[11],x[11],y[11];
           cout<<"\nEnter the element to be Edited: ";
           scanf("%s",ele);
            cout<<"\nEnter the new name and mobile: ";
            scanf("%s %s",x,y);


           node * found=search(root,ele);
            circle(found->ux,found->uy,35);
            setfillstyle(8,CYAN);
            floodfill(found->ux,found->uy,WHITE);
            outtextxy(found->ux-80,found->uy+45,"ELEMENT TO BE EDITED!!");
            delay(2000);

            root=deleteNode(root,ele);
            co=0;

            printLevelOrder(root);
            strcpy(temp[co].name,x);
            strcpy(temp[co++].mob,y);

            final();
            break;
        }


        case 4:
        {
            char ele[11];
           cout<<"\nEnter the element to be deleted: ";
           scanf("%s",ele);

           node * found=search(root,ele);
            circle(found->ux,found->uy,35);
            setfillstyle(8,CYAN);
            floodfill(found->ux,found->uy,WHITE);
            outtextxy(found->ux-80,found->uy+45,"ELEMENT TO BE DELETED!!");
            delay(2000);

            root=deleteNode(root,ele);
            co=0;

            printLevelOrder(root);

            final();
           break;
        }


        case 5:
            compareit();
            break;

        case 6:
            exit();
            break;

        default :
        setcolor(1);
        outtextxy(240,400,"'Incorrect choice'");
        delay(1000);
        break;
    }

    cout<<"\nDo you want to enter more choices? (y/n)\n";
    cin>>ans;
    }while(ans=='y');
}



/*********Time conversion *******/


struct DS{
char type[100];
double time;
};
DS store[10];
 int ptr=0;

struct Node
{
    int mob;
    string name;
    struct Node *left;
    struct Node *right;
    int height;
};

void incompare(){

char c;
int clr=0;
cout<<"Time of execution comparison using various Data Structures"<<endl;

do{
    cout<<"Enter name and mobile mobber to "<<endl;
    cin>>name[clr]>>mob[clr];
    clr++;
    cout<<"Do you want to enter more? (y/n)"<<endl;
    cin>>c;

}while(c=='y');


}
// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}


struct Node* newnode(int mob,string name)
{
    struct Node* node = new Node;
    node->mob   = mob;
    node->name=name;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}


struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}


struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}


int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Node* insert(struct Node* node, int mob,string name )
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newnode(mob,name));

    if (mob < node->mob)
        node->left  = insert(node->left, mob,name);
    else if (mob > node->mob)
        node->right = insert(node->right, mob,name);
    else // Equal mobs are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    if (balance > 1 && mob < node->left->mob)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && mob > node->right->mob)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && mob > node->left->mob)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && mob < node->right->mob)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}



void preAvl(struct Node *root)
{
    if(root != NULL)
    {
        cout<<root->mob<<" "<<root->name<<endl;
        preAvl(root->left);
        preAvl(root->right);
    }
}


struct bT{
string name;
int mob;
struct bT *right;
struct bT *left;
};


bT *newNode(int mob,string name){
bT *temp;
temp=new bT;
temp->mob=mob;
temp->name=name;
temp->left=NULL;
temp->right=NULL;
return temp;
}


int hasBothChild(struct bT* temp)
{
    return temp && temp->left && temp->right;
}


queue <bT *> myq;


void insertbt(struct bT **root, int mob, string name)
{
    struct bT *temp = newNode(mob,name);

    if (!*root)
        *root = temp;

    else
    {

        struct bT* front = myq.front();
if (front->left==NULL)
            front->left = temp;
        else if (front->right==NULL)
            front->right = temp;

        if (hasBothChild(front))
            myq.pop();
    }


myq.push(temp);
}

bT *binaryST(bT *root, int mob,string name){

if(root==NULL)
{
    return (newNode(mob,name));

}
if(name<root->name){

root->left=binaryST(root->left,mob,name);
}else {

    root->right=binaryST(root->right,mob,name);

}
return root;
}

void timein(char type[100]){
gettimeofday(&end2, NULL);
double delta = ((end2.tv_sec  - start2.tv_sec) * 1000000u +
         end2.tv_usec - start2.tv_usec) / 1.e6;
printf("Time is : %f ",delta);
cout<<type<<endl;
store[ptr].time=delta;
strcpy(store[ptr++].type,type);
}
void print(bT *temp){
if(temp){

    print(temp->left);
    cout<<temp->name<<" "<<temp->mob<<endl;
    print(temp->right);
}
}

void crheap(int k[],int n)
{
 int i,q, parent,child,temp;
 for(q=2;q<=n;q++)
 {
  child=q;
  parent=(int)child/2;
  while(child >1 && k[child] > k[parent])
  {
    temp=k[child];
    k[child]= k[parent];
    k[parent]=temp;
    child=parent;
    parent=(int)child/2;
    if(parent < 1)
       parent=1;
  }
 }
 printf("\n Now the array in heap form is: ");
  for(i=1;i<=n;i++)
    printf(" %3d",k[i]);
}

/* function to sort a heap */
void processheap(int k[],int n)
{
 int current,parent,child,i,maxnodes;
 for(maxnodes=n;maxnodes>=2;maxnodes--)
 {
  current=k[maxnodes];;
  k[maxnodes]=k[1];
  /* adjust the array to be a heap of size n-1 */
  parent=1;
  /* obtain the larger of the root's children */
  if (maxnodes-1 >= 3 && k[3] > k[2])
      child=3;
  else
      child = 2;
  /* move keys upwards to find place for current */
  while (child<=maxnodes-1 && k[child]>=current)
  {
   k[parent]=k[child];
   parent=child;
   child=child*2;
   if(child+1 <= maxnodes-1 && k[child+1] > k[child])
     child = child + 1;
  }
  k[parent]=current;
 }
 /* end of for */
 printf("\n The sorted array is : ");

 for(i=1;i<=n;i++)

       printf("%4d",k[i]);

}
void displaydata(){

    for(int i=0;i<10;i++) cout<<endl;
    initwindow(1000,650,"hello");

    rectangle(0,0,997,647);
    setfillstyle(8,9);
    floodfill(2,2,WHITE);


    rectangle(20,20,977,627);
    setfillstyle(1,7);
    floodfill(2,2,WHITE);

    rectangle(200,100,800,550);
    setfillstyle(1,7);
    floodfill(500,325,WHITE);

    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    setbkcolor(7);
    setcolor(5);
    outtextxy(210,110,"Time of Execution");

for(int i=0;i<ptr;i++){

    char asstr[10];
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    setbkcolor(7);
    setcolor(9);
    outtextxy(210,200+i*50,store[i].type);

    for(double j=0.000000;j<=store[i].time;j=j+0.000001){

     sprintf(asstr,"%f",j);
     setcolor(BLACK);
     outtextxy(680,200+i*50,asstr);

    }
    cout<<store[i].type<<"\t "<<store[i].time<<endl;

}

system("PAUSE");
}

void compareit()
{ bT *root=NULL;



int n=sizeof(mob)/sizeof(int);

/*B Tree*/
gettimeofday(&start2, NULL);
for(int i=0;i<n;i++){

       insertbt(&root,mob[i],name[i]);
}
print(root);
timein("Complete Binary Tree(Queue)");
/*BT Ends*/

/*Binary S T*/
bT *root2=NULL;
gettimeofday(&start2, NULL);
for(int i=0;i<n;i++){

      root2=binaryST(root2,mob[i],name[i]);
}
print(root2);
timein("Binary Search Tree(Recursion)");
/*BST ENDS*/

/*AVL Starts*/
struct Node *rootavl = NULL;
gettimeofday(&start2, NULL);
for(int i=0;i<n;i++){

    rootavl=insert(rootavl,mob[i],name[i]);

}
preAvl(rootavl);
timein("AVL Tree");
/*Avl Ends*/

/*heap*/
   gettimeofday(&start2, NULL);

   crheap(mob,n);

   processheap(mob,n);

   timein("Heap Tree");
/*heap ends*/
displaydata();
    return;
}
/********Time Conversion ENDS*****/
int main()
{
    welcome();
    menu();

   system("PAUSE");
    return 0;
}