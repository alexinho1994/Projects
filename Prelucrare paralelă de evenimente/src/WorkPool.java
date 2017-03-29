package temaApd;

import java.util.LinkedList;

public class WorkPool {
	int nThreads; // nr total de thread-uri worker
	int nWaiting = 0; // nr de thread-uri worker care sunt blocate asteptand un task
	public boolean ready = false; // daca s-a terminat complet rezolvarea problemei 
	int reps;
	
	LinkedList<Event> tasks = new LinkedList<Event>();

	public WorkPool(int nThreads, int reps) {
		this.nThreads = nThreads;
		this.reps = reps;
	}

	
	public synchronized Event getWork() {
		if (tasks.size() == 0) { // workpool gol
			nWaiting++;
			
			if (reps == 0) {
				ready = true;
				
				notifyAll();
				return null;
			} else {
				while (!ready && tasks.size() == 0) {
					try {
						this.wait();
					} catch(Exception e) {e.printStackTrace();}
				}
				
				if (ready)
				    /* s-a terminat prelucrarea */
				    return null;

				nWaiting--;
				
			}
		}
		reps--;
		return tasks.remove();

	}


	
	synchronized void putWork(Event sp) {
		tasks.add(sp);
		/* anuntam unul dintre workerii care asteptau */
		this.notify();

	}


}
