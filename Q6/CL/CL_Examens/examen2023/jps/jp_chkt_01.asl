func main()
  var a : array[5] of float
  var b : array[10] of int
  var z,p : float
  var i : int

  read p;
  foreach z in a do
     if z>p and not b then
        i = 0;
        while i<10 do
           b[i] = z;
           i = i + 1;
        endwhile
        p = z*2;
     endif
  endfor

  write p;
  write q;
endfunc
