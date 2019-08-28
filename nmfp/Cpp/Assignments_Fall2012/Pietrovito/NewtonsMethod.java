
public class NewtonsMethod {
	public static void main(String[] args) {
		
		double x = 0.8;
		double f;
		double fPrime;
		
		for(int i=0; i<10; i++) {
			f = x*x*x - 9.42478*x*x - 29.60881*x + 31.00628;
			fPrime = 3*x*x - 18.84956*x - 29.60881;
			x = x-(f/fPrime);
			System.out.println(x);
		}
	}
}
