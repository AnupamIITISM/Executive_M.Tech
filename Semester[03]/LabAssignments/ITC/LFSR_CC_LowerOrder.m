n=7
fprintf('Generator Polynomial : ');
g=[1 1 0 1]     
k=length(g)
fprintf('Information bits are : ');
bin=[0 1 0 1]   
for i=1:k-1
    b(i)=0;
    d(i)=0;
end
for i=1:n-1
    c(i)=0;
end
Shift=1
for C=k:-1:1
    for i=n:-1:1
        if(i==1)
                c(i)=d(k-1);
        else
                c(i)=c(i-1);
        end
    end
    bf=b(k-1)
    for i=k-1:-1:1
        if(g(i)==1)
            if(i==1)
                 b(i)=xor(bin(C),bf);
            else
                    b(i)=xor(b(i-1),bf);
            end
        else   if(i==1)
                b(i)=bin(C);
            else
                 b(i)=b(i-1);
            end
          end       
    end
    for i=k-1:-1:1
        if(i==1)
            d(i)=bin(C);
        else
            d(i)=d(i-1);
        end
    end
    b
    d
    c
    Shift=Shift+1
end
for i=n-k:-1:1
    for i=n:-1:1
        if(i==1)
            c(i)=d(k-1);
        else
            c(i)=c(i-1);
        end
    end
    bf=b(k-1)
    for i=k-1:-1:1
        if(g(i)==1)
            if(i==1)
                    b(i)=xor(0,bf);
            else
                    b(i)=xor(b(i-1),bf);
            end
        else   if(i==1)
                b(i)=0;
       else
                b(i)=b(i-1);
       end
        end
    end
    for i=k-1:-1:1
        if(i==1)
                d(i)=0;
        else
                d(i)=d(i-1);
        end
    end
    b
    d
    c 
    Shift=Shift+1
end
for i=n-k:-1:1
    for i=n:-1:1
        if(i==1)
            c(i)=b(k-1);
        else
            c(i)=c(i-1);
        end
    end
    for i=k-1:-1:1
        if(i==1)
            b(i)=0;
        else
            b(i)=b(i-1);        
        end
    end
    b
    d
    c 
    if(Shift<(2*n)-k)
        Shift=Shift+1
    end
end