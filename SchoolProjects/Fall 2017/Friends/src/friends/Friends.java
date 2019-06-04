package friends;

import structures.Queue;
import structures.Stack;

import java.io.File;
import java.util.*;

public class Friends {

	/**
	 * Finds the shortest chain of people from p1 to p2.
	 * Chain is returned as a sequence of names starting with p1,
	 * and ending with p2. Each pair (n1,n2) of consecutive names in
	 * the returned chain is an edge in the graph.
	 * 
	 * @param g Graph for which shortest chain is to be found.
	 * @param p1 Person with whom the chain originates
	 * @param p2 Person at whom the chain terminates
	 * @return The shortest chain from p1 to p2. Null if there is no
	 *         path from p1 to p2
	 */
	public static ArrayList<String> shortestChain(Graph g, String p1, String p2) {
		int counter=0;
		while(counter<g.members.length) {
			String Check=g.members[counter].name;
			if(Check.contains(p1)) {
				break;
			}
			counter++;
		}
		Person Person1=g.members[counter];
		if(counter==g.members.length) {
			return null;
		}
		counter=0;
		while(counter<g.members.length) {
			String Check=g.members[counter].name;
			if(Check.contains(p2)) {
				break;
			}
			counter++;
		}
		Person Person2=g.members[counter];
		if(counter==g.members.length) {
			return null;
		}
		//Setting up persons
		
		ArrayList<String> fun = new ArrayList<String>();
		Friend sonny= Person1.first;
		fun.add(Person1.name);
		counter=0;
		Queue total = new Queue();
		Queue backup = new Queue();
		ArrayList<String> gone = new ArrayList<String>();
		Queue numbers= new Queue();
		gone.add(Person1.name);
		Map<String, String> parentNodes;
		ArrayList<ArrayList<String>> froyo= new ArrayList<ArrayList<String>>();
		Friend plus=null;
		while(sonny!=null) {
			ArrayList funk= new ArrayList();
			
			if(g.members[sonny.fnum]==Person2) {
				if(plus!=null) {
					fun.add(g.members[plus.fnum].name);
				}
				fun.add(g.members[sonny.fnum].name);
				break;
			}
			if(!gone.contains(g.members[sonny.fnum].name)) {
				total.enqueue(sonny);
				gone.add(g.members[sonny.fnum].name);
				funk.add(g.members[sonny.fnum].name);
			}
			
			sonny=sonny.next;
			froyo.add(funk);
			while (sonny==null) {
				if (total.isEmpty()) {
					break;
				}
				
				plus=(Friend)total.dequeue();
				sonny=g.members[plus.fnum].first;
				System.out.println("b");
				
			}
		}
		System.out.println("got");
		if (fun.size()==1) {
			return null;
		}
		System.out.println(gone);
		System.out.println(fun);
		return fun;
	}

	/**
	 * Finds all cliques of students in a given school.
	 * 
	 * Returns an array list of array lists - each constituent array list contains
	 * the names of all students in a clique.
	 * 
	 * @param g Graph for which cliques are to be found.
	 * @param school Name of school
	 * @return Array list of clique array lists. Null if there is no student in the
	 *         given school
	 */
	public static ArrayList<ArrayList<String>> cliques(Graph g, String school) {
		int counter=0;
		boolean baby=false;
		ArrayList<ArrayList<String>> full= new ArrayList<ArrayList<String>>();
		ArrayList fun= new ArrayList<String>();
		while(counter<g.members.length) {
			String Check=g.members[counter].school;
			if (!g.members[counter].student) {

			}else if(Check.contains(school)) {
				fun.add(g.members[counter]);
			}	
			counter++;
		}


		while(!fun.isEmpty()) {
			Person fred=(Person) fun.get(0);
			ArrayList enroll= new ArrayList<String>();
			enroll.add(fred.name);
			fun.remove(0);
			Friend son=fred.first;
			Friend daughter=son;
			while(son!=null) {
				if(fun.contains(g.members[son.fnum])) {
					enroll.add(g.members[son.fnum].name);
					fun.remove(g.members[son.fnum]);
					daughter=son;
					baby=true;
					son=g.members[son.fnum].first;
					continue;
				}
				if(baby) {
					son=daughter;
					baby=false;

				}
				son=son.next;
			}

			full.add(enroll);
		}
		System.out.println(full);
		return full;

	}

	/**
	 * Finds and returns all connectors in the graph.
	 * 
	 * @param g Graph for which connectors needs to be found.
	 * @return Names of all connectors. Null if there are no connectors.
	 */
	public static ArrayList<String> connectors(Graph g) {
		ArrayList connect= new ArrayList<String>();
		for(int counter =0; counter<g.members.length ; counter++) {
			String Name=g.members[g.members[counter].first.fnum].name;
			if(g.members[counter].first.next==null&&!connect.contains(Name)) {
				connect.add(Name);
			}		
		}
		System.out.println(connect);
		if (connect.isEmpty()) {
			return null;
		}
		return connect;
	}
}

