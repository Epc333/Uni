function main
  vars
    a integer
    b integer
    x float
    y float
  endvars

     %1 = 3
     %3 = float %1
     x = %3
     %4 = 2
     a = %4
     %7 = 6
     b = %7
     %15 = 1
     %10 = 0
     %11 = a
     %13 = 1.0
     %14 = x
  label potenciaLoop1 :
     %12 = %10 < %11
     ifFalse %12 goto potenciaEnd2
     %13 = %13 *. %14
     %10 = %10 + %15
     goto potenciaLoop1
  label potenciaEnd2 :
     y = %13
     %18 = 2
     %21 = float %18
     %19 = y *. %21
     writef %19
     writes "\n"
  label while7 :
     %27 = 1
     %22 = 0
     %23 = b
     %25 = 1.0
     %26 = x
  label potenciaLoop3 :
     %24 = %22 < %23
     ifFalse %24 goto potenciaEnd4
     %25 = %25 *. %26
     %22 = %22 + %27
     goto potenciaLoop3
  label potenciaEnd4 :
     %28 = 3
     %30 = float %28
     %31 = %25 <=. %30
     %31 = not %31
     ifFalse %31 goto endwhile7
     writef x
     writes "**"
     writei b
     writes "="
     %37 = 1
     %32 = 0
     %33 = b
     %35 = 1.0
     %36 = x
  label potenciaLoop5 :
     %34 = %32 < %33
     ifFalse %34 goto potenciaEnd6
     %35 = %35 *. %36
     %32 = %32 + %37
     goto potenciaLoop5
  label potenciaEnd6 :
     writef %35
     writes "\n"
     %38 = 1
     %39 = b - %38
     b = %39
     goto while7
  label endwhile7 :
     %44 = 3
     %45 = 2.5
     %46 = y -. %45
     %50 = 4
     %51 = b + %50
     %60 = 1
     %55 = 0
     %56 = %51
     %58 = 1.0
     %59 = %46
  label potenciaLoop8 :
     %57 = %55 < %56
     ifFalse %57 goto potenciaEnd9
     %58 = %58 *. %59
     %55 = %55 + %60
     goto potenciaLoop8
  label potenciaEnd9 :
     %62 = float %44
     %61 = %62 +. %58
     %64 = 1
     %65 = b - %64
     %74 = 1
     %69 = 0
     %70 = %65
     %72 = 1.0
     %73 = x
  label potenciaLoop10 :
     %71 = %69 < %70
     ifFalse %71 goto potenciaEnd11
     %72 = %72 *. %73
     %69 = %69 + %74
     goto potenciaLoop10
  label potenciaEnd11 :
     %75 = %61 -. %72
     writef %75
     writes "\n"
     return
endfunction


