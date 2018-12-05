%Encode Linear code 
n=7;   
k=4   
fprintf('Message: ');
data = randi([0 1],k,1)
pol = cyclpoly(n,k);
parmat = cyclgen(n,pol);
genmat = gen2par(parmat);
fprintf('Encoded linear code message is : ');
encodeddata = encode(data,n,k,'linear/binary',genmat)
encodeddata(4) = ~encodeddata(4);
fprintf('Decoded linear code message is : ');
decodedData = decode(encodeddata,n,k,'linear/binary',genmat)