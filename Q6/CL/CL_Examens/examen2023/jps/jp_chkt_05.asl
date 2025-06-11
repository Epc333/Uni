func suma(a: float, b: float) : float
  return a+b;
endfunc

func last(a: char, b: char) : char
   if a>=b then return a;
   else return b;
   endif
endfunc

func main()
  var a : array[10] of float
  var s : float
  var b : array[20] of char
  var m : char

  s = s + p;
  s = reduce(a,suma);
  write s;
  c = reduce(b,last);
  write c;
  
  m = s*s - 1;
  a = m[i] + b[0];
endfunc
