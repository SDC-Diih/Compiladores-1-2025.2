%{
#include "parser.tab.h" 
#include <stdlib.h>
#include <string.h>
%}

%x COMMENT

%%

"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>.|\n           { /* Dentro do comentário, ignora tudo */ }

"//".*                  { /* Comentário de linha única: ignora o resto da linha */ }

"int"                   { return INT; }
"float"                 { return FLOAT; }
"print"                 { return PRINT; }
"return"                { return RETURN; }

/* Reconhece números de ponto flutuante (precisa vir antes do [0-9]+ ) */
[0-9]+"."[0-9]+         { yylval.fval = atof(yytext); return NUMBER_FLOAT; }

/* Números inteiros */
[0-9]+                  { yylval.ival = atoi(yytext); return NUMBER; }

/* Identificadores */
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return ID; }

/* Símbolos */
"="                     { return '='; }
";"                     { return ';'; }
"("                     { return '('; }
")"                     { return ')'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
[+\-*/]                 { return yytext[0]; }

/* Espaços em branco */
[ \t\n\r]+              ;

/* Caracteres inválidos */
.                       { printf("Erro lexico: caractere inválido '%s'\n", yytext); }

%%
