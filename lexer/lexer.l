%{
#include "parser.tab.h"
%}

%%
"int"           { return INT; }
"print"         { return PRINT; }
[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return ID; }
"="             { return '='; }
";"             { return ';'; }
[+\-*/]         { return yytext[0]; }
[ \t\n]+         ;  /* ignora espaços e quebras */
.               { /* caractere inválido */ }
%%
