package lse;

import java.io.*;
import java.util.*;

import javax.print.attribute.DocAttributeSet;

/**
 * This class builds an index of keywords. Each keyword maps to a set of pages in
 * which it occurs, with frequency of occurrence in each page.
 *
 */
public class LittleSearchEngine {

	/**
	 * This is a hash table of all keywords. The key is the actual keyword, and the associated value is
	 * an array list of all occurrences of the keyword in documents. The array list is maintained in 
	 * DESCENDING order of frequencies.
	 */
	HashMap<String,ArrayList<Occurrence>> keywordsIndex;
	
	/**
	 * The hash set of all noise words.
	 */
	HashSet<String> noiseWords;
	
	/**
	 * Creates the keyWordsIndex and noiseWords hash tables.
	 */
	public LittleSearchEngine() {
		keywordsIndex = new HashMap<String,ArrayList<Occurrence>>(1000,2.0f);
		noiseWords = new HashSet<String>(100,2.0f);
	}
	
	/**
	 * Scans a document, and loads all keywords found into a hash table of keyword occurrences
	 * in the document. Uses the getKeyWord method to separate keywords from other words.
	 * 
	 * @param docFile Name of the document file to be scanned and loaded
	 * @return Hash table of keywords in the given document, each associated with an Occurrence object
	 * @throws FileNotFoundException If the document file is not found on disk
	 */
	public HashMap<String,Occurrence> loadKeywordsFromDocument(String docFile) 
			throws FileNotFoundException {
		HashMap<String,Occurrence> funk = new HashMap<String, Occurrence>();
		Scanner sc = new Scanner(new File(docFile));
		while(sc.hasNext()){
			String next = sc.next();
			next=getKeyword(next);
			if (next==null) {
				continue;
			}
			if( funk.get(next)==null) {		
				Occurrence brand=new Occurrence(docFile,1);
				funk.put(next,brand);
			}else {
				funk.get(next).frequency++;
			}
		}
		return funk;
	}

	/**
	 * Merges the keywords for a single document into the master keywordsIndex
	 * hash table. For each keyword, its Occurrence in the current document
	 * must be inserted in the correct place (according to descending order of
	 * frequency) in the same keyword's Occurrence list in the master hash table. 
	 * This is done by calling the insertLastOccurrence method.
	 * 
	 * @param kws Keywords hash table for a document
	 */
	public void mergeKeywords(HashMap<String,Occurrence> kws) {
		Object[] jd =kws.keySet().toArray();
		int count=0;
		while(count<kws.size()) {
			ArrayList<Occurrence> list=new ArrayList<Occurrence>();
			list.add(list.size(),kws.get(jd[count]));
			if(keywordsIndex.containsKey(jd[count].toString())) {
				keywordsIndex.get(jd[count].toString()).add(kws.get(jd[count]));
				insertLastOccurrence(keywordsIndex.get(jd[count].toString()));			
			}else {
				keywordsIndex.put(jd[count].toString(),list);
			}
			count++;
		}
		return;
	}

	/**
	 * Given a word, returns it as a keyword if it passes the keyword test,
	 * otherwise returns null. A keyword is any word that, after being stripped of any
	 * trailing punctuation, consists only of alphabetic letters, and is not
	 * a noise word. All words are treated in a case-INsensitive manner.
	 * 
	 * Punctuation characters are the following: '.', ',', '?', ':', ';' and '!'
	 * 
	 * @param word Candidate word
	 * @return Keyword (word without trailing punctuation, LOWER CASE)
	 */
	public String getKeyword(String word) {
		String trimmed=word.trim().toLowerCase();
		int counter=0;
		while (!Character.isLetter(trimmed.charAt(trimmed.length()-1))) {
			trimmed=trimmed.substring(0,trimmed.length() -1);
			if (trimmed.length()==0) {
				return null;
			}
		}
		while(counter<trimmed.length()) {
			if (!Character.isLetter(trimmed.charAt(counter))) {
				return null;
			}
			counter++;
		}
		counter=0;
		if (noiseWords.contains(trimmed)) {
			return null;
		}
		return trimmed;
	}

	/**
	 * Inserts the last occurrence in the parameter list in the correct position in the
	 * list, based on ordering occurrences on descending frequencies. The elements
	 * 0..n-2 in the list are already in the correct order. Insertion is done by
	 * first finding the correct spot using binary search, then inserting at that spot.
	 * 
	 * @param occs List of Occurrences
	 * @return Sequence of mid point indexes in the input list checked by the binary search process,
	 *         null if the size of the input list is 1. This returned array list is only used to test
	 *         your code - it is not used elsewhere in the program.
	 */
	public ArrayList<Integer> insertLastOccurrence(ArrayList<Occurrence> occs) {
		if(occs.size()<2) {
			return null;
		}
		ArrayList<Integer> finale = new ArrayList<Integer>();
		int movement=occs.size();
		Occurrence place =occs.get(movement-1);
		occs.remove(movement-1);
		int lo=0;
		int hi=occs.size()-1;
		int mid=0;
		while(lo<=hi) {
			mid=(lo+hi)/2;
			finale.add(mid);
			if (place.frequency==occs.get(mid).frequency) {
				break;
			}else if(place.frequency<occs.get(mid).frequency) {
				lo=mid+1;
			}else {
				hi=mid-1;
			}
		}
		if(place.frequency<occs.get(mid).frequency) {
			occs.add(mid+1, place);
		}else {
			occs.add(mid, place);
		}
		return finale;
	}
	
	/**
	 * This method indexes all keywords found in all the input documents. When this
	 * method is done, the keywordsIndex hash table will be filled with all keywords,
	 * each of which is associated with an array list of Occurrence objects, arranged
	 * in decreasing frequencies of occurrence.
	 * 
	 * @param docsFile Name of file that has a list of all the document file names, one name per line
	 * @param noiseWordsFile Name of file that has a list of noise words, one noise word per line
	 * @throws FileNotFoundException If there is a problem locating any of the input files on disk
	 */
	public void makeIndex(String docsFile, String noiseWordsFile) 
	throws FileNotFoundException {
		// load noise words to hash table
		Scanner sc = new Scanner(new File(noiseWordsFile));
		while (sc.hasNext()) {
			String word = sc.next();
			noiseWords.add(word);
		}
		
		// index all keywords
		sc = new Scanner(new File(docsFile));
		while (sc.hasNext()) {
			String docFile = sc.next();
			HashMap<String,Occurrence> kws = loadKeywordsFromDocument(docFile);
			mergeKeywords(kws);
		}
		System.out.println(keywordsIndex);
		sc.close();
	}
	
	/**
	 * Search result for "kw1 or kw2". A document is in the result set if kw1 or kw2 occurs in that
	 * document. Result set is arranged in descending order of document frequencies. (Note that a
	 * matching document will only appear once in the result.) Ties in frequency values are broken
	 * in favor of the first keyword. (That is, if kw1 is in doc1 with frequency f1, and kw2 is in doc2
	 * also with the same frequency f1, then doc1 will take precedence over doc2 in the result. 
	 * The result set is limited to 5 entries. If there are no matches at all, result is null.
	 * 
	 * @param kw1 First keyword
	 * @param kw1 Second keyword
	 * @return List of documents in which either kw1 or kw2 occurs, arranged in descending order of
	 *         frequencies. The result size is limited to 5 documents. If there are no matches, returns null.
	 */
	public ArrayList<String> top5search(String kw1, String kw2) {
		int counter=0;
		int counter1=0;
		int counter2=0;
		String added="";
		ArrayList<String> documents=new ArrayList<String>();
		ArrayList<Occurrence> list1=keywordsIndex.get(kw1);
		boolean copied=false;
		
		ArrayList<Occurrence> list2=keywordsIndex.get(kw2);
		System.out.println(list1);
		System.out.println(list2);
		while(documents.size()<5) {
			if(list1.isEmpty()&&list2.isEmpty()) {
				break;
			}
			if(list1.isEmpty()) {
				added=list2.get(0).document;
				list2.remove(0);
			}else if(list2.isEmpty()) {
				added=list1.get(0).document;
				list1.remove(0);
			}else if(list1.get(0).frequency>=list2.get(0).frequency) {
				added=list1.get(0).document;
				list1.remove(0);
			}else {
				added=list2.get(0).document;
				list2.remove(0);
			}
			while(counter<documents.size()) {
				if (added==documents.get(counter)) {
					copied=true;
					break;
				}	
				counter++;
			}
			if(!copied) {
				documents.add(added);
			}
			copied=false;
			counter=0;

		}
		System.out.println(documents);
		return documents;

	}
}
