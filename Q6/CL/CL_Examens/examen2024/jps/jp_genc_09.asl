func main()
  var i, j : int

  read i;
  switch i*i:
  case 1:  write "case value = 1\n"; endcase
  case 4:  write "case value = 4\n"; endcase
  case 9:  write "case value = 9\n"; endcase
  case 16: write "case value = 16\n"; endcase
  case 9:  write "case value = 9 err!\n"; endcase
  endswitch

  switch i:
  case 33: i = 33; endcase
  endswitch

  write i; write "\n";
endfunc
