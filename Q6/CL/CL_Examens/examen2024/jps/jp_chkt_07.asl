func main()
  var i , j : int
  var c1 , c2 : char
  var A: array[10] of float

  if i > j then
    switch c1:
    case 'a': write(1); endcase
    endswitch

    switch p:
    case 33: i = p; endcase
    endswitch
  endif

  switch i*j:
  case false: i = 0; endcase
  case 3: i = A[i]+1; j = A-1; endcase
  case 2.5: i = 2; endcase
  case 1: j = 3 > c1; endcase
  case 'a': i = i+1; endcase
  default: k = 4;
  endswitch

endfunc
