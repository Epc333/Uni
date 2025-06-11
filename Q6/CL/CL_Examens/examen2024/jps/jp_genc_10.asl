func main()
  var i, j : int

  i = 1;
  while i < 4 do
    write "i="; write i; write "    i*i="; write i*i;
    switch i*i:
    case 0:  write "    case value = 0\n"; endcase
    case 1:  write "    case value = 1\n"; endcase
    case 4:  write "    case value = 4\n"; endcase
    default: write "    case default\n";
    endswitch
    i = i + 1;
  endwhile
endfunc
