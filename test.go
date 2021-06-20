func integer: numPrint (integer: num, integer: length) {
	integer: i, j, z, sqr;
	i := 2;
	in >> j;
	if j > 3 : {
	    z := 3 * i + j;
	 }
	 else {
	    z := 42;

	 }
	 print(z);
	 while i < 10: {
        sqr := i * i;
        print(sqr);
        i := i + 1;


	 }


}

