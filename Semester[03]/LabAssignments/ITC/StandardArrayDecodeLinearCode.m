%coding to generate standard array 
n=7;
k=4;
a=[0 0 0 0;0 0 0 1;0 0 1 0;0 0 1 1;0 1 0 0;0 1 0 1;0 1 1 0;0 1 1 1;
   1 0 0 0;1 0 0 1;1 0 1 0;1 0 1 1;1 1 0 0;1 1 0 1;1 1 1 0;1 1 1 1];
e = [0 0 0 0 0 0 0];
std_arr = e;
%cyclic generator polynomial
pol = cyclpoly(n,k);
%parity check matrix
H = cyclgen(n,pol);
%Convert parity check matrix into generator matrix
G = gen2par(H);
standard_array = e;
for i=2:16
    encdata = encode(a(i,:),n,k,'linear/binary',G);
    data = bitxor(encdata,e);
    std_arr = [std_arr;data];
    standard_array = [standard_array;data];
 end
fprintf('Row 1')
std_arr
e = [0 0 0 0 0 0 1]; 
for j=1:7
    std_arr=e;
    standard_array = [standard_array;e];
    for i=2:16
        encdata = encode(a(i,:),n,k,'linear/binary',G);
        data = bitxor(encdata,e);
        std_arr = [std_arr;data];
        standard_array = [standard_array;data];
    end
    fprintf('Row %d',j+1)
    std_arr
    e=circshift(e,[0,-1]);    
end
%Decoding
recdword = [1     0     1     0     0     0     0]
for i=1:(n+1)*2^k
   if(xor(standard_array(i,:),recdword)==0)       
       standard_array(i,:);
       x = floor(i/16);
       syndrome = standard_array(16*x+1,:)
       break;
   end
end
decoded = xor(recdword,syndrome)