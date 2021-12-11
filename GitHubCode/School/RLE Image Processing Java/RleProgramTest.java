import java.util.Arrays;

public class RleProgramTest {
    public static void main(String[] args) {
        byte[] data = {3, 15, 6, 4};
        byte[] flatData = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        byte[] rleData = {15, 15, 6, 4, 4, 13};
        String dataString = "13f";
        //stringToRle("12a:102:6f");

    }


}


/*
int length = colonSplit[i].length();
            for (j = 0; j < length-1; j++){
            if (length > 2){
                String repeatSubstring = colonSplit[i].substring(0,2);
                noOfRepeats = (byte) Integer.parseInt(repeatSubstring);
                rleArray[j] = noOfRepeats;
                j+=2;
            } else if (colonSplit[i].length() == 2){
                String repeatSubstring = colonSplit[i].substring(0,1);
                System.out.println(repeatSubstring);
                noOfRepeats = (byte) Integer.parseInt(repeatSubstring);
                rleArray[j] = noOfRepeats;
                j+=1;
                length2 = false;
            }
            }

            String hex = colonSplit[i].substring(j, j+1);
            char hexChar = colonSplit[i].charAt(j);
        if (hexChar == 'A' || hexChar == 'a') { //gives decimal value for non-numeric characters
            hexByte = 10;
        } else if (hexChar == 'B' || hexChar == 'b') {
            hexByte = 11;
        } else if (hexChar == 'C' || hexChar == 'c') {
            hexByte = 12;
        } else if (hexChar == 'D' || hexChar == 'd') {
            hexByte = 13;
        } else if (hexChar == 'E' || hexChar == 'e') {
            hexByte = 14;
        } else if (hexChar == 'F' || hexChar == 'f') {
            hexByte = 15;
        } else {
            hexByte = (byte) Integer.parseInt(hex); //gives value for numeric characters
        }
            if (length2){
                rleArray[j-1] = hexByte;
        } else {
                rleArray[j] = hexByte;
            }
 */