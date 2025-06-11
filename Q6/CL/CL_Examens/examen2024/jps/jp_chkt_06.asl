func main()
  var i , j : int
  var c1 , c2 : char
  var A: array[10] of int

  if i > c2 then
    switch c1:
    case 'a': write 1; endcase
    endswitch
    A[c1] = 19;
  endif

  j = c1[3] + k;
  
  switch i*j:
  case 3: i = A[i+1]; j = j-1; endcase
  case 1: j = 3-1; endcase
  default: i = 4; write 2*j; write "\n";
  endswitch

endfunc
