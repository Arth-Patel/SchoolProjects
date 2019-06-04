package trie;

import java.util.ArrayList;

/**
 * This class implements a Trie. 
 * 
 * @author Sesh Venugopal
 *
 */
public class Trie {

	// prevent instantiation
	private Trie() { }

	/**
	 * Builds a trie by inserting all words in the input array, one at a time,
	 * in sequence FROM FIRST TO LAST. (The sequence is IMPORTANT!)
	 * The words in the input array are all lower case.
	 * 
	 * @param allWords Input array of words (lowercase) to be inserted.
	 * @return Root of trie with all words inserted from the input array
	 */
	public static TrieNode buildTrie(String[] allWords) {
		/** COMPLETE THIS METHOD **/
		if(allWords.length==0) {
			TrieNode root=new TrieNode(null,null,null);
			return root;
		}
		int x=allWords.length;
		short counter=0;

		short length=(short)(allWords[counter].length());
		Indexes blahIndex= new Indexes(counter,(short)0,(short)(length-1)); 
		TrieNode blah = new TrieNode(blahIndex,null,null);
		TrieNode root=new TrieNode(null,blah,null);
		counter=1;
		TrieNode ptr=root.firstChild;
		boolean startOver=false;
		TrieNode prev=null;
		short charCounter=0;

		while(counter!=x) {
			while(true) {
				System.out.println(counter);
				Trie.print(root,allWords);
				if (allWords[ptr.substr.wordIndex].charAt(charCounter)==allWords[counter].charAt(charCounter)) {
						if (ptr.firstChild==null) {
							while(allWords[ptr.substr.wordIndex].charAt(charCounter)==allWords[counter].charAt(charCounter)) {
								charCounter++;
							}
							Indexes movedIndex=new Indexes(ptr.substr.wordIndex,charCounter,ptr.substr.endIndex);
							TrieNode movedDown=new TrieNode(movedIndex,null,null);
							movedDown.substr.startIndex=charCounter;
							Indexes friendIndex=new Indexes(counter,charCounter,(short)(allWords[counter].length()-1));
							TrieNode friend=new TrieNode(friendIndex,null,null);
							movedDown.sibling=friend;
							ptr.substr.endIndex=(short)(charCounter-1);
							ptr.firstChild=movedDown;
							break;
							
						}else{
							
							while(true) {
								charCounter=0;
								while(allWords[ptr.substr.wordIndex].charAt(charCounter)==allWords[counter].charAt(charCounter)) {
									charCounter++;
								}
							System.out.println(charCounter);
							System.out.println(ptr.substr.endIndex+1);
							if(charCounter==ptr.substr.endIndex+1) {
								System.out.println("better");
								ptr=ptr.firstChild;
								charCounter=0;
								while (true) {
									int locator=ptr.substr.startIndex;
									while(allWords[ptr.substr.wordIndex].charAt(locator)==allWords[counter].charAt(locator)) {
										charCounter++;
										locator++;
									}
									if (charCounter>0) {
										System.out.println("boom");
										startOver=true;
										break;
									}
									prev=ptr;
									ptr=ptr.sibling;
									if (ptr==null) {
										Indexes friendIndex=new Indexes(counter,prev.substr.startIndex,(short)(allWords[counter].length()-1));
										TrieNode friend=new TrieNode(friendIndex,null,null);
										prev.sibling=friend;
										break;
									}
									
								}
								if(startOver) {
									startOver=false;
									continue;
								}
								break;
							}else if(charCounter<(ptr.substr.endIndex+1)) {
								System.out.println("watch");
								Indexes movedIndex=new Indexes(ptr.substr.wordIndex,charCounter,ptr.substr.endIndex);
								TrieNode movedDown=new TrieNode(movedIndex,ptr.firstChild,null);
								movedDown.substr.startIndex=charCounter;
								Indexes friendIndex=new Indexes(counter,charCounter,(short)(allWords[counter].length()-1));
								TrieNode friend=new TrieNode(friendIndex,null,null);
								movedDown.sibling=friend;
								ptr.substr.endIndex=(short)(charCounter-1);
								ptr.firstChild=movedDown;
								break;
							}else {
								System.out.println("out");
								
								
								if(ptr.firstChild.firstChild!=null) {
									ptr=ptr.firstChild;
									System.out.println("FOUND");
									continue;
								}
								ptr=ptr.firstChild;
								Indexes movedIndex=new Indexes(ptr.substr.wordIndex,charCounter,ptr.substr.endIndex);
								TrieNode movedDown=new TrieNode(movedIndex,null,null);
								movedDown.substr.startIndex=charCounter;
								Indexes friendIndex=new Indexes(counter,charCounter,(short)(allWords[counter].length()-1));
								TrieNode friend=new TrieNode(friendIndex,null,null);
								movedDown.sibling=friend;
								ptr.substr.endIndex=(short)(charCounter-1);
								ptr.firstChild=movedDown;
								System.out.print(ptr.toString());
								
								break;
							}

							}
						}
						break;
				
			}else {
				prev=ptr;
				ptr=ptr.sibling;
				if (ptr==null) {
					Indexes friendIndex=new Indexes(counter,(short)0,(short)(allWords[counter].length()-1));
					TrieNode friend=new TrieNode(friendIndex,null,null);
					prev.sibling=friend;
					break;
				}
			}
			
		}	
			charCounter=0;
			ptr=root.firstChild;
			counter++;
		}
		
	
		
//		while (counter!=x) {
//			while(ptr!=null) {
//				if(allWords[ptr.substr.wordIndex].charAt(ptr.substr.startIndex)==allWords[counter].charAt(ptr.substr.startIndex)) {
//					sibling=false;
//					if(ptr.firstChild==null) {
//						birth=true;
//						break;
//					}else {
//						int location=ptr.substr.startIndex;
//						while(partCounter!=(ptr.firstChild.substr.endIndex-ptr.firstChild.substr.startIndex)) {
//							if (allWords[ptr.substr.wordIndex].charAt(ptr.substr.startIndex)==allWords[counter].charAt(ptr.substr.startIndex)) {
//								partCounter++;
//								location++;
//							}else {
//								System.out.println("cool");
//								break;
//								
//							}
//						}
//						prev=ptr;
//						ptr=ptr.firstChild;
//					}
//					
//				}else {
//					prev=ptr;
//					ptr=ptr.sibling;
//					sibling=true;
//					birth=false;
//				}
//				
//			}
//			if(sibling) {
//				length=(short)(allWords[counter].length());
//				blahIndex= new Indexes(counter,(short)0,(short)(length-1));
//				TrieNode next= new TrieNode(blahIndex,null,null);
//				prev.sibling=next;	
//			}else if(birth) {
//				otherPtr=root.firstChild;
//				while(otherPtr!=null) {
//					
//				}
//				Indexes moving=new Indexes(ptr.substr.wordIndex,ptr.substr.startIndex,(short)(charCounter-1));
//				ptr.substr.startIndex=charCounter;
//				TrieNode movedDown=new TrieNode(moving,)
//				TrieNode next= new TrieNode(Replace,null,null);
//				movedDown.sibling=next;
//			}else {
//				
//			}
//			sibling=false;
//			birth=false;
//			ptr=root.firstChild;
//			counter++;
//		}
		
		
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

//		while(counter!=x) {
//			while(otherPtr!=null) {
//				if(allWords[otherPtr.substr.wordIndex].charAt(otherPtr.substr.startIndex)==allWords[counter].charAt(otherPtr.substr.startIndex)) {
//					if(otherPtr.firstChild==null) {
//						match=true;
//						System.out.println(allWords[counter]);
//						break;
//					}else {
//						System.out.println("GOTTEM COACH");
//						prev=otherPtr;
//						otherPtr=otherPtr.firstChild;
//					}
//				}else {
//					prev=otherPtr;
//					otherPtr=otherPtr.sibling;
//				}
//			}if (match) {
//				while(true) {
//					if (allWords[otherPtr.substr.wordIndex].substring(otherPtr.substr.startIndex).charAt(charCounter)!=allWords[counter].charAt(charCounter)) {
//						System.out.println("WHY WHY ");
//						break;
//					}
//					charCounter++;
//				}
//				charCounter+=otherPtr.substr.startIndex;
//				System.out.println(charCounter);
//				length=(short)(allWords[counter].length());
//				Indexes Replace= new Indexes(counter,(short)(charCounter),(short)(length-1));
//				System.out.println("child created"+ allWords[counter]);
//				if(otherPtr.substr.startIndex!=0) {
//					charCounter++;
//				}
//				if (otherPtr.firstChild==null) {	
//					//first child
//					
//					Indexes tempIndex=new Indexes(otherPtr.substr.wordIndex,(short)otherPtr.substr.startIndex,(short)(charCounter-1));
//					TrieNode temp= new TrieNode(tempIndex,otherPtr,otherPtr.sibling);
//					if(root.firstChild==otherPtr) {
//						root.firstChild=temp;
//					}
//					if (prev==null) {
//						System.out.println("Boom BAM");
//						prev=otherPtr;
//					}
//					if (prev.firstChild!=null) {
//						System.out.println("Boom");
//					}
//					prev.substr.startIndex=charCounter;
//					prev.sibling=temp;
//					otherPtr.substr.startIndex=(short)charCounter;
//					TrieNode next= new TrieNode(Replace,null,null);
//					otherPtr.sibling=next;
//					 
//				}else{
//					System.out.println("here boss");
//					otherPtr=otherPtr.firstChild;
//					while(otherPtr.sibling!=null) {
//						otherPtr=otherPtr.sibling;
//					}
//					TrieNode next= new TrieNode(Replace,null,null);
//					otherPtr.sibling=next;
//				
//				}
//			}else {
//				length=(short)(allWords[counter].length());
//				blahIndex= new Indexes(counter,(short)prev.substr.startIndex,(short)(length-1));
//				TrieNode next= new TrieNode(blahIndex,null,null);
//				prev.sibling=next;
//				System.out.println("sibling created" +allWords[counter] );
//			}
//			otherPtr=root.firstChild;
//			System.out.println(allWords[counter]); 
//			Trie.print(root, allWords);
//			charCounter=0;
//			counter++;
//			match=false;
//		}


		// FOLLOWING LINE IS A PLACEHOLDER TO ENSURE COMPILATION
		// MODIFY IT AS NEEDED FOR YOUR IMPLEMENTATION
		return root;
	}

	/**
	 * Given a trie, returns the "completion list" for a prefix, i.e. all the leaf nodes in the 
	 * trie whose words start with this prefix. 
	 * For instance, if the trie had the words "bear", "bull", "stock", and "bell",
	 * the completion list for prefix "b" would be the leaf nodes that hold "bear", "bull", and "bell"; 
	 * for prefix "be", the completion would be the leaf nodes that hold "bear" and "bell", 
	 * and for prefix "bell", completion would be the leaf node that holds "bell". 
	 * (The last example shows that an input prefix can be an entire word.) 
	 * The order of returned leaf nodes DOES NOT MATTER. So, for prefix "be",
	 * the returned list of leaf nodes can be either hold [bear,bell] or [bell,bear].
	 *
	 * @param root Root of Trie that stores all words to search on for completion lists
	 * @param allWords Array of words that have been inserted into the trie
	 * @param prefix Prefix to be completed with words in trie
	 * @return List of all leaf nodes in trie that hold words that start with the prefix, 
	 * 			order of leaf nodes does not matter.
	 *         If there is no word in the tree that has this prefix, null is returned.
	 */
	public static ArrayList<TrieNode> completionList(TrieNode root,
			String[] allWords, String prefix) {
		ArrayList<TrieNode> total= new ArrayList<TrieNode>();
		ArrayList<TrieNode> fathers= new ArrayList<TrieNode>();
		int charValue=0;
		String value = "a";
		TrieNode ptr=root.firstChild;
		//lol no prefix
		if	(prefix.length()==0) {
			while(charValue!=27) {
			charValue = value.charAt(0);
			if (completionList(root,allWords,value)!=null){
				total.addAll(completionList(root,allWords,value));
			}
			value = String.valueOf( (char) (charValue + 1));
			}
			return total;
		}
		if (ptr==null) {
			return null;
			
		}
		int length=prefix.length();
		while(ptr!=null) {
			if(prefix.charAt(0)==allWords[ptr.substr.wordIndex].charAt(0)) {
				if(ptr.firstChild!=null) {
					ptr=ptr.firstChild;
				}else {
					if (allWords[ptr.substr.wordIndex].substring(0,length).contains(prefix)){
						total.add(ptr);
						return total;
					}
					return null;
				}

				while(ptr!=null) {
					if (allWords[ptr.substr.wordIndex].substring(0,Math.min(length,ptr.substr.endIndex+1)).contains(prefix.substring(0,Math.min(length,ptr.substr.endIndex+1)))){
						if(ptr.firstChild!=null) {
							fathers.add(ptr);
						}else {
							total.add(ptr);
						}

						
					}
					ptr=ptr.sibling;
				}
				break;
			}else {
				ptr=ptr.sibling;
			}

		}
		while(!fathers.isEmpty()) {
			ptr=fathers.remove(0);
			ptr=ptr.firstChild;
			while(ptr!=null) {
				System.out.println(allWords[ptr.substr.wordIndex]);
				if (!allWords[ptr.substr.wordIndex].substring(0,Math.min(length,ptr.substr.endIndex+1)).contains(prefix.substring(0,Math.min(length,ptr.substr.endIndex+1)))){
					ptr=ptr.sibling;
					continue;
				}
				if (ptr.firstChild!=null) {
					fathers.add(ptr);
				}else {
					total.add(ptr);
				}
				ptr=ptr.sibling;
					
			}
		}
		System.out.println("broke5");
		if (total.isEmpty()) {
			return null;
		}
		return total;
	}

	
	
	
	public static void print(TrieNode root, String[] allWords) {
		System.out.println("\nTRIE\n");
		print(root, 1, allWords);
	}

	private static void print(TrieNode root, int indent, String[] words) {
		if (root == null) {
			return;
		}
		for (int i=0; i < indent-1; i++) {
			System.out.print("    ");
		}

		if (root.substr != null) {
			String pre = words[root.substr.wordIndex]
					.substring(0, root.substr.endIndex+1);
			System.out.println("      " + pre);
		}

		for (int i=0; i < indent-1; i++) {
			System.out.print("    ");
		}
		System.out.print(" ---");
		if (root.substr == null) {
			System.out.println("root");
		} else {
			System.out.println(root.substr);
		}

		for (TrieNode ptr=root.firstChild; ptr != null; ptr=ptr.sibling) {
			for (int i=0; i < indent-1; i++) {
				System.out.print("    ");
			}
			System.out.println("     |");
			print(ptr, indent+1, words);
		}
	}
}
