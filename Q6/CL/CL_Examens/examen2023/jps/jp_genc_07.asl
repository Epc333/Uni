func suma(n: int, m: int): int
  return n+m;
endfunc

func minim(n: int, m: int): int
  if n < m then return n; endif
  return m;
endfunc

func maxim(n: int, m: int): int
  if n > m then return n; endif
  return m;
endfunc

func maximC(c1: char, c2: char): char
  if c1 > c2 then return c1; endif
  return c2;
endfunc

func main()
  var A: array[1] of int
  var i, k: int
  var r: float
  var c: char
  var AC: array[1] of char

  A[0] = 231;
  write "A[0]="; write A[0]; write "\n";
  
  r = reduce(A,suma)/10.0; write r; write "\n";  
  k = reduce(A,minim); write k; write "\n";
  k = reduce(A,maxim); write k; write "\n";

  AC[0] = 'h'; 
  c = reduce(AC, maximC);
  write c; write "\n";  
endfunc