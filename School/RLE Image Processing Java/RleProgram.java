import java.util.Arrays;
import java.util.Scanner;

public class RleProgram {
    public static String toHexString(byte[] data){
        String output = ""; //creates empty string
        for (int i=0; i<data.length; i++){ //loops thru each value in data array
            String str = Integer.toHexString(data[i]); //converts to hex string
            output += str; //appends to output
        }
        //System.out.print(output);
        return output;
    }
    public static int countRuns(byte[] flatData) {
        byte groups = 1;
        byte noInRow = 1;
        for (int i = 0; i < flatData.length - 1; i++) {
            if (flatData[i] != flatData[i + 1]) { //add to groups if the next value is not equal to the preceding
                groups++;
            } else if (flatData[i] == flatData[i + 1]) { // if same value, add to no of consecutive digits
                noInRow++;
                if (noInRow >= 15) { //if more than 15 consecutive digits, need new group
                    groups++;
                    noInRow = 1;
                }

            }
        }
        //System.out.println(groups);
        return groups;
    }

    public static byte[] encodeRle(byte[] flatData){
        int posInEncoded = 0;
        byte noInGroup = 1;
        int i;
        byte [] encodedRle = new byte[countRuns(flatData)*2]; //creates empty array twice length of groups
        for (i = 0; i < (flatData.length-1); i++){
            if (flatData[i] == flatData[i+1]&& noInGroup<15) { //noInGroup goes up if next value is same as preceding and less than 15 in a row
                noInGroup += 1;
            } else {
                encodedRle[posInEncoded++] = noInGroup; //once the group ends, add noInGroup to array
                //posInEncoded++;
                encodedRle[posInEncoded++] = flatData[i]; //add the last value itself to the array;
                noInGroup = 1;
            }
        }
        encodedRle[posInEncoded++] = noInGroup; //this is for when the for loop has ended, last values must be added
        encodedRle[posInEncoded] = flatData[i];
        //System.out.println(Arrays.toString(encodedRle));

        return encodedRle;
    }

    public static int getDecodedLength(byte[] rleData) { //basically adds the values of indexes starting from 0 and going up by 2
        int sum = 0;
        for (int i = 0; i <= (rleData.length); i++) {
            if (i >= rleData.length / 2) {
                break;
            }
            byte number = rleData[2 * i];
            sum += number;
        }
        //System.out.print(sum);
        return sum;
    }
    public static byte[] decodeRle (byte[] rleData){
        byte [] decodedRle = new byte [RleProgram.getDecodedLength(rleData)]; //create array with length equal to returned value from getLength method
        int index = 0;
        for (int i = 0; i< rleData.length -1; i+=2){
            for (int j = 0; j < rleData[i]; j++){
                decodedRle[index] = rleData[i+1];
                index++;
            }
        }
        //System.out.print(Arrays.toString(decodedRle));
        return decodedRle;
    }
    public static byte [] stringToData(String dataString){
        int length = dataString.length();
        int intnumber;
        byte [] rleByte = new byte [length];
        char referenceChar;
        String referenceString;
        for (int i=0; i<length;i++){
            referenceChar = dataString.charAt(i);
            referenceString = Character.toString(referenceChar);
            intnumber = Integer.parseInt(referenceString,16); //converts hex String to number
            rleByte[i] = (byte) intnumber; //adds hex value to the rleByte array
        }
        //System.out.print(Arrays.toString(rleByte));
        return rleByte;
    }
    public static String toRleString(byte[]rleData){
        String rleString = "";
        int runLength1;
        int runLength2;

        for (int i = 0; i<rleData.length-1; i+=2){
            if (rleData[i] >= 10){ //when the first number has more than 1 character
                runLength1 = rleData[i]/10;  //first character is quotient when divided by 10
                runLength2 = rleData[i]%10; // second is remainder
                rleString += Character.forDigit(runLength1, 10);
                rleString += Character.forDigit(runLength2, 10);
                int hexValue = rleData[i + 1];
                rleString += Integer.toHexString(hexValue); //coverts to hex value and adds to string
            } else { //when the first number has only one character
                runLength1 = rleData[i];
                rleString += Character.forDigit(runLength1, 10);
                int hexValue = (int) rleData[i + 1];
                rleString += Integer.toHexString(hexValue);
            }
            if (i<rleData.length-2){  //as long as we are not at the end of the array, keep adding colons after each grouping
                rleString+=":";
            }
        }
        //System.out.println(rleString);
        return rleString;
    }
    public static byte[]stringToRle(String rleString){
        String [] colonSplit = rleString.split(":", -1); //splits string into array at each colon
        byte [] rleArray = new byte [colonSplit.length * 2];
        int length;
        byte hexByte;

        int i;
        int j = 0;
        for (i = 0; i< colonSplit.length; i++){
            length = colonSplit[i].length();
            String noOfRepeats = colonSplit[i].substring(0, length-1); //grabs the last value of every index in colonString
            char hexChar = colonSplit[i].charAt(length-1); //grabs remaining values

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
                hexByte = (byte) Character.getNumericValue(hexChar); //gives value for numeric characters
            }


            rleArray[j] = (byte) Integer.parseInt(noOfRepeats);
            rleArray[j+=1] = hexByte;
            j++;

        }
        //System.out.println(Arrays.toString(rleArray));
        return rleArray;

    }


    public static void main (String[] args){
        Scanner scn = new Scanner(System.in);
        String fileToLoad = "";
        boolean run = true;
        byte[] dataEncoded = new byte [100];
        byte[] dataDecoded = new byte [100];
        boolean badData = true;
        String outputString = "";

        //1. Display welcome message
        System.out.println("Welcome to the RLE image encoder!");

        //2. Display color test with the message
        System.out.println("Displaying Spectrum Image: ");
        ConsoleGfx.displayImage(ConsoleGfx.testRainbow);

        while(run) {
            //3. Display the menu = Part A: while loop or if-else chains
            System.out.println("RLE Menu");
            System.out.println("--------");
            System.out.println("0. Exit");
            System.out.println("1. Load File");
            System.out.println("2. Load Test Image");
            System.out.println("3. Read RLE String");
            System.out.println("4. Read RLE Hex String");
            System.out.println("5. Read Data Hex String");
            System.out.println("6. Display Image");
            System.out.println("7. Display RLE String");
            System.out.println("8. Display Hex RLE Data");
            System.out.println("9. Display Hex Flat Data");
            System.out.println("");
            System.out.print("Select a Menu Option: ");
            int userChoice = scn.nextInt();
            //System.out.println();
            if (userChoice == 1) {
                System.out.print("Enter name of file to load: ");
                fileToLoad = scn.next();
                dataDecoded = ConsoleGfx.loadFile(fileToLoad);
                badData = false;
            } else if (userChoice == 2) {
                System.out.println("Test image data loaded.");
                dataDecoded = ConsoleGfx.testImage;
                badData = false;
                //ConsoleGfx.loadFile(fileToLoad);
            }
            else if (userChoice == 3) {
                System.out.println("Enter an RLE string to be decoded:");
                String toDecode = scn.next();
                dataEncoded = stringToRle(toDecode);
                dataDecoded = decodeRle(dataEncoded);
                badData = false;

            } else if (userChoice == 4) {
                System.out.println("Enter the hex string holding RLE data: ");
                String hexStringHolding = scn.next();
                dataDecoded = stringToData(hexStringHolding);
                badData = false;
            } else if (userChoice == 5) {
                System.out.println("Enter the hex string holding flat data: ");
                String enteredString = scn.next();
                dataDecoded = stringToData(enteredString);
                dataEncoded = encodeRle(dataDecoded);
                badData = false;
            } else if (userChoice == 6) {
                if (badData){
                    System.out.println("(no data)");
                } else {
                        System.out.println("Displaying image...");
                        ConsoleGfx.displayImage(dataDecoded);
                }

            } else if (userChoice == 7) {
                if (badData){
                    System.out.println("(no data)");
                }
                dataEncoded = encodeRle(dataDecoded);
                outputString = toRleString(dataEncoded);
                System.out.println("RLE representation: " + outputString);
            } else if (userChoice == 8){
                if (badData){
                    System.out.println("(no data)");
                }
                dataEncoded = encodeRle(dataDecoded);
                outputString = toHexString(dataEncoded);
                System.out.println("RLE hex values: " + outputString);
            } else if (userChoice == 9){
                if (badData){
                    System.out.println("(no data)");
                }
                outputString = toHexString(dataDecoded);
                System.out.println("Flat hex values: " + outputString);

            } else if (userChoice == 0){
                run = false;
                break;
            } else {
                System.out.println("Error! Invalid input.");
            }



        }
    }
}
