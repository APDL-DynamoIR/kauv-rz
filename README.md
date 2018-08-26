
# kauv-rz

This code set accompanies a paper called 
"Hypergraph Type Theory for Specifications-Conformant Code and
Generalized Lambda Calculus".

Be sure to clone the repo to a folder called "cpp" 
(do not let git choose the folder name automaticallly).

To build the code, open the projects in Qt Creator and 
build them in the order listed in "rz-build-order.txt".

Create a folder sibling to "cpp" called "data", and inside 
that a folder called "scripts", and inside that a folder called 
"rz", and inside that a file called "t1.rz" (unless you want to 
edit the paths coded into the "main.cpp" files).

Run the compiler with rz-graph-dynamo-runtime-console or 
one of the other executables.  The t1.rz file can have 
sample code like: 
```
,fnd ::: Fn_Doc*;
fnd \== default; 

,kenv ::: KCM_Env*;
kenv \= (envv "KCM_Env*");

fnd -> init kenv;

,test-fn ::: .(int)  $-> extern;

fnd -> read  "test-fn";

```

Other examples of sample code are in the "samp" folder.  Multiple 
samples can be executed in sequence with the project/executable called "rz-multi-console".

*UDPIPE*

Note: the "udpipe" project includes code from UDPipe, a Natural Language Processing framework. 
This code has its own copyright and license, but is copied here for convenience.  

Please bear in mind the provenance of code in the UDPipe project folder if reusing.  

This distribution has only a minimal working example of a script interfacing 
with UDPipe code; please ask about more complex examples. 

*ECL*

This code requires ECL (Embeddable Common Lisp) and a C++ ECL wrapper called 
cl-cxx.  Fortunately, both of these are easy to find and build: check 
https://common-lisp.net/project/ecl/ and https://github.com/juanjosegarciaripoll/cl-cxx.

You may need to edit the find-ecl-sexpr.pri file to point to 
the correct folder(s) where ECL includes and libs are located.

*COMMENTS*

This code set will be expanded in conjunction with other 
data sets published in the same volume as the 
"Hypergraphs" chapter.  Future versions of this repo 
will hold longer "Interface Definition Language" 
code describing code libraries built to manage data 
for these other data sets.  Please check back!


