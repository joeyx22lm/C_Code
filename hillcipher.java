/* hillcipher CLI Java Console Application 
*  @author Joseph Orlando
*  @creation 2/22/2015
*/
import java.io.*;
import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.nio.charset.Charset;
import java.nio.file.Paths;
import java.nio.file.Files;
public class hillcipher
{
   public static Map<String, Integer> Alpha;
   public static int modval(int x, int y){
      return (x % y);
   }
   private static String[] splitByNumber(String s, int chunkSize){
      String[] SplitString = s.split("(?<=\\G.{" + chunkSize + "})");
      int lasti = (SplitString.length - 1);
      while(SplitString[lasti].length() < chunkSize){
         // plaintext padding
         SplitString[lasti] = (SplitString[lasti] + "X");
      }
      return SplitString;
   }
   private static String readAll(String path, Charset encoding){
      try {
         byte[] encoded = Files.readAllBytes(Paths.get(path));
         return new String(encoded, encoding);
      } catch(Exception e) {
         System.out.println(e.getMessage());
         return null;
      }
   }
   private static String[] readLine(String filename) {
       try {
            FileReader fileReader = new FileReader(filename);      
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            List<String> lines = new ArrayList<String>();
            String line = null;
            while ((line = bufferedReader.readLine()) != null) {
                lines.add(line);
            }
            bufferedReader.close();
            // return string array
            return lines.toArray(new String[lines.size()]);
        } catch(Exception e) {
            // output exception message
            System.out.println(e.getMessage());
           return null;
        }
     
   }
   public static void main(String [] args)
   {
      // build alphabet map
      Alpha = new HashMap<String, Integer>();
      String[] Alphabet =  {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
      for(int i = 0;i<Alphabet.length;i++){
         Alpha.put(Alphabet[i], i);
      }
      // declare output string
      String Output = new String();
      // begin reading keyfile
      String[] keyLines = readLine(args[0]);
      if(keyLines == null){
         // printed exception, now die
         System.exit(0);
      }else{
         // returned key data
         int n = Integer.parseInt(keyLines[0]);
         int keyTable[][] = new int[n][n];
         System.out.printf("Key Table:\n    ");
         for(int row = 1;row<keyLines.length;row++){
            String[] columns = keyLines[row].split(" ");
            for(int col = 0;col<columns.length;col++){
               try {
                  keyTable[(row-1)][col] = Integer.parseInt(columns[col]);
                  System.out.printf(keyTable[(row-1)][col] + " ");
               } catch (Exception e){
                  // exception occurred
               }
            }
            System.out.printf("\n    ");
         }
         System.out.println("");
         // begin reading source content
         String source = readAll(args[1], Charset.defaultCharset()).replaceAll("[^A-Za-z]", "").toUpperCase();
         // output source
         System.out.printf("Plaintext:\n" + source.replaceAll("(.{80})", "$1\n").toLowerCase() + "\n\nCiphertext:\n");
         String[] sourceSplit = splitByNumber(source, n);
         for(int sets = 0;sets<sourceSplit.length;sets++){
            // interate through every nth characters
            int[] setMatrix = new int[n];
            for(int charc = 0;charc<n;charc++){
               // iterate through every char within every nth characters
               String currentset = sourceSplit[sets];
               if(currentset.length() != n){
                  continue;
               }
               char currentchar = currentset.charAt(charc);
               String checkchar = Character.toString(currentchar);
               for (Map.Entry<String, Integer> chark : Alpha.entrySet()){
                  // iterate through alphabet to match to char
                  if(chark.getKey().equals(checkchar)){
                     // match found, add mod 26 int value of char to matrix
                     setMatrix[charc] = chark.getValue();
                  }
               }
               
            }
            // matrix for this set of nth numbers has been built
            // apply against key matrix
            // create output matrix for this set
            Map<Integer, Integer> outputMatrix = new HashMap<Integer, Integer>();
            for(int keyrow = 0;keyrow<n;keyrow++){
               // iterate each row of keyTable
               int rowval = 0;
               for(int keycol = 0;keycol<n;keycol++){
                  // iterate each col of keyTable
                  int iteratehash = (keyTable[keyrow][keycol]*setMatrix[keycol]);
                  rowval = (rowval + iteratehash);
               }
               outputMatrix.put(keyrow, rowval);
            }
            for (Map.Entry<Integer, Integer> switchmod : outputMatrix.entrySet()){
               float modval = modval(switchmod.getValue(), 26);
               for (Map.Entry<String, Integer> outputalpha : Alpha.entrySet()){
                  // iterate through alphabet to match to char
                  if(outputalpha.getValue() == modval){
                     Output = (Output + outputalpha.getKey());
                  }
               }
            }
         }
      }
      System.out.printf(Output.replaceAll("(.{80})", "$1\n").toLowerCase());
   }
}
