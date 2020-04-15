%{
  #define YYSTYPE VarNode
  #include "mainhead.hpp"
  #include "y.tab.hh"
  extern VarNode yylval;
  extern "C"{
    int yywrap(void);
    int yylex(void);
  }


VarNode gen_int(int val){
	VarNode terminal;
	terminal._INT = val;
	terminal._ID_defined=0;
	terminal._type = INT_type;
	terminal._TUPLE = 0;
	terminal._iteration =0;
	return terminal;
}

VarNode gen_real(double val){
	VarNode terminal;
	terminal._REAL = val;
	terminal._ID_defined=0;
	terminal._type = REAL_type;
	terminal._TUPLE = 0;
	terminal._iteration =0;
	return terminal;
}

VarNode gen_id(string val){
	VarNode terminal;
	terminal._ID = val;
	terminal._ID_defined = 1;
	terminal._TUPLE = 0;
	terminal._iteration =0;
	if(val == "quit") terminal._type = FUNC_QUIT;
	else if(val == "range") terminal._type = FUNC_RANGE;
	else if(val == "append") terminal._type = FUNC_APPEND;
	else if(val == "print") terminal._type = FUNC_PRINT;
	else if(val == "list") terminal._type = FUNC_LIST;
	else if(val == "len") terminal._type = FUNC_LEN;
	else if(val == "tuple") terminal._type = FUNC_TUPLE;
	else {	terminal._type=ID_type; terminal._ID_defined = 0;}
	return terminal;
}

VarNode gen_string(string val){
	VarNode terminal;
	terminal._ID_defined=0;
	terminal._STRING = val;
	terminal._STRING = terminal._STRING.substr(1, terminal._STRING.length() - 1);
	//cout<< terminal._STRING <<endl;
	terminal._STRING = terminal._STRING.substr(0, terminal._STRING.length() - 1);
	//cout<< terminal._STRING <<endl;
	terminal._type = STRING_type;
	terminal._TUPLE = 0;
	terminal._iteration =0;
	return terminal;
}

/*  any C declaration  */
%}

letter    [a-zA-Z]

digit     [0-9]

number   {digit}+

id       {letter}({letter}|{digit})*

real     {number}"."{number}?|{number}?"."{number}

%%
[ \t]+      {/*do nothing , just skip */}
{number}    { 
				        yylval=gen_int(atoi(yytext));
                return INT;
            }
{real}      {
				        yylval=gen_real(atof(yytext));
           	    return REAL;
            }
{id}        {
				        yylval=gen_id(yytext);
            	  return ID; 
            }
\"(\\.|[^\\"])*\"	{
			yylval = gen_string(yytext);
             return(STRING_LITERAL); 
                  }
.|\n        { return yytext[0];}
%%

int yywrap()
{ return 1; }  
