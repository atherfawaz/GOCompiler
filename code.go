func integer: numPrint (integer: num, integer: length) {
	integer: i, j, first, temp;
	char : a;
	a := 'x';
	print ("enter number");
	in >> i;
	println (i);
	i := length;
	while i > 0 :
	{
	first:= 0; /*this line contains a comment*/
	j := 1;
	while j < i:
	{
		write( j);
			j := j + 1;
	}
	if a == 3: {
	    print("a");
	}
	if j == 1:{
		print("one");


	}
	elif j==2:{
		print("two");
	}
	elif a ==3:{
	    print("balalalal");

	}
	else
	{
		print("others");
	}
		/* this is a comment */
		i:= i - 1;
		/*This is a
		Multiline
		Comment*/
	}
	print("temp is");
	println(temp);
	ret i;
}

