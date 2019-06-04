package apps;

import java.io.*;
import java.util.*;
import java.util.regex.*;

import structures.Stack;

public class Expression {

	/**
	 * Expression to be evaluated
	 */
	String expr;                
    
	/**
	 * Scalar symbols in the expression 
	 */
	ArrayList<ScalarSymbol> scalars;   
	
	/**
	 * Array symbols in the expression
	 */
	ArrayList<ArraySymbol> arrays;
    
    /**
     * String containing all delimiters (characters other than variables and constants), 
     * to be used with StringTokenizer
     */
    public static final String delims = " \t*+-/()[]";
    
    /**
     * Initializes this Expression object with an input expression. Sets all other
     * fields to null.
     * 
     * @param expr Expression
     */
    public Expression(String expr) {
        this.expr = expr;
    }
    

    /**
     * Populates the scalars and arrays lists with symbols for scalar and array
     * variables in the expression. For every variable, a SINGLE symbol is addedInd and stored,
     * even if it appears more than once in the expression.
     * At this time, values for all variables are set to
     * zero - they will be loaded from a file in the loadSymbolValues method.
     */
    public void buildSymbols() {
    		/** COMPLETE THIS METHOD **/
    	
		scalars = new ArrayList<ScalarSymbol>();
		arrays = new ArrayList<ArraySymbol>();
		int guide=0;
		String total = "";
		int sSearchCounter=0;
		int sSearchReset=0;
		int aSearchCounter=0;
		int aSearchReset=0;		
		boolean repeat=false;
		int length=this.expr.length();
		while(guide!=length) {
			char addedIn=expr.charAt(guide);
			if (Character.isLetter(addedIn)) {
				total=total+addedIn;
			}
			if (addedIn=='+'||addedIn=='-'||addedIn=='*'||addedIn=='/'||addedIn=='('||addedIn==')'||addedIn==']'||guide==length-1) {
				if (total!="") {
					ScalarSymbol createdScalar = new ScalarSymbol(total);	
					while(sSearchCounter!=0) {
						if (scalars.get(sSearchCounter-1).equals(createdScalar)) {
							repeat=true;
						}
						sSearchCounter--;
					}
					if (repeat==false) {
						scalars.add(createdScalar);
						sSearchReset++;
					}
					repeat=false;
					sSearchCounter=sSearchReset;
				}
				total="";
			}
			if(addedIn=='[') {
				ArraySymbol createdArray = new ArraySymbol(total);
				while(aSearchCounter!=0) {
					if (arrays.get(aSearchCounter-1).equals(createdArray)) {
						repeat=true;
					}
					aSearchCounter--;
				}
				if (repeat==false) {
					arrays.add(createdArray);
					aSearchReset++;
				}
				repeat=false;
				aSearchCounter=aSearchReset;
				total="";
			}
			guide++;		
		}
}		
    
    /**
     * Loads values for symbols in the expression
     * 
     * @param sc Scanner for values input
     * @throws IOException If there is a problem with the input 
     */
    public void loadSymbolValues(Scanner sc) 
    throws IOException {
        while (sc.hasNextLine()) {
            StringTokenizer st = new StringTokenizer(sc.nextLine().trim());
            int numTokens = st.countTokens();
            String sym = st.nextToken();
            ScalarSymbol ssymbol = new ScalarSymbol(sym);
            ArraySymbol asymbol = new ArraySymbol(sym);
            int ssi = scalars.indexOf(ssymbol);
            int asi = arrays.indexOf(asymbol);
            if (ssi == -1 && asi == -1) {
            	continue;
            }
            int num = Integer.parseInt(st.nextToken());
            if (numTokens == 2) { // scalar symbol
                scalars.get(ssi).value = num;
            } else { // array symbol
            	asymbol = arrays.get(asi);
            	asymbol.values = new int[num];
                // following are (index,val) pairs
                while (st.hasMoreTokens()) {
                    String tok = st.nextToken();
                    StringTokenizer stt = new StringTokenizer(tok," (,)");
                    int index = Integer.parseInt(stt.nextToken());
                    int val = Integer.parseInt(stt.nextToken());
                    asymbol.values[index] = val;              
                }
            }
        }
    }
    
    
    /**
     * Evaluates the expression, using RECURSION to evaluate subexpressions and to evaluate array 
     * subscript expressions.
     * @param total2 
     * @param total2 
     * 
     * @return Result of evaluation
     */
    public float evaluate() {
    		/** COMPLETE THIS METHOD **/
    	int ptr=0;
		while (ptr < this.scalars.size()){
			expr = expr.replace(scalars.get(ptr).name, ""+scalars.get(ptr).value);
			ptr++;
		}
		ptr=0;
		System.out.println(expr);
    	return evaluateString(expr);
    }

    private float evaluateString(String Express) {
    	int guide=0;
    	String total="";
    	String backString="";
    	int length=Express.length();
    	char search=' ';
    	int pCounter=0;
    	int bCounter=0;
    	char backup=' ';
    	String frontStringSave="";
    	while (guide<length) {
    		search=Express.charAt(guide);
    		if (search=='(') {
    			pCounter++;
    			frontStringSave=Express.substring(0,guide);
    			guide++;
    			while(pCounter!=0) {
    				search=Express.charAt(guide);
    				if (search==')') {
    					pCounter--;
    				}
    				if (search=='(') {
    					pCounter++;
    				}
    				total+=search;
    				guide++;
    			}

    			evaluateString(total.substring(0, total.length()-1));
    			int funny=(int)(evaluateString(total.substring(0, total.length()-1)));
    			backString=Express.substring(guide, Express.length());
    			Express=frontStringSave+funny+backString;
    			System.out.println(Express);
    			length=Express.length();
    			guide=-1;
    			total="";
    			search=' ';
    		}
    		
    		if (search=='[') {
    			bCounter++;
    			String arrayNamed="";
    			frontStringSave=Express.substring(0,guide);
    			int guidesave=guide;
    			while(Character.isLetter((Express.charAt(guide-1)))) {
    				arrayNamed=(Express.charAt(guide-1))+arrayNamed;
    				guide--;
    				if (guide==0) {
    					break;
    				}
    			}
    			int x=0;
    			while(!arrays.get(x).name.equals(arrayNamed)) {
    				x++;
    			}
    			int[] Arrayd;
    			Arrayd=arrays.get(x).values;
    			guide=guidesave;
    			guide++;
    			while(bCounter!=0) {
    				search=Express.charAt(guide);
    				if (search==']') {
    					bCounter--;
    				}
    				if (search=='[') {
    					bCounter++;
    				}
    				total+=search;
    				guide++;
    			}
    			evaluateString(total.substring(0, total.length()-1));
    			int funny=(int)(evaluateString(total.substring(0, total.length()-1)));
    			ArraySymbol a = new ArraySymbol(arrayNamed);
    			int b= arrays.get(arrays.indexOf(a)).values[funny];
    			backString=Express.substring(guide, Express.length());
    			Express=frontStringSave+b+backString;
    			Express=Express.replaceFirst(arrayNamed, "");
    			System.out.println(Express);
    			length=Express.length();
    			guide=-1;
    			total="";
    			
    			
    		}
    		guide++;
    	}
    	length=Express.length();
    	Stack <Float> numbers=new Stack<Float>();
    	Stack <Character> operators = new Stack<Character>();
    	Stack <Float> revnumbers=new Stack<Float>();
    	Stack <Character> revoperators = new Stack<Character>();
    	float result=0;
    	StringTokenizer stk = new StringTokenizer(Express, delims);
    	while(stk.hasMoreTokens()){
    	float added=Integer.parseInt(stk.nextToken());
    	numbers.push(added);
    	}
    	guide=1;
    	while (guide<length) {
    		search=Express.charAt(guide-1);
    		backup=Express.charAt(guide);
    		if (backup=='*'||backup=='+'||backup=='-'||backup=='/') {
    			if (backup=='+'&&search=='-') {
    			operators.push('-');
    			operators.pop();
    		}else if (backup=='-'&&search=='-') {
    			operators.push('+');
    			operators.pop();
    		}else {
    			operators.push(backup);
    		}
    		}
    		guide++;
    	}
    	while(!operators.isEmpty()) {
    		revoperators.push(operators.pop());
    	}
    	while(!numbers.isEmpty()) {
    		revnumbers.push(numbers.pop());
    	}
    	guide=0;
    	total="";
    	
    	while(revoperators.size()>1) {
    		float first=revnumbers.pop();
    		float second=revnumbers.pop();
    		float third=revnumbers.pop();
    		char firstchar=revoperators.pop();
    		char secondchar=revoperators.pop();
    			if (firstchar=='*') {
    				revnumbers.push(third);
    				revoperators.push(secondchar);
    				revnumbers.push(first*second);
    			}
    			if (firstchar=='/') {
    				revnumbers.push(third);
    				revoperators.push(secondchar);
    				revnumbers.push(first/second);
    			} 			
    			if ((firstchar=='+'&&secondchar=='*')||(firstchar=='-'&&secondchar=='*')) {
    				revoperators.push(firstchar);
    				revnumbers.push(second*third);
    				revnumbers.push(first);
    			} 	
    			if ((firstchar=='+'&&secondchar=='/')||(firstchar=='-'&&secondchar=='/')) {
    				revoperators.push(firstchar);
    				revnumbers.push(second/third);
    				revnumbers.push(first);
    			}
    			if ((firstchar=='+'&&secondchar=='+')||(firstchar=='+'&&secondchar=='-')) {
    				revnumbers.push(third);
    				revoperators.push(secondchar);
    				revnumbers.push(first+second);
    			} 
    			if ((firstchar=='-'&&secondchar=='+')||(firstchar=='-'&&secondchar=='-')) {
    				revnumbers.push(third);
    				revoperators.push(secondchar);
    				revnumbers.push(first-second);
    			}
       	}
    	
    	if (!revoperators.isEmpty()) {
    		if (revoperators.peek()=='-'&& revnumbers.size()==1) {
    		revoperators.pop();
    		return (-1*revnumbers.pop());
    	}
    	}
    	if (revoperators.size()==1) {
    		
    		float first=revnumbers.pop();
    		float second=revnumbers.pop();
    		char thingy=revoperators.pop();
    		switch(thingy) {
            case '+':
            	revnumbers.push(first+second);
            	break;
            case '-':
            	revnumbers.push(first-second);
            	break;
            case '/':
            	revnumbers.push(first/second);
            	break;
            case '*':
            	revnumbers.push(first*second);
            	break;
            default:
            	break;
    		}
    	}
    	if(revnumbers.size()==1);{
    		result=revnumbers.pop();
    	}
    	  	
		return result;
	}


	/**
     * Utility method, prints the symbols in the scalars list
     */
    public void printScalars() {
        for (ScalarSymbol ss: scalars) {
            System.out.println(ss);
        }
    }
    
    /**
     * Utility method, prints the symbols in the arrays list
     */
    public void printArrays() {
    		for (ArraySymbol as: arrays) {
    			System.out.println(as);
    		}
    }

}
