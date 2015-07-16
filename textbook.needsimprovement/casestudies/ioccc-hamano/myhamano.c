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


            int filePos,refData[64],fileSize,v[32]={84,0,64,282,90,74,330,85,93,173,167,176,80,208,81,13,7,87,160,346,32,128,170,218,16,26}; 
            
            char* w[]={"+*-(,&-&","+*,&-&","+*.&/&","+*/*/+","+*())'('","+**&)&","+*(&'&","+*'*'+","","+,./","+,-,./","+--,+*"  ,"","+,(/","+,),(/","+-),+*","10 0 d0 ","8 7 2 2 re ","+*+.'`'@'mi +/+/(mi"};
           
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
            
            int main(){
                int c;
                char bodyData[256];
                
                PRNTTOPDF("%%PDF-1.3\n");
                
                PRNTPDFOBJ(1)
                PRNTTOPDF(STRTAGS(/Length 2 0 R) "stream\n");
                
                refData[0] = ~fileSize;
                
                PRNTTOPDF("BT 12 818"" Td/%c 12 Tf 12 TL\n",v[7]);


                for(; c = getchar(),~c;){ 
                    if(c-10){ 
                        PRNTTOPDF("/%c 12 Tf(\\%o)" "Tj", v[ ((c-1)%32) < v[25] && !((c-1)/64)-1 ? 0 : 7],c);
                    }
                    else{
                        PRNTTOPDF("()");
                    }
                }
                
                PRNTTOPDF("\nET ");

                refData[0] += fileSize + 1;

                PRNTTOPDF(ENDSTRM"  "); 
                
                for(c=65; c < 123; c++){
                    filePos = processBody(bodyData + sprintf(bodyData,w[16]),c,6)-bodyData; 

                    PRNTPDFOBJ(c-59) 
                    PRNTTOPDF(STRTAGS(/Length %d) "stream\n%s" ENDSTRM,filePos,bodyData);
                }
                     
                PRNTPDFOBJ(2)
                PRNTTOPDF(" %u"ENDOBJ,refData[0]);
                
                PRNTPDFOBJ(3)
                PRNTTOPDF(STRTAGS(/Pages 4 0 R) ENDOBJ);
                
                PRNTPDFOBJ(4)
                PRNTTOPDF(STRTAGS(/Count 1/MediaBox[0 0 595 842]/Kids[5 0 R]) ENDOBJ);
                
                PRNTPDFOBJ(5)
                PRNTTOPDF(FONTINF,4,0,6e-2,6e-2f,65,122,65);
                    
                for(c = 65; c < 123; c++){
                    PRNTTOPDF("/%c", (c-1)/6 - 15 ? c : 65); 
                }

                TOSTR(]>>/CharProcs<<);
                    
                for(c = 65 ; c < 123; c++){
                    
                    if( (c-1)/6 - 15 ){
                        PRNTTOPDF("/%c %d 0 R",c,c-59);
                    }
                }

                TOSTR(>>/Widths[);

                for(c=59; c-1 ; c--){ 
                    PRNTTOPDF(" 10");
                }
                
                c--; 

                filePos = PRNTTOPDF("]>>>>>>/Contents 1                              0 R>>" ENDOBJ); 

                PRNTTOPDF("xref 0 %d ",64);
                
                for(; c<64;c++){ 
                    PRNTTOPDF("%010u %05d n  ",refData[c],NULL);
                }
  
                return !(PRNTTOPDF(TRAILER,64,filePos));
  
            }
