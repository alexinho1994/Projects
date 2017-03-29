package temaApd;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.Vector;

public class Main {
	
	public static void main(String args[]) throws IOException
	{
		Vector coada = new Vector();
		Vector<Integer> prim = new Vector<Integer>();
		Vector<Integer> fib = new Vector<Integer>();
		Vector<Integer> fact = new Vector<Integer>();
		Vector<Integer> square = new Vector<Integer>();
		
		
		int size = Integer.parseInt(args[0]);
		int evenimente = Integer.parseInt(args[1]);
		int generatoare = args.length - 2;
		Generator generatoarev[] = new Generator[generatoare];
		int reps = evenimente * generatoare;
		
		WorkPool wp = new WorkPool(4, reps);
		
		for(int i = 0; i < generatoare; i++)
			generatoarev[i] = new Generator(evenimente, args[i+2], coada, size, wp);
		
		for(int i = 0; i < generatoare; i++)
			generatoarev[i].start();
		
		Workr w1 = new Workr(wp, prim, fib, fact, square);
		Workr w2 = new Workr(wp, prim, fib, fact, square);
		Workr w3 = new Workr(wp, prim, fib, fact, square);
		Workr w4 = new Workr(wp, prim, fib, fact, square);
		
		
		w1.start();
		w2.start();
		w3.start();
		w4.start();
		
		for(int i = 0; i < generatoare; i++)
		{
			try {
				generatoarev[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		try {
			w1.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	
		try {
			w2.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			w3.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			w4.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		Collections.sort(prim);
		Collections.sort(fib);
		Collections.sort(square);
		Collections.sort(fact);
		
		FileWriter out=new FileWriter("PRIME.out");
		for(int i = 0; i<prim.size(); i++)
			out.write((int) prim.get(i) + "\r\n");
		out.close();
		
		out=new FileWriter("FACT.out");
		for(int i = 0; i<fact.size(); i++)
			out.write(fact.get(i) + "" +"\r\n");
		out.close();
		
		out=new FileWriter("SQUARE.out");
		for(int i = 0; i<square.size(); i++)
			out.write(square.get(i) + "" +"\r\n");
		out.close();
		
		out=new FileWriter("FIB.out");
		for(int i = 0; i<fib.size(); i++)
		{
			out.write(fib.get(i) + "" +"\r\n");
		}
		out.close();
	}

}
