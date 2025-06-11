
func wasa(M : array[5]
              of float): bool
   var elem : int
   var elem2 : float
   var b : bool
   var p,q,s : int
   
   foreach elem in M do
      write elem;
      foreach x in M do
        s = s + x;
      endfor
   endfor
   
   foreach M in M do
      elem2 = 1/M[0];
      foreach elem in x do
         q = q * -elem;
      endfor
   endfor
   
   foreach elem in b do
      foreach x in y do
         b = true;
      endfor
      foreach b in M do
         a = M;
      endfor
   endfor

   foreach elem2 in M do
      write elem2 - 1/elem2;
   endfor
endfunc

func main()
  var a : array[5] of float
  var b : array[10] of int
  var z,p : float
  var i,j : int

  read p;
  foreach z in b do
     if z>p and not b then
        a[i+1] = wasa(b);
        p = z*2;
     endif
  endfor

  write p;
  write q;
endfunc
