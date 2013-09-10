/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */


package dracula;
import dracula.Move;
import dracula.PlayerEnum;

public interface Player {

   public void move (Move m);
   public PlayerEnum whoAmI();
   public Location whereAmI();

   public int health();
}