% 1. Genera una matriu A de 10x10 amb valors aleatoris entre 0 i 255 de tipus enter
A = randi([0,255],10,10, "int16")
% 2. Obté un vector amb la 4ª fila de A
vec4 = A(4,:)
% 3. Obté un vector amb la 4ª columna de A
col4 = A(:,4)
% 4. Obté una matriu on s'hagi suprimit la 4ª columna de A
A_aux = A
A_aux(:,4) = []
% 5. Obté un vector amb el valor màxim de cada columna de A
maxCol = max(A)
% 6. Obté el valor màxim de la matriu A
maxValor = max(A(:))
% 7. Obté una matriu amb només les files parells de A
pRow = A(2:2:end, :)
% 8. Obté la fila i columna on es troba el valor mínim de A
[minValor, idx] = min(A(:))
[rowMin, colMin] = ind2sub(size(A), idx)
% 9. Genera la matriu B trasposant la matriu A
B =  transpose(A)
% 10. Obté el producte de les matrius A i B
C = double(A) * double(B)
% 11. Obté el producte element a element de A i B
C_element = A.*B
% 12. Genera una matriu booleana on cada element (i,j) valgui 1 si A(i,j) > B(i,j), i 0 en cas contrari
boolMat = A > B
% 13. Genera un vector amb tots els elements A(i,j) més grans que B(i,j)
resultVec = A(A > B)
% 14. Genera una matriu on cada element (i,j) valgui A(i,j) si A(i,j)>B(i,j) , i 0 en cas contrari
D = double(A) .* (A > B)