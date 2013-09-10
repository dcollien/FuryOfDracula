/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */

package example;

import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;

import example.Player;
import example.PlayerFactory;

public class View {
   private List<Player> players;
   private int move;

   public View(String past_moves, String[] messages) {
      players = new ArrayList<Player>();

      for (PlayerEnum e : PlayerEnum.values()) {
         players.add(PlayerFactory.getPlayer(e, this));
      }

      int i = 0;
      for (String s : past_moves.split(" ")) {
         Move m = new Move(s);
         for (Player p : players) {
            if (p.whoAmI() == m.owner()) {
               p.move(m);
            }
            if (p.whoAmI().isDracula()) {
               move++;
//               if m.wasVampPlaced
            }
         }
      }
   }

   public Location whereIsDracula() {
      Location drac = null;
      for (Player p : players) {
         if (p.whoAmI().isDracula()) {
            drac = p.whereAmI();
         }
      }
      return drac;
   }

   public List<Location> whereAreHunters() {
      List<Location> hunters = new ArrayList<Location>();
      for (Player p : players) {
         if (p.whoAmI().isHunter()) {
            hunters.add(p.whereAmI());
         }
      }
      return hunters;
   }

   public int moveNumber () {
      return move;
   }

}