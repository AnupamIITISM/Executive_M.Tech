freq = [70 20 10] 
seq = [2 3 1 3 3]
%Arithmatic Encoding
a_code = arithenco(seq, freq)
%Arithmatic Decoding
a_deco = arithdeco(a_code,freq,length(seq))