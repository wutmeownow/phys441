
public class NewtonMethodRoot {
	
	public static void main(String[] args){
		int n=0;
		double root = 0;
		double x = -3;
		double xPlusOne;
		
		while(n<5){
			xPlusOne= x - ((Math.pow(x, 3) - 9.42478*Math.pow(x, 2) - 29.60881*x +31.00628)/(3*Math.pow(x, 2) - 18.84956*x - 29.60881));
			root = xPlusOne;
			x = xPlusOne;
			n++;
		}
		System.out.println(root);
		
	}

}
