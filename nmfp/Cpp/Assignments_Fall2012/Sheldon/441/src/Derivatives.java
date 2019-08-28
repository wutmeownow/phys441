import org.math.plot.*;

import javax.swing.JFrame;
public class Derivatives {

	public static double f(double exp){
		return (Math.pow(exp, 2));
	}
	
	public static double f_prime(double exp){
		return (2 * exp);
	}
	public static void main(String[] args){
		double x = 1;
		double h[] = new double[1000];
		double deltah[] = new double[1000];
		
		for(int i = 0; i < 1000; i++){
			h[i] = Math.pow(10, (-20 + (0.02 * i)));
		}
		for(int i = 0; i < 1000; i++){
			deltah[i] = f_prime(x) - (f(x + h[i]) - f(x)) / h[i] ;
		}
		
		Plot2DPanel plot = new Plot2DPanel();
		plot.addScatterPlot("My Plot", deltah, h);
		
		JFrame frame = new JFrame("Test");
		frame.setSize(600,600);
		frame.setContentPane(plot);
		frame.setVisible(true);
	}
}
