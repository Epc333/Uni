func catorze(n: int, m: int): int
  return 14;
endfunc

func lletraF(c1: char, c2: char): char
  return 'F';
endfunc

func main()
  var A: array[10] of int
  var B: array[1] of int
  var i, k: int
  var r: float
  var c: char
  var AC: array[12] of char
  var BC: array[1] of char

  i = 9;
  while i >= 0 do
    read A[i];
    write "A["; write i; write "]=";
    write A[i]; write "\n";
    i = i - 1;
  endwhile
  
  r = reduce(A,catorze)/10.0;
  write r; write "\n";  
  k = reduce(A,catorze);
  write k; write "\n";

  B[0] = A[3];
  write reduce(B,catorze); write "\n";
  B[0] = A[6];
  write reduce(B,catorze); write "\n";

  i = 0;
  while i < 12 do
    // read chars from input
    // (skips whitespaces)
    read AC[i];
    i = i + 1;
  endwhile
  c = reduce(AC, lletraF);
  write c; write "\n";  

  BC[0] = AC[7];
  c = reduce(BC, lletraF);
  write c; write "\n";  
endfunc