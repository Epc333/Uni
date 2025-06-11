function suma
  params
    _result integer
    n integer
    m integer
  endparams

   %1 = n + m
   _result = %1
   return
   return
endfunction

function minim
  params
    _result integer
    n integer
    m integer
  endparams

     %3 = n < m
     ifFalse %3 goto endif1
     _result = n
     return
  label endif1 :
     _result = m
     return
     return
endfunction

function resta
  params
    _result integer
    n integer
    m integer
  endparams

   %1 = n - m
   _result = %1
   return
   return
endfunction

function AND
  params
    _result boolean
    a boolean
    b boolean
  endparams

   %1 = a and b
   _result = %1
   return
   return
endfunction

function maximC
  params
    _result character
    c1 character
    c2 character
  endparams

     %3 = c1 <= c2
     %3 = not %3
     ifFalse %3 goto endif1
     _result = c1
     return
  label endif1 :
     _result = c2
     return
     return
endfunction

function main
  vars
    A integer 10
    B boolean 10
    i integer
    k integer
    r float
    c character
    AC character 13
  endvars

     %1 = 9
     i = %1
  label while1 :
     %4 = 0
     %7 = i < %4
     %7 = not %7
     ifFalse %7 goto endwhile1
     %8 = &A
     readi %9
     %8[i] = %9
     %10 = &B
     %12 = &A
     %11 = %12[i]
     %13 = 2
     %17 = %11 / %13
     %18 = %13 * %17
     %14 = %11 - %18
     %19 = 0
     %22 = %14 == %19
     %10[i] = %22
     %27 = 1
     %28 = i - %27
     i = %28
     goto while1
  label endwhile1 :
     %33 = &A
     %35 = 0
     %36 = 1
     %37 = 10
     %34 = %33[%35]
     %38 = %37 < %36
     %38 = not %38
     ifFalse %38 goto endReduce1
     %39 = %36
     %42 = 1
  label reduceLoop2 :
     %40 = %39 < %37
     ifFalse %40 goto endReduceLoop3
     %41 = %33[%39]
     pushparam 
     pushparam %34
     pushparam %41
     call suma
     popparam 
     popparam 
     popparam %34
     %39 = %39 + %42
     goto reduceLoop2
  label endReduceLoop3 :
  label endReduce1 :
     %43 = 10.0
     %45 = float %34
     %44 = %45 /. %43
     r = %44
     writef r
     %49 = '\n'
     writec %49
     %50 = &A
     %52 = 0
     %53 = 1
     %54 = 10
     %51 = %50[%52]
     %55 = %54 < %53
     %55 = not %55
     ifFalse %55 goto endReduce2
     %56 = %53
     %59 = 1
  label reduceLoop4 :
     %57 = %56 < %54
     ifFalse %57 goto endReduceLoop5
     %58 = %50[%56]
     pushparam 
     pushparam %51
     pushparam %58
     call minim
     popparam 
     popparam 
     popparam %51
     %56 = %56 + %59
     goto reduceLoop4
  label endReduceLoop5 :
  label endReduce2 :
     k = %51
     writei k
     %62 = '\n'
     writec %62
     %63 = &A
     %65 = 0
     %66 = 1
     %67 = 10
     %64 = %63[%65]
     %68 = %67 < %66
     %68 = not %68
     ifFalse %68 goto endReduce3
     %69 = %66
     %72 = 1
  label reduceLoop6 :
     %70 = %69 < %67
     ifFalse %70 goto endReduceLoop7
     %71 = %63[%69]
     pushparam 
     pushparam %64
     pushparam %71
     call resta
     popparam 
     popparam 
     popparam %64
     %69 = %69 + %72
     goto reduceLoop6
  label endReduceLoop7 :
  label endReduce3 :
     k = %64
     writei k
     %75 = '\n'
     writec %75
     %76 = 0
     i = %76
  label while8 :
     %79 = 13
     %82 = i < %79
     ifFalse %82 goto endwhile8
     %83 = &AC
     readc %84
     %83[i] = %84
     %85 = 1
     %86 = i + %85
     i = %86
     goto while8
  label endwhile8 :
     %91 = &AC
     %93 = 0
     %94 = 1
     %95 = 13
     %92 = %91[%93]
     %96 = %95 < %94
     %96 = not %96
     ifFalse %96 goto endReduce4
     %97 = %94
     %100 = 1
  label reduceLoop9 :
     %98 = %97 < %95
     ifFalse %98 goto endReduceLoop10
     %99 = %91[%97]
     pushparam 
     pushparam %92
     pushparam %99
     call maximC
     popparam 
     popparam 
     popparam %92
     %97 = %97 + %100
     goto reduceLoop9
  label endReduceLoop10 :
  label endReduce4 :
     c = %92
     writec c
     writes "\n"
     %103 = &B
     %105 = 0
     %106 = 1
     %107 = 10
     %104 = %103[%105]
     %108 = %107 < %106
     %108 = not %108
     ifFalse %108 goto endReduce5
     %109 = %106
     %112 = 1
  label reduceLoop11 :
     %110 = %109 < %107
     ifFalse %110 goto endReduceLoop12
     %111 = %103[%109]
     pushparam 
     pushparam %104
     pushparam %111
     call AND
     popparam 
     popparam 
     popparam %104
     %109 = %109 + %112
     goto reduceLoop11
  label endReduceLoop12 :
  label endReduce5 :
     ifFalse %104 goto else6
     writes "all even\n"
     goto endif6
  label else6 :
     writes "some odd\n"
  label endif6 :
     return
endfunction


