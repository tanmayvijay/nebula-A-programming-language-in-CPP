# nebula-A programming language in CPP
 This is a programming language I created using C++.

**I am creating this language to sharpen my core Computer Science understanding. It can also be considered as my take on the subject of "Compiler Design", which I have for this semester.
At this point, when I start, I have no idea how compilers or interpreters work. But, let's just hit it.**
<b>
 
 ### Edit-12: For loops *run()* implemented:
 * Changed ForBlock structure and constructor to maintain conditional expression, loop variable update statement
 * Implemented run() method, which checks for condition being true --> executes all atatements in the block --> updates the loop variable and repeats.
 
 ### Edit-11: Expressions evaluate correctly:
 * *evaluate()* method implemented for all sub types of ExpressionAST.
 * ExpressionSatatement, VariableDeclarationStatement, VariableAssignmentStatement, OutputStatament and IfBlock *run()* method implemented.
 * *Simple programs can be executed now!!* Yay! *:)* 🎉🤩
 * ForBlock, WhileBlock, InputStatement and Function Calls implementation to go.
 
 ### Edit-10: Semantic Analyzer Implemented:
* Each program element has its own semanticc checker.
* Type checking.
* Type checking rules: integer and decimal can be used with any operator
* strings are supported by +, == and !=
* booleans are supported by and, or, not, == and !=.
 
 ### Edit-9: Implemented Error Reporting in various parsing elements.
* Still has scope of improvement in error reporting
 
 
 ### Edit-8: Function calling parser is now implemented. This is a big one!
* Function calls and Expressions can be recursively nested. Yay!.
* Like this: decimal some_var = addiv( x+y/var, addi(x, addi(var, n)) )
* *Still need a better regular expression for recognizing correct expression, but this is a small one*.

 
 
 ### Edit-7: Function Definition parser implementaton done:
Each block stores its own functions in the symbol table itself. In case of name-clash between functions (or Symbols in general), one closest in the nesting is used.
 
 
 ### Edit-6: For and While loops parser implemented
 
 
 ### Edit-5: Implemented if, if-else, if-else_if, if-else_if-else
 
 
 ### Edit-4: Changed entire expression and program_element architecture to support Symbol Table:
* Each block has its own symbol table.
* Symbol Table is now updated everytime a Variable Declaration Statement or Variable Assignment Statement is encountered.
* Variables are searched in the most closely nested block.
 
 
 ### Edit-3: Added all types of expressions:
* Arithmetic
* Relational
* Logical

 
 ### Edit-2: Tested Partially comepleted Parser for 3 types of program elements:
* Simple Expression Statements
* Variable Declaration Statements
* Variable Assignment Statements


### Edit-1: Done with the phase-1 : Tokenizer (Lexical Analyzer).
