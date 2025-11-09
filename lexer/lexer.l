%{
#include "parser.tab.h" 
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
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"=="                    { return EQ; }
"!="                    { return NEQ; }
"<="                    { return LEQ; }
">="                    { return GEQ; }
"<"                     { return LT; }
">"                     { return GT; }
[0-9]+\.[0-9]+          { yylval.fval = atof(yytext); return FLOAT_NUM; }
[0-9]+                  { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return ID; }
"="                     { return '='; }
";"                     { return ';'; }
"("                     { return '('; }
")"                     { return ')'; }
"["                     { return '['; }
"]"                     { return ']'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
[+\-*/]                 { return yytext[0]; }
[ \t\n\r]+              ;
.                       { printf("Erro lexico: caractere inválido '%s'\n", yytext); }
%%
