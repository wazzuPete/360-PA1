#define _CRT_SECURE_NO_WARNINGS
#include "treeNode.h"



//////////NODE////////////////22




tree_node* new_node(char* name, char file_or_dir)
{
    tree_node* mpNode = (tree_node*)malloc(sizeof(tree_node));
    if (mpNode == NULL)
    {
        return NULL;
    }
    strncpy(mpNode->name, name, sizeof(mpNode->name) - 1);
    mpNode->name[sizeof(mpNode->name) - 1] = '\0'; // Ensure null-termination
    mpNode->type = file_or_dir;
    mpNode->sibling = NULL;
    mpNode->parent = NULL;
    mpNode->child = NULL;
    mpNode->num_of_sib = 1;

    return mpNode;
}

tree_node* add_child_node(tree_node* parent, char* name, char file_or_dir)
{
    
    tree_node* temp = parent->child;
    tree_node* mpNode = new_node(name, file_or_dir);

    if (parent == NULL)
    {
        return NULL;
    }

    if (mpNode == NULL)
    {
        return NULL;
    }

   
    if (parent->child == NULL)
    {
        parent->child = mpNode;
        mpNode->parent = parent;
    }
    else
    {
        
        while (temp->sibling != NULL)
        {
            temp = temp->sibling;
        }
        temp->sibling = mpNode;
        mpNode->parent = parent;
    }
    return mpNode;
}


void delete_child_node(tree_node* parent, char* name)
{
    if (parent == NULL || parent->child == NULL)
    {
        printf("No File or Directory With that Name!\n");
        return;
    }

    tree_node* temp2 = parent->child, *temp = NULL;

    while (temp2 != NULL) 
    {
        if (strcmp(temp2->name, name) == 0) 
        {
            if (temp2->child != NULL)
            {
                printf("Dir is NOT empty");
                return;
            }
            if (temp == NULL)
            { 
                parent->child = temp2->sibling;
            }
            else 
            { 
                temp->sibling = temp2->sibling;
            }

            free_node(temp2); 
            printf("\nDeleted\n");
            return; 
        }

        temp = temp2;
        temp2 = temp2->sibling;
    }

    printf("\nCould not find File or Dir\n");
}


void free_node(tree_node* node) {
    if (node == NULL) return;


    free_node(node->child);
    free(node);
}



tree_node* check_dir(tree_node* parent, char* name)
{
    tree_node* temp = parent->child;

    
        while (temp != NULL)
        {
            if (strcmp(temp->name, name) == 0)
            {
                return temp;
            }
            temp = temp->sibling;
        }
    

}



/////////////TREE/////////////////////
TREE* init_tree(tree_node* nn)
{
    TREE* new_tree = malloc(sizeof(TREE));
    new_tree->root = nn;
    new_tree->size = 1;

    return new_tree;
}





  

void print_tree_ls(tree_node* child) {
    if (child->sibling == NULL)
    {
       printf("%s  ", child->name);
       return;
    }

    print_tree_ls(child->sibling);
    printf("%s  ", child->name);

}




void print_cwd(tree_node* cwd)
{
    if (strcmp(cwd->name, "/") == 0)
    {
        printf("\n/");
        return;
    }

    print_cwd(cwd->parent);

  
    printf("%s/", cwd->name);
}




//this is bascally a Depth First Traversal but you print out the parents before the node value you are on


void write_tree_r(tree_node* node, FILE* file, const char* basename)
{
    if (node == NULL || file == NULL) 
    {
        return;
    }

    char dirname[1024];

   
    if (strcmp(node->name, "/") == 0)
    {
        snprintf(dirname, sizeof(dirname), "/");
    }
    else 
    {
      
        if (strcmp(basename, "/") == 0) 
        {
            snprintf(dirname, sizeof(dirname), "/%s", node->name);
        }
        else 
        {
            snprintf(dirname, sizeof(dirname), "%s/%s", basename, node->name);
        }
    }

    
    fprintf(file, "%c %s\n", node->type, dirname);

   
    if (node->child != NULL) 
    {
        write_tree_r(node->child, file, dirname);      // this checks the rest of the children for the cwd
    }

 
    if (node->sibling != NULL) 
    {
        write_tree_r(node->sibling, file, basename);   // this will then move on to the siblings of the node "parents other children"
    }
}

void write_to_file(tree_node* root, FILE* file) 
{
    if (root != NULL && file != NULL)
    {
        write_tree_r(root, file, "");
    }
}



TREE* read_from_file(FILE* file)
{
    tree_node* new_root = malloc(sizeof(tree_node));
    strcpy(new_root->name, "/");
    new_root->parent = new_root;
    new_root->sibling = NULL;
    new_root->child = 0;
    new_root->type = 'D';


    tree_node* current_tree_node = malloc(sizeof(tree_node));
    char temp[1024];
    char* set;
    char type;
    
    
    char* dirname = malloc(sizeof(temp));
    char* basename = malloc(sizeof(temp));
    char* one_more = malloc(sizeof(temp));

    TREE* plz = init_tree(new_root);

    fgets(temp, sizeof(temp), file);

    current_tree_node = new_root;

    while (fgets(temp, sizeof(temp), file) != NULL) {

        set = strtok(temp, "/");
        type = *set;

        

        while (dirname != NULL || basename != NULL) {
            

            if (dirname != NULL && basename == NULL)
            {
                
                current_tree_node = add_child_node(new_root, dirname, type);

            }
            if (dirname != NULL && basename != NULL && one_more == NULL)
            {
                current_tree_node = add_child_node(current_tree_node, basename, type);
            }
           
            dirname = strtok(NULL, "/\n"); // Get the dirname and basename
            basename = strtok(NULL, "/\n");
            one_more = strtok(NULL, "/\n");
             
        }
        dirname = malloc(sizeof(temp));
        basename = malloc(sizeof(temp));
        one_more = malloc(sizeof(temp));
        

    }
    return plz;

}




















// void *free_tree(TREE* tree)
// {
//     tree->root = free_node(tree->root);
// }