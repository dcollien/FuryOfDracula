/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  EDIT this file
 */

package dracula;

import dracula.Dracula;
import dracula.Damocula;
import dracula.Player;
import dracula.PlayerEnum;
import dracula.View;

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
