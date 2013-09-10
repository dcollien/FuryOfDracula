/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */

package example;

import java.util.List;
import java.util.ArrayList;

import example.DraculaMove;
import example.Move;
import example.PlayerEnum;
import example.Location;
import example.Dracula;
import example.Player;

public class Damocula implements Dracula, Player {

   private PlayerEnum p = PlayerEnum.D;
   private int health;
   private View view;
   private List<Location> past_places;
   private Location loc;

   Damocula(PlayerEnum p, View view) {
      this.view = view;
      past_places = new ArrayList<Location>();
      p = p;
      assert(p.isDracula());
   }

   public DraculaMove decideMove() {
      //TODO(damonkey): Stop being lazy and actually implement a decent implementation.
      //                Or at least choose randomly... <.<
      List<Location> possibleMoves = loc.adjacentCities();
      possibleMoves.addAll(loc.seaAdjacentCities());

      //Remove all illegal moves.
      while (past_places.contains(possibleMoves.get(0))) {
         past_places.remove(0);
      }

      //Make move.
      Move move = new Move(p, possibleMoves.get(0));
      return move;
   }


   public void move (Move m) {
      past_places.add(m.location);
      //TODO(damonkey): Deal with losing health etc. Could be useful..
      loc = m.location;
   }

   public PlayerEnum whoAmI() {
      return p;
   }

   public Location whereAmI() {
      return loc;
   }

   public int health() {
      return health;
   }
}

