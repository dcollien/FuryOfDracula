/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */
package example;

public enum PlayerEnum {
   G(PlayerType.Hunter),
   S(PlayerType.Hunter),
   H(PlayerType.Hunter),
   M(PlayerType.Hunter),
   D(PlayerType.Dracula);

   private final PlayerType type;
   private PlayerEnum(PlayerType p) {this.type = p;}

   public static PlayerEnum convert(String s) {
      if (s.toLowerCase().equals("G")) {
         return PlayerEnum.G;
      } else if (s.toLowerCase().equals("S")) {
         return PlayerEnum.S;
      } else if (s.toLowerCase().equals("H")) {
         return PlayerEnum.H;
      } else if (s.toLowerCase().equals("M")) {
         return PlayerEnum.M;
      } else if (s.toLowerCase().equals("D")) {
         return PlayerEnum.D;
      }
      return PlayerEnum.D;
   }

   public boolean isDracula(){return this.type.equals(PlayerType.Dracula);};
   public boolean isHunter(){return this.type.equals(PlayerType.Hunter);};

   public String toString() {
      if (this.type.equals(PlayerEnum.G)) {
         return "G";
      } else if (this.type.equals(PlayerEnum.S)) {
         return "S";
      } else if (this.type.equals(PlayerEnum.H)) {
         return "H";
      } else if (this.type.equals(PlayerEnum.M)) {
         return "M";
      } else if (this.type.equals(PlayerEnum.D)) {
         return "D";
      }
      return "";
   }

   private enum PlayerType {
      Hunter,
      Dracula;
   }
}

