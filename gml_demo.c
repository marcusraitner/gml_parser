/*
 * Demo for the GML_parser. Usage: gml_demo <gml_file>
 * Simply prints the list of Key-Value pairs to stdout
 */

#include "gml_parser.h"
#include <stdio.h>
#include <stdlib.h>

void print_keys (struct GML_list_elem* list) {
    
    while (list) {
	printf ("%s\n", list->key);
	list = list->next;
    }
}

void main (int argc, char* argv[]) {
  
    struct GML_pair* list;
    struct GML_stat* stat=(struct GML_stat*)malloc(sizeof(struct GML_stat));
    stat->key_list = NULL;
    
    if (argc != 2) printf ("Usage: gml_test <gml_file> \n");
    else {
	FILE* file = fopen (argv[1], "r");
	if (file == 0) printf ("\n No such file: %s", argv[1]);
	else {
	    GML_init ();
	    list = GML_parser (file, stat, 0);

	    if (stat->err.err_num != GML_OK) {
		printf ("An error occured while reading line %d column %d of %s:\n", stat->err.line, stat->err.column, argv[1]);
		
		switch (stat->err.err_num) {
		case GML_UNEXPECTED:
		    printf ("UNEXPECTED CHARACTER");
		    break;
		    
		case GML_SYNTAX:
		    printf ("SYNTAX ERROR"); 
		    break;
		    
		case GML_PREMATURE_EOF:
		    printf ("PREMATURE EOF IN STRING");
		    break;
		    
		case GML_TOO_MANY_DIGITS:
		    printf ("NUMBER WITH TOO MANY DIGITS");
		    break;
		    
		case GML_OPEN_BRACKET:
		    printf ("OPEN BRACKETS LEFT AT EOF");
		    break;
		    
		case GML_TOO_MANY_BRACKETS:
		    printf ("TOO MANY CLOSING BRACKETS");
		    break;
		
		default:
		    break;
		}
		
		printf ("\n");
	    }      
	    GML_print_list (list, 0);
	    printf ("Keys used in %s: \n", argv[1]);
	    print_keys (stat->key_list);
	    GML_free_list (list, stat->key_list);
	}
    }
}
