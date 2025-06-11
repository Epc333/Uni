func main()
   var i: int
   var x : float
   var a : array[10] of int
   var b : array[5] of float
   var elemi : int
   var elemf : float

   i = 0;
   while i < 10 do
     read x;
     b[i/2] = x*2;
     a[i] = i;
     i = i+1;
   endwhile
   
   foreach elemf in a do
      write elemf;
      write "\n";
      foreach x in b do
         write "  ";
         write elemf - x/3.5;
      endfor
      write "\n";
   endfor
endfunc
