grammar SV;

module          : module_header module_body ENDMODULE;

module_header   : MODULE name=SYMNAME LBRACK ports? RBRACK SEMICOLON;

ports           : (port COMMA)* port;

port            : INPUT WIRE name=SYMNAME
                | OUTPUT LOGIC name=SYMNAME
                ;

module_body     : module_block*;

module_block    : sync_proc
                | LOGIC name=SYMNAME
                | WIRE name=SYMNAME
                ;

sync_proc       : ALWAYS AT signal_trans BEGIN block_body END;

signal_trans    : LBRACK POSEDGE name=SYMNAME RBRACK;

block_body      : (if_block | statement)*;

if_block        : IF LBRACK expr RBRACK BEGIN (statement)* END;

statement       : block_ops SEMICOLON;

block_ops       : left=SYMNAME BLOCK_ASS right=expr;

expr:   '(' expr ')' # brack  
    |   left=expr '/' right=expr # div
    |   left=expr '*' right=expr # mul
    |   left=expr '+' right=expr # add
    |   left=expr '-' right=expr # sub
    |   TILDA expr # bitwise_not
    |   BANG expr # not
    |   INT # lit
    |   name=SYMNAME # var
    ;

WS: [ \t\r\n]+ -> skip;
MODULE      : 'module';
ENDMODULE   : 'endmodule';
ALWAYS      : 'always';
BEGIN       : 'begin';
END         : 'end';
POSEDGE     : 'posedge';
LOGIC       : 'logic';
WIRE        : 'wire';
IF          : 'if';
INPUT       : 'input';
OUTPUT      : 'output';
NEWLINE     : [\r\n]+ ;
INT         : [0-9]+ ;
LBRACE      : '{';
RBRACE      : '}';
LBRACK      : '(';
RBRACK      : ')';
BLOCK_ASS   : '<=';
EQUAL       : '=';
AT          : '@';
COMMA       : ',';
TILDA       : '~';
BANG        : '!';
SEMICOLON   : ';';
SYMNAME     : [a-z]+;