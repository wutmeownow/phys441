import java.util.ArrayList; 
public class NewtonsMethod {

	
	public static void main(String[] args){
		double x = 0;
		double fx = (x*x*x)-(9.42478*x*x)+(29.60881*x)-(31.00628);
		double fpx = (3*x*x)-(18.84956*x)+(29.60881);
		double i=-10.000;
		ArrayList listx = new ArrayList();
		ArrayList listy = new ArrayList();
		while(i<=10.000){
			x=i;
			listy.add((x*x*x)-(9.42478*x*x)+(29.60881*x)-(31.00628));
			listx.add(i);
			i+=.001;
		}
		double a=0, b=0;
		while(true){
			a = (Double) listy.remove(0);
			b = (Double) listy.get(0);
			x = (Double) listx.remove(0);
//			System.out.println("a="+a);
//			System.out.println("b="+b);
			if(a>0&&b<0 || a<0&&b>0){
				break;
			}
			
		}
		System.out.println("guess is: "+x);
		double h = 0;
		int n=0;
		while(true){
			n++;
			fx = (x*x*x)-(9.42478*x*x)+(29.60881*x)-(31.00628);
			fpx = (3*x*x)-(18.84956*x)+(29.60881);
			h = x-(fx/fpx);
	//		System.out.println(h+"   "+x);
			if(x==h||n==50){
				break;
			}
			else{
				x=h;
			}
			
		}
		System.out.println(x+"    "+"interations:"+n);
		
	}
	
}