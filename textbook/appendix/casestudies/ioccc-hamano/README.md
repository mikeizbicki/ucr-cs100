#Guide to hamano.c

``` c
                          #define  \
                        D(s)"<<"#s">>"
                      #define  q(s)p(#s)
                     #define S " endobj "
                    #define Y "endstream"S
                    #include     <stdio.h>
                    #define  o(s) b[s]=_;\
                     p("%u    0  obj",s);
#define E for         (c=d;c  < 123;c++)
  #define DANCE         "trailer   "D\
    (/Root 3 0            R /Size %d)            "\nstartxref %u %%%%EOF\n*/"
      #define              p(s, ...)             _+=printf(s,  ##__VA_ARGS__)
       #define C         "<</Type/Page         /Parent %d %d R /Resources <<\
        /ProcSet[       /PDF/Text]/Font       <</U"D(/Subtype/Type1/BaseFont\
          /Courier) "  /T<</Subtype/Type3   /FontBBox[0 0 10 10]/FontMatrix[\
           %f 0 0 %f 0 0]/FirstChar %d/LastChar %d/Encoding<</Differences[%d"
            typedef int N;typedef char*Nyan;typedef char A;N a,b[64],d=65,_,v
              [32]={84,0,64,282,90,74,330,85,93,173,167,176,80,208,81,13,7,87
                ,160,346,32,128,170,218,16,26}; Nyan w[]={"+*-(,&-&","+*,&-&"
                  ,"+*.&/&","+*/*/+","+*())'('"  ,"+**&)&","+*(&'&","+*'*'+",
                    "","+,./","+,-,./","+--,+*"  ,"","+,(/","+,),(/","+-),+*"
                     ,"10 0 d0 ","8 7 2 2 re "   ,"+*+.'`'@'mi +/+/(mi"};Nyan
                       nyan(Nyan _,N y,A n){
                        N g=v[~-y%32];Nyan
                         s=w[g>>n&3|n*2];
                         for(a=0;*_=*s++;
                         a++,_++,*_++=32)
                         {*_+=*_-32?10:0;
                         if(a%2&&*_/16==3
                         ){if(g>>8)*_=105-*_;
                        _++;*_++=32;*_=~-a&&a-13
                        ?108:109;}}return n?n-9?nyan
                       (_,y,n-2):_:nyan(_+=~y&' '?sprintf
                      (_,17[w]):0,y,9);}N main(N c){A e[256];
                     p("/*%%PDF-1.3%%*/")-2;q(#include<stdio.h>\n);
                    q(#define o *_++&& *_-41\n#define);p(" endstream ");q
                   (main(){for(;*_++;      *_-40?:putchar(o?*_:o?10:41));\n)
                  ;q(#define  endobj          return 0;}\n);q(typedef int ET;/)
                 ;q(*);o(1)*b=~(p(D                 (/Length 2 0 R)"stream\n"))
                ;for(p("BT 12 818"                    " Td/%c 12 Tf 12 TL%%%c/"
               "static char*_=\""                       " \\\n",7[v],*v/2);c=
              getchar(),~c;c-10?                         p("/%c 12 Tf(\\%o)"
             "Tj",v[~-c%' '<25[                         v]&&!~-(~-c/'@')?0
            :7],c):(p("()'")))                         ;p("%%\";\nET ");*
           b-=~_;p(Y"/*");E{a                         =nyan(e+sprintf(e,
          16[w]),c,6)-e;o(c-                         59)p(D(/Length %d)
         "stream\n%s"Y,a,e)                         ;}o(2)p(" %u"S,*b);
        o(3)p(D(/Pages 4 0                         R)S);o(4)p(D(/Count
       1/MediaBox[0 0 595                         842]/Kids[5 0 R])S)
      ;o(5)p(C,4,0,6e-2,                         6e-2f,d,122,d);E p(
     "/%c",~-c/6+~14?c:                         d);q(]>>/CharProcs<<)
    ;E if(~-c/6+~14)p(                           "/%c %d 0 R",c,c+~58);
   for(q(>>/Widths[),                             c=59;--c;p(" 10"));a=p
  ("]>>>>>>/Contents 1                              0 R>>"S);for(p("xref\
 0 %d ",--d);c<d;p("%010u\
 %05d n  ",*(c+++b),NULL));
  return!(p(DANCE,d,a));}
```



##1. What is hamano.c?
Hamano.c is a program written for the 21st International Obfuscated C Code Contest (2012) by Tsukasa Hamano. It is the winner of most elementary use of C - silver award.
Its purpose is to output a pdf file containing dancing characters based upon input text. This output pdf file can also be compiled and the new program based on your text
input will output the original text input given to hamano. Hamano.c is also able to obfuscate input c code.   

This guide will only focus on the classical methods of obfuscation found within hamano.c and generation of the dancing man pdf file.


Official hints to hamano can be found here: [**www.ioccc.org/2012/hamano/hint.html**](http://www.ioccc.org/2012/hamano/hint.html)

Download the winning files here: [**www.ioccc.org/years.html#2012_hamano**](http://www.ioccc.org/years.html#2012_hamano)



##2. Helpful things to know

This section is intended to provide a starting point to begin deobfuscation and convey prerequisite information.


####Operation of hamano.c

Usage of hamano is as follows: `./hamano < textfile > ouput.pdf`

From this we know:

_stdin contains our input text_

_stdout is redirected to output.pdf_


####PDF file structure

Become familiar with the basic structure of an unpolluted pdf file, comparing and contrasting with the hamano output pdf. 
This will be used to remove code not useful to pdf creation and as a guide to direct deobfuscation.


_Note:_ the file below has been modified to be of reduced size, it is the output of hamano, and anything which is not pdf relevant has been omitted

```
**HEADER**
%PDF-1.3

**OBJECT**
1    0  obj<</Length 2 0 R>>stream
BT 12 818 Td/U 12 Tf 12 TL
/T 12 Tf(\141)Tj/T ET 
endstream endobj   

**OBJECT**
6    0  obj<</Length 131>>stream
10 0 d0 5 6 m 2 9 l 5 6 m 8 9 l 5 
endstream endobj  

**OBJECT**
4    0  obj`<`<
  /Count 1
  /MediaBox[0 0 595 842]
  /Kids[5 0 R]
>> endobj 

**CROSS REFERENCE**
xref 
  0 64 
  0000000193 00000 n  
  0000000009 00000 n  
  0000004864 00000 n  

**TRAILER**
trailer <<
  /Root 3 0 R 
  /Size 64  
>> 
startxref 11413 
%%EOF
```

**Header**: designates file as PDF

**Object**: data stored here

**Cross Reference**: locations pointing to each object, counted in bytes

**Trailer**: holds the starting location of the cross reference table and designates end of file 


####First steps

Hamano.c will need to be reformatted using proper spacing with special attention given to `\` which marks the continuation of the current line onto the next.
This will allow proper examination of the code.

Proper spacing added:

```c
#define D(s) "<<"#s">>"
#define q(s) p(#s)
#define S " endobj "
#define Y "endstream"S
#include <stdio.h>
#define o(s) b[s]=_; p("%u    0  obj",s);
#define E for(c=d;c  < 123;c++)
#define DANCE "trailer   " D(/Root 3 0            R /Size %d) "\nstartxref %u %%%%EOF\n*/"
#define p(s, ...)_+=printf(s,  ##__VA_ARGS__)
#define C         "<</Type/Page         /Parent %d %d R /Resources <<\
/ProcSet[       /PDF/Text]/Font       <</U"D(/Subtype/Type1/BaseFont\
/Courier) "  /T<</Subtype/Type3   /FontBBox[0 0 10 10]/FontMatrix[\
%f 0 0 %f 0 0]/FirstChar %d/LastChar %d/Encoding<</Differences[%d"

typedef int N;
typedef char*Nyan;
typedef char A;

N a,b[64],d=65,_,v[32]={84,0,64,282,90,74,330,85,93,173,167,176,80,208,81,13,7,87,160,346,32,128,170,218,16,26}; 

Nyan w[]={"+*-(,&-&","+*,&-&","+*.&/&","+*/*/+","+*())'('"  ,"+**&)&","+*(&'&","+*'*'+","","+,./","+,-,./","+--,+*"  ,"","+,(/","+,),(/","+-),+*","10 0 d0 ","8 7 2 2 re "   ,"+*+.'`'@'mi +/+/(mi"};

Nyan nyan(Nyan _,N y,A n){
    N g=v[~-y%32];
    Nyan s=w[g>>n&3|n*2];
    
    for(a=0;*_=*s++;a++,_++,*_++=32){
        *_+=*_-32?10:0;
        
        if(a%2&&*_/16==3){
            
            if(g>>8)
                *_=105-*_;
                
            _++;
            *_++=32;
            
            *_=~-a&&a-13?108:109;
        }
    }
    
    return n?n-9?nyan(_,y,n-2):_:nyan(_+=~y&' '?sprintf(_,17[w]):0,y,9);
}

N main(N c){
    A e[256];
    p("/*%%PDF-1.3%%*/")-2;
    q(#include<stdio.h>\n);
    q(#define o *_++&& *_-41\n#define);
    p(" endstream ");
    
    q(main(){for(;*_++;*_-40?:putchar(o?*_:o?10:41));\n);
    q(#define  endobj          return 0;}\n);
    q(typedef int ET;/);
    q(*);
    o(1)
    *b=~(p(D(/Length 2 0 R)"stream\n"));
    
    for(p("BT 12 818"                    " Td/%c 12 Tf 12 TL%%%c/"
        "static char*_=\""                       " \\\n",7[v],*v/2);
        c=getchar(),~c;c-10?p("/%c 12 Tf(\\%o)""Tj",v[~-c%' '<25[v]&&!~-(~-c/'@')?0
        :7],c):(p("()'")));
    
    p("%%\";\nET ");
    *b-=~_;
    p(Y"/*");
    
    E{
        a=nyan(e+sprintf(e,16[w]),c,6)-e;
        o(c-59)
        p(D(/Length %d)"stream\n%s"Y,a,e);
    }
    
    o(2)
    p(" %u"S,*b);
    
    o(3)
    p(D(/Pages 4 0R)S);
    o(4)
    p(D(/Count1/MediaBox[0 0 595 842]/Kids[5 0 R])S);
    o(5)
    p(C,4,0,6e-2,6e-2f,d,122,d);
    
    E p("/%c",~-c/6+~14?c:d);
    q(]>>/CharProcs<<);

    E if(~-c/6+~14)
        p("/%c %d 0 R",c,c+~58);

    for(q(>>/Widths[),c=59;--c;p(" 10"));
        
    a=p("]>>>>>>/Contents 1                              0 R>>"S);

    for(p("xref 0 %d ",--d);c<d;p("%010u %05d n  ",*(c+++b),NULL));
    
    return!(p(DANCE,d,a));
}
```


##3. Deobfuscation
This section will step through the code in logical blocks and explain the obfuscation used. Items will also be properly named.

####Section 1: #define

``` c
#define D(s) "<<"#s">>" //converts input to string and adds << >> tags
#define q(s) p(#s) //converts input of q to string and send it to p
#define S " endobj "
#define Y "endstream"S //combines "endstream" and " endobj "
#include <stdio.h>

#define o(s) b[s]=_; p("%u    0  obj",s);
//create beginning object tags in pdf, %u places arg s into the string
//every time this is called reference table data is saved

#define E for(c=d;c  < 123;c++) //copy into code, will be REMOVED
#define DANCE "trailer   " D(/Root 3 0            R /Size %d) "\nstartxref %u %%%%EOF\n*/" //trailer of pdf file

#define p(s, ...)_+=printf(s,  ##__VA_ARGS__)
// ... and __VA_ARGS__ is used to specify undetermined amount of arguments to print
// ## in __VA_ARGS__ allows printf to function if there is only one argument

//entire contents is sent to p later in code which populations %d and %f, this holds the font info
#define C         "<</Type/Page         /Parent %d %d R /Resources <<\
/ProcSet[       /PDF/Text]/Font       <</U"D(/Subtype/Type1/BaseFont\
/Courier) "  /T<</Subtype/Type3   /FontBBox[0 0 10 10]/FontMatrix[\
%f 0 0 %f 0 0]/FirstChar %d/LastChar %d/Encoding<</Differences[%d"
```

**Obfuscation used:**

1.Obscure naming

2.`#x` - converts x to string in #define, more info can be found here: [**en.cppreference.com/w/cpp/preprocessor/replace**](http://en.cppreference.com/w/cpp/preprocessor/replace)

3.Using PRNTTOPDF for inserting arguments into strings, see link in #2 for more info.

**After changes:**

``` c
#define STRTAGS(s) "<<" #s ">>"
#define TOSTR(s) PRNTTOPDF(#s) 
#define ENDOBJ " endobj "
#define ENDSTRM "endstream" ENDOBJ 
#include <stdio.h>
#define PRNTPDFOBJ(s) refData[s] = fileSize; PRNTTOPDF("%u    0  obj",s); 

#define TRAILER "trailer   " STRTAGS(/Root 3 0 R /Size %d) "\nstartxref %u %%%%EOF\n" 

#define PRNTTOPDF(s, ...)  fileSize += printf(s,  ##__VA_ARGS__) 

#define FONTINF "<</Type/Page         /Parent %d %d R /Resources <<\
        /ProcSet[       /PDF/Text]/Font       <</U" STRTAGS(/Subtype/Type1/BaseFont\
          /Courier) "  /T<</Subtype/Type3   /FontBBox[0 0 10 10]/FontMatrix[\
           %f 0 0 %f 0 0]/FirstChar %d/LastChar %d/Encoding<</Differences[%d"
```

####Section 2: Variable declarations

``` c
//these obfuscate the data types, they can be used interchangeably with the type they are defined as
//will be REMOVED
typedef int N;
typedef char*Nyan;
typedef char A;

//d = 65 replaced in code
N a,b[64],d=65,_,v[32]={84,0,64,282,90,74,330,85,93,173,167,176,80,208,81,13,7,87,160,346,32,128,170,218,16,26}; 

//each of these element represents a memory location
Nyan w[]={"+*-(,&-&","+*,&-&","+*.&/&","+*/*/+","+*())'('"  ,"+**&)&","+*(&'&","+*'*'+","","+,./","+,-,./","+--,+*"  ,"","+,(/","+,),(/","+-),+*","10 0 d0 ","8 7 2 2 re "   ,"+*+.'`'@'mi +/+/(mi"};
```
**Obfuscation used:**

1. Obscure naming

2. Typedef to hide variable types

3. Unnecessary variable creation

4. Use of memory addresses stored in an array

**After changes:**

``` c
int filePos,refData[64],fileSize,v[32]={84,0,64,282,90,74,330,85,93,173,167,176,80,208,81,13,7,87,160,346,32,128,170,218,16,26}; 
            
char* w[]={"+*-(,&-&","+*,&-&","+*.&/&","+*/*/+","+*())'('","+**&)&","+*(&'&","+*'*'+","","+,./","+,-,./","+--,+*"  ,"","+,(/","+,),(/","+-),+*","10 0 d0 ","8 7 2 2 re ","+*+.'`'@'mi +/+/(mi"};
```

####Section 3: Function nyan

``` c 
Nyan nyan(Nyan _,N y,A n){ //pass in a memory address past the beginning of bodyData(type char[256]) into bodyAddr(type char*, variable _)
    
    N g=v[~-y%32]; 
    //typedef obfuscation
    //picks an int g from int array v based on the current body object being created
    //~-x equates to x-1, this is a bitwise negation and unary minus
    
    Nyan s=w[g>>n&3|n*2];
    //pick a mem location from w based on int g and char n
    // g >> n is a right bitshift of g by n shifts
    // & is bitwise and
    // | is bitwise or
    // n is of type char, characters decimal value is being used, value can be found in ASCII charts
    
    for(a=0;*_=*s++;a++,_++,*_++=32){ //many unnecessary items placed in increment section to obfuscate, intentionally filled condition section
        *_+=*_-32?10:0;//ternary operator, if condition before ? is true expression before : will run, if false expression after : will run
        
        if(a%2&&*_/16==3){
            
            if(g>>8)
                *_=105-*_;
                
            _++;
            *_++=32;
            
            *_=~-a&&a-13?108:109;
        }
    }
    
    return n?n-9?nyan(_,y,n-2):_:nyan(_+=~y&' '?sprintf(_,17[w]):0,y,9);
    //equivalent of nested if statements
}
```
**Obfuscation used:**

1. Extensive use of operators: [**?**](http://en.wikipedia.org/wiki/%3F:),[**~**](http://en.wikipedia.org/wiki/Bitwise_operation#NOT),
[**&**](http://en.wikipedia.org/wiki/Bitwise_operation#AND),[**|**](http://en.wikipedia.org/wiki/Bitwise_operation#OR),
[**-**](http://en.wikipedia.org/wiki/Additive_inverse),[**>>**](http://en.wikipedia.org/wiki/Bitwise_operation#Bit_shifts)

2. Typedef to hide variable types

3. For loop could be simplified

4. Obscure naming

5. Characters used as decimal values, use ASCII chart for conversion purposes: [**en.wikipedia.org/wiki/ASCII**](http://en.wikipedia.org/wiki/ASCII)

**After changes:**

``` c
char* processBody(char* bodyAddr, int c, char n){ 
		    int g = v[(c-1)%32]; 

		    char* memAddr = w[(g>>n)&3|n*2];

		    filePos = 0;
		    
		    for(; *bodyAddr = *memAddr; memAddr++){
		      
			*bodyAddr += (*bodyAddr - 32) ? 10 : 0;
			
			if( filePos%2 && *bodyAddr/16 == 3 ){ 
			    
			    if(g >> 8){
				*bodyAddr = 105 - *bodyAddr;
			    }

			    bodyAddr++;
			    *bodyAddr = 32;
			    *bodyAddr++;

			    if(filePos-1 && filePos-13){
				*bodyAddr = 108;
			    }
			    else{
				*bodyAddr = 109;
			    }
			}
		    
			filePos++;
			bodyAddr++;
			*bodyAddr = 32;
			bodyAddr++;
		    
		    }

		    if(n){
			if(n-9){
			    return processBody(bodyAddr,c,n-2);
			}
			else{
			    return bodyAddr;
			}
		    }
		    else{
			return processBody(bodyAddr += ~c & 32 ? sprintf(bodyAddr,17[w]):0, c, 9);
		    }
	    }
```
####Section 4: main

``` c
N main(N c){ //int c unneeded here, receives nothing, can be moved in main
    
    A e[256]; //bodyData
    
    p("/*%%PDF-1.3%%*/")-2; //has extra non pdf content
    
    //many of these below are useful to other functions of hamano, but have been removed
    q(#include<stdio.h>\n); //non pdf, will be REMOVED
    q(#define o *_++&& *_-41\n#define);//non pdf, will be REMOVED
    p(" endstream ");//non pdf, will be REMOVED
    
    q(main(){for(;*_++;*_-40?:putchar(o?*_:o?10:41));\n);//non pdf, will be REMOVED
    q(#define  endobj          return 0;}\n);//non pdf, will be REMOVED
    q(typedef int ET;/);//non pdf, will be REMOVED
    q(*);//non pdf, will be REMOVED
    
    o(1) //print object begin tag to pdf
    *b=~(p(D(/Length 2 0 R)"stream\n"));
    
    for(p("BT 12 818"                    " Td/%c 12 Tf 12 TL%%%c/"
        "static char*_=\""                       " \\\n",7[v],*v/2);
        c=getchar(),~c;c-10?p("/%c 12 Tf(\\%o)""Tj",v[~-c%' '<25[v]&&!~-(~-c/'@')?0
        :7],c):(p("()'"))); 
    //for loop contains non pdf info
    //grabs info from stdin, and writes to pdf file
    //~-x equates to x-1
    //array element calling: 25[v] == v[25]
    
    p("%%\";\nET "); //contains non pdf info
    *b-=~_; //holds the filesize
    p(Y"/*"); //print endstream to pdf
    
    
    //prints main body data
    E{
        a=nyan(e+sprintf(e,16[w]),c,6)-e; 
	//passes memory location past the beginning of bodyData(variable e) since data was copied to it, nyan will populate bodyData
        
	o(c-59)
        p(D(/Length %d)"stream\n%s"Y,a,e);// print bodyData to pdf
    }
    
    o(2)//print object begin tag to pdf
    p(" %u"S,*b);//print to pdf
    
    o(3)//print object begin tag to pdf
    p(D(/Pages 4 0R)S);//print to pdf
    
    o(4)//print object begin tag to pdf
    p(D(/Count1/MediaBox[0 0 595 842]/Kids[5 0 R])S);//print to pdf
    
    o(5)//print object begin tag to pdf
    p(C,4,0,6e-2,6e-2f,d,122,d); //begin font info
    
    E p("/%c",~-c/6+~14?c:d);//loop to print data to pdf 
    q(]>>/CharProcs<<);//print to pdf, converted to string

    E if(~-c/6+~14)//loop to print data to pdf 
        p("/%c %d 0 R",c,c+~58);

    for(q(>>/Widths[),c=59;--c;p(" 10"));//loop to print data to pdf 
        
    a=p("]>>>>>>/Contents 1                              0 R>>"S);

    for(p("xref 0 %d ",--d);c<d;p("%010u %05d n  ",*(c+++b),NULL)); //print reference table data
    
    return!(p(DANCE,d,a)); //print trailer
}
```

**Obfuscation used:**

1. Obscure naming

2. Typedef to hide variable types

3. Extensive use of operators, a full list can be found here: [en.wikipedia.org/wiki/Operators_in_C_and_C++](http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B)

4. Non pdf data present in many strings being written to pdf, many these likely contribute to the deeper features of hamano

5. Several #defines hide what is written to pdf

**After changes:**

``` c
	    int main(){
		
		int c; //c for counter
		char bodyData[256];
		
		PRNTTOPDF("%%PDF-1.3\n");
		
		PRNTPDFOBJ(1)
		PRNTTOPDF(STRTAGS(/Length 2 0 R) "stream\n");
		
		refData[0] = ~fileSize; //save (-filesize - 1)

		PRNTTOPDF("BT 12 818"" Td/%c 12 Tf 12 TL\n",v[7]);


		for(; c = getchar(),~c;){ 
		    //gets text input from stdin, getchar returns int EOF (-1) when there is no more input text.
		    //only second condition relevant in evaluation of for condition 
		    
		    if(c-10){//if character is not newline
			PRNTTOPDF("/%c 12 Tf(\\%o)" "Tj", v[ ((c-1)%32) < v[25] && !((c-1)/64)-1 ? 0 : 7],c);
		    }
		    else{//if character is newline
			PRNTTOPDF("()"); //removed ' at end of string
		    }
		}

		PRNTTOPDF("\nET ");

		refData[0] += fileSize + 1; 

		PRNTTOPDF(ENDSTRM"  "); 
		
		//prints main body data
		for(c=65; c < 123; c++){
		    filePos = processBody(bodyData + sprintf(bodyData,w[16]),c,6)-bodyData; 

		    PRNTPDFOBJ(c-59) 
		    PRNTTOPDF(STRTAGS(/Length %d) "stream\n%s" ENDSTRM,filePos,bodyData);
		}
		    
		PRNTPDFOBJ(2)
		PRNTTOPDF(" %u"ENDOBJ,refData[0]); //changed *b to b[0]
		
		PRNTPDFOBJ(3)
		PRNTTOPDF(STRTAGS(/Pages 4 0 R) ENDOBJ);
		
		PRNTPDFOBJ(4)
		PRNTTOPDF(STRTAGS(/Count 1/MediaBox[0 0 595 842]/Kids[5 0 R]) ENDOBJ);
		
		PRNTPDFOBJ(5)
		PRNTTOPDF(FONTINF,4,0,6e-2,6e-2f,65,122,65); //FONTINF populated by PRNTTOPDF
		    
		for(c = 65; c < 123; c++){
		    PRNTTOPDF("/%c", (c-1)/6 - 15 ? c : 65); 
		    //if statement inside, (~-) subtracts one, (+ ~14) subtracts 15
		}

		TOSTR(]>>/CharProcs<<);
		    
		for(c = 65 ; c < 123; c++){
		    
		    if( (c-1)/6 - 15 ){
			PRNTTOPDF("/%c %d 0 R",c,c-59); //+~58 before
		    }
		}

		TOSTR(>>/Widths[);

		for(c=59; c-1 ; c--){ 
		    PRNTTOPDF(" 10");
		}
		
		c--; 
		//added because c-- will not take place when c-1 evaluates to false, required

		filePos = PRNTTOPDF("]>>>>>>/Contents 1                              0 R>>" ENDOBJ); 
		//sets filepos = filesize, saves location for trailer data since filesize will still increase 
		//filepos holds the amount of bytes to keyword xref

		//print cross reference table to PDF
		PRNTTOPDF("xref 0 %d ",64);
		
		//print reference table data
		for(; c<64;c++){ 
		    //PRNTTOPDF("%010u %05d n  ",*(c++ + b),NULL);
		    PRNTTOPDF("%010u %05d n  ",refData[c],NULL);
		}
  
		//print pdf trailer and return control
		return !(PRNTTOPDF(TRAILER,64,filePos));
  
	    }
```
##4. Ending remarks

Complete source of deobfuscated code can be found attached as myhamano.c

outputORIG.pdf is output from unchanged hamano using text `aabbccddxx`

output.pdf is output from myhamano.c using text `aabbccddxx`

