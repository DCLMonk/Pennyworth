#!/bin/sh
# script to copy the headers to all the source files and header files

shopt -s globstar nullglob extglob
for f in **/*.@(cpp|h|java|c); do
    if (grep Copyright $f);then 
        echo "No need to copy the License Header to $f"
    else
        cat header.c $f > $f.new
        mv $f.new $f
        echo "License Header copied to $f"
    fi 
done 

