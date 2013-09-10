/**
 * Written for COMP9024 2013s2 at UNSW Kensington.
 * @author dstacey@cse.unsw.edu.au
 *
 *  DO NOT Provide to students
 */

package dracula;
import java.util.List;
import java.util.ArrayList;

public enum Location {

   JM("JM", "St Joseph & St Mary",  Size.none,  true,  false,  true,   false,  false),
   CD("CD", "Castle Dracula",       Size.none,  true,  false,  false,  true,   false),
   AL("AL", "Alicante",             Size.small, true,  true,   false,  false,  false),
   AM("AM", "Alicante",             Size.large, true,  true,   false,  false,  false),
   AT("AT", "Athens",               Size.large, true,  true,   false,  false,  false),
   BA("BA", "Barcelona",            Size.large, true,  true,   false,  false,  false),
   BI("BI", "Bari",                 Size.small, true,  true,   false,  false,  false),
   BE("BE", "Belgrade",             Size.small, true,  false,  false,  false,  false),
   BR("BR", "Berlin",               Size.large, true,  false,  false,  false,  false),
   BO("BO", "Bordeaux",             Size.large, true,  true,   false,  false,  false),
   BU("BU", "Brussels",             Size.small, true,  false,  false,  false,  false),
   BC("BC", "Bucharest",            Size.large, true,  false,  false,  false,  false),
   BD("BD", "Budapest",             Size.large, true,  false,  false,  false,  false),
   CA("CA", "Cadiz",                Size.large, true,  true,   false,  false,  false),
   CG("CG", "Cagliari",             Size.small, true,  true,   false,  false,  false),
   CF("CF", "Clermont Ferrand",     Size.small, true,  false,  false,  false,  false),
   CO("CO", "Cologne",              Size.large, true,  false,  false,  false,  false),
   CN("CN", "Constanta",            Size.large, true,  true,   false,  false,  false),
   DU("DU", "Dublin",               Size.small, true,  true,   false,  false,  false),
   ED("ED", "Edinburgh",            Size.large, true,  true,   false,  false,  false),
   FL("FL", "Florence",             Size.small, true,  false,  false,  false,  false),
   FR("FR", "Frankfurt",            Size.small, true,  false,  false,  false,  false),
   GA("GA", "Galatz",               Size.small, true,  false,  false,  false,  false),
   GW("GW", "Galway",               Size.small, true,  true,   false,  false,  false),
   GE("GE", "Geneva",               Size.small, true,  false,  false,  false,  false),
   GO("GO", "Genoa",                Size.large, true,  true,   false,  false,  false),
   GR("GR", "Granada",              Size.small, true,  false,  false,  false,  false),
   HA("HA", "Hamburg",              Size.large, true,  true,   false,  false,  false),
   KL("KL", "Klausenburg",          Size.small, true,  false,  false,  false,  false),
   LE("LE", "Le Havre",             Size.small, true,  true,   false,  false,  false),
   LI("LI", "Leipzig",              Size.large, true,  false,  false,  false,  false),
   LS("LS", "Lisbon",               Size.large, true,  true,   false,  false,  false),
   LV("LV", "Liverpool",            Size.large, true,  true,   false,  false,  false),
   LO("LO", "London",               Size.large, true,  true,   false,  false,  false),
   MA("MA", "Madrid",               Size.large, true,  false,  false,  false,  false),
   MN("MN", "Manchester",           Size.large, true,  false,  false,  false,  false),
   MR("MR", "Marseilles",           Size.large, true,  true,   false,  false,  false),
   MI("MI", "Milan",                Size.large, true,  false,  false,  false,  false),
   MU("MU", "Munich",               Size.large, true,  false,  false,  false,  false),
   NA("NA", "Nantes",               Size.large, true,  true,   false,  false,  false),
   NP("NP", "Naples",               Size.large, true,  true,   false,  false,  false),
   NU("NU", "Nuremburg",            Size.small, true,  false,  false,  false,  false),
   PA("PA", "Paris",                Size.large, true,  false,  false,  false,  false),
   PL("PL", "Plymouth",             Size.small, true,  true,   false,  false,  false),
   PR("PR", "Prague",               Size.large, true,  false,  false,  false,  false),
   RO("RO", "Rome",                 Size.large, true,  true,   false,  false,  false),
   SA("SA", "Salonica",             Size.small, true,  true,   false,  false,  false),
   SN("SN", "Santander",            Size.small, true,  true,   false,  false,  false),
   SR("SR", "Saragossa",            Size.small, true,  false,  false,  false,  false),
   SJ("SJ", "Sarajevo",             Size.small, true,  false,  false,  false,  false),
   SO("SO", "Sofia",                Size.small, true,  false,  false,  false,  false),
   ST("ST", "Strasbourg",           Size.small, true,  false,  false,  false,  false),
   SW("SW", "Swansea",              Size.small, true,  true,   false,  false,  false),
   SZ("SZ", "Szeged",               Size.small, true,  false,  false,  false,  false),
   TO("TO", "Toulouse",             Size.small, true,  false,  false,  false,  false),
   VA("VA", "Valona",               Size.small, true,  true,   false,  false,  false),
   VR("VR", "Varna",                Size.large, true,  true,   false,  false,  false),
   VE("VE", "Venice",               Size.small, true,  true,   false,  false,  false),
   VI("VI", "Vienna",               Size.large, true,  false,  false,  false,  false),
   ZA("ZA", "Zagreb",               Size.small, true,  false,  false,  false,  false),
   ZU("ZU", "Zurich",               Size.small, true,  false,  false,  false,  false),
   NS("NS", "North Sea",            Size.none,  false, false,  false,  false,  true),
   EC("EC", "English Channel",      Size.none,  false, false,  false,  false,  true),
   IS("IS", "Irish Sea",            Size.none,  false, false,  false,  false,  true),
   AO("AO", "Atlantic Ocean",       Size.none,  false, false,  false,  false,  true),
   BB("BB", "Bay of Biscay",        Size.none,  false, false,  false,  false,  true),
   MS("MS", "Mediterranean Sea",    Size.none,  false, false,  false,  false,  true),
   TS("TS", "Tyrrhenian Sea",       Size.none,  false, false,  false,  false,  true),
   IO("IO", "Ionian Sea",           Size.none,  false, false,  false,  false,  true),
   AS("AS", "Adriatic Sea",         Size.none,  false, false,  false,  false,  true),
   BS("BS", "Black Sea",            Size.none,  false, false,  false,  false,  true);

   private Location(String s, String loc, Size size,
                    boolean isCity, boolean isPort,
                    boolean isHospital, boolean isCastleDracula, boolean isSea) {
      this.s = s;
      this.loc = loc;
      this.size = size;
      this.isCity = isCity;
      this.isPort = isPort;
      this.isHospital = isHospital;
      this.isCastleDracula = isCastleDracula;
      this.isSea = isSea;
   }

   private enum Size {
      small, large, none;
   };

   private String s;
   private String loc;
   private Size size;
   private boolean isCity;
   private boolean isPort;
   private boolean isHospital;
   private boolean isCastleDracula;
   private boolean isSea;
   private List<Location> adjacentCities;
   private List<Location> seaAdjacentCities;

   public static Location get(String s) {
      if (s.equals("JM")) {
        return Location.JM;
      } else if (s.equals("CD")) {
         return Location.CD;
      } else if (s.equals("AL")) {
         return Location.AL;
      } else if (s.equals("AM")) {
         return Location.AM;
      } else if (s.equals("AT")) {
         return Location.AT;
      } else if (s.equals("BA")) {
         return Location.BA;
      } else if (s.equals("BI")) {
         return Location.BI;
      } else if (s.equals("BE")) {
         return Location.BE;
      } else if (s.equals("BR")) {
         return Location.BR;
      } else if (s.equals("BO")) {
         return Location.BO;
      } else if (s.equals("BU")) {
         return Location.BU;
      } else if (s.equals("BC")) {
         return Location.BC;
      } else if (s.equals("BD")) {
         return Location.BD;
      } else if (s.equals("CA")) {
         return Location.CA;
      } else if (s.equals("CG")) {
         return Location.CG;
      } else if (s.equals("CF")) {
         return Location.CF;
      } else if (s.equals("CO")) {
         return Location.CO;
      } else if (s.equals("CN")) {
         return Location.CN;
      } else if (s.equals("DU")) {
         return Location.DU;
      } else if (s.equals("ED")) {
         return Location.ED;
      } else if (s.equals("FL")) {
         return Location.FL;
      } else if (s.equals("FR")) {
         return Location.FR;
      } else if (s.equals("GA")) {
         return Location.GA;
      } else if (s.equals("GW")) {
         return Location.GW;
      } else if (s.equals("GE")) {
         return Location.GE;
      } else if (s.equals("GO")) {
         return Location.GO;
      } else if (s.equals("GR")) {
         return Location.GR;
      } else if (s.equals("HA")) {
         return Location.HA;
      } else if (s.equals("KL")) {
         return Location.KL;
      } else if (s.equals("LE")) {
         return Location.LE;
      } else if (s.equals("LI")) {
         return Location.LI;
      } else if (s.equals("LS")) {
         return Location.LS;
      } else if (s.equals("LV")) {
         return Location.LV;
      } else if (s.equals("LO")) {
         return Location.LO;
      } else if (s.equals("MA")) {
         return Location.MA;
      } else if (s.equals("MN")) {
         return Location.MN;
      } else if (s.equals("MR")) {
         return Location.MR;
      } else if (s.equals("MI")) {
         return Location.MI;
      } else if (s.equals("MU")) {
         return Location.MU;
      } else if (s.equals("NA")) {
         return Location.NA;
      } else if (s.equals("NP")) {
         return Location.NP;
      } else if (s.equals("NU")) {
         return Location.NU;
      } else if (s.equals("PA")) {
         return Location.PA;
      } else if (s.equals("PL")) {
         return Location.PL;
      } else if (s.equals("PR")) {
         return Location.PR;
      } else if (s.equals("RO")) {
         return Location.RO;
      } else if (s.equals("SA")) {
         return Location.SA;
      } else if (s.equals("SN")) {
         return Location.SN;
      } else if (s.equals("SR")) {
         return Location.SR;
      } else if (s.equals("SJ")) {
         return Location.SJ;
      } else if (s.equals("SO")) {
         return Location.SO;
      } else if (s.equals("ST")) {
         return Location.ST;
      } else if (s.equals("SW")) {
         return Location.SW;
      } else if (s.equals("SZ")) {
         return Location.SZ;
      } else if (s.equals("TO")) {
         return Location.TO;
      } else if (s.equals("VA")) {
         return Location.VA;
      } else if (s.equals("VR")) {
         return Location.VR;
      } else if (s.equals("VE")) {
         return Location.VE;
      } else if (s.equals("VI")) {
         return Location.VI;
      } else if (s.equals("ZA")) {
         return Location.ZA;
      } else if (s.equals("ZU")) {
         return Location.ZU;
      } else if (s.equals("NS")) {
         return Location.NS;
      } else if (s.equals("EC")) {
         return Location.EC;
      } else if (s.equals("IS")) {
         return Location.IS;
      } else if (s.equals("AO")) {
         return Location.AO;
      } else if (s.equals("BB")) {
         return Location.BB;
      } else if (s.equals("MS")) {
         return Location.MS;
      } else if (s.equals("TS")) {
         return Location.TS;
      } else if (s.equals("IO")) {
         return Location.IO;
      } else if (s.equals("AS")) {
         return Location.AS;
      } else if (s.equals("BS")) {
         return Location.BS;
      } else {
         throw new AssertionError("Not a real location");
      }
   }

   public String toString() {
      return s;
   }

   public boolean isSea() {
      return isSea;
   }

   public boolean isCity() {
      return !isSea();
   }

   public List<Location> adjacentCities() {
      if (this.adjacentCities != null) return this.adjacentCities;
      List<Location> l = new ArrayList<Location>();
      if (this.isSea()) {
         if (s.equals("MS")) l.add(get("AL")); // type:"sea";
         if (s.equals("NS")) l.add(get("AM")); // type:"sea";
         if (s.equals("IO")) l.add(get("AT")); // type:"sea";
         if (s.equals("MS")) l.add(get("BA")); // type:"sea";
         if (s.equals("AS")) l.add(get("BI")); // type:"sea";
         if (s.equals("BB")) l.add(get("BO")); // type:"sea";
         if (s.equals("AO")) l.add(get("CA")); // type:"sea";
         if (s.equals("MS")) l.add(get("CG")); // type:"sea";
         if (s.equals("TS")) l.add(get("CG")); // type:"sea";
         if (s.equals("BS")) l.add(get("CN")); // type:"sea";
         if (s.equals("IS")) l.add(get("DU")); // type:"sea";
         if (s.equals("NS")) l.add(get("ED")); // type:"sea";
         if (s.equals("AO")) l.add(get("GW")); // type:"sea";
         if (s.equals("TS")) l.add(get("GO")); // type:"sea";
         if (s.equals("NS")) l.add(get("HA")); // type:"sea";
         if (s.equals("EC")) l.add(get("LE")); // type:"sea";
         if (s.equals("AO")) l.add(get("LS")); // type:"sea";
         if (s.equals("IS")) l.add(get("LV")); // type:"sea";
         if (s.equals("EC")) l.add(get("LO")); // type:"sea";
         if (s.equals("MS")) l.add(get("MR")); // type:"sea";
         if (s.equals("BB")) l.add(get("NA")); // type:"sea";
         if (s.equals("TS")) l.add(get("NP")); // type:"sea";
         if (s.equals("EC")) l.add(get("PL")); // type:"sea";
         if (s.equals("TS")) l.add(get("RO")); // type:"sea";
         if (s.equals("IO")) l.add(get("SA")); // type:"sea";
         if (s.equals("BB")) l.add(get("SN")); // type:"sea";
         if (s.equals("IS")) l.add(get("SW")); // type:"sea";
         if (s.equals("IO")) l.add(get("VA")); // type:"sea";
         if (s.equals("BS")) l.add(get("VR")); // type:"sea";
         if (s.equals("AS")) l.add(get("VE")); // type:"sea";

         if (s.equals("EC")) l.add(get("NS")); // type:"sea";
         if (s.equals("AO")) l.add(get("NS")); // type:"sea";
         if (s.equals("AO")) l.add(get("EC")); // type:"sea";
         if (s.equals("AO")) l.add(get("IS")); // type:"sea";
         if (s.equals("BB")) l.add(get("AO")); // type:"sea";
         if (s.equals("MS")) l.add(get("AO")); // type:"sea";
         if (s.equals("TS")) l.add(get("MS")); // type:"sea";
         if (s.equals("IO")) l.add(get("TS")); // type:"sea";
         if (s.equals("AS")) l.add(get("IO")); // type:"sea";
         if (s.equals("BS")) l.add(get("IO")); // type:"sea" }
      } else {
         if (s.equals("AL")) l.add(get("GR")); //type:"road";
         if (s.equals("AL")) l.add(get("MA")); //type:"road";
         if (s.equals("AL")) l.add(get("SR")); //type:"road";
         if (s.equals("AM")) l.add(get("BU")); //type:"road";
         if (s.equals("AM")) l.add(get("CO")); //type:"road";
         if (s.equals("AT")) l.add(get("VA")); //type:"road";

         if (s.equals("BA")) l.add(get("SR")); //type:"road";
         if (s.equals("BA")) l.add(get("TO")); //type:"road";
         if (s.equals("BI")) l.add(get("NP")); //type:"road";
         if (s.equals("BI")) l.add(get("RO")); //type:"road";
         if (s.equals("BE")) l.add(get("BC")); //type:"road";
         if (s.equals("BE")) l.add(get("JM")); //type:"road";
         if (s.equals("BE")) l.add(get("KL")); //type:"road";
         if (s.equals("BE")) l.add(get("SJ")); //type:"road";
         if (s.equals("BE")) l.add(get("SO")); //type:"road";
         if (s.equals("BE")) l.add(get("SZ")); //type:"road";
         if (s.equals("BR")) l.add(get("HA")); //type:"road";
         if (s.equals("BR")) l.add(get("LI")); //type:"road";
         if (s.equals("BR")) l.add(get("PR")); //type:"road";

         if (s.equals("BO")) l.add(get("CF")); //type:"road";
         if (s.equals("BO")) l.add(get("NA")); //type:"road";
         if (s.equals("BO")) l.add(get("SR")); //type:"road";
         if (s.equals("BO")) l.add(get("TO")); //type:"road";
         if (s.equals("BU")) l.add(get("CO")); //type:"road";
         if (s.equals("BU")) l.add(get("LE")); //type:"road";
         if (s.equals("BU")) l.add(get("PA")); //type:"road";
         if (s.equals("BU")) l.add(get("ST")); //type:"road";
         if (s.equals("BC")) l.add(get("CN")); //type:"road";
         if (s.equals("BC")) l.add(get("GA")); //type:"road";
         if (s.equals("BC")) l.add(get("KL")); //type:"road";
         if (s.equals("BC")) l.add(get("SO")); //type:"road";
         if (s.equals("BD")) l.add(get("KL")); //type:"road";
         if (s.equals("BD")) l.add(get("SZ")); //type:"road";
         if (s.equals("BD")) l.add(get("VI")); //type:"road";
         if (s.equals("BD")) l.add(get("ZA")); //type:"road";

         if (s.equals("CA")) l.add(get("GR")); //type:"road";
         if (s.equals("CA")) l.add(get("LS")); //type:"road";
         if (s.equals("CA")) l.add(get("MA")); //type:"road";
         if (s.equals("CD")) l.add(get("GA")); //type:"road";
         if (s.equals("CD")) l.add(get("KL")); //type:"road";
         if (s.equals("CF")) l.add(get("GE")); //type:"road";
         if (s.equals("CF")) l.add(get("MR")); //type:"road";
         if (s.equals("CF")) l.add(get("NA")); //type:"road";
         if (s.equals("CF")) l.add(get("PA")); //type:"road";
         if (s.equals("CF")) l.add(get("TO")); //type:"road";
         if (s.equals("CO")) l.add(get("FR")); //type:"road";
         if (s.equals("CO")) l.add(get("HA")); //type:"road";
         if (s.equals("CO")) l.add(get("LI")); //type:"road";
         if (s.equals("CO")) l.add(get("ST")); //type:"road";
         if (s.equals("CN")) l.add(get("GA")); //type:"road";
         if (s.equals("CN")) l.add(get("VR")); //type:"road";

         if (s.equals("DU")) l.add(get("GW")); //type:"road";

         if (s.equals("ED")) l.add(get("MN")); //type:"road";

         if (s.equals("FL")) l.add(get("GO")); //type:"road";
         if (s.equals("FL")) l.add(get("RO")); //type:"road";
         if (s.equals("FL")) l.add(get("VE")); //type:"road";
         if (s.equals("FR")) l.add(get("LI")); //type:"road";
         if (s.equals("FR")) l.add(get("NU")); //type:"road";
         if (s.equals("FR")) l.add(get("ST")); //type:"road";

         if (s.equals("GA")) l.add(get("KL")); //type:"road";
         if (s.equals("GE")) l.add(get("MR")); //type:"road";
         if (s.equals("GE")) l.add(get("PA")); //type:"road";
         if (s.equals("GE")) l.add(get("ST")); //type:"road";
         if (s.equals("GE")) l.add(get("ZU")); //type:"road";
         if (s.equals("GO")) l.add(get("MR")); //type:"road";
         if (s.equals("GO")) l.add(get("MI")); //type:"road";
         if (s.equals("GO")) l.add(get("VE")); //type:"road";
         if (s.equals("GR")) l.add(get("MA")); //type:"road";

         if (s.equals("HA")) l.add(get("LI")); //type:"road";

         if (s.equals("JM")) l.add(get("SJ")); //type:"road";
         if (s.equals("JM")) l.add(get("SZ")); //type:"road";
         if (s.equals("JM")) l.add(get("ZA")); //type:"road";

         if (s.equals("KL")) l.add(get("SZ")); //type:"road";

         if (s.equals("LE")) l.add(get("NA")); //type:"road";
         if (s.equals("LE")) l.add(get("PA")); //type:"road";
         if (s.equals("LI")) l.add(get("NU")); //type:"road";
         if (s.equals("LS")) l.add(get("MA")); //type:"road";
         if (s.equals("LS")) l.add(get("SN")); //type:"road";
         if (s.equals("LV")) l.add(get("MN")); //type:"road";
         if (s.equals("LV")) l.add(get("SW")); //type:"road";
         if (s.equals("LO")) l.add(get("MN")); //type:"road";
         if (s.equals("LO")) l.add(get("PL")); //type:"road";
         if (s.equals("LO")) l.add(get("SW")); //type:"road";

         if (s.equals("MA")) l.add(get("SN")); //type:"road";
         if (s.equals("MA")) l.add(get("SR")); //type:"road";
         if (s.equals("MR")) l.add(get("MI")); //type:"road";
         if (s.equals("MR")) l.add(get("TO")); //type:"road";
         if (s.equals("MR")) l.add(get("ZU")); //type:"road";
         if (s.equals("MI")) l.add(get("MU")); //type:"road";
         if (s.equals("MI")) l.add(get("VE")); //type:"road";
         if (s.equals("MI")) l.add(get("ZU")); //type:"road";
         if (s.equals("MU")) l.add(get("NU")); //type:"road";
         if (s.equals("MU")) l.add(get("ST")); //type:"road";
         if (s.equals("MU")) l.add(get("VE")); //type:"road";
         if (s.equals("MU")) l.add(get("VI")); //type:"road";
         if (s.equals("MU")) l.add(get("ZA")); //type:"road";
         if (s.equals("MU")) l.add(get("ZU")); //type:"road";

         if (s.equals("NA")) l.add(get("PA")); //type:"road";
         if (s.equals("NP")) l.add(get("RO")); //type:"road";
         if (s.equals("NU")) l.add(get("PR")); //type:"road";
         if (s.equals("NU")) l.add(get("ST")); //type:"road";

         if (s.equals("PA")) l.add(get("ST")); //type:"road";
         if (s.equals("PR")) l.add(get("VI")); //type:"road";

         if (s.equals("SA")) l.add(get("SO")); //type:"road";
         if (s.equals("SA")) l.add(get("VA")); //type:"road";
         if (s.equals("SN")) l.add(get("SR")); //type:"road";
         if (s.equals("SR")) l.add(get("TO")); //type:"road";
         if (s.equals("SJ")) l.add(get("SO")); //type:"road";
         if (s.equals("SJ")) l.add(get("VA")); //type:"road";
         if (s.equals("SJ")) l.add(get("ZA")); //type:"road";
         if (s.equals("SO")) l.add(get("VR")); //type:"road";
         if (s.equals("SO")) l.add(get("VA")); //type:"road";
         if (s.equals("ST")) l.add(get("ZU")); //type:"road";
         if (s.equals("SZ")) l.add(get("ZA")); //type:"road";

         if (s.equals("VI")) l.add(get("ZA")); //type:"road";

         if (s.equals("AL")) l.add(get("BA")); //type:"rail";
         if (s.equals("AL")) l.add(get("MA")); //type:"rail";
         if (s.equals("BA")) l.add(get("SR")); //type:"rail";
         if (s.equals("BI")) l.add(get("NP")); //type:"rail";
         if (s.equals("BE")) l.add(get("SO")); //type:"rail";
         if (s.equals("BE")) l.add(get("SZ")); //type:"rail";
         if (s.equals("BR")) l.add(get("HA")); //type:"rail";
         if (s.equals("BR")) l.add(get("LI")); //type:"rail";
         if (s.equals("BR")) l.add(get("PR")); //type:"rail";
         if (s.equals("BO")) l.add(get("PA")); //type:"rail";
         if (s.equals("BO")) l.add(get("SR")); //type:"rail";
         if (s.equals("BU")) l.add(get("CO")); //type:"rail";
         if (s.equals("BU")) l.add(get("PA")); //type:"rail";
         if (s.equals("BC")) l.add(get("CN")); //type:"rail";
         if (s.equals("BC")) l.add(get("GA")); //type:"rail";
         if (s.equals("BC")) l.add(get("SZ")); //type:"rail";
         if (s.equals("BD")) l.add(get("VI")); //type:"rail";
         if (s.equals("BD")) l.add(get("SZ")); //type:"rail";
         if (s.equals("CO")) l.add(get("FR")); //type:"rail";
         if (s.equals("ED")) l.add(get("MN")); //type:"rail";
         if (s.equals("FL")) l.add(get("MI")); //type:"rail";
         if (s.equals("FL")) l.add(get("RO")); //type:"rail";
         if (s.equals("FR")) l.add(get("LI")); //type:"rail";
         if (s.equals("FR")) l.add(get("ST")); //type:"rail";
         if (s.equals("GE")) l.add(get("MI")); //type:"rail";
         if (s.equals("GO")) l.add(get("MI")); //type:"rail";
         if (s.equals("LE")) l.add(get("PA")); //type:"rail";
         if (s.equals("LI")) l.add(get("NU")); //type:"rail";
         if (s.equals("LS")) l.add(get("MA")); //type:"rail";
         if (s.equals("LV")) l.add(get("MN")); //type:"rail";
         if (s.equals("LO")) l.add(get("MN")); //type:"rail";
         if (s.equals("LO")) l.add(get("SW")); //type:"rail";
         if (s.equals("MA")) l.add(get("SN")); //type:"rail";
         if (s.equals("MA")) l.add(get("SR")); //type:"rail";
         if (s.equals("MR")) l.add(get("PA")); //type:"rail";
         if (s.equals("MI")) l.add(get("ZU")); //type:"rail";
         if (s.equals("MU")) l.add(get("NU")); //type:"rail";
         if (s.equals("NP")) l.add(get("RO")); //type:"rail";
         if (s.equals("PR")) l.add(get("VI")); //type:"rail";
         if (s.equals("SA")) l.add(get("SO")); //type:"rail";
         if (s.equals("SO")) l.add(get("VR")); //type:"rail";
         if (s.equals("ST")) l.add(get("ZU")); //type:"rail";
         if (s.equals("VE")) l.add(get("VI")); //type:"rail";
      }
      this.adjacentCities = l;
      return l ;
   }

   public List<Location> seaAdjacentCities() {
      if (this.seaAdjacentCities != null) return this.seaAdjacentCities;
      List<Location> l = new ArrayList<Location>();
      if (s.equals("AL")) l.add(get("MS")); // type:"sea";
      if (s.equals("AM")) l.add(get("NS")); // type:"sea";
      if (s.equals("AT")) l.add(get("IO")); // type:"sea";
      if (s.equals("BA")) l.add(get("MS")); // type:"sea";
      if (s.equals("BI")) l.add(get("AS")); // type:"sea";
      if (s.equals("BO")) l.add(get("BB")); // type:"sea";
      if (s.equals("CA")) l.add(get("AO")); // type:"sea";
      if (s.equals("CG")) l.add(get("MS")); // type:"sea";
      if (s.equals("CG")) l.add(get("TS")); // type:"sea";
      if (s.equals("CN")) l.add(get("BS")); // type:"sea";
      if (s.equals("DU")) l.add(get("IS")); // type:"sea";
      if (s.equals("ED")) l.add(get("NS")); // type:"sea";
      if (s.equals("GW")) l.add(get("AO")); // type:"sea";
      if (s.equals("GO")) l.add(get("TS")); // type:"sea";
      if (s.equals("HA")) l.add(get("NS")); // type:"sea";
      if (s.equals("LE")) l.add(get("EC")); // type:"sea";
      if (s.equals("LS")) l.add(get("AO")); // type:"sea";
      if (s.equals("LV")) l.add(get("IS")); // type:"sea";
      if (s.equals("LO")) l.add(get("EC")); // type:"sea";
      if (s.equals("MR")) l.add(get("MS")); // type:"sea";
      if (s.equals("NA")) l.add(get("BB")); // type:"sea";
      if (s.equals("NP")) l.add(get("TS")); // type:"sea";
      if (s.equals("PL")) l.add(get("EC")); // type:"sea";
      if (s.equals("RO")) l.add(get("TS")); // type:"sea";
      if (s.equals("SA")) l.add(get("IO")); // type:"sea";
      if (s.equals("SN")) l.add(get("BB")); // type:"sea";
      if (s.equals("SW")) l.add(get("IS")); // type:"sea";
      if (s.equals("VA")) l.add(get("IO")); // type:"sea";
      if (s.equals("VR")) l.add(get("BS")); // type:"sea";
      if (s.equals("VE")) l.add(get("AS")); // type:"sea";

      if (s.equals("NS")) l.add(get("EC")); // type:"sea";
      if (s.equals("NS")) l.add(get("AO")); // type:"sea";
      if (s.equals("EC")) l.add(get("AO")); // type:"sea";
      if (s.equals("IS")) l.add(get("AO")); // type:"sea";
      if (s.equals("AO")) l.add(get("BB")); // type:"sea";
      if (s.equals("AO")) l.add(get("MS")); // type:"sea";
      if (s.equals("MS")) l.add(get("TS")); // type:"sea";
      if (s.equals("TS")) l.add(get("IO")); // type:"sea";
      if (s.equals("IO")) l.add(get("AS")); // type:"sea";
      if (s.equals("IO")) l.add(get("BS")); // type:"sea" }
      this.seaAdjacentCities = l;
      return l;
   }
}