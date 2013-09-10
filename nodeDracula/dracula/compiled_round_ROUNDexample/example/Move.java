/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */

package example;

import example.DraculaMove;
import example.PlayerEnum;

public class Move extends DraculaMove {

   private PlayerEnum player;
   private String asString;

   public Location location;
   public boolean wasTrapEncountered;
   public boolean wasVampireEncountered;
   public boolean wasDraculaFound;
   public boolean wasCityMove;
   public boolean wasSeaMove;
   public boolean wasHideMove;
   public boolean wasDoubleBack;
   public boolean wasTeleportMove;
   public boolean isMoveKnown;
   public boolean wasTrapLaid;
   public boolean wasVampPlaced;
   public boolean didTrapLeaveTrail;
   public boolean didVampMature;
   public int doubleBackLength;

   public Move(PlayerEnum player, Location location) {
      this.player = player;
      this.location = location;
   }

   public Move(String s) {
      player = PlayerEnum.convert(s.charAt(0) + "");
      if (player.isDracula()) {

         wasCityMove = (s.charAt(1) + s.charAt(2) + "").equals("C?");
         wasSeaMove = (s.charAt(1) + s.charAt(2) + "").equals("S?");
         wasHideMove = (s.charAt(1) + s.charAt(2) + "").equals("HI");
         wasDoubleBack = (s.charAt(1) + s.charAt(2) + "").equals("Dn");
         wasTeleportMove = (s.charAt(1) + s.charAt(2) + "").equals("TP");
         isMoveKnown = !(wasCityMove || wasSeaMove || wasHideMove || wasDoubleBack || wasTeleportMove);
         if (!isMoveKnown) {
            location = Location.get(s.charAt(0) + s.charAt(1) + "");
         }
         wasTrapEncountered = (s.charAt(3) == 'T');
         wasVampPlaced = (s.charAt(4) == 'V');
         didTrapLeaveTrail = (s.charAt(5) == 'M');
         didVampMature = (s.charAt(5) == 'V');

      } else {
         location = Location.get(s.charAt(0) + s.charAt(1) + "");
         wasTrapEncountered = (s.charAt(2) == 'T');
         wasVampireEncountered = (s.charAt(2) == 'V');
         wasDraculaFound = (s.charAt(2) == 'D');
      }
   }

   public String getPlayAsString() {
      return this.toString();
   }

   public String toString() {
      String result = "";
      result += player.toString();
      if (player.isDracula()) {
         result += location.toString();
         result += "....";
      } else {
         result += location.toString();
         if (wasTrapEncountered)          result += "T";
         else if (wasVampireEncountered)  result += "V";
         else if (wasDraculaFound)        result += "D";
         else                             result += ".";
         result += "...";
      }
      return result;
   }

   public PlayerEnum owner() {
      return player;
   }
}
