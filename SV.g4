grammar SV;

module          : module_header module_body ENDMODULE;

module_header   : MODULE name=SYMNAME LBRACK ports? RBRACK SEMICOLON;

ports           : (port COMMA)* port;

port            : INPUT WIRE name=SYMNAME # inwire
                | OUTPUT LOGIC name=SYMNAME # outreg
                ;

module_body     : (module_block)*;

module_block    : sync_proc # proc
                | LOGIC name=SYMNAME SEMICOLON # reg_decl
                | WIRE name=SYMNAME SEMICOLON # wire_decl
                ;

sync_proc       : ALWAYS AT signal_trans BEGIN block_body* END;

signal_trans    : LBRACK POSEDGE name=SYMNAME RBRACK;

block_body      : IF LBRACK expr RBRACK BEGIN (block_body)* END # if
                | statement # stmt;

statement       : block_ops SEMICOLON;

block_ops       : left=SYMNAME BLOCK_ASS right=expr;

// expr:   '(' expr ')' # brack  
    // |   left=expr '/' right=expr # div
    // |   left=expr '*' right=expr # mul
    // |   left=expr '+' right=expr # add
    // |   left=expr '-' right=expr # sub
expr            :   TILDA expr # bitwise_not
                |   BANG expr # not
                |   name=SYMNAME # var
                |   INT # lit
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