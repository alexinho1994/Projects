import java.util.ArrayList;
import java.util.Random;


/**
 * BotStarter class
 * 
 * Magic happens here. You should edit this file, or more specifically
 * the makeTurn() method to make your bot do more than random moves.
 * 
 * @author Jim van Eeden <jim@starapple.nl>
 */

public class BotStarter {

    /**
     * Makes a turn. Edit this method to make your bot smarter.
     * Currently does only random moves.
     *
     * @return The column where the turn was made.
     */
	public Move makeTurn(Field field, int id) {
		Random r = new Random();
		ArrayList<Move> moves = field.getAvailableMoves();
		int n = moves.size();
		Move move=null;
		if(field.mMoveNr%2==0)
		{
			int min=99999;
			int score;
			for(Move m:moves)
			{
				score=Minimax.maxi(5, field.mBoard, field.mMacroboard, m, -200, 200);
				if(score<min)
				{
					min=score;
					move=m;
				}
			}
		}
		else
		{
			int max=-999999;
			
			int score;
			for(Move m:moves)
			{
				score=Minimax.mini(5, field.mBoard, field.mMacroboard, m, -200, 200);
				//System.out.println(score);
				if(score>max)
				{
					max=score;
					move=m;
				}
			}
			
		}
		if(move==null)
			move = moves.get(r.nextInt(n));
		return move;
	}


	public static void main(String[] args) {
		BotParser parser = new BotParser(new BotStarter());
		parser.run();
	}
}
