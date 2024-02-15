#pragma once
#ifndef treeNode_h
#define treeNode_h
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/////////NODE////////////////


typedef struct tree_node {
    char name[64];
    char type;
    int num_of_sib;
    struct tree_node* sibling, * parent, * child;
} tree_node;


tree_node* new_node(char* name, char file_or_dir);

tree_node* add_child_node(tree_node* parent, char* name, char file_or_dir);

void delete_child_node(tree_node* parent, char* name);



void free_node(tree_node* node);







/////////TREE//////////////



typedef struct
{
    tree_node* root;
    int size;
} TREE;


TREE* init_tree(tree_node* nn);


void print_cwd(tree_node* cwd);
void print_tree_ls(tree_node* child);


tree_node *check_dir(tree_node* parent, char* name);






void write_tree_to_file_recursive(tree_node* node, FILE* file, char* path_prefix);

void write_to_file(tree_node* root, FILE* file);



TREE* read_from_file(FILE* file);


//void* free_tree(TREE* tree);



#endif
