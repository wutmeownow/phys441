import java.util.ArrayList;
import java.util.Scanner;


public class ProjectileMotion {
	
	public static void main(String[] args){
		double ax = 0;
		double ay = -9.81;
		double timeStep;
		Scanner scanner = new Scanner(System.in);
		System.out.println("What is the timestep?");
		timeStep = scanner.nextDouble();
		ArrayList<Double> xArray = new ArrayList<Double>();
		ArrayList<Double> yArray = new ArrayList<Double>();
		double x = 0;
		double y;
		System.out.println("What is the initial height?");
		y = scanner.nextDouble();
		xArray.add(x);
		yArray.add(y);
		double angleInRadians;
		System.out.println("What is angle in radians?");
		angleInRadians = scanner.nextDouble();
		System.out.println("What is initial speed?");
		double initialSpeed = scanner.nextDouble();
		double vx = initialSpeed*Math.cos(angleInRadians);
		double vy = initialSpeed*Math.sin(angleInRadians);
		
		while (y > 0){
			vy = vy + ay*timeStep;
			x = x + vx*timeStep + 0.5*ax*(Math.pow(timeStep, 2));
			y = y + vy*timeStep + 0.5*ay*(Math.pow(timeStep, 2));
			xArray.add(x);
			yArray.add(y);
			
			
		}
		for(int j = 0; j < xArray.size() ; j ++){
			System.out.print(xArray.get(j) + " ");
			System.out.print(yArray.get(j) + " ");
			System.out.println();
		}
		
		
		
		
	}

}
