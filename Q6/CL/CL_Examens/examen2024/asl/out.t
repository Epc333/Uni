function main
  vars
    i integer
    n integer
    x float
    y float
    A float 10
    B float 10
  endvars

     %1 = 10
     n = %1
     %2 = 0
     i = %2
  label while1 :
     %5 = i < n
     ifFalse %5 goto endwhile1
     %6 = i * i
     %9 = 1
     %10 = %6 + %9
     %13 = float %10
     A[i] = %13
     %14 = 1000
     %15 = %14 - i
     %18 = float %15
     B[i] = %18
     %19 = 1
     %20 = i + %19
     i = %20
     goto while1
  label endwhile1 :
     %23 = 0
     i = %23
  label while2 :
     %26 = i < n
     ifFalse %26 goto endwhile2
     writes "before. A["
     writei i
     writes "] = "
     %28 = &A
     %27 = %28[i]
     writef %27
     writes " - B["
     writei i
     writes "] = "
     %30 = &B
     %29 = %30[i]
     writef %29
     writes "\n"
     %31 = 1
     %32 = i + %31
     i = %32
     goto while2
  label endwhile2 :
     %38 = 10
     %37 = 0
     %40 = 1
  label arrayCopyWhile3 :
     %39 = %37 < %38
     ifFalse %39 goto arrayCopyend4
     %35 = B[%37]
     %36 = A[%37]
     B[%37] = %36
     A[%37] = %35
     %37 = %37 + %40
     goto arrayCopyWhile3
  label arrayCopyend4 :
     %41 = 0
     i = %41
  label while5 :
     %44 = i < n
     ifFalse %44 goto endwhile5
     writes "after. A["
     writei i
     writes "] = "
     %46 = &A
     %45 = %46[i]
     writef %45
     writes " - B["
     writei i
     writes "] = "
     %48 = &B
     %47 = %48[i]
     writef %47
     writes "\n"
     %49 = 1
     %50 = i + %49
     i = %50
     goto while5
  label endwhile5 :
     return
endfunction


