func main()
  var i, n: int
  var x, y: float
  var A, B: array[10] of float

  n = 10;
  i = 0;
  while i < n do
    A[i] = i*i + 1;
    B[i] = 1000-i;
    i = i +1;
  endwhile

  i = 0;
  while i < n do
    write "before. A["; write i; write "] = "; write A[i];
    write " - B["; write i; write "] = "; write B[i]; write "\n";
    i = i + 1;
  endwhile

  swap(A, B);
  
  i = 0;
  while i < n do
    write "after. A["; write i; write "] = "; write A[i];
    write " - B["; write i; write "] = "; write B[i]; write "\n";
    i = i + 1;
  endwhile

endfunc