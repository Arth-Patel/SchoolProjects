package math;

/**
 *PERSONAL 
 * 
 */
public class BigInteger {

	/**
	 * True if this is a negative integer
	 */
	boolean negative;
	/**
	 * Number of digits in this integer
	 */
	int numDigits;
	
	/**
	 * Reference to the first node of this integer's linked list representation
	 * NOTE: The linked list stores the Least Significant Digit in the FIRST node.
	 * For instance, the integer 235 would be stored as:
	 *    5 --> 3  --> 2
	 */
	DigitNode front;
	
	/**
	 * Initializes this integer to a positive number with zero digits, in other
	 * words this is the 0 (zero) valued integer.
	 */
	public BigInteger() {
		negative = false;
		numDigits = 0;
		front = null;
	}
	
	/**
	 * Parses an input integer string into a corresponding BigInteger instance.
	 * A correctly formatted integer would have an optional sign as the first 
	 * character (no sign means positive), and at least one digit character
	 * (including zero). 
	 * Examples of correct format, with corresponding values
	 *      Format     Value
	 *       +0            0
	 *       -0            0
	 *       +123        123
	 *       1023       1023
	 *       0012         12  
	 *       0             0
	 *       -123       -123
	 *       -001         -1
	 *       +000          0
	 *       
	 * 
	 * @param integer Integer string that is to be parsed
	 * @return BigInteger instance that stores the input integer
	 * @throws IllegalArgumentException If input is incorrectly formatted
	 */
	public static BigInteger parse(String integer) {
		BigInteger Project=new BigInteger();
		String integer2 = integer;
		DigitNode fronts=null;
		
		int x=0;
		if (integer.length()==0) {
			return null;
		}
		if (integer.charAt(0)=='-') {
			Project.negative = true;
		}
		while (integer2.charAt(0)=='0'||integer2.charAt(0)=='-'||integer2.charAt(0)=='+'||integer2.charAt(0)==' ') {
			if (integer2.length()==1) {
				break;
			}
			x=integer2.length();
			integer2=integer2.substring(1, x);
		}
		if (integer2.charAt(0)=='0') {
			Project.negative=false;
		}
		Project.numDigits=integer2.length();
		
		while (integer2.length()!=0) {
			char firstdig=integer2.charAt(0);
			if ( Character.isDigit(firstdig)==false) {
				throw new IllegalArgumentException();
				}
			int digit =Character.getNumericValue(firstdig);
			fronts=new DigitNode(digit,fronts);
			x=integer2.length();
			integer2=integer2.substring(1, x);
					}
		Project.front=fronts;
		return Project;
	}
	
	/**
	 * Adds an integer to this integer, and returns the result in a NEW BigInteger object. 
	 * DOES NOT MODIFY this integer.
	 * NOTE that either or both of the integers involved could be negative.
	 * (Which means this method can effectively subtract as well.)
	 * 
	 * @param other Other integer to be added to this integer
	 * @return Result integer
	 */
	public BigInteger add(BigInteger other) {
		// THE FOLLOWING LINE IS A PLACEHOLDER SO THE PROGRAM COMPILES
		// YOU WILL NEED TO CHANGE IT TO RETURN THE APPROPRIATE BigInteger
		BigInteger Sol= new BigInteger();
		DigitNode fronts=null;
		int Digits= this.numDigits;
		int carry=0;
		int DigitsB=other.numDigits;
		DigitNode ptr=other.front;	
		if ((this.negative==false && other.negative==false)|| (this.negative&&other.negative)) {
			if (Digits >=DigitsB) {
			while (DigitsB!=0) {
				DigitsB--;
				Digits--;
				int x= this.front.digit + ptr.digit+carry;
				int remain= x%10;
				carry= x/10;
				fronts=new DigitNode(remain,fronts);
				front=front.next;
				ptr=ptr.next;
			}
			while (Digits!=0) {
				int f=carry+this.front.digit;
				int remain=f%10;
				carry=f/10;
				
				fronts=new DigitNode(remain,fronts);
				Digits--;
				front=front.next;
			}
			if(carry!=0) {
				fronts=new DigitNode(carry,fronts);
			}
		}else {
			while (Digits!=0) {
				DigitsB--;
				Digits--;
				int x= this.front.digit + ptr.digit+carry;
				int remain= x%10;
				carry= x/10;
				fronts=new DigitNode(remain,fronts);
				front=front.next;
				ptr=ptr.next;
			}
			while (DigitsB!=0) {
				int f=carry+ptr.digit;
				int remain=f%10;
				carry=f/10;
				fronts=new DigitNode(remain,fronts);
				DigitsB--;
				ptr=ptr.next;
			}
			if(carry!=0) {
				fronts=new DigitNode(carry,fronts);
			}
		}
		}
		else {
			if(this.compare(other)) {
				while (DigitsB!=0) {
					DigitsB--;
					Digits--;
					int x= this.front.digit - ptr.digit-carry;
					carry=0;
					if (x<0) {
						x=x+10;
						carry=1;
					}
					int remain= x%10;
					fronts=new DigitNode(remain,fronts);
					front=front.next;
					ptr=ptr.next;
				}
				while (Digits!=0) {
					int f=this.front.digit-carry;
					carry=0;
					if (f<0) {
						f=f+10;
						carry=1;
					}					
					int remain=f%10;
					fronts=new DigitNode(remain,fronts);
					Digits--;
					front=front.next;
				}
				if(carry!=0) {
					fronts=new DigitNode(carry,fronts);
				}
				if (this.negative) {
					Sol.negative=true;
				}
				

		}
			if (other.compare(this)){
				while (Digits!=0) {
					DigitsB--;
					Digits--;
					int x= ptr.digit - this.front.digit-carry;
					carry=0;
					if (x<0) {
						x=x+10;
						carry=1;
					}
					int remain= x%10;
					fronts=new DigitNode(remain,fronts);
					front=front.next;
					ptr=ptr.next;
				}
				while (DigitsB!=0) {
					int f=ptr.digit-carry;
					carry=0;
					if (f<0) {
						f=f+10;
						carry=1;
					}	
					int remain=f%10;
					
					fronts=new DigitNode(remain,fronts);
					DigitsB--;
					ptr=ptr.next;
				}
				if(carry!=0) {
					fronts=new DigitNode(carry,fronts);
				}
				if (other.negative) {
					Sol.negative=true;
				}
			}
		}
		DigitNode rev=null;
		while (fronts!=null) {
			rev=new DigitNode(fronts.digit,rev);
			fronts=fronts.next;
		}
		if (other.negative && this.negative) {
			Sol.negative=true;
		}
		Sol.front=rev;
		
		return (parse(Sol.toString()));
	}
	
	/**
	 * Returns the BigInteger obtained by multiplying the given BigInteger
	 * with this BigInteger - DOES NOT MODIFY this BigInteger
	 * 
	 * @param other BigInteger to be multiplied
	 * @return A new BigInteger which is the product of this BigInteger and other.
	 */
	public BigInteger multiply(BigInteger other) {
		// THE FOLLOWING LINE IS A PLACEHOLDER SO THE PROGRAM COMPILES
		// YOU WILL NEED TO CHANGE IT TO RETURN THE APPROPRIATE BigInteger
		BigInteger A= new BigInteger();
		BigInteger B= new BigInteger();
		DigitNode F=null;
		DigitNode G=null;
		int DigitsA= this.numDigits;
		int DigitsB=other.numDigits;
		int location=1;
		int locationb=1;
		int Mul=0;
		int catching=0;
		DigitNode otherptr=other.front;
		DigitNode thisptr=this.front;
		while (DigitsA!=0) {
		Mul=thisptr.digit*otherptr.digit+catching;
		catching=0;
		catching=Mul/10;
		Mul=Mul%10;
		DigitsA--;
		thisptr=thisptr.next;
		F=new DigitNode(Mul,F);
		A.numDigits++;
		}
		if (catching!=0) {
			F=new DigitNode(catching, F);
			A.numDigits++;
		}
		DigitNode revF=null;
		while (F!=null) {
		revF=new DigitNode(F.digit,revF);
		F=F.next;
		}
		A.front=revF;
		DigitsB--;
		catching=0;
		while(DigitsB!=0) {
			while (location!=0) {
				location--;
				G=new DigitNode(0, G);
				B.numDigits++;
			}
			otherptr=otherptr.next;
			thisptr=this.front;
			DigitsA=this.numDigits;
			while (DigitsA!=0) {
				Mul=thisptr.digit*otherptr.digit+catching;			
				catching=0;
				catching=Mul/10;
				Mul=Mul%10;
				DigitsA--;
				thisptr=thisptr.next;
				G=new DigitNode(Mul,G);
				B.numDigits++;
			}
			if (catching!=0) {
				G=new DigitNode(catching, G);
				B.numDigits++;
			}
			DigitNode revG=null;
			while (G!=null) {
			revG=new DigitNode(G.digit,revG);
			G=G.next;
			}
			B.front=revG;
			locationb++;
			location=locationb;
			DigitsA=this.numDigits;
			DigitsB--;
			A=A.add(B);
			B.numDigits=0;
			G=null;
			revG=null;
			B.front=null;
		}
		if ((this.negative&&other.negative==false)|| (other.negative&&this.negative==false)) {
			A.negative=true;
		}
		return A;
	}
	
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		if (front == null) {
			return "0";
		}
		
		String retval = front.digit + "";
		for (DigitNode curr = front.next; curr != null; curr = curr.next) {
				retval = curr.digit + retval;
		}
		
		if (negative) {
			retval = '-' + retval;
		}
		
		return retval;
	}
	private boolean compare(BigInteger other) {
		if (this.numDigits>other.numDigits) {
		return true;
	}else if (other.numDigits>this.numDigits) {
		return false;
	}else { 
	String uno=this.toString();
	String dos=other.toString();
	int i=0;
	if (uno.charAt(0)=='-') {
		uno= uno.substring(1);
	}
	if (dos.charAt(0)=='-') {
		dos= dos.substring(1);
	}	
	while (dos.length()!=0) {
		char firstdig=uno.charAt(i);
		char seconddig=dos.charAt(i);
		if (Character.getNumericValue(firstdig) > Character.getNumericValue(seconddig)) {
			return true;
		}else if (Character.getNumericValue(firstdig) < Character.getNumericValue(seconddig)) {
			return false;
		}
		i++;
		if (i==dos.length()) {
			break;
		}
	}
	
}
		return true;
}
}