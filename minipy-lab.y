%{
   /* definition */
   #include "mainhead.hpp" 
   #include "OP_miniPY.hpp" 
   //#include "lex.yy.cc"
   extern "C"{
      extern int yylex(void);
      void yyerror(char *s);
     // int yywrap(void);
   }
   #define YYSTYPE VarNode

%}

%token ID,INT,REAL,STRING_LITERAL

%%
Start : prompt Lines
      ;
Lines : Lines  stat '\n' prompt
      | Lines  '\n' prompt
      | 
      | error '\n' {yyerrok;}
      ;
prompt : {cout << "miniPy> ";}
       ;
stat  : assignExpr
      ;
assignExpr:
        atom_expr '=' assignExpr{ $$= Call_Assign($1,$3);}
      | add_expr {out_assignExpr($1);}
      ;
number : INT
       | REAL
       ;
factor : '+' factor
	{
		$$=$2;
	}
       | '-' factor
	{
		$$=$2;
		if ($2._type == INT_type)  $$._INT= -$2._INT;
		else if ($2._type == REAL_type) $$._REAL= -$2._REAL;
	}
       | atom_expr
       ; 
atom  : ID {$$= search_table($1);}
      | STRING_LITERAL 
      | List 
      | number 
      ;
slice_op :  /*  empty production */{$$._type=INT_type;$$._INT=1;}
        | ':' add_expr {$$=$2;}
        ;
sub_expr:  /*  empty production */
        | add_expr
        ;        
atom_expr : atom 
        | atom_expr  '[' sub_expr  ':' sub_expr  slice_op ']' 
	{	$$ = LIST_CUT($1,$3,$5,$6);
	}
        | atom_expr  '[' add_expr ']' {$$=LIST_SUB($1,$3);}
        | atom_expr  '.' ID 
		{
			if ($1._type == LIST_type && $3._type== FUNC_APPEND)
			{
				$$=$1;
				//cout << $1._iteration << endl;
				$$._ID=$1._ID;
				$$._type=FUNC_APPEND;
			}
			else 
			{
				$$=EmptyVarNode();
				cout<< "invalid append for this type";
			}
		}
        | atom_expr  '(' arglist opt_comma ')'
		{
		if ($1._type == FUNC_LEN) $$=LEN($3);
		else if ($1._type == FUNC_PRINT) $$=PRINT($3);
		else if ($1._type == FUNC_RANGE) $$=RANGE($3);
		else if ($1._type == FUNC_APPEND) $$=APPEND($1,$3);
		else if ($1._type == FUNC_TUPLE) $$=TUPLE($3);
		else if ($1._type == FUNC_LIST) $$=LIST($3);

		}
        | atom_expr  '('  ')'
		{	
			if ($1._type == FUNC_QUIT) return 0;
		}
        ;
arglist : add_expr{ $$=CreateArgList($1);}
        | arglist ',' add_expr {$$=AddArgListMember($1,$3);}
        ;
        ;      
List  : '[' ']'{ $$=Call_CreateEmptyList();}
      | '[' List_items opt_comma ']' {$$=$2;}
      ;
opt_comma : /*  empty production */
          | ','
          ;
List_items  
      : add_expr{ $$=CreateList($1);}
      | List_items ',' add_expr {$$=AddListMember($1,$3);}
      ;
add_expr : add_expr '+' mul_expr
		{
			$$=add($1,$3); 
		}
	      |  add_expr '-' mul_expr
		{
			$$=sub($1,$3);
		}
	    |  mul_expr 
        ;
mul_expr : mul_expr '*' factor
		{
			$$=mul($1,$3);
		}
        |  mul_expr '/' factor
		{
			$$=div($1,$3);
	    	}
		|  mul_expr '%' factor
        	{
			$$= mod ($1,$3);
		}
		|  factor
        ;


%%
void yyerror(char *s)
{
   cout << s << endl<<"miniPy> "; 
}

int main()
{
   return yyparse();
}
