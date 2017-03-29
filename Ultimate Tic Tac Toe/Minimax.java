import java.util.ArrayList;

public class Minimax {
	
	int[][] mBoard;
	int[][] mMacroboard;
	private final static int COLS = 9;
	private static final int ROWS = 9;
	
	
	public Minimax()
	{
		
	}
	
	public static boolean gameOver(int[][] Board)
	{
		if(Board[0][0]==Board[0][1] && Board[0][1]==Board[0][2] && Board[0][0]>0)
		{
			
			return true;
		}
		if(Board[1][0]==Board[1][1] && Board[1][1]==Board[1][2] && Board[1][0]>0)
		{
		
			return true;
		}
		if(Board[2][0]==Board[2][1] && Board[2][1]==Board[2][2] && Board[2][0]>0)
		{
			
			return true;
		}
		if(Board[0][0]==Board[1][0] && Board[1][0]==Board[2][0] && Board[0][0]>0)
		{
			
			return true;
		}
		if(Board[0][1]==Board[1][1] && Board[1][1]==Board[2][1] && Board[0][1]>0)
		{
			
			return true;
		}
		if(Board[0][2]==Board[1][2] && Board[1][2]==Board[2][2] && Board[0][2]>0)
		{
			
			return true;
		}
		if(Board[0][0]==Board[1][1] && Board[1][1]==Board[2][2] && Board[0][0]>0)
		{
			
			return true;
		}
		if(Board[0][2]==Board[1][1] && Board[1][1]==Board[2][0] && Board[0][2]>0)
		{
			
			return true;
		}
		return false;
	}
	
	
	public static int evaluate(int[][] Board)
	{
		if(gameOver(Board))
		{
			if(Board[0][0]==Board[0][1] && Board[0][1]==Board[0][2])
			{
				if(Board[0][0]==1)
					return 20;
				else return -20;
			}
			if(Board[1][0]==Board[1][1] && Board[1][1]==Board[1][2])
			{
				if(Board[1][0]==1)
					return 20;
				else return -20;
			}
			if(Board[2][0]==Board[2][1] && Board[2][1]==Board[2][2])
			{
				if(Board[2][0]==1)
					return 20;
				else return -20;
			}
			if(Board[0][0]==Board[1][0] && Board[1][0]==Board[2][0])
			{
				if(Board[0][0]==1)
					return 20;
				else return -20;
			}			
			if(Board[0][1]==Board[1][1] && Board[1][1]==Board[2][1])
			{
				if(Board[0][1]==1)
					return 20;
				else return -20;
			}
			if(Board[0][2]==Board[1][2] && Board[1][2]==Board[2][2])
			{
				if(Board[0][2]==1)
					return 20;
				else return -20;
			}
			if(Board[0][0]==Board[1][1] && Board[1][1]==Board[2][2])
			{
				if(Board[0][0]==1)
					return 20;
				else return -20;
			}
			if(Board[0][2]==Board[1][1] && Board[1][1]==Board[2][0])
			{
				if(Board[0][2]==1)
					return 20;
				else return -20;
			}
		}
		int prim=0, doi=0;
		int i, j;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
			{
				if(Board[i][j]==1)
					prim++;
				if(Board[i][j]==2)
					doi++;
			}
		return prim-doi;
	}
	
	
	public static int maxi(int depth, int[][] mBoard, int[][] mMacroboard, Move move, int alpha, int beta)
	{
		int[][] Board = new int[COLS][ROWS];
		int[][] Macroboard = new int[COLS / 3][ROWS / 3];
		int i,j;
		
		for (i=0;i<COLS;i++)
			for(j=0;j<ROWS;j++)
				Board[i][j]=mBoard[i][j];
		for (i=0;i<COLS/3;i++)
			for(j=0;j<ROWS/3;j++)
				Macroboard[i][j]=mMacroboard[i][j];
		
		Board[move.getX()][move.getY()]=2;
		
		int [][]brd = new int[COLS/3][ROWS/3];
		for (i=0;i<COLS;i++)
			for(j=0;j<ROWS;j++)
				if(i/3==move.getX()/3 && j/3==move.getY()/3)
					brd[i%3][j%3]=Board[i][j];
		
		if(gameOver(brd))
		{
			Macroboard[move.getX()/3][move.getY()/3]=2;
		}
		
		if(Macroboard[move.getX()%3][move.getY()%3]<=0)
		{
			for (i=0;i<COLS/3;i++)
				for(j=0;j<ROWS/3;j++)
					if(Macroboard[i][j]==-1 || Macroboard[i][j]==0)
						Macroboard[i][j]=0;
			Macroboard[move.getX()%3][move.getY()%3]=-1;
		}
		else
			for (i=0;i<COLS/3;i++)
				for(j=0;j<ROWS/3;j++)
					if(Macroboard[i][j]==-1 || Macroboard[i][j]==0)
						Macroboard[i][j]=-1;	
		
		if(gameOver(Macroboard) || depth==0)
			return evaluate(Macroboard)*(depth+1);
		
		//int max=-99999;
		ArrayList<Move> moves = new ArrayList<Move>();
			
		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLS; x++) {
				if (Macroboard[(int) x/3][(int) y/3] == -1 && Board[x][y] == 0) {
	                moves.add(new Move(x, y));
	                }
	            }
	        }
		for(Move m : moves)
		{
			int score=mini(depth-1, Board, Macroboard, m, alpha, beta);
		//	System.out.println(score);
			if(score>=beta)
				return beta;
			if(score>alpha)
				alpha=score;
		}
		return alpha;
	}
	
	
	
	public static int mini(int depth, int[][] mBoard, int[][] mMacroboard, Move move, int alpha, int beta)
	{
		//System.out.println(depth);
		int[][] Board = new int[COLS][ROWS];
		int[][] Macroboard = new int[COLS / 3][ROWS / 3];
		int i,j;
		
		for (i=0;i<COLS;i++)
			for(j=0;j<ROWS;j++)
				Board[i][j]=mBoard[i][j];
		for (i=0;i<COLS/3;i++)
			for(j=0;j<ROWS/3;j++)
				Macroboard[i][j]=mMacroboard[i][j];
		
		Board[move.getX()][move.getY()]=1;
		
		int [][]brd = new int[COLS/3][ROWS/3];
		for (i=0;i<COLS;i++)
			for(j=0;j<ROWS;j++)
				if(i/3==move.getX()/3 && j/3==move.getY()/3)
					brd[i%3][j%3]=Board[i][j];
		
		if(gameOver(brd))
		{
			Macroboard[move.getX()/3][move.getY()/3]=1;
		}
		
		if(Macroboard[move.getX()%3][move.getY()%3]<=0)
		{
			for (i=0;i<COLS/3;i++)
				for(j=0;j<ROWS/3;j++)
					if(Macroboard[i][j]==-1 || Macroboard[i][j]==0)
						Macroboard[i][j]=0;
			Macroboard[move.getX()%3][move.getY()%3]=-1;
		}
		else
			for (i=0;i<COLS/3;i++)
				for(j=0;j<ROWS/3;j++)
					if(Macroboard[i][j]==-1 || Macroboard[i][j]==0)
						Macroboard[i][j]=-1;	
		/*for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
				System.out.print(Macroboard[i][j]+" ");
			System.out.println();
		}
		System.out.println();*/
		if(gameOver(Macroboard)==true || depth==0)
		{
			return evaluate(Macroboard)*(depth+1);
		}
		//System.out.println();
		//int min=99999;
		ArrayList<Move> moves = new ArrayList<Move>();
			
		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLS; x++) {
				if (Macroboard[x/3][y/3] == -1 && Board[x][y] == 0) {
	                moves.add(new Move(x, y));
	                }
	            }
	        }
		for(Move m : moves)
		{
			int score=maxi(depth-1, Board, Macroboard, m, alpha, beta);
			//System.out.println(score);
			if(score<=alpha)
				return alpha;
			if(score<beta)
				beta=score;
		}
		return beta;
	}
}
