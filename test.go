func integer: numPrint (integer: num, integer: length) {
	integer: i, j, first, temp, length, z;
	length := 1;
	char : a;
	j := 2;
	first := 4;
	temp := 5;
    i := j + (first + temp) * temp - first;
	a := 'x';
	println (i);
	print("Enter number:");
    in >> i;
	i := length;
	while i > 0 : {
	    j := 1;
	    first := 3;
	    if j == 1 : {
	        print("j is one");
	        if first == 3 : {
	            print("first is three");
	        }
	    }
	    elif j == 2 : {
	        print("j is two");
	        first := 4;
	        print("but now first is four");
	    }
	    /* this is a comment */
        i := i - 1;
        /*This is a
        Multiline
        Comment*/
    }
	z := 3 * 5 + 24 - 3 / temp + 20 + ( 3 / 4 - 2);
	print("Temp is: ");
	print(temp);
	ret i;
}