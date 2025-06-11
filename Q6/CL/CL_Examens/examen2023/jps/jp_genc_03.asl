func main()
   var i: int
   var a : array[10] of int
   var b : array[5] of float
   var elemi : int
   var elemf : float

   i = 0;
   while i < 10 do
     read elemi;
     a[i] = elemi*2;
     i = i+1;
   endwhile
   
   foreach elemi in a do
      i = 0;
      while i < 5 do
        b[i] = 1.0/(2*elemi+1);
        i = i+1;
      endwhile

      write elemi;
      write "\n";
      foreach elemf in b do
         write "  ";
         write elemf*3.5;
      endfor
      write "\n";
   endfor
endfunc
