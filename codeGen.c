#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"


int reg[8];
int regused[8];
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0, i=0, regid = 0,tableid=0,a=0,b=0,first=0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = table[ tableid = getval(root->lexeme,1) ].val;
                for( i=0; i<8; i++){
                	if(regused[i] == 0){
                		regid = i;
						reg[i] = retval;
                		printf ("MOV r%d [%d]\n", regid, tableid*4);
                		regused[i] = 1;
						break;
					}
				}
                break;
            case INT:
                for( i=0; i<8; i++){
                	if(regused[i] == 0){
                		regid = i;
						//reg[i] = retval;
                		printf ("MOV r%d %d\n", regid, atoi(root->lexeme));
						regused[i] = 1;
						break;
					}
				}
                break;
            case ADDSUB:

				lv = evaluateTree(root->left);
                if( lv == -1)	lv = evaluateTree(root->left->right);
                rv = evaluateTree(root->right);
                if( rv == -1)	rv = evaluateTree(root->right->right);

				if (strcmp(root->lexeme, "+") == 0) {
                    reg[lv] = retval = reg[lv] + reg[rv];
                    regused[rv] = 0;
					regid = lv;
					printf ("ADD r%d r%d\n", lv, rv);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    reg[lv] = retval = reg[lv] - reg[rv];
                    regid = lv;
                    regused[rv] = 0;
					printf ("SUB r%d r%d\n", lv, rv);
				}
				break;
            case MULDIV:
                lv = evaluateTree(root->left);
                if( lv == -1)	lv = evaluateTree(root->left->right);
                rv = evaluateTree(root->right);
                if( rv == -1)	rv = evaluateTree(root->right->right);

                if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)	error(DIVZERO);
                    if(reg[rv]!=0)  reg[lv] = retval = reg[lv] / reg[rv];
                   	regused[rv] = 0;
				    regid = lv;
					printf ("DIV r%d r%d\n", lv, rv);
                }else if (strcmp(root->lexeme, "*") == 0) {
                    reg[lv] = retval = reg[lv] * reg[rv];
                    regid = lv;
					printf ("MUL r%d r%d\n", lv, rv);
                    regused[rv] = 0;
                }
                break;
            case INCDEC:
            	first = 0;
                for (i = 0; i < 8; i++)
                {
                    if (regused[i]==0)
                    {
                        first = 1;
						tableid = getval(root->left->lexeme, 1);
                        int a = i;
                        lv = i;
                        reg[i] = table[tableid].val;
						regused[i] = 1;
						printf("MOV r%d [%d]\n", i, tableid*4);
                    }
                    if(first == 1 && regused[i] == 0){
                        regused[i] = 1;
						reg[i] = 1;
                        int b = i;
                        rv = i;
                        printf ("MOV r%d %d\n", lv, 1);
						break;
					}
                }

                if (strcmp(root->lexeme, "--") == 0)
                    {
                        reg[a] = table[tableid].val = retval = reg[b]+1;
						printf ("SUB r%d r%d\n", rv, lv);
                    }
                else
                    {
                        reg[a] = table[tableid].val = retval = reg[b]-1;
						printf ("ADD r%d r%d\n", rv, lv);
                    }
                regid = rv;
				regused[rv] = 0;
                regused[lv] = 0;
                printf ("MOV [%d] r%d\n", tableid*4, rv);
                break;
            case AND:
                lv = evaluateTree(root->left);
                if( lv == -1)	lv = evaluateTree(root->left->right);
                rv = evaluateTree(root->right);
                if( rv == -1)	rv = evaluateTree(root->right->right);

				reg[lv] = retval= reg[lv] & reg[rv];
                printf("AND r%d r%d\n", lv, rv);
                break;
            case OR:
                lv = evaluateTree(root->left);
                if( lv == -1)	lv = evaluateTree(root->left->right);
                rv = evaluateTree(root->right);
                if( rv == -1)	rv = evaluateTree(root->right->right);

				reg[lv] = retval =reg[lv] | reg[rv];
                printf("OR r%d r%d\n", lv, rv);
                break;
            case XOR:
                lv = evaluateTree(root->left);
                if( lv == -1)	lv = evaluateTree(root->left->right);
                rv = evaluateTree(root->right);
                if( rv == -1)	rv = evaluateTree(root->right->right);

				reg[lv] = retval= reg[lv] ^ reg[rv];
                printf("XOR r%d r%d\n", lv, rv);
                break;
			case ASSIGN:
                rv = evaluateTree(root->right);
                if (rv == -1)	rv = evaluateTree(root->right->right);
                retval = setval(root->left->lexeme, reg[rv]);
                for ( i = 0; i < 64; i++)
                {
                    if (strcmp(root->left->lexeme, table[i].name) == 0)
                        {
                            regused[rv] = 0;
                            table[i].val = reg[rv];
							printf("MOV [%d] r%d\n", i*4, rv);
                        }
                }
                break;
            default:
                retval = 0;
    	}
    }
    return regid;

}
/*int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme,0);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)
                        error(DIVZERO);
                    retval = lv / rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}*/

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
