%{
#include "parser.tab.h" 
%}

%x COMMENT

%%
"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>.|\n           { /* Dentro do comentário, ignora tudo */ }
"//".*                  { /* Comentário de linha única: ignora o resto da linha */ }
[ \t\n]+                ; 
"int"                   { return INT; }
"print"                 { return PRINT; }
[0-9]+                  { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return ID; }
"="                     { return '='; }
";"                     { return ';'; }
[+\-*/]                 { return yytext[0]; }
.                       { printf("Erro léxico: caractere inválido '%s'\n", yytext); }
%%
