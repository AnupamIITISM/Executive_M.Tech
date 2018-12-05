%Syndrome table
n=7;
k=4;
pol = cyclpoly(n,k);
parmat = cyclgen(n,pol);
syntab = syndtable(parmat);
recdata = [0 1 1 1 0 1 0]
syndrome = rem(recdata * parmat',2);
syndrome_de = bi2de(syndrome,'left-msb'); 
disp(['Syndrome = ',num2str(syndrome_de),...
      ' (decimal), ',num2str(syndrome),' (binary)'])
correctvector = syntab(1+syndrome_de,:) 
correctedcode = rem(correctvector+recdata,2)