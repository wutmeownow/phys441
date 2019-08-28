import org.math.plot.*;
import java.util.Scanner;
import javax.swing.JFrame;

public class ProjectileMotion {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		
		System.out.println("Enter the angle (degrees):");
		double angle = input.nextDouble();
		
		System.out.println("Enter the initial height:");
		double y_initial = input.nextDouble();
		double x_initial = 0;
		
		System.out.println("Enter the initial velocity:");
		double v_initial = input.nextDouble();
		double g = -9.8;
		double t = 0;
		double y_pos[] = new double [1000];
		double x_pos[] = new double [1000];
		double vx = v_initial * Math.cos(angle * (Math.PI / 180));
		double vy = v_initial * Math.sin(angle * (Math.PI / 180));
		double x_pos_air[] = new double[1000];
		double y_pos_air[] = new double[1000];
		double rho = 1.2; //density of air
		double dc = 0.35; //drag coefficient;
		double mass = 1;
		double area = 1;
		double resist = -0.5 * dc * rho * (area/mass);
		
		//no air resistance
		for(int i = 0; i < 1000; i++){
			y_pos[i] = y_initial + vy * t + 0.5 * g * t * t;
			x_pos[i] = x_initial + vx * t;
			if (y_pos[i] < 0){
				break;
			}
			t += 0.1;
		}
		t = 0;
		
		
		//with air resistance\
		double vx_air[] = new double[1000];
		double vy_air[] = new double[1000];
		for(int i = 0; i < 1000; i++){
			vx_air[i] = vx + resist * t;
			vy_air[i] = vy + resist * t + g * t;
			t += 0.1;
		}
		t = 0;
		
		
		for(int i = 0; i < 1000; i++){
			
			y_pos_air[i] = y_initial + vy_air[i] * t;
			x_pos_air[i] = vx_air[i] * t;
			if(y_pos_air[i] < 0){
				break;
			}
			t += 0.1;
		}
		
		
		Plot2DPanel plot = new Plot2DPanel();
		plot.addScatterPlot("X vs Y", x_pos, y_pos);
		plot.addScatterPlot("X vs Y (With Air Resistance)", x_pos_air, y_pos_air);
		
		JFrame frame = new JFrame("X vs Y");
		frame.setSize(600,600);
		frame.setContentPane(plot);
		frame.setVisible(true);
		
	}
}