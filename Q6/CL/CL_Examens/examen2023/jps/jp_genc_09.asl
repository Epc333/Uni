func suma(n: int, m: int): int
  return n+m;
endfunc

func minim(n: int, m: int): int
  if n < m then return n; endif
  return m;
endfunc

func resta(n: int, m: int): int
  return n-m;
endfunc

func AND(a: bool, b: bool) : bool
   return a and b;
endfunc

func maximC(c1: char, c2: char): char
  if c1 > c2 then return c1; endif
  return c2;
endfunc

func main()
  var A: array[10] of int
  var B: array[10] of bool
  var i, k: int
  var r: float
  var c: char
  var AC: array[13] of char

  i = 9;
  while i >= 0 do
    read A[i];
    B[i] = (A[i]%2 == 0);
    i = i - 1;
  endwhile
  
  r = reduce(A,suma)/10.0;
  write r; write '\n';  
  k = reduce(A,minim);
  write k; write '\n';
  k = reduce(A,resta);
  write k; write '\n';

  i = 0;
  while i < 13 do
    // read chars from input
    // (skips whitespaces)
    read AC[i]; 
    i = i + 1;
  endwhile
  c = reduce(AC, maximC);
  write c; write "\n";

  if reduce(B,AND) then
     write "all even\n";
  else
     write "some odd\n";
  endif
endfunc