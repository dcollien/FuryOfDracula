/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */

package example;

import example.DraculaMove;
import example.Player;
import example.Move;
import example.PlayerEnum;
import example.View;
import example.Location;

public class Hunter implements Player {

   private PlayerEnum p;
   private int health;
   private View view;
   private Location loc;

   public Hunter(PlayerEnum p, View view) {
      this.view = view;
      this.p = p;
      assert(p.isHunter());
   }

   public void move (Move m) {
      loc = m.location;
   }

   public PlayerEnum whoAmI() {
      return PlayerEnum.D;
   }

   public Location whereAmI() {
      return loc;
   }

   public int health() {
      return health;
   }


}
