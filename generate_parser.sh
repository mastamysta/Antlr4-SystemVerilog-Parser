#!/bin/sh

# Grab the antlr4 generator if we don't already have it.
if [ ! -f antlr-4.11.1-complete.jar ]; then
    curl --output antlr-4.11.1-complete.jar https://www.antlr.org/download/antlr-4.11.1-complete.jar
fi

# Requires a Java install, this is left to the user.
java -jar ./antlr-4.11.1-complete.jar -Dlanguage=Cpp SV.g4 -o antlr_generated/

return 0
