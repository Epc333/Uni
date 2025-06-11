func main()
  var i, j, k, n: int
  var c1, c2: char
  var x, y: float
  var Ai: array[10] of int
  var Af: array[10] of float

  n = 10;
  i = 0;
  while i < n do
    Ai[i] = i*i + 1;
    i = i +1;
  endwhile

  read k;
  j = 5;
  // swap(left_expr1, left_expr2)
  swap(k, Ai[j+1]);
  write "A. "; write k; write " ";
  write Ai[j+1]; write "\n";
  
  swap(Ai[0], Ai[n-1]);
  write "B. "; write Ai[0]; write " ";
  write Ai[n-1]; write "\n";

  swap(Ai[0], k);
  write "C. "; write Ai[0]; write " ";
  write k; write "\n";

  i = 0;
  while i < n do
    write "Ai["; write i; write "] = ";
    write Ai[i]; write "\n";
    i = i +1;
  endwhile
  
endfunc