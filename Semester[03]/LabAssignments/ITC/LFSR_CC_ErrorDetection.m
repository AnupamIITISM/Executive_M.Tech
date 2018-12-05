% LFSR_Error_Detection
n=7
k=4
g=[1 1 0 1] 
fprintf('Decoding LFSR based :\n');
vx=[1 1 0 1 1 0 1]
for i=1:k-1
    B(i)=0;
end
Shift=0;
for C=n:-1:1
     Shift=Shift+1
    Bf=B(k-1)
    for i=k-1:-1:1
        if(g(i)==1)
            if(i==1)
                B(i)=xor(vx(C),Bf);
            else
                B(i)=xor(B(i-1),Bf);
            end
        else   if(i==1)             
                B(i)=vx(C);
            else
                 B(i)=B(i-1);
            end
          end       
    end
    
    B
   
end
Syndrome=B
OR_SYN=0;
for i=1:length(Syndrome)
    OR_SYN=or(OR_SYN,Syndrome(i));
end
OR_of_Syndrome_bits=OR_SYN
if(OR_SYN==1)
    fprintf('\nConclusion - Recieved Codeword is errorneous');
else
    fprintf('\nConclusion - No Error in Recieved Codeword');
end
 
 
% LFSR based Error correction
for i=1:k-1
    b(i)=0;
end
for i=1:n
    d(i)=0;
    e(i)=0;
    c(i)=0;
end
if(OR_SYN==1)
    Shift=0;
    for C=n:-1:1
        Shift=Shift+1
        
        for i=n:-1:1
            if(i==1)
                c(i)=xor(d(n),e(n));
            else
                c(i)=c(i-1);
            end
        end
        
        for i=n:-1:1
            if(i==1)
                vx(C)
                d(i)=vx(C);
            else
                d(i)=d(i-1);
            end
        end        
                
        bf=b(k-1)
        for i=k-1:-1:1
            if(g(i)==1)
                if(i==1)
                     b(i)=xor(vx(C),bf);
                else
                        b(i)=xor(b(i-1),bf);
                end
            else   if(i==1)
                    b(i)=vx(C);
                else
                     b(i)=b(i-1);
                end
              end       
        end
 
        b
        d
        c
 
    end
    Error_Loc=bi2de(b)
    e(Error_Loc+1)=1
    for C=n:-1:1
        Shift=Shift+1
 
        for i=n:-1:1
            if(i==1)
                c(i)=xor(d(n),e(n));
            else
                c(i)=c(i-1);
            end
        end
        
        for i=n:-1:1
            if(i==1)
     
                d(i)=e(n);
            else
                d(i)=d(i-1);
            end
        end        
        for i=n:-1:1
            if(i==1)
                e(i)=0;
            else
                e(i)=e(i-1);
            end
        end        
    
        e
        d
        c
 
    end
end
 

