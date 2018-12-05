S=[1 2 3 4 5 6]
P=[0.4 0.2 0.2 0.05 0.05 0.1]
codify=huffmandict(S,P)
seq=[5 1 4 2]
%Huffman Encoding
encoded_msg=huffmanenco(seq,codify)
%Huffman Decoding
decoded_msg=huffmandeco(encoded_msg,codify)