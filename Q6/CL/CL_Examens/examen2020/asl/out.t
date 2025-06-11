function ff
  params
    _result boolean
    n integer
  endparams

   %1 = 2
   %2 = n * %1
   %5 = 3
   %9 = %2 / %5
   %10 = %5 * %9
   %6 = %2 - %10
   %11 = 1
   %14 = %6 == %11
   %14 = not %14
   _result = %14
   return
   return
endfunction

function main
  vars
    a integer
    b boolean
    t integer
  endvars

     %1 = 12
     t = %1
     %2 = 0
     %3 = &a
     %4 = 23
     %5 = %4 * t
     %3[%2] = %5
     %8 = 0
     %10 = &a
     %9 = %10[%8]
     writei %9
     writes "\n"
     %11 = 4
     %12 = t - %11
     %16 = 0
     %18 = 1
     %17 = 0
     %21 = 1
  label while1 :
     %19 = %17 < %18
     ifFalse %19 goto whileEnd2
     %20 = a[%17]
     pushparam 
     pushparam %20
     call ff
     popparam 
     popparam %20
     b[%17] = %20
     %16 = %16 + %20
     %17 = %17 + %21
     goto while1
  label whileEnd2 :
     %22 = 2
     %23 = %16 + %22
     %27 = %12 * %23
     writei %27
     writes "\n"
     %30 = 0
     %32 = &b
     %31 = %32[%30]
     %33 = not %31
     ifFalse %33 goto else1
     writes "no\n"
     goto endif1
  label else1 :
     writes "yes\n"
  label endif1 :
     %34 = 0
     %35 = &a
     %36 = 0
     %38 = &a
     %37 = %38[%36]
     %39 = 2
     %40 = %37 + %39
     %35[%34] = %40
     %43 = 4
     %44 = t - %43
     %48 = 0
     %50 = 1
     %49 = 0
     %53 = 1
  label while3 :
     %51 = %49 < %50
     ifFalse %51 goto whileEnd4
     %52 = a[%49]
     pushparam 
     pushparam %52
     call ff
     popparam 
     popparam %52
     b[%49] = %52
     %48 = %48 + %52
     %49 = %49 + %53
     goto while3
  label whileEnd4 :
     %54 = 2
     %55 = %48 + %54
     %59 = %44 * %55
     writei %59
     writes "\n"
     %62 = 0
     %64 = &b
     %63 = %64[%62]
     ifFalse %63 goto else2
     writes "no\n"
     goto endif2
  label else2 :
     writes "yes\n"
  label endif2 :
     return
endfunction


