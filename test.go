func integer: numPrint (integer: num, integer: length) {
	integer: i, j, first, temp;
	char : a;
	j := 2;
	first := 4;
	temp := 5;
    i := j + (first + temp) * temp - first;
    /*z := 3 * 5 + 24 - 3 / a + 20 + ( 3 / 4 -2);*/
    /*j := j + 3 * 5 - 2;*/
	a := 'x';
	print ("enter number");
	in >> i;
	println (i);
	i := length;
	while i > 0 : {
        first:= 0; /*this line contains a comment*/
        j := 1;
        while j < i: {
            write( j);
                j := j + 1;
        }
        if j == 1:{
                print("one");
            if k == 2:{
                print("three");
            }
        }
        elif j==2:{
            print("two");
        }
        elif a ==3:{
            print("balalalal");
        } else {
            print("others");
        }
        /* this is a comment */
        i:= i - 1;
        /*This is a
        Multiline
        Comment*/
    }
	z := 3 * 5 + 24 - 3 / a + 20 + ( 3 / 4 -2);
	print("temp is");
	println(temp);
	ret i;
}