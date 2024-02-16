#include <stdio.h>
#include <string.h>
#include <stdlib.h>    
#include "treeNode.h"   


//HEADERS////22


//Global//
tree_node* root;
tree_node* cwd;
char* cmd[] = { "mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm","reload", "save", "cd..", "quit", 0};



int main() {
	initialize();
	tree_node* check = new_node("", NULL);
	TREE* tree = init_tree(root);
	int x = 0;
	char answer[200];
	char* command, * name;
	tree_node* current_tree_node = root;

	FILE* file;


	while (x != 11) 
	{
		printf("\n");
		print_cwd(current_tree_node);
		printf("");
			if (fgets(answer, sizeof(answer), stdin) != NULL) 
			{
				size_t len = strlen(answer);
				if (len > 0 && answer[len - 1] == '\n') {
					answer[len - 1] = '\0';
				}
				
			}
			else 
			{
				printf("Error reading input.\n");
				return 1;
			};

		
		command = strtok(answer, " ");

		name = strtok(NULL, " ");


		if (command == NULL && name == NULL)
		{

			printf("\nWrong Amount of arguments\n");
			continue;
		}



		x = find_command(command) + 1;
		// complete implementations
		if (x != -1)
		{
			switch (x)
			{
			case 1: //mkdir makes new directory 




				if (current_tree_node->type == 'F')
				{
					printf("You are curently in a File!!!\n");
					break;
				}

				tree_node* temp2 = check_dir(current_tree_node, name);

				if (temp2 == NULL)
				{
					add_child_node(current_tree_node, name, 'D');
					break;
				}
				printf("This Folder is already created in this Dir");
				
				
				break;



			case 2: //rmdir removes a directory




				if (current_tree_node->type == 'F')
				{
					printf("You are curently in a File!!!\n");
					break;
				}

				tree_node* temp3 = check_dir(current_tree_node, name);

				if (temp3 != NULL)
				{
					delete_child_node(current_tree_node, name);
					break;
				}
				printf("This Folder is not in the Dir");
				

			
				break;






			case 3: //ls identifies nodes within current directory




				if (current_tree_node->type != 'D')
				{
					printf("You are curently in a File!!!\n");
					break;
				}
				
				else if (current_tree_node->child != NULL)
				{
					print_tree_ls(current_tree_node->child);
				}
				else
				{
					printf("empty dir\n");
				}

				
				break;



				

			case 4: //cd allows you to enter into next directory


				

				check = check_dir(current_tree_node, name);

				if (check != NULL)
				{
					current_tree_node = check;
					break;
				}
				printf("There is no Directory to Enter");

				break;





			case 5: //pwd print the absolute pathname of CWD(Current Working Directory)



				print_cwd(current_tree_node);
				printf("\n");
				break;




			case 6: //creat creates a new file





				if (current_tree_node->type == 'F')
				{
					printf("You are curently in a File!!!\n");
					break;
				}

				tree_node* temp4 = check_dir(current_tree_node, name);

				if (temp4 == NULL)
				{
					add_child_node(current_tree_node, name, 'F');
					break;
				}
				printf("This File is already created in this Dir");

				break;







			case 7: //rm removes file from directory





				if (current_tree_node->type != 'F')
				{
					printf("You are curently in a File!!!\n");
					break;
				}




				tree_node* temp5 = check_dir(current_tree_node, name);

				if (temp5 != NULL)
				{
					delete_child_node(current_tree_node, name);
					break;
				}

				printf("This File is not in the Dir");







			case 8: //reload the text from the file.txt

				file = fopen("fssim_lagonegro.txt", "r");

				tree = read_from_file(file);

				current_tree_node = tree->root;

				fclose(file);
				
				break;




			case 9: //save to the file.txt

				file = fopen("fssim_lagonegro.txt", "w");

				write_to_file(current_tree_node, file);

				fclose(file);
				break;

			case 10:// goes back to previos directory 
				if (current_tree_node != "/")
				{
					current_tree_node = current_tree_node->parent;
				}
				break;
				
			case 11:
				
				file = fopen("fssim_lagonegro.txt", "w");

				write_to_file(root, file);

				fclose(file);
				break;
				//quit
			//required to save this as well
				;
			}
		}

		else {
			printf("Invalid Command\n");
		}

	}

	free(tree);
}

int find_command(char* user_command) {
	int i = 0;
	while (cmd[i]) {
		if (strcmp(user_command, cmd[i]) == 0)
			return i;
		i++;
	}
	return -1;
}












int initialize() {
	root = (tree_node*)malloc(sizeof(tree_node));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	cwd = root;
	printf("Filesystem initialized!\n");
}
