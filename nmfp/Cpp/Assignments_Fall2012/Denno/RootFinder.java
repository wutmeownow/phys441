import java.util.Scanner;
import java.text.*;

public class RootFinder {
	DecimalFormat df=new DecimalFormat("#.####");
	static void Newton(double a, double b, double c, double d){
		double f,df,x_old,x_new=0,accu,diff;
		Scanner scan=new Scanner(System.in);
		System.out.print("Initial Guess? ");
		x_old=scan.nextDouble();
		System.out.print("Accuracy? ");
		accu=scan.nextDouble();
		diff=accu+1;
		while(diff>accu){
			f=(a*x_old*x_old*x_old)+(b*x_old*x_old)+(c*x_old)+d;
			df=(3*a*x_old*x_old)+(2*b*x_old)+c;
			x_new=x_old-(f/df);
			diff=x_old-x_new;
			diff=Math.abs(diff);
			System.out.println("New x: "+x_new+" Difference: "+diff);
			x_old=x_new;
		}
		System.out.println("Root of given function is "+x_new);
	}
	
	public static void main(String[] args) {
		double a=1; double b=-9.42478;double c=29.6088; double d=-31.00628;
		System.out.println("x^3+("+b+")x^2+("+c+")x+"+d);
		Newton(a,b,c,d);
	}

}
