/* Grep line.  */


%{
#include "automata.h"
#include "define.h"
#include <stdio.h>
%}

%token ALFANUM


%% /* Grammar rules and actions follow.  */

input: expression { automata = $1; };

expression:  data operators rest {$$ = automata_handle_expression($1, $2, $3); }
;

data: parenthesis  {}
    | final {printf("data-final\n");}
;

rest: {$$ = build_empty_automata();}
    | binary expression {$$ = concat_automatas($1, $2);}
;

operators: {$$ = build_empty_automata();}
    | unary operators {$$ = automata_apply_operator($2 , $1);}
;

parenthesis: '('expression')' {$$ = sinthesize_automata($1);}
;

final: '.' {$$ = build_any_alfanum_automata()}
    | ALFANUM {$$ = $1;}
;

unary: '?' {$$ = build_onezero_automata();}
    | '+' {$$ = build_oneplus_automata();}
    | '*' {$$ = build_zeroplus_automata();}
;

binary: {$$ build_empty_automata();}
    | '|' {$$ = build_or_automata();}
;


%%
     

