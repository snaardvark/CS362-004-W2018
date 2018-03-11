

import junit.framework.TestCase;
import java.io.*;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest() throws IOException
   {
	   //You can use this function to implement your manual testing
	   //Code suggested by "Java A Beginner's Guid, 6th Edition" by Schildt, Herbert, 2014
	   BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String url;
	   System.out.println("Enter URLs for testing, one per line. Type 'stop' on a line by itself to quit");
	   do {
		   url = br.readLine();
		   System.out.println(urlVal.isValid(url));
	      } while(!url.equals("stop"));
	   }
	   
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   
   
   public static void main(String args[]) throws IOException
   {
	   UrlValidatorTest fct = new UrlValidatorTest("url test");
	   fct.testManualTest();
   }

}
