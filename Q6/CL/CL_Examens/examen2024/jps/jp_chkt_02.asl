func main()
  var i, j, n: int
  var c1, c2: char
  var x, y: float
  var Ai: array[10] of int
  var Af: array[10] of float

  // ok:
  swap(x, y);
  swap(c1, c2);
  swap(Ai[0], Ai[n-1]);

  // error en swap:
  swap(c1, x);
  swap(x, Ai[2]);

  // errors en operands:
  swap(x, x[3]);
  swap(zzzz, Ai[3]);

endfunc