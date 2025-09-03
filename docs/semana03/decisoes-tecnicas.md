# Decisões Técnincas Semana 3

Para desenvolver um interpretador de C, analisamos que, para definir um arquivo .c, é necessário realizar a chamada da função main. Contudo, implementar todas as declarações de funções logo no início do projeto seria muito complexo.

Por isso, decidimos adotar inicialmente um pseudo-C, uma linguagem simplificada que se assemelha à sintaxe de Python, mas mantém o uso de ponto e vírgula (;) e delimitadores de escopo com chaves ({ }).

Essa abordagem será utilizada apenas no início do projeto, servindo como uma base para simplificar a implementação. A meta, entretanto, é evoluir gradualmente até que a estrutura final seja compatível com a sintaxe do C real.