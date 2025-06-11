function main
  vars
    i integer
    j integer
    M float 150
    t float
  endvars

     %1 = 0
     i = %1
  label while2 :
     %2 = 10
     %5 = i < %2
     ifFalse %5 goto endwhile2
     %6 = 0
     j = %6
  label while1 :
     %7 = 15
     %10 = j < %7
     ifFalse %10 goto endwhile1
     %11 = 0
     %12 = 10
     %13 = 15
     %14 = %11 < i
     ifFalse %14 goto boundsOk1_1
     halt "Container index out of range."
  label boundsOk1_1 :
     %15 = i < %12
     ifFalse %15 goto boundsOk2_2
     halt "Container index out of range."
  label boundsOk2_2 :
     %16 = %11 < j
     ifFalse %16 goto boundsOk3_3
     halt "Container index out of range."
  label boundsOk3_3 :
     %17 = j < %13
     ifFalse %17 goto boundsOk4_4
     halt "Container index out of range."
  label boundsOk4_4 :
     %20 = 15
     %21 = i * %20
     %19 = %21 + j
     %18 = &M
     %22 = i + j
     %25 = float %22
     %18[%19] = %25
     %26 = 1
     %27 = j + %26
     j = %27
     goto while1
  label endwhile1 :
     %30 = 1
     %31 = i + %30
     i = %31
     goto while2
  label endwhile2 :
     %34 = 0
     i = %34
  label while4 :
     %35 = 15
     %38 = i < %35
     ifFalse %38 goto endwhile4
     %39 = 0
     j = %39
  label while3 :
     %40 = 10
     %43 = j < %40
     ifFalse %43 goto endwhile3
     %44 = 0
     %45 = 10
     %46 = 15
     %47 = %44 < i
     ifFalse %47 goto boundsOk1_5
     halt "Container index out of range."
  label boundsOk1_5 :
     %48 = i < %45
     ifFalse %48 goto boundsOk2_6
     halt "Container index out of range."
  label boundsOk2_6 :
     %49 = %44 < j
     ifFalse %49 goto boundsOk3_7
     halt "Container index out of range."
  label boundsOk3_7 :
     %50 = j < %46
     ifFalse %50 goto boundsOk4_8
     halt "Container index out of range."
  label boundsOk4_8 :
     %52 = 15
     %53 = i * %52
     %51 = %53 + j
     %55 = &M
     %54 = %55[%51]
     writef %54
     writes " "
     %56 = 1
     %57 = j + %56
     j = %57
     goto while3
  label endwhile3 :
     writes "\n"
     %60 = 1
     %61 = i + %60
     i = %61
     goto while4
  label endwhile4 :
     return
endfunction


