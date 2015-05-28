import java.util.Scanner;
import java.util.*;
public class fact {
	public static void main(String[] args) {
		Map<Integer,testcase> TestCases = new HashMap<Integer, testcase>();
		Scanner console = new Scanner(System.in);
		int caseno = console.nextInt();
		console.nextLine();
		for(int currentcase = 1;currentcase<=caseno;currentcase++){
			String listLengths = console.nextLine();
			String listA = console.nextLine();
			String listB = console.nextLine();
			String listC = console.nextLine();
			testcase newCase = new testcase(listA, listB, listC);
			TestCases.put(currentcase, newCase);
		}
		for(int currentcase = 1;currentcase<=caseno;currentcase++){
			testcase currentCase = TestCases.get(currentcase);
			System.out.println("Case #" + currentcase +": " + currentCase.profact());
		}
	}

}
class testcase {
	Set<Integer> A, B, C = new HashSet<Integer>();
	int sizeA, sizeB, sizeC;
	public static int factorial(int input){
		if(input == 0){
			return 1;
		}else{
			return input*factorial(--input);
		}
	}
	public static int profact(Set<Integer> inputlist){
		int factorial = 0;
		for(Integer number : inputlist){
			factorial += factorial(number);
		}
		return factorial;
	}
	public int profact(String returnList){
		if(returnList == "a"){
			return profact(A);
		}else if(returnList == "b"){
			return profact(B);
		}else if(returnList == "c"){
			return profact(C);
		}
		return 0;
	}
	public String profact(){
		if(profact(A) == profact(B) || profact(B) == profact(C) || profact(A) == profact(C)){
			return "TIE";
		}
		if(profact(A) > profact(B)){
			if(profact(C) > profact(A)){
				// C A B
				return "C";
			}else if(profact(C) > profact(B)){
				// A C B
				return "A";
			}
			// A B C
			return "A";
		}else{
			if(profact(C) > profact(B)){
				// C B A
				return "C";
			}else if(profact(C) > profact(A)){
				// B C A
				return "B";
			}
			// B A C
			return "B";
		}
	}
	public static Set<Integer> StringToSet(String input){
		Set<Integer> output = new HashSet<Integer>();
		String[] input_exp=input.split(" ");
		for(String listLengthsItem : input_exp){
			output.add(Integer.parseInt(listLengthsItem));
		}
		return output;
	}
	public testcase(String aList, String bList, String cList){
		A = StringToSet(aList);
		B = StringToSet(bList);
		C = StringToSet(cList);
	}
}
