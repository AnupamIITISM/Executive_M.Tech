n=7;
k=4; 
%Encode Cyclic Code
gx=cyclpoly(n,k) 
ix=[0 1 0 1]    
cx=gfconv(ix,gx);
if(length(cx)<n)
    no_zeros=zeros(1,n-length(cx));
    cx=[cx,no_zeros]
end
cx 
%Decode Cyclic Code
ex=zeros(1,n); 
ex(3)=~ex(3);   
vx=bitxor(cx,ex) 
[quot,sx] = gfdeconv(vx,gx,2);
Syndrome=sx
syn_dec = bi2de(sx,'left-msb') 
[Hns,Gns]=cyclgen(n,gx) 
syntab=syndtable(Hns) 
Detected_ext = syntab(1+syn_dec,:) 
Corrected_codeword = bitxor(Detected_ext,vx)