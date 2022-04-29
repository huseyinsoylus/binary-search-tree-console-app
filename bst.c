// Binary Search Tree operations in C

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

struct node {
  int key;
  struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

/*
void findParent(struct Node* node,
                int val, int parent)
{
    if (node == NULL)
        return;
 
    // If current node is the required node
    if (node->data == val) {
 
        // Print its parent
        cout << parent;
    }
    else {
 
        // Recursive calls for the children
        // of the current node
        // Current node is now the new parent
        findParent(node->left, val, node->data);
        findParent(node->right, val, node->data);
    }
}

*/


void who_is_parent(struct node * root,int val, int parent) {
  
  struct node* node = (struct node *)malloc(sizeof(struct node));
  node = root;
  
  
  if(node == NULL)
    return;
  
  if(node->key == val)
  {
    printf("The parent of %d is %d\n",val,parent);
  }
  else
  {
    who_is_parent(node->left,val,node->key);
    who_is_parent(node->right,val,node->key);
  }  
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    //Traverse root
    printf("%d ", root->key);

    //Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == NULL) return newNode(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;	

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

void is_parameter_int(char * command,char * command_buff, char * parameter)
{
  int j = 0;
  int k=0;
  //char command_buff[100]; 
  int command_lenght = strlen(command) - 1;
  for(int i = 0; i < command_lenght ; i++)
  {
    if(command[i] != ' ')
    {
      command_buff[i] = command[i];
    }
    else
    {
      j = i+1;
      for(;j<command_lenght;j++)
      {
        parameter[k] = command[j];
        k++;
      }
      break;
      
    } 
  }
}

int charToInt(char c){
	int num = 0;

	//Substract '0' from entered char to get
	//corresponding digit
	num = c - '0';

	return num;
}

int parameter_to_int(char * parameter)
{
  int lenght = strlen(parameter);
  int toplam = 0;
  int katsayi=1;
  for(int i = lenght-1;i>=0;i--)
  {
    int sayisal_deger=0;
    //printf("kaRAKTER %c",parameter[i]);
    sayisal_deger = charToInt(parameter[i]);
    //printf("sAYI KARŞILIGI %d",sayisal_deger);
    toplam += ((sayisal_deger*katsayi));
    katsayi*=10;
  }
  
  return toplam;
}


int * parameter_convert_construct(char * parameter)
{
  int k=0,p=0;
  int lenght = strlen(parameter);
  char * construct_parameter = (char *)malloc(sizeof(char)*50);
  int * return_arr = (int *)malloc(sizeof(int)*30);
  for(int i=0; i<lenght; i++)
  {
    
    if(parameter[i] == ',' || parameter[i] == '[' || parameter[i] == ']')
    {
      k=0;
      if(i != 0)
      {
      //printf("girdi if %d %s\n",i,construct_parameter);
        int insert_value = parameter_to_int(construct_parameter);
        return_arr[p] = insert_value;
        //printf("return array %d\n",return_arr[p]);
        p++;
        //printf("insert value %d\n",insert_value);
      }
    }
    else
    {
      //printf("girdi else %d \n",i);
      construct_parameter[k]=parameter[i];
      construct_parameter[k+1] = '\0';
      k++;
    }
  }
  
  return return_arr;
}
void deneme(struct node*root)
{
  root = insert(root, 15);
}

// Driver code
int main() {

  struct node *root = NULL;
  
  
  size_t buff_size = 50;
 
  while(1)
  {
    char * command = (char *)malloc(sizeof(char)*100);
    char * command_buff = (char *)malloc(sizeof(char)*100);//ilk parametre
    char * parameter = (char *)malloc(sizeof(char)*50);//ikinci parametre
    
    fflush(stdin);
    fgets(command, 100, stdin);
    //getline(&command,&buff_size,stdin);
    //printf("%s %ld",command, strlen(command));
    
    is_parameter_int(command,command_buff,parameter);//İlk parametre ile ikinci parametrenin ayrılması işlemi
    //printf("Command --> %sParameter --> %s %ld\n",command_buff,parameter,strlen(parameter));
    
    if(strcmp(command_buff,"EXIT") == 0)
    {
      _Exit(0); 
    }
    else if(strcmp(command_buff,"INSERT") == 0)
    {
      int insert_value = parameter_to_int(parameter);
      root = insert(root, insert_value);
      who_is_parent(root,insert_value,-1);
    }
    else if(strcmp(command_buff,"LIST") == 0)
    {
      inorder(root);
      printf("\n");
    }
    else if(strcmp(command_buff,"DELETE") == 0)
    {
      int delete_value = parameter_to_int(parameter);
      if(root != NULL)
      {
        if(root->key == delete_value)
        {
          root = deleteNode(root, delete_value);
          if(root != NULL)
          printf("Root Changed. The new root is %d\n",root->key);
        }
        else
        {
          root = deleteNode(root, delete_value);
        }    
      }
    }
    else if(strcmp(command_buff,"PARENT") == 0)
    {
      int value = parameter_to_int(parameter);
      if(root!=NULL && root->key == value)
      {
        printf("It is a root node\n");
      }
      else
      {
        who_is_parent(root,value,-1);
      }
      
      //printf("%d nin Parenti %d",value,parent->key);
    }
    else if(strcmp(command_buff,"CONSTRUCT") == 0)
    {
      int z=0; 
      int * construct_par_arr = (int*)malloc(sizeof(int)*30);
      construct_par_arr = parameter_convert_construct(parameter);
      while(construct_par_arr[z]!='\0')
      {
        //printf("%d eleman %d\n",z+1,construct_par_arr[z]);
        root = insert(root, construct_par_arr[z]);
        z++;
      }
    }
    free(command);
    free(command_buff);
    free(parameter);     
  }
}

