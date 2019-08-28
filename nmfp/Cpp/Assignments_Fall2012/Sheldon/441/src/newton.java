//import java.util.Scanner;
import java.lang.Math;
public class newton {
	public static double f(double x_in){
		double result = (Math.pow(x_in, 3)) - ((9.42478) * Math.pow(x_in, 2)) + ((29.60881) * x_in) - 31.00628;
		return result;
		
	}
	public static double f_prime(double x_in){
		double result = (3 * Math.pow(x_in, 2)) - ((2 * 9.42478) * x_in) + 29.60881;
		return result;
	}
	public static void main(String[] args){
		double[] x = new double[50];
		x[0] = 2;
		//System.out.println(newton.f(x[0]));
		//System.out.println(newton.f_prime(x[0]));
		x[1] = (x[0] - newton.f(x[0])/newton.f_prime(x[0]));
		//System.out.println(x_new);
		int count = 1;
		while(Math.abs(x[count] - x[count - 1]) > 0.0001 && count + 1 < 50){
			x[count + 1] = (x[count] - newton.f(x[count])/newton.f_prime(x[count]));
			//System.out.println(x[count]);
			count++;
		}
		System.out.println(x[count]);
	}
}
