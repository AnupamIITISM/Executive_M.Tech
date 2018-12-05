m=[0 0 0 0;0 0 0 1;0 0 1 0;0 0 1 1;0 1 0 0;0 1 0 1;0 1 1 0;0 1 1 1;1 0 0 0;1 0 0 1;1 0 1 0;1 0 1 1;1 1 0 0;1 1 0 1;1 1 1 0;1 1 1 1]
b=[];
m_p=[]; 
for i=1:16    
    p1=mod((m(i,1)+m(i,3)+m(i,4)),2);
    p2=mod((m(i,1)+m(i,2)+m(i,4)),2);
    p4=mod((m(i,1)+m(i,2)+m(i,3)),2);    
    b=[b;m(i,1),m(i,2),m(i,3),p4,m(i,4),p2,p1];
    m_p=[m_p;m(i,1),m(i,2),m(i,3),m(i,4),p4,p2,p1] ;   
end
fprintf('Format:\n  m4  m3  m2   p4  m1  p2  p1')
b
fprintf('Format:\n           Message             Parity ');
fprintf('\n  m4  m3  m2   m1  p4  p2  p1')
m_p