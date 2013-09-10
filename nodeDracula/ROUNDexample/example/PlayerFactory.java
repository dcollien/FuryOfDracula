/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  EDIT this file
 */

package example;

import example.Dracula;
import example.Damocula;
import example.Player;
import example.PlayerEnum;
import example.View;

public class PlayerFactory {

   public static Dracula getDracula(String pastPlays, String[] messages) {
      View d = new View(pastPlays, messages);
      return new Damocula( PlayerEnum.D, d );
   }

   public static Player getPlayer(PlayerEnum e, View v) {
      if (e.isDracula()) {
         return new Damocula(e, v);
      } else if (e.isHunter()) {
         return new Hunter(e, v);
      }
      return null;
   }
}
